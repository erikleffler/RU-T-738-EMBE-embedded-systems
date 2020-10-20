echo $led_pin > /sys/class/gpio/export
sleep 0.5
echo "out" > /sys/class/gpio/gpio$led_pin/direction
COUNTER=0
while [ $COUNTER -lt 100000 ]; do
    echo 1 > /sys/class/gpio/gpio$led_pin/value
    let COUNTER=COUNTER+1
    echo 0 > /sys/class/gpio/gpio$led_pin/value
done

echo $led_pin > /sys/class/gpio/unexport
