from m5stack import *
from m5ui import *
from uiflow import *


x = 160
y = 115
m = 's'

screen = M5Screen()
screen.clean_screen()
setScreenColor(0x0)

# 320x230
head = M5Circle(x, y, 50, 0x0, lcd.GREEN)
eyeL = M5Circle(x-20, y-10, 5, lcd.GREEN, lcd.GREEN)
eyeR = M5Circle(x+20, y-10, 5, lcd.GREEN, lcd.GREEN)
mouth = M5Line(M5Line.PLINE, x-20, y+20, x+20, y+20, lcd.GREEN)

def btnLeft_click():
    global m
    m = 'l'

def btnRight_click():
    global m
    m = 'r'
    
def btnStop_click():
    global m
    m = 's'

btnA.wasPressed(btnLeft_click)
btnB.wasPressed(btnStop_click)
btnC.wasPressed(btnRight_click)

while(True):
    wait_ms(100)
    if m == 'l':
        x -= 10
    elif m == 'r':
        x += 10
    else:
      continue
    
    if x >= 370:
        x = -49
    if x <= -50:
        x = 370
    
    head.setPosition(x, y)
    eyeL.setPosition(x-20, y-10)
    eyeR.setPosition(x+20, y-10)
    mouth.setSize(x-20, y+20, x+20, y+20)
