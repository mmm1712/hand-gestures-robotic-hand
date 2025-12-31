import cv2
import mediapipe as mp
import serial
import time


SERIAL_PORT = "/dev/cu.usbserial-210" 
BAUD = 115200

ANGLE_OPEN = 30
ANGLE_CLOSED = 150
SEND_HZ = 15


mp_hands = mp.solutions.hands
mp_draw = mp.solutions.drawing_utils

THUMB_TIP = 4
THUMB_IP  = 3

INDEX_TIP = 8
INDEX_PIP = 6

MIDDLE_TIP = 12
MIDDLE_PIP = 10

RING_TIP = 16
RING_PIP = 14

PINKY_TIP = 20
PINKY_PIP = 18


def finger_open(tip, pip, lm):
    return lm[tip].y < lm[pip].y   # finger up


def thumb_open(lm):
    return lm[THUMB_TIP].x < lm[THUMB_IP].x  # works for right hand


def map_finger(is_open):
    return ANGLE_CLOSED if is_open else ANGLE_OPEN


def main():
    ser = serial.Serial(SERIAL_PORT, BAUD)
    time.sleep(2)

    cap = cv2.VideoCapture(0)
    last_send = 0

    with mp_hands.Hands(
        max_num_hands=1,
        min_detection_confidence=0.6,
        min_tracking_confidence=0.6
    ) as hands:

        while True:
            ret, frame = cap.read()
            if not ret:
                break

            frame = cv2.flip(frame, 1)
            rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            res = hands.process(rgb)

            if res.multi_hand_landmarks:
                hand = res.multi_hand_landmarks[0]
                lm = hand.landmark
                mp_draw.draw_landmarks(frame, hand, mp_hands.HAND_CONNECTIONS)

                thumb  = map_finger(thumb_open(lm))
                index  = map_finger(finger_open(INDEX_TIP, INDEX_PIP, lm))
                middle = map_finger(finger_open(MIDDLE_TIP, MIDDLE_PIP, lm))
                ring   = map_finger(finger_open(RING_TIP, RING_PIP, lm))

                # M,<middle>,<thumb>,<ring>,<index>
                cmd = f"M,{middle},{thumb},{ring},{index}\n"

                now = time.time()
                if now - last_send > 1 / SEND_HZ:
                    ser.write(cmd.encode())
                    last_send = now

            cv2.imshow("Hand Mirror Control", frame)
            if cv2.waitKey(1) & 0xFF in [27, ord('q')]:
                break

    cap.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
