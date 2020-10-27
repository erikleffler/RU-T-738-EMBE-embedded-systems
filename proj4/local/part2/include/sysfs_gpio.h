#ifndef _SYSFS_GPIO_H_
#define _SYSFS_GPIO_H_

#include <fcntl.h>
#include <limits.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int setupGpioPin(const char* const gpio_dir, const char* const pin,
                 const char* const direction);

int unexportGpioPin(const char* const gpio_dir, const char* const pin);

#endif  // _SYSFS_GPIO_H_
