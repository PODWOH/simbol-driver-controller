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
        .value = 1,
    };
    
    
    
    printf("Setting GPIO direction to OUTPUT...\n");
    data.direction = GPIO_DIRECTION_OUT;
    if (ioctl(fd, RK3588_GPIO_SET_DIRECTION, &data) < 0) {
        perror("Failed to set direction to OUTPUT");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("Direction set to OUTPUT successfully.\n");
    
    
    printf("Test Ф2: Setting GPIO value to 1...\n");
    if (ioctl(fd, RK3588_GPIO_SET_VALUE, &data) < 0) {
        perror("Test F2: Failed to set value to 1");
    } else {
        printf("Test F2: Value set to 1 successfully.\n");
    }

    data.value = 0;
    printf("Test F2: Setting GPIO value to 0...\n");
    if (ioctl(fd, RK3588_GPIO_SET_VALUE, &data) < 0) {
        perror("Test F2: Failed to set value to 0");
    } else {
        printf("Test F2: Value set to 0 successfully.\n");
    }

    close(fd);
    return EXIT_SUCCESS;
}

