#ifndef __RK3588_GPIO_DRIVER_H__
#define __RK3588_GPIO_DRIVER_H__

#include <linux/ioctl.h>

// magic number for gpio_ioctl
#define RK3588_GPIO_MAGIC 'G'

#define GPIO_DIRECTION_IN  0
#define GPIO_DIRECTION_OUT 1

// set commands for k3588_gpio_ioctl
#define RK3588_GPIO_SET_DIRECTION _IOW(RK3588_GPIO_MAGIC, 1, struct rk3588_gpio_ioctl_data)
#define RK3588_GPIO_SET_VALUE     _IOW(RK3588_GPIO_MAGIC, 2, struct rk3588_gpio_ioctl_data)
#define RK3588_GPIO_GET_VALUE     _IOR(RK3588_GPIO_MAGIC, 3, struct rk3588_gpio_ioctl_data)
#define RK3588_GPIO_RELEASE       _IO(RK3588_GPIO_MAGIC, 4)

// in/out structure
struct rk3588_gpio_ioctl_data {
    unsigned int controller_id; 
    unsigned int pin;           
    unsigned int direction;     
    unsigned int value;         
};

#endif // __RK3588_GPIO_DRIVER_H__

