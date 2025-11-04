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
        
    };
    

    
    
    printf("Setting GPIO direction to INPUT...\n");
    data.direction = GPIO_DIRECTION_IN;
    if (ioctl(fd, RK3588_GPIO_SET_DIRECTION, &data) < 0) {
        perror("Failed to set direction to INPUT");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("Direction set to INPUT successfully.\n");
	
	
    printf("Test Ф3: Reading GPIO value...\n");
    if (ioctl(fd, RK3588_GPIO_GET_VALUE, &data) < 0) {
        perror("Test F3: Failed to get value");
    } else {
        printf("Test F3: Current GPIO value: %d\n", data.value);
    }

    close(fd);
    return EXIT_SUCCESS;
}

