#!/bin/bash
# Send "Hi" to LCD

echo 0 > /sys/class/gpio/gpio2/value

echo 0 > /sys/class/gpio/gpio14/value
echo 0 > /sys/class/gpio/gpio49/value
echo 1 > /sys/class/gpio/gpio51/value
echo 1 > /sys/class/gpio/gpio48/value
echo 0 > /sys/class/gpio/gpio15/value
echo 0 > /sys/class/gpio/gpio31/value
echo 0 > /sys/class/gpio/gpio60/value
echo 0 > /sys/class/gpio/gpio30/value

echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value
echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value
echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value

# Function Set
echo 0 > /sys/class/gpio/gpio2/value

echo 0 > /sys/class/gpio/gpio14/value
echo 0 > /sys/class/gpio/gpio49/value
echo 1 > /sys/class/gpio/gpio51/value
echo 1 > /sys/class/gpio/gpio48/value
echo 1 > /sys/class/gpio/gpio15/value
echo 0 > /sys/class/gpio/gpio31/value
echo 0 > /sys/class/gpio/gpio60/value
echo 0 > /sys/class/gpio/gpio30/value

echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value

# Display On/Off control
echo 0 > /sys/class/gpio/gpio2/value

echo 0 > /sys/class/gpio/gpio14/value
echo 0 > /sys/class/gpio/gpio49/value
echo 0 > /sys/class/gpio/gpio51/value
echo 0 > /sys/class/gpio/gpio48/value
echo 1 > /sys/class/gpio/gpio15/value
echo 1 > /sys/class/gpio/gpio31/value
echo 1 > /sys/class/gpio/gpio60/value
echo 0 > /sys/class/gpio/gpio30/value

echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value

# Entry mode set
echo 0 > /sys/class/gpio/gpio2/value

echo 0 > /sys/class/gpio/gpio14/value
echo 0 > /sys/class/gpio/gpio49/value
echo 0 > /sys/class/gpio/gpio51/value
echo 0 > /sys/class/gpio/gpio48/value
echo 0 > /sys/class/gpio/gpio15/value
echo 1 > /sys/class/gpio/gpio31/value
echo 1 > /sys/class/gpio/gpio60/value
echo 0 > /sys/class/gpio/gpio30/value


echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value


# Display Clear
echo 0 > /sys/class/gpio/gpio2/value

echo 0 > /sys/class/gpio/gpio14/value
echo 0 > /sys/class/gpio/gpio49/value
echo 0 > /sys/class/gpio/gpio51/value
echo 0 > /sys/class/gpio/gpio48/value
echo 0 > /sys/class/gpio/gpio15/value
echo 0 > /sys/class/gpio/gpio31/value
echo 0 > /sys/class/gpio/gpio60/value
echo 1 > /sys/class/gpio/gpio30/value


echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value

# Set DDRAM address to 0x00
echo 0 > /sys/class/gpio/gpio2/value

echo 1 > /sys/class/gpio/gpio14/value
echo 0 > /sys/class/gpio/gpio49/value
echo 0 > /sys/class/gpio/gpio51/value
echo 0 > /sys/class/gpio/gpio48/value
echo 0 > /sys/class/gpio/gpio15/value
echo 0 > /sys/class/gpio/gpio31/value
echo 0 > /sys/class/gpio/gpio60/value
echo 0 > /sys/class/gpio/gpio30/value

echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value

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

# Write "b" for flat

# Set CGRAM address <- Not right now. Does Not Work.
#echo 0 > /sys/class/gpio/gpio2/value

#echo 0 > /sys/class/gpio/gpio14/value
#echo 1 > /sys/class/gpio/gpio49/value
#echo 0 > /sys/class/gpio/gpio51/value
#echo 0 > /sys/class/gpio/gpio48/value
#echo 0 > /sys/class/gpio/gpio15/value
#echo 0 > /sys/class/gpio/gpio31/value
#echo 0 > /sys/class/gpio/gpio60/value
#echo 0 > /sys/class/gpio/gpio30/value

#echo 0 > /sys/class/gpio/gpio3/value
#echo 1 > /sys/class/gpio/gpio3/value


# Starting with top row, write characters for flat
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

