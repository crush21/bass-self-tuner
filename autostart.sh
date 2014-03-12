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
echo 66 > /sys/class/gpio/export
echo 0 > /sys/class/gpio/gpio66/value
echo high > /sys/class/gpio/gpio66/direction
echo 69 > /sys/class/gpio/export
echo 0 > /sys/class/gpio/gpio69/value
echo high > /sys/class/gpio/gpio69/direction
echo 45 > /sys/class/gpio/export
echo 0 > /sys/class/gpio/gpio45/value
echo high > /sys/class/gpio/gpio45/direction
echo "Done!"

