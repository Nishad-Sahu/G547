/*
 *  chardev2.c - Assignement 1 Device Drivers Character Driver for 10 DOF IMU sensor 
 */

#include <linux/kernel.h>       /* We're doing kernel work */
#include <linux/module.h>       /* Specifically, a module */
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <asm/uaccess.h>        /* for get_user and put_user */
#include <linux/time.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/random.h>         /* for random number generation */
#include "chardev.h"

#define SUCCESS 0
#define DEVICE_NAME "imu_device"
#define BUF_LEN 80


static dev_t first; // variable for device number
static struct cdev c_dev; // variable for the character device structure
static struct class *cls; // variable for device class



/*
 * Is the device open right now? Used to prevent
 * concurent access into the same device
 */
static int Device_Open = 0;

/*
 * The message the device will give when asked
 */
static char Message[BUF_LEN];  

/*
 * How far did the process reading the message get?
 * Useful if the message is larger than the size of the
 * buffer we get to fill in device_read.
 */
static char *Message_Ptr;





//-----------------------------------------------------------------------------device-open()------------------------------------------------------------------------------

/*
 * This is called whenever a process attempts to open the device file
 */
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
static int device_open(struct inode *inode, struct file *file)
{
#ifdef DEBUG
        printk(KERN_INFO "device_open(%p)\n", file);
#endif

    /*
     * We don't want to talk to two processes at the same time
     */
    if (Device_Open)
        return -EBUSY;

    Device_Open++;
    /*
     * Initialize the message
     */
    Message_Ptr = Message;
    try_module_get(THIS_MODULE);
    return SUCCESS;
}

//------------------------------------------------------------------------------------------------device_release--------------------------------------------------------------

static int device_release(struct inode *inode, struct file *file)
{
#ifdef DEBUG
    printk(KERN_INFO "device_release(%p,%p)\n", inode, file);
#endif

    /*
     * We're now ready for our next caller
     */
    Device_Open--;

    module_put(THIS_MODULE);
    return SUCCESS;
}
//-----------------------------------------------------------------------------device-read()------------------------------------------------------------------------------
/*
 * This function is called whenever a process which has already opened the
 * device file attempts to read from it.
 */
 //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static ssize_t device_read(struct file *file,   /* see include/linux/fs.h   */
                           char __user * buffer,        /* buffer to be
                                                         * filled with data */
                           size_t length,       /* length of the buffer     */
                           loff_t * offset)
{
    /*
     * Number of bytes actually written to the buffer
     */
    int bytes_read = 0;

#ifdef DEBUG
    printk(KERN_INFO "device_read(%p,%p,%d)\n", file, buffer, length);
#endif

    /*
     * If we're at the end of the message, return 0
     * (which signifies end of file)
     */
    if (*Message_Ptr == 0)
        return 0;

    /*
     * Actually put the data into the buffer
     */
    while (length && *Message_Ptr) {

    /*
     * Because the buffer is in the user data segment,
     * not the kernel data segment, assignment wouldn't
     * work. Instead, we have to use put_user which
     * copies data from the kernel data segment to the
     * user data segment.
     */
     put_user(*(Message_Ptr++), buffer++);
     length--;
     bytes_read++;
}

#ifdef DEBUG
    printk(KERN_INFO "Read %d bytes, %d left\n", bytes_read, length);
#endif

    /*
     * Read functions are supposed to return the number
     * of bytes actually inserted into the buffer
     */
    return bytes_read;
}

//-----------------------------------------------------------------------------device-write()------------------------------------------------------------------------------
/*
 * This function is called when somebody tries to
 * write into our device file.
 */
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static ssize_t
device_write(struct file *file,
             const char __user * buffer, size_t length, loff_t * offset)
{
    int i;

#ifdef DEBUG
    printk(KERN_INFO "device_write(%p,%s,%d)", file, buffer, length);
#endif

    for (i = 0; i < length && i < BUF_LEN; i++)
        get_user(Message[i], buffer + i);

    Message_Ptr = Message;

    /*
     * Again, return the number of input characters used
     */
    return i;
}

//-----------------------------------------------------------------------------------device_ioctl()--------------------------------------------------------------

/*
 * This function is called whenever a process tries to do an ioctl on our
 * device file. We get two extra parameters (additional to the inode and file
 * structures, which all device functions get): the number of the ioctl called
 * and the parameter given to the ioctl function.
 *
 * If the ioctl is write or read/write (meaning output is returned to the
 * calling process), the ioctl call returns the output of this function.
 *
 */
 
 //----------------------------------------------------------------------------------------------------------------------------------------------------------------
long device_ioctl(struct file *file,             /* ditto */
                  unsigned int ioctl_num,        /* number and param for ioctl */
                  unsigned long ioctl_param)
{

    long num;
    
    

    /*
     * Switch according to the ioctl called
     */
    switch (ioctl_num) 
    {
    	
    	
    	case IOCTL_XGYRO:
    	num = 100  ;//num=randomize_page(0,65536);
    	return num;
    	
    	break;
    	
    	case IOCTL_YGYRO:
    	num = 205 ; //num=randomize_page(0,65536);
    	return num;
    	
    	
    	break;
    	
    	case IOCTL_ZGYRO:
    	num = 467 ; //num=randomize_page(0,65536);
    	return num;
    	
    	
    	break;
    	
    	case IOCTL_XACCL:
    	num = 678 ;//num=randomize_page(0,65536);
    	return num;
    	
    	
    	break;
    	
    	case IOCTL_YACCL:
    	num = 1006 ; //num=randomize_page(0,65536);
    	return num;
    	
    	
    	break;
    	
    	case IOCTL_ZACCL:
    	num = 10 ; //num=randomize_page(0,65536);
    	return num;
    	
    	
    	break;
    	
    	case IOCTL_XMAG:
    	num = 5 ;//num=randomize_page(0,16384);
    	return num;
    	
    	
    	break;
    	
    	case IOCTL_YMAG:
    	num = 6 ; //num=randomize_page(0,16384);
    	return num;
    	
    	
    	break;
    	
    	case IOCTL_ZMAG:
    	num = 9 ;//num=randomize_page(0,16384);
    	return num;
    	
    	
    	break;
    	
    	case IOCTL_PRESS:
    	num = 11000 ; //num=randomize_page(0,16777216);
    	return num;
    	
    	
    	break;
    	
    	/* NOTE: Here I have commented the randomize code as it was crashing in my PC , I seached on internet and it may be due to the memory size constraints
    	*        Using this randomize_page function in the linux/random.h we can set the range and account for the number of bits , for the MPU9255 it is 16 bits ( 2^ 16 = 65536) for accelerometer
    	*        and gyroscope and is 14 bits for the magnetometer(2^14 = 16384). For the BMP280 pressure sensor it is 32 bits with 24 bits integer part and 8 bits 
    	*        fractional part( 2^24 = 16777216)
    	*/
    	
    }
    
    return SUCCESS;
    
}
    	


//---------------------------------------------------------------------------------##LINKING the user space and kernel space##-------------------------------------------------------

/* Module Declarations */

/*
 * This structure will hold the functions to be called
 * when a process does something to the device we
 * created. Since a pointer to this structure is kept in
 * the devices table, it can't be local to
 * init_module. NULL is for unimplemented functions.
 */
struct file_operations Fops = {
        .read = device_read,
        .write = device_write,
        .unlocked_ioctl = device_ioctl,
        .open = device_open,
        .release = device_release,      /* a.k.a. close */
};

//----------------------------------------------------------------/ ######### INITIALIZATION FUNCTION ##########-------------------------------------------------------
/*
 * Initialize the module - Register the character device
 */
// STEP 1, 2 & 3 are to be executed in this function ###
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

static int __init mychar_init(void)
{
    
    // STEP 1 : reserve <major, minor?
    int ret_val;
    
     /*
     * Register the character device (atleast try)
     */
    ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);

    /*
     * Negative values signify an error
     */
     
    if (ret_val < 0) 
    {
        printk(KERN_ALERT "%s failed with %d\n",
               "Sorry, registering the character device ", ret_val);
        return ret_val;
    }
     
    
    printk(KERN_INFO "Namaste: The 10 DOF IMU driver is registered");
    printk(KERN_INFO "%s The major device number is %d.\n",
          "Registeration is a success", MAJOR_NUM);
           

	
	
	if (alloc_chrdev_region(&first, 0,1,"BITS-PILANI") < 0)
	{
	return -1;
	}

	// STEP 2: dynamically create device node in \dev directory
	if ((cls = class_create(THIS_MODULE, "imu_device")) == NULL)
	{
		unregister_chrdev_region(first, 1);
		return -1;
	}
	if (device_create(cls, NULL, first, NULL, "imu_char") == NULL)
	{
		class_destroy(cls);
		unregister_chrdev_region(first, 1);
		return -1;
	}

	// STEP 3: Link fops and cdev to device node
	cdev_init(&c_dev, &Fops);
	if (cdev_add(&c_dev, first, 1) == -1)
	{
		device_destroy(cls, first);
		class_destroy(cls);
		unregister_chrdev_region(first, 1);
		return -1;	
	}
    
   
    printk(KERN_INFO "mknod %s c %d 0\n", DEVICE_FILE_NAME, MAJOR_NUM);

    return 0;
}

//---------------------------------------------------------------------------------MODUL EXIT CODE --------------------------------------------------------------------------------

static void __exit mychar_exit(void)
{ 
cdev_del(&c_dev);
device_destroy(cls, first);
class_destroy(cls);
unregister_chrdev_region(first, 1);
unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
printk(KERN_INFO "Bye: 10 DOF imu driver unregistered \n\n");
}

//-----------------------------------------------------------------------------MODULE INFORMATION AND LICENSES-------------------------------------------------------------------------


module_init(mychar_init);
module_exit(mychar_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("EEE G547");
MODULE_DESCRIPTION("Device Driver Assignmnet 1 10 DOF IMU sensor driver");

//------------------------------------------------------------------------------------END OF CODE---------------------------------------------------------------------------------------



