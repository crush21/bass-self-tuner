#echo 1 > /sys/bus/iio/devices/iio_sysfs_trigger/add_trigger
# echo 1 > /sys/bus/iio/devices/trigger0/trigger_now
echo 1 > /sys/bus/iio/devices/iio\:device0/scan_elements/in_voltage7_en
echo 1 > /sys/bus/iio/devices/iio\:device0/scan_elements/in_voltage0_en
#./generic_buffer -n TI-am335x-adc -t sysfstrig1 -l 128
./generic_buffer -n tiadc -t sysfstrig1 -l 256 -c 3

