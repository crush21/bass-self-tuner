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
echo cape-bone-iio > /sys/devices/bone_capemgr.9/slots
echo "Done!"

# Initialize digital General Purpose Input/Output (GPIO) pins
echo "Initializing Digital GPIO..."

echo "Motor Control Pins..."
# Motor 1
echo 66 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio66/direction
echo 0 > /sys/class/gpio/gpio66/value
echo 69 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio69/direction
echo 0 > /sys/class/gpio/gpio69/value
echo 45 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio45/direction
echo 0 > /sys/class/gpio/gpio45/value

# Motor 2
echo 67 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio67/direction
echo 0 > /sys/class/gpio/gpio67/value
echo 68 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio68/direction
echo 0 > /sys/class/gpio/gpio68/value
echo 44 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio44/direction
echo 0 > /sys/class/gpio/gpio44/value

# Motor 3
echo 23 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio23/direction
echo 0 > /sys/class/gpio/gpio23/value
echo 47 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio47/direction
echo 0 > /sys/class/gpio/gpio47/value
echo 27 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio27/direction
echo 0 > /sys/class/gpio/gpio27/value

# Motor 4
echo 26 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio26/direction
echo 0 > /sys/class/gpio/gpio26/value
echo 46 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio46/direction
echo 0 > /sys/class/gpio/gpio46/value
echo 65 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio65/direction
echo 0 > /sys/class/gpio/gpio65/value


echo "LCD Display Control Pins..."
# Data Pins
echo 70 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio70/direction
echo 0 > /sys/class/gpio/gpio70/value
echo 71 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio71/direction
echo 0 > /sys/class/gpio/gpio71/value
echo 72 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio72/direction
echo 0 > /sys/class/gpio/gpio72/value
echo 73 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio73/direction
echo 0 > /sys/class/gpio/gpio73/value
echo 74 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio74/direction
echo 0 > /sys/class/gpio/gpio74/value
echo 75 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio75/direction
echo 0 > /sys/class/gpio/gpio75/value
echo 76 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio76/direction
echo 0 > /sys/class/gpio/gpio76/value
echo 77 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio77/direction
echo 0 > /sys/class/gpio/gpio77/value

# Register Select
echo 60 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio60/direction
echo 0 > /sys/class/gpio/gpio60/value

# Clock
echo 30 > /sys/class/gpio/export
echo high > /sys/class/gpio/gpio30/direction
echo 1 > /sys/class/gpio/gpio30/value

echo "Done!"

echo "Initializing LCD Screen..."
# Clear display
echo 0 > /sys/class/gpio/gpio60/value
echo 0 > /sys/class/gpio/gpio77/value
echo 0 > /sys/class/gpio/gpio76/value
echo 0 > /sys/class/gpio/gpio75/value
echo 0 > /sys/class/gpio/gpio74/value
echo 0 > /sys/class/gpio/gpio73/value
echo 0 > /sys/class/gpio/gpio72/value
echo 0 > /sys/class/gpio/gpio71/value
echo 1 > /sys/class/gpio/gpio70/value

# Trigger Clock to call command
echo 0 > /sys/class/gpio/gpio30/value
sleep 0.05
echo 1 > /sys/class/gpio/gpio30/value

# Set screen to 8-bit, 2 lines, 5x10 dots (0 00111100)
echo 0 > /sys/class/gpio/gpio60/value
echo 0 > /sys/class/gpio/gpio77/value
echo 0 > /sys/class/gpio/gpio76/value
echo 1 > /sys/class/gpio/gpio75/value
echo 1 > /sys/class/gpio/gpio74/value
echo 1 > /sys/class/gpio/gpio73/value
echo 0 > /sys/class/gpio/gpio72/value
echo 0 > /sys/class/gpio/gpio71/value
echo 0 > /sys/class/gpio/gpio70/value

# Trigger Clock to call command
echo 0 > /sys/class/gpio/gpio30/value
sleep 0.05
echo 1 > /sys/class/gpio/gpio30/value

# Activate Display and Cursor on and Blinking
echo 0 > /sys/class/gpio/gpio60/value
echo 0 > /sys/class/gpio/gpio77/value
echo 0 > /sys/class/gpio/gpio76/value
echo 0 > /sys/class/gpio/gpio75/value
echo 0 > /sys/class/gpio/gpio74/value
echo 1 > /sys/class/gpio/gpio73/value
echo 1 > /sys/class/gpio/gpio72/value
echo 1 > /sys/class/gpio/gpio71/value
echo 1 > /sys/class/gpio/gpio70/value

# Trigger Clock to call command
echo 0 > /sys/class/gpio/gpio30/value
sleep 0.05
echo 1 > /sys/class/gpio/gpio30/value
