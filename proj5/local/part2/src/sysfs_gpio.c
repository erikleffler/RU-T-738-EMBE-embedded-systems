#include "sysfs_gpio.h"

int setupGpioPin(const char* const gpio_dir, const char* const pin,
                 const char* const direction) {
    int export_fd, direction_fd, pin_fd, unexport_fd, edge_fd;
    char path_buffer[PATH_MAX];
    int pin_oflags;

    // Are we reading or writing to gpio register? Set pin_oflags accordingly.

    if (*direction == 'i') {
        pin_oflags = O_RDONLY;
    } else if (*direction == 'o') {
        pin_oflags = O_WRONLY;
    } else {
        perror(
            "Expected direction to be a const char* to one of the strings "
            "\"in\" or \"out\" ");
        return -1;
    }

    // Open export file and request access to pin gpio

    snprintf(path_buffer, sizeof(path_buffer), "%s/export", gpio_dir);

    if ((export_fd = open(path_buffer, O_WRONLY)) < 0) {
        perror("Failed to open export fd\n");
        return -1;
    }

    if (write(export_fd, pin, strlen(pin)) < strlen(pin)) {
        close(export_fd);
        perror("Failed to write led pin to export fd\n");
        return -1;
    }

    close(export_fd);

    // Set gpio direction register

    snprintf(path_buffer, sizeof(path_buffer), "%s/gpio%s/direction", gpio_dir,
             pin);

    if ((direction_fd = open(path_buffer, O_WRONLY)) < 0) {
        perror("Failed to open direction fd\n");
        unexportGpioPin(gpio_dir, pin);
        return -1;
    }

    if (write(direction_fd, direction, strlen(direction)) < strlen(direction)) {
        close(direction_fd);
        perror("Failed to write to pin direction file\n");
        unexportGpioPin(gpio_dir, pin);
        return -1;
    }

    close(direction_fd);

    // Trigger poll on both rising and falling edge

    snprintf(path_buffer, sizeof(path_buffer), "%s/gpio%s/edge", gpio_dir, pin);

    if ((edge_fd = open(path_buffer, O_WRONLY)) < 0) {
        perror("Failed to open edge fd\n");
        unexportGpioPin(gpio_dir, pin);
        return -1;
    }

    if (write(edge_fd, "both", strlen("both")) < strlen("both")) {
        close(edge_fd);
        perror("Failed to write to pin edge file\n");
        unexportGpioPin(gpio_dir, pin);
        return -1;
    }

    close(edge_fd);

    // Finaly, retrieve the file descriptor to the actual gpio pin

    snprintf(path_buffer, sizeof(path_buffer), "%s/gpio%s/value", gpio_dir,
             pin);

    if ((pin_fd = open(path_buffer, pin_oflags)) < 0) {
        perror("Failed to open pin file descriptor\n");
        unexportGpioPin(gpio_dir, pin);
        return -1;
    }

    return pin_fd;
}

int unexportGpioPin(const char* const gpio_dir, const char* const pin) {
    int unexport_fd;
    char path_buffer[PATH_MAX];

    // Open unexport file and terminate access to pin gpio

    snprintf(path_buffer, sizeof(path_buffer), "%s/unexport", gpio_dir);

    if ((unexport_fd = open(path_buffer, O_WRONLY)) < 0) {
        perror("Failed to open unexport file during cleanup\n");
        return -1;
    }

    if (write(unexport_fd, pin, strlen(pin)) < strlen(pin)) {
        close(unexport_fd);
        perror("Failed to write led pin to unexport fd during cleanup\n");
        return -1;
    }
    close(unexport_fd);
    return -1;
}
