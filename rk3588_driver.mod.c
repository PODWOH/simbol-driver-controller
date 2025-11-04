#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0x6e5e9ea5, "module_layout" },
	{ 0x201d0f70, "class_destroy" },
	{ 0xb84635fe, "device_destroy" },
	{ 0xef4606af, "device_create" },
	{ 0x7e5c1500, "cdev_del" },
	{ 0xa640d12, "__class_create" },
	{ 0x37a0cba, "kfree" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x5079af69, "cdev_add" },
	{ 0x8e68f516, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x977f511b, "__mutex_init" },
	{ 0xf163e0f9, "kmem_cache_alloc_trace" },
	{ 0xe157ef13, "kmalloc_caches" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xccc61baf, "gpiod_direction_input" },
	{ 0xb80a5d0c, "gpiod_set_raw_value" },
	{ 0x821b215c, "gpiod_direction_output_raw" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x7fac3f40, "gpiod_get_raw_value" },
	{ 0x140c863c, "gpio_to_desc" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0xc5850110, "printk" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0x2ab7989d, "mutex_lock" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "9C00740ECE7B803A1955B81");
