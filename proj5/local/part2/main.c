#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <unistd.h>

#define LED_PIN "27"
#define BUTTON_PIN "17"
#define GPIO_DIR "/sys/class/gpio"

int main() {

	int export_fd, led_fd, button_fd;

    const char* export_path = GPIO_DIR "/export";
    const char* unexport_path = GPIO_DIR "/unexport";
    const char* led_path = GPIO_DIR "/gpio" LED_PIN "/value";
    const char* button_path = GPIO_DIR "/gpio" BUTTON_PIN "/value";

    if ((export_fd = open(export_path, O_WRONLY)) < 0) {
        perror("Failed to open export fd\n");
        return -1;
    }

    if (write(export_fd, LED_PIN, sizeof(LED_PIN)) < sizeof(LED_PIN)) {
        perror("Failed to write led pin to export fd\n");
        return -1;
    }

    if (write(export_fd, BUTTON_PIN, sizeof(BUTTON_PIN)) <
        sizeof(BUTTON_PIN)) {
        perror("Failed to write button pin to export fd\n");
        return -1;
    }

    if ((button_fd = open(button_path, O_RDONLY)) < 0) {
        perror("Failed to open button fd\n");
        return -1;
    }

    if ((led_fd = open(led_path, O_WRONLY)) < 0) {
        perror("Failed to open led fd\n");
        return -1;
    }

    struct pollfd button_poll;
    button_poll.fd = button_fd;
	button_poll.events = POLLPRI | POLLERR;

	while(1) {
		if(poll(&button_poll, 1, -1) < 0) {
            perror("An error occurred when polling the button file");
		}
		printf("button polled\n");
	}
}
