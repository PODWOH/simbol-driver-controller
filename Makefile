obj-m += rk3588_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	sudo insmod rk3588_gpio_driver.ko

remove:
	sudo rmmod rk3588_gpio_driver
