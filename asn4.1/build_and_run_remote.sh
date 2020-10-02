#!/bin/bash

set -e

positional=()

while [[ $# -gt 0 ]]
do
	key="$1"

	case $key in
		-p|--part)
			part="$2"
			shift
			shift
			;;
		*)
			positional+=("$1")
			shift
			;;
	esac
done

set -- "${positional[@]}"

local_dir="./part$part"
pi_dir="/home/pi/part$part"

ssh -i /Users/erikleffler1/.ssh/passwordless pi@raspberrypi.local "rm -rf $pi_dir"

scp  -i /Users/erikleffler1/.ssh/passwordless \
	-pr $local_dir  pi@raspberrypi.local:${pi_dir}

commands="
	cd $pi_dir &&
	ls &&
	make &&
	echo "----BINARY-OUTPUT-BELLOW---\n" &&
	./main
"

ssh -i /Users/erikleffler1/.ssh/passwordless pi@raspberrypi.local "$commands"

