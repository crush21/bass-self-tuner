#!/bin/sh
# 
# Written by Cheyn Rushing
# This file automatically sets up the analog and digital pins that are
# to be used in the self-tuning bass guitar.
# Place "autostart.sh" in home folder, then add
#	sh autostart.sh
# to .bashrc to automatically initialize the analog and digital pins
# upon login.
# 
# Later, functionality to start the self-tuning program from this
# bash script will be added.


# Initialize analog input pins
echo "Initializing Analog Inputs..."
# echo BB-ADC > /sys/devices/bone_capemgr.9/slots
echo cape-bone-iio > /sys/devices/bone_capemgr.9/slots
echo "Done!"

# Initialize digital General Purpose Input/Output (GPIO) pins
echo "Initializing Digital GPIO..."

echo "Motor Control Pins..."
echo 87 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio87/direction
echo 89 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio89/direction
echo 10 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio10/direction
echo 11 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio11/direction

# Motor 1
echo 9 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio9/direction
echo 0 > /sys/class/gpio/gpio9/value
echo 81 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio81/direction
echo 0 > /sys/class/gpio/gpio81/value

# Motor 2
echo 8 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio8/direction
echo 0 > /sys/class/gpio/gpio8/value
echo 80 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio80/direction
echo 0 > /sys/class/gpio/gpio80/value

# Motor 3
echo 78 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio78/direction
echo 0 > /sys/class/gpio/gpio78/value
echo 79 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio79/direction
echo 0 > /sys/class/gpio/gpio79/value

# Motor 4
echo 76 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio76/direction
echo 0 > /sys/class/gpio/gpio76/value
echo 77 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio77/direction
echo 0 > /sys/class/gpio/gpio77/value


echo "LCD Display Control Pins..."
# Data Pins
echo 30 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio30/direction
echo 0 > /sys/class/gpio/gpio30/value
echo 60 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio60/direction
echo 0 > /sys/class/gpio/gpio60/value
echo 31 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio31/direction
echo 0 > /sys/class/gpio/gpio31/value
echo 15 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio15/direction
echo 0 > /sys/class/gpio/gpio15/value
echo 48 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio48/direction
echo 0 > /sys/class/gpio/gpio48/value
echo 51 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio51/direction
echo 0 > /sys/class/gpio/gpio51/value
echo 49 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio49/direction
echo 0 > /sys/class/gpio/gpio49/value
echo 14 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio14/direction
echo 0 > /sys/class/gpio/gpio14/value

# Register Select
echo 2 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio2/direction
echo 0 > /sys/class/gpio/gpio2/value

# Clock
echo 3 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio3/direction
echo 1 > /sys/class/gpio/gpio3/value

echo "Done!"

echo "Initializing LCD Screen..."
echo 73 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio73/direction
echo 1 > /sys/class/gpio/gpio73/value
echo 20 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio20/direction
echo 7 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio7/direction
echo 70 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio70/direction
echo 71 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio71/direction
echo 72 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio72/direction


# Function Set 8 bits
echo 0 > /sys/class/gpio/gpio2/value

echo 0 > /sys/class/gpio/gpio14/value
echo 0 > /sys/class/gpio/gpio49/value
echo 1 > /sys/class/gpio/gpio51/value
echo 1 > /sys/class/gpio/gpio48/value
echo 0 > /sys/class/gpio/gpio15/value
echo 0 > /sys/class/gpio/gpio31/value
echo 0 > /sys/class/gpio/gpio60/value
echo 0 > /sys/class/gpio/gpio30/value

# "Call" three times
echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value
echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value
echo 0 > /sys/class/gpio/gpio3/value
echo 1 > /sys/class/gpio/gpio3/value

# Function Set 8 bits with two lines
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

