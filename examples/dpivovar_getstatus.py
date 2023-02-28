from m5stack import *
from m5stack_ui import *
from uiflow import *
from easyIO import *


screen = M5Screen()
screen.clean_screen()
screen.set_screen_bg_color(0x0)

#lBat = M5Label('Bat', x=250, y=15, color=0xFFFFFF, font=FONT_MONT_14, parent=None)
#lTime = M5Label('Time', x=15, y=15, color=0xFFFFFF, font=FONT_MONT_14, parent=None)
#lTouch = M5Label('X: 0, Y: 0', x=15, y=50, color=0xFFFFFF, font=FONT_MONT_14, parent=None)
lBat = M5Label('Bat', 250, 15, 0xFFFFFF, FONT_MONT_14, None)
lTime = M5Label('Time', 15, 15, 0xFFFFFF, FONT_MONT_14, None)
lTouch = M5Label('X: 0, Y: 0', 15, 50, 0xFFFFFF, FONT_MONT_14, None)

rtc.settime('ntp', host='cn.pool.ntp.org', tzone=2)


while(not btnC.wasPressed()):
  bat = map_value((power.getBatVoltage()), 3.7, 4.1, 0, 100)
  lBat.set_text("%d%%" % bat)
  
  time = rtc.datetime()
  lTime.set_text("%d-%d-%d %d:%02d:%02d" % (time[0], time[1], time[2], time[4], time[5], time[6]))
  
  t = touch.read()
  lTouch.set_text("X: %d, Y: %d" % (t[0], t[1]))
  
  wait(0.2)