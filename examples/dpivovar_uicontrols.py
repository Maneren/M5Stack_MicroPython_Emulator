from m5stack import *
from m5stack_ui import *
from uiflow import *


def play():
    power.setVibrationEnable(True)
    speaker.playTone(131, 1)
    power.setVibrationEnable(False)


screen = M5Screen()
screen.clean_screen()
screen.set_screen_bg_color(0x0)

# btn = M5Btn("Play", x=15, y=15, w=50, h=30)
# ch = M5Checkbox("Checkbox", x=15, y=50, w=50, h=30, text_c=0x0288FB, check_c=0xCCCCCC)
# switch = M5Switch(x=15, y=85, w=70, h=30, bg_c=0xCCCCCC, color=0x0288FB)
btn = M5Btn("Play", 15, 15, 50, 30)
ch = M5Checkbox(
    "Checkbox", 15, 50, 50, 30, 0x0288FB, 0xCCCCCC
)  # text color, check color
switch = M5Switch(15, 85, 70, 30, 0xCCCCCC, 0x0288FB)  # bg color, color


def pressed_cb():
    play()


btn.pressed(pressed_cb)


play()

while not btnC.wasPressed():
    ch.set_checked(switch.get_state())
    wait(0.2)
