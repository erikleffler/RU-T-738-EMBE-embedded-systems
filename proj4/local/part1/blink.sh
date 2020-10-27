#!/bin/bash

set -e

# Default values
button_pin=17
led_pin=27
gpio_dir=/sys/class/gpio

# Parse cmdline parameters
positional=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -l|--led-pin)
    led_pin="$2"
    shift
    shift
    ;;
    -b|--button-pin)
    button_pin="$2"
    shift
    shift
    ;;
    *)
    positional+=("$1")
    shift
    ;;
esac
done
set -- "${positional[@]}" # restore positional parameters

echo "Using pin $led_pin for LED."
echo "Using pin $button_pin for button."

echo "Setting up gpio..."
echo $led_pin > $gpio_dir/export
echo $button_pin > $gpio_dir/export

# Want to unexport all gpio pins on exit and CTRL-C 
trap unexport_and_exit EXIT

function unexport_and_exit() {
	echo $led_pin > $gpio_dir/unexport
	echo $button_pin > $gpio_dir/unexport
}

# Busy loop while not have write access
while [[ ! -w $gpio_dir/gpio$led_pin/direction \
	|| ! -w $gpio_dir/gpio$button_pin/direction ]];
do
	:
done

echo "out" > $gpio_dir/gpio$led_pin/direction
echo "in" > $gpio_dir/gpio$button_pin/direction

echo "... Setup done!"

while true; do
	button_pressed=$(( $(cat $gpio_dir/gpio$button_pin/value) ^ 1 ))
	echo $button_pressed > $gpio_dir/gpio$led_pin/value
done
