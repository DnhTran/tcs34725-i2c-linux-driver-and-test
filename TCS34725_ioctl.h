#ifndef _TCS34725_IOCTL_H_
#define _TCS34725_IOCTL_H_

#include <linux/ioctl.h>
#include <linux/types.h>

#define CMD_BIT            0x80      
#define ENABLE_REGISTER    (CMD_BIT | 0x00)        
#define ATIME_REGISTER     (CMD_BIT | 0x01)        
#define CONTROL_REGISTER   (CMD_BIT | 0x0F)         
#define STATUS_REGISTER    (CMD_BIT | 0x13)
#define CLEAR_REGISTER     (CMD_BIT | 0x14)
#define RED_REGISTER       (CMD_BIT | 0x16)
#define GREEN_REGISTER     (CMD_BIT | 0x18)
#define BLUE_REGISTER      (CMD_BIT | 0x1A)

#define IOCTL_MAGIC         'T'
#define IOCTL_SET_ATIME     _IOW(IOCTL_MAGIC, 1, uint8_t)
#define IOCTL_SET_GAIN      _IOW(IOCTL_MAGIC, 2, uint8_t)
#define IOCTL_ENABLE_SENSOR _IOW(IOCTL_MAGIC, 3, uint8_t)

long TCS34725_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

#endif
