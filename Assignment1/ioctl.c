/*
 *  ioctl.c - the process to use ioctl's to control the kernel module
 *
 *  Until now we could have used cat for input and output.  But now
 *  we need to do ioctl's, which require writing our own process.
 */

/*
 * device specifics, such as ioctl numbers and the
 * major device file.
 */
#include "chardev.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <sys/ioctl.h>          /* ioctl */

/*
 * Functions for the ioctl calls
 */


int ioctl_read_x_gyro(int file_desc)
{
    int c;
    
    c= ioctl(file_desc,IOCTL_XGYRO,0);
    printf("The x axis reading of gyrometer ( 16 bits) ");
    if (c < 0) 
    {
            printf("sensor malfunction");
            exit(-1);
    }
    else 
    {
            printf("= %d \n\n",c);
    }

    putchar('\n');
    return 0;
}

int ioctl_read_y_gyro(int file_desc)
{
    int c;
    
    c= ioctl(file_desc,IOCTL_YGYRO,0);
    printf("The y axis reading of gyrometer ( 16 bits) ");
    if (c < 0) 
    {
            printf("sensor malfunction");
            exit(-1);
    }
    else 
    {
            printf("= %d \n\n",c);
    }

    putchar('\n');
    return 0;
}

int ioctl_read_z_gyro(int file_desc)
{
    int c;
    
    c= ioctl(file_desc,IOCTL_ZGYRO,0);
    printf("The z axis reading of gyrometer  ( 16 bits) ");
    if (c < 0) 
    {
            printf("sensor malfunction");
            exit(-1);
    }
    else 
    {
            printf("= %d \n\n",c);
    }

    putchar('\n');
    return 0;
}


int ioctl_read_x_accl(int file_desc)
{
    int c;
    
    c= ioctl(file_desc,IOCTL_XACCL,0);
    printf("The x axis reading of accelerometer  ( 16 bits) ");
    if (c < 0) 
    {
            printf("sensor malfunction");
            exit(-1);
    }
    else 
    {
            printf("= %d \n\n",c);
    }

    putchar('\n');
    return 0;
}

int ioctl_read_y_accl(int file_desc)
{
    int c;
    
    c= ioctl(file_desc,IOCTL_YACCL,0);
    printf("The y axis reading of accelerometer  ( 16 bits) ");
    if (c < 0) 
    {
            printf("sensor malfunction");
            exit(-1);
    }
    else 
    {
            printf("= %d \n\n",c);
    }

    putchar('\n');
    return 0;
}

int ioctl_read_z_accl(int file_desc)
{
    int c;
    
    c= ioctl(file_desc,IOCTL_ZACCL,0);
    printf("The z axis reading of accelerometer  ( 16 bits)  ");
    if (c < 0) 
    {
            printf("sensor malfunction");
            exit(-1);
    }
    else 
    {
            printf("= %d \n\n",c);
    }

    putchar('\n');
    return 0;
}

int ioctl_read_x_magn(int file_desc)
{
    int c;
    
    c= ioctl(file_desc,IOCTL_XACCL,0);
    printf("The x axis reading of magnetometer/compass  ( 14 bits)  ");
    if (c < 0) 
    {
            printf("sensor malfunction");
            exit(-1);
    }
    else 
    {
            printf("= %d \n\n",c);
    }

    putchar('\n');
    return 0;
}

int ioctl_read_y_magn(int file_desc)
{
    int c;
    
    c= ioctl(file_desc,IOCTL_YACCL,0);
    printf("The y axis reading of magnetometer/compass ( 14 bits) "); 
    if (c < 0) 
    {
            printf("sensor malfunction");
            exit(-1);
    }
    else 
    {
            printf("= %d \n\n",c);
    }

    putchar('\n');
    return 0;
}

int ioctl_read_z_magn(int file_desc)
{
    int c;
    
    c= ioctl(file_desc,IOCTL_ZACCL,0);
    printf("The z axis reading of magnetometer/compass  ( 14 bits) " );
    if (c < 0) 
    {
            printf("sensor malfunction");
            exit(-1);
    }
    else 
    {
            printf("= %d \n\n",c);
    }

    putchar('\n');
    return 0;
}

int ioctl_read_pressure(int file_desc)
{
    int c;
    
    c= ioctl(file_desc,IOCTL_PRESS,0);
    printf("The pressure reading of sensor in Pascal ( 32 bits : 24 Bits is interger and 8 bits is fraction) ");
    if (c < 0) 
    {
            printf("sensor malfunction");
            exit(-1);
    }
    else 
    {
            printf("= %d \n\n",c);
    }

    putchar('\n');
    return 0;
}


/*
 * Main - Call the ioctl functions
 */
int main()
{
    int file_desc, ret_val;
    char *msg = "Message passed by ioctl\n";

    file_desc = open(DEVICE_FILE_NAME, 0);
    if (file_desc < 0) {
        printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }

    ioctl_read_x_gyro(file_desc);
    ioctl_read_y_gyro(file_desc);
    ioctl_read_z_gyro(file_desc);
    ioctl_read_x_accl(file_desc);
    ioctl_read_y_accl(file_desc);
    ioctl_read_z_accl(file_desc);
    ioctl_read_x_magn(file_desc);
    ioctl_read_y_magn(file_desc);
    ioctl_read_z_magn(file_desc);
    ioctl_read_pressure(file_desc);

    close(file_desc);
    return 0;
}
