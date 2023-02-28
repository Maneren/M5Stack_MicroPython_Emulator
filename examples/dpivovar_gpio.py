from m5stack import *
from m5stack_ui import *
from uiflow import *
from machine import Pin, PWM, ADC, DAC


screen = M5Screen()
screen.clean_screen()
screen.set_screen_bg_color(0x0)

pinOUT = Pin(27, Pin.OUT)
pinIN = Pin(19, Pin.IN, Pin.PULL_UP)

# pwm = PWM(Pin(27), freq=20000, duty=50)
# dac = DAC(Pin(25))
# dac.write(126)

count = 0
value = 1

while(not btnC.wasPressed()):
  val = pinIN.value()
  if val != value and val == 0:
    count +=1
    
  value = val
  pinOUT.value(not val)
  
  lcd.clear()
  lcd.print('Pressed: %d' % int(not val),0,0)
  lcd.print('Count: %d' % count,0,15)
  
  wait(0.2)

lcd.clear()
lcd.print('Finished.',0,0)
