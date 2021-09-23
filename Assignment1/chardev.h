/*
 *  chardev2.h - the header file with the ioctl definitions.
 *
 *  The declarations here have to be in a header file, because
 *  they need to be known both to the kernel module
 *  (in chardev.c) and the process calling ioctl (ioctl.c)
 */

#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

/*
 * The major device number. We can't rely on dynamic
 * registration any more, because ioctls need to know
 * it.
 */
#define MAJOR_NUM 100



/*
 * The IOCTL is used for both input and output. Here we give the IMU sensor the input that 
 * what kind of reading is required to be read from the I2C bus and then read the data 
 * from the I2C bus. So we use IOWR as both read and write functionalities are required 
 */
 #define IOCTL_XGYRO _IOWR(MAJOR_NUM, 0, int)
 #define IOCTL_YGYRO _IOWR(MAJOR_NUM, 1, int)
 #define IOCTL_ZGYRO _IOWR(MAJOR_NUM, 2, int)
 #define IOCTL_XACCL _IOWR(MAJOR_NUM, 3, int)
 #define IOCTL_YACCL _IOWR(MAJOR_NUM, 4, int)
 #define IOCTL_ZACCL _IOWR(MAJOR_NUM, 5, int)
 #define IOCTL_XMAG _IOWR(MAJOR_NUM, 6, int)
 #define IOCTL_YMAG _IOWR(MAJOR_NUM, 7, int)
 #define IOCTL_ZMAG _IOWR(MAJOR_NUM, 8, int)
 #define IOCTL_PRESS _IOWR(MAJOR_NUM, 9, int)

/*
 * The name of the device file
 */
#define DEVICE_FILE_NAME "/dev/imu_char"

#endif
