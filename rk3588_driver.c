#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include "rk3588_driver.h"

#define DRIVER_NAME "rk3588_gpio"
#define DEVICE_NAME "rk3588_gpio_dev"
#define MAX_CONTROLLERS 5

static int major; 
static struct class *cls;
static dev_t dev;
static struct rk3588_gpio_driver_data *global_data;  

// monitoring driver status
struct rk3588_gpio_driver_data {
    struct mutex lock;
    unsigned int in_use[MAX_CONTROLLERS];
    struct cdev cdev;  
};

// open device
static int rk3588_gpio_open(struct inode *inode, struct file *file) {
    struct rk3588_gpio_driver_data *data = container_of(inode->i_cdev, struct rk3588_gpio_driver_data, cdev);  
    file->private_data = data;
    return 0;
}

// close device
static int rk3588_gpio_release(struct inode *inode, struct file *file) {
    struct rk3588_gpio_driver_data *data = file->private_data;
    unsigned int controller_id;
    mutex_lock(&data->lock);
    for (controller_id = 0; controller_id < MAX_CONTROLLERS; controller_id++) {
        if (data->in_use[controller_id]) {
            data->in_use[controller_id] = 0;
            printk(KERN_INFO "controller free %d\n", controller_id);
        }
    }
    mutex_unlock(&data->lock);
    return 0;
}

// in/out 
static long rk3588_gpio_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    struct rk3588_gpio_ioctl_data ioctl_data;
    struct rk3588_gpio_driver_data *data = file->private_data;
    int ret = 0;

    if (copy_from_user(&ioctl_data, (void __user *)arg, sizeof(ioctl_data)))
        return -EFAULT;

    // controller check
    if (ioctl_data.controller_id >= MAX_CONTROLLERS)
        return -EINVAL;

    mutex_lock(&data->lock);

    switch (cmd) {
        case RK3588_GPIO_SET_DIRECTION:
            // controller is busy
            if (data->in_use[ioctl_data.controller_id]) {
                 ret = -EBUSY;  
                 break;
            }
            
            data->in_use[ioctl_data.controller_id] = 1;



            // setting the direction of interaction
            if (ioctl_data.direction == GPIO_DIRECTION_IN) {
                if (gpio_direction_input(ioctl_data.pin) < 0) {
			
                    data->in_use[ioctl_data.controller_id] = 0;
                    ret = -EINVAL;
                }
            } else {
            	
                if (gpio_direction_output(ioctl_data.pin, 0) < 0) {

                    data->in_use[ioctl_data.controller_id] = 0;
                    ret = -EINVAL;
                }
            }
            break;

        case RK3588_GPIO_SET_VALUE:
            if (!data->in_use[ioctl_data.controller_id]) {
                ret = -EACCES;
                break;
            }
            gpio_set_value(ioctl_data.pin, ioctl_data.value);
            break;

        case RK3588_GPIO_GET_VALUE:
            if (!data->in_use[ioctl_data.controller_id]) {
                ret = -EACCES;
                break;
            }
            ioctl_data.value = gpio_get_value(ioctl_data.pin);
            if (copy_to_user((void __user *)arg, &ioctl_data, sizeof(ioctl_data))) {
                ret = -EFAULT;
            }
            break;
            
        case RK3588_GPIO_RELEASE:
            data->in_use[ioctl_data.controller_id] = 0;
            break;

        default:
            ret = -ENOTTY;
            break;
    }

    mutex_unlock(&data->lock);
    return ret;
}

// driver operations open/release/in/out
static struct file_operations rk3588_gpio_fops = {
    .owner = THIS_MODULE,
    .open = rk3588_gpio_open,
    .release = rk3588_gpio_release,
    .unlocked_ioctl = rk3588_gpio_ioctl,
};

// driver initial
static int __init rk3588_gpio_init(void) {
    struct rk3588_gpio_driver_data *data;
    int ret;

    // set data space
    data = kzalloc(sizeof(*data), GFP_KERNEL);
    if (!data)
        return -ENOMEM;

    mutex_init(&data->lock);
    global_data = data;  

    // reg character device
    ret = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        kfree(data);
        return ret;
    }
    
    major = MAJOR(dev);
    
    // character device initial 
    cdev_init(&data->cdev, &rk3588_gpio_fops);  
    data->cdev.owner = THIS_MODULE;
    
    // add device in sys
    ret = cdev_add(&data->cdev, dev, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev, 1);
        kfree(data);
        return ret;
    }

    cls = class_create(THIS_MODULE, DEVICE_NAME);
    if (IS_ERR(cls)) {
        cdev_del(&data->cdev);  
        unregister_chrdev_region(dev, 1);
        kfree(data);
        return PTR_ERR(cls);
    }

    device_create(cls, NULL, dev, NULL, DEVICE_NAME);
    printk(KERN_INFO "RK3588 GPIO Driver initialized\n");
    return 0;
}

// driver exit, freeing space
static void __exit rk3588_gpio_exit(void) {
    device_destroy(cls, dev);
    class_destroy(cls);
    cdev_del(&global_data->cdev);  
    unregister_chrdev_region(dev, 1);
    kfree(global_data); 
    printk(KERN_INFO "RK3588 GPIO Driver exited\n");
}

module_init(rk3588_gpio_init);
module_exit(rk3588_gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("PODWOH");
MODULE_DESCRIPTION("RK3588 GPIO Driver");
