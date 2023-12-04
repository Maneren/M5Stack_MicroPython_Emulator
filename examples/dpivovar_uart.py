from m5stack import *
from m5stack_ui import *
from uiflow import *
from machine import UART

screen = M5Screen()
screen.clean_screen()
screen.set_screen_bg_color(0x0)

uart1 = UART(1, 1, 3)  # tx=32, rx=33
uart1.init(115200, bits=8, parity=None, stop=1)


while not btnC.wasPressed():
    if btnA.wasPressed():
        uart1.write("Hello world!\n")

    if uart1.any():
        lcd.clear()
        lcd.print((uart1.read()).decode(), 0, 0)
    wait(0.2)
