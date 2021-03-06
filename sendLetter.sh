#!/bin/bash
# Send "->Eb" to LCD

# Draw arrow
echo 1 > /sys/class/gpio/gpio2/value

echo 0 > /sys/class/gpio/gpio14/value
echo 1 > /sys/class/gpio/gpio49/value  
echo 1 > /sys/class/gpio/gpio51/value
echo 1 > /sys/class/gpio/gpio48/value
echo 1 > /sys/class/gpio/gpio15/value
echo 1 > /sys/class/gpio/gpio31/value
echo 1 > /sys/class/gpio/gpio60/value
echo 0 > /sys/class/gpio/gpio30/value

echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value


# Write "E"
echo 1 > /sys/class/gpio/gpio2/value

echo 0 > /sys/class/gpio/gpio14/value
echo 1 > /sys/class/gpio/gpio49/value
echo 0 > /sys/class/gpio/gpio51/value
echo 0 > /sys/class/gpio/gpio48/value
echo 0 > /sys/class/gpio/gpio15/value
echo 1 > /sys/class/gpio/gpio31/value
echo 0 > /sys/class/gpio/gpio60/value
echo 1 > /sys/class/gpio/gpio30/value

# Clock enable, then go high.
echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value


# "b" for flat.
echo 1 > /sys/class/gpio/gpio2/value

echo 0 > /sys/class/gpio/gpio14/value
echo 1 > /sys/class/gpio/gpio49/value
echo 1 > /sys/class/gpio/gpio51/value
echo 0 > /sys/class/gpio/gpio48/value
echo 0 > /sys/class/gpio/gpio15/value
echo 0 > /sys/class/gpio/gpio31/value
echo 1 > /sys/class/gpio/gpio60/value
echo 0 > /sys/class/gpio/gpio30/value

echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value

