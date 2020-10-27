#include <fcntl.h>
#include <limits.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "sysfs_gpio.h"

#define LED_PIN "27"
#define BUTTON_PIN "17"
#define GPIO_DIR "/sys/class/gpio"

void cleanup(int not_used) {
    unexportGpioPin(GPIO_DIR, LED_PIN);
    unexportGpioPin(GPIO_DIR, BUTTON_PIN);
    exit(1);
}

int main() {
    char button_value, led_value;
    int button_fd = setupGpioPin(GPIO_DIR, BUTTON_PIN, "in");
    int led_fd = setupGpioPin(GPIO_DIR, LED_PIN, "out");

    int count;

	// Catch ctrl-c and unexport all used gpio pins
    signal(SIGINT, cleanup);

    struct pollfd button_poll;
    button_poll.fd = button_fd;
    button_poll.events =
        POLLPRI | POLLERR;  // These settings detect pin changes

    while (1) {
        if (poll(&button_poll, 1, -1) < 0) {
            perror(
                "An error occurred when polling the button file for pin "
                "change");
        }

        // Reset seek to begining, otherwise we keep reading the final newline
        if (lseek(button_fd, 0, SEEK_SET) < 0) {
            perror("Error when moving button file seek\n");
        }

        if (read(button_fd, &button_value, 1) != 1) {
            perror("Error when reading button value\n");
        }

        button_value ^= 1;

        if (write(led_fd, &button_value, 1) != 1) {
            perror("Error when writing value to led\n");
        }
    }
}
