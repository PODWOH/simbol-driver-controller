#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "rk3588_driver.h"

#define DEVICE_PATH "/dev/rk3588_gpio_dev"
#define MAX_CONTROLLERS 5

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return EXIT_FAILURE;
    }

    struct rk3588_gpio_ioctl_data data = {
        .controller_id = 0,
        .pin = 10,
        .direction = GPIO_DIRECTION_OUT,
    };

    printf("Test Ф1: Setting GPIO direction to output...\n");
    if (ioctl(fd, RK3588_GPIO_SET_DIRECTION, &data) < 0) {
        perror("Test F1: Failed to set direction to output");
    } else {
        printf("Test F1: Direction set to output successfully.\n");
    }
    
    if (ioctl(fd, RK3588_GPIO_RELEASE, &data) < 0) {
        perror("Failed to release controller");
    }

    data.direction = GPIO_DIRECTION_IN;
    printf("Test F1: Setting GPIO direction to input...\n");
    if (ioctl(fd, RK3588_GPIO_SET_DIRECTION, &data) < 0) {
        perror("Test F1: Failed to set direction to input");
    } else {
        printf("Test F1: Direction set to input successfully.\n");
    }

    close(fd);
    return EXIT_SUCCESS;
}

