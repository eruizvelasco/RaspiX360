import math

from smbus import SMBus

# I2C values
addr = 0x8 # bus address
bus = SMBus(1) # indicates /dev/ic2-1

LED_GREEN  = 0x0
LED_RED    = 0x1
LED_YELLOW = 0x2

led_state_green = 0
led_state_red = 0
led_state_yellow = 0

if __name__ == '__main__':

    bExit = False

    btn = ""

    prev_state = 0

    while not bExit:

        btn = raw_input("Enter A,B,Y,:")

        # LEDs
        led_state_green  = 1 if btn == 'A' else 0
        led_state_red    = 1 if btn == 'B' else 0
        led_state_yellow = 1 if btn == 'Y' else 0

        bExit = not btn in "ABY"

        bus.write_byte(8, led_state_green)
        bus.write_byte(8, led_state_red)
        bus.write_byte(8, led_state_yellow)

        cur_state = (led_state_green +
                    led_state_red +
                    led_state_yellow)

        if cur_state != prev_state:
            print("green:",led_state_green,"\n")
            print("red:",led_state_red,"\n")
            print("yellow:",led_state_yellow,"\n")

        prev_state = cur_state

    bus.close()
