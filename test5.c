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

    struct rk3588_gpio_ioctl_data data;
    int i;

    printf("Test F5: Testing multiple GPIO controllers...\n");
    for (i = 0; i < MAX_CONTROLLERS; i++) {
        data.controller_id = i;
        data.pin = 10+i;
        data.direction = GPIO_DIRECTION_OUT;
        data.value = 1;

        printf("Test F5: Configuring controller %d...\n", i);
        if (ioctl(fd, RK3588_GPIO_SET_DIRECTION, &data) < 0) {
            printf("Test F5: Failed to set direction for controller %d\n", i);
        } else {
            printf("Test F5: Controller %d configured successfully.\n", i);
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}

