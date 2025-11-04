#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define DEVICE_PATH "/dev/rk3588_gpio_dev"
#define MAX_CONTROLLERS 5

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Test F4: Failed to open character device");
        return EXIT_FAILURE;
    }

    printf("Test F4: Character device opened successfully (fd=%d).\n", fd);
    close(fd);
    printf("Test F4: Character device closed successfully.\n");

    return EXIT_SUCCESS;
}

