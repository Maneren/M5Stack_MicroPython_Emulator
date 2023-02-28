from m5stack import lcd, btnA

count = 0

def print_count(c):
    lcd.clear()
    lcd.print('Count: %d' % c, 0, 0)

def pressed():
    global count
    count += 1
    print_count(count)

btnA.wasPressed(pressed)

print_count(0)
