#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "rk3588_driver.h"

#define DEVICE_PATH "/dev/rk3588_gpio_dev"

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

    int fd2 = open(DEVICE_PATH, O_RDWR);
    if (fd2 < 0) {
        perror("Test F6: Failed to open device for second time");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Test F6: Testing exclusive access to GPIO controller...\n");

    if (ioctl(fd, RK3588_GPIO_SET_DIRECTION, &data) < 0) {
        perror("Test F6: Failed to set direction in first process");
        close(fd);
        close(fd2);
        return EXIT_FAILURE;
    }

    if (ioctl(fd2, RK3588_GPIO_SET_DIRECTION, &data) < 0) {
        printf("Test F6: Exclusive access test passed: Controller is busy.\n");
    } else {
        printf("Test F6: Exclusive access test failed: Controller was not busy.\n");
    }

    close(fd);
    close(fd2);
    return EXIT_SUCCESS;
}

