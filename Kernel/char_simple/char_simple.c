#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h> /* char driver support */
#include <linux/uaccess.h>
#define DEVICE_NAME "My_Char_Driver"
#define CLASS_NAME "MyChar"

MODULE_LICENSE("GPL");  
MODULE_AUTHOR("Eero Leinamo");
MODULE_DESCRIPTION("Character driver");
MODULE_VERSION("0.1");

static int majorNmb;
static struct class* my_class = NULL;
static struct device* my_device = NULL;
static int my_open (struct inode *pinode, struct file *pfile);
static ssize_t my_read (struct file *pfile, char __user *buffer, size_t len, loff_t *offset);
static ssize_t my_write (struct file *pfile, const char __user *buffer, size_t len, loff_t *offset);
static int my_close (struct inode *pinode, struct file *pfile);

struct file_operations my_file_operations = {
        .owner = THIS_MODULE,
        .open = my_open,
        .read = my_read,
        .write = my_write,
        .release = my_close
};

static int my_open (struct inode *pinode, struct file *pfile){
        printk(KERN_ALERT "Inside the %s function \n", __FUNCTION__);
        return 0;
}

static ssize_t my_read (struct file *pfile, char __user *buffer, size_t len, loff_t *offset){
        printk(KERN_ALERT "Inside the %s function \n", __FUNCTION__);
        return 0;
}

static ssize_t my_write (struct file *pfile, const char __user *buffer, size_t len, loff_t *offset){
        printk(KERN_ALERT "Inside the %s function \n", __FUNCTION__);
        return len;
}

static int my_close (struct inode *pinode, struct file *pfile){
        printk(KERN_ALERT "Inside the %s function \n", __FUNCTION__);
        return 0;
}

static int __init char_module_init(void){
	printk(KERN_ALERT "Inside the %s function \n", __FUNCTION__);
	majorNmb = register_chrdev(0,		       /* Major number */	
			DEVICE_NAME,  /* Name of the driver */
			&my_file_operations); /* file operations */
	if(majorNmb < 0){
		printk(KERN_ALERT "MyCHAR failed to register majorNmb\n");
		return majorNmb;
	}

	my_class = class_create(THIS_MODULE, CLASS_NAME);
	if(IS_ERR(my_class)){
		unregister_chrdev(majorNmb, DEVICE_NAME);
		printk(KERN_ALERT "MyCHAR failed to register device class\n");
		return PTR_ERR(my_class);
	}

	my_device = device_create(my_class, NULL, MKDEV(majorNmb, 0), NULL, DEVICE_NAME);
	if(IS_ERR(my_device)){
		class_destroy(my_class);
		unregister_chrdev(majorNmb, DEVICE_NAME);
		printk(KERN_ALERT "MyCHAR failed to create device\n");
		return PTR_ERR(my_device);
	}
	printk(KERN_INFO "MyCHAR device created succesfully\n");
	return 0;
}

void char_module_exit(void){

	printk(KERN_ALERT "Inside the %s function \n", __FUNCTION__);
	device_destroy(my_class, MKDEV(majorNmb,0));
	class_unregister(my_class);
	class_destroy(my_class);
	unregister_chrdev(majorNmb, DEVICE_NAME);
}


module_init(char_module_init);
module_exit(char_module_exit);
