#include <linux/uaccess.h>
#include <linux/i2c.h>
#include <linux/kernel.h>
#include "TCS34725_ioctl.h"

extern struct i2c_client* tcs_client; // Global reference for ioctl

// IOCTL command definitions
long TCS34725_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    uint8_t value;

    if (!tcs_client)
        return -ENODEV;

    switch (cmd) {
        case IOCTL_SET_ATIME:
            if (copy_from_user(&value, (uint8_t __user *)arg, sizeof(uint8_t)))
                return -EFAULT;
            if (i2c_smbus_write_byte_data(tcs_client,ATIME_REGISTER, value) < 0) // ATIME
                return -EIO;
            printk("TCS34725: Set ATIME = 0x%02X\n", value);
            break;

        case IOCTL_SET_GAIN:
            if (copy_from_user(&value, (uint8_t __user *)arg, sizeof(uint8_t)))
                return -EFAULT;
            if (i2c_smbus_write_byte_data(tcs_client,CONTROL_REGISTER, value) < 0) // CONTROL
                return -EIO;
            printk("TCS34725: Set Gain = 0x%02X\n", value);
            break;

        case IOCTL_ENABLE_SENSOR:
            if (copy_from_user(&value, (uint8_t __user *)arg, sizeof(uint8_t)))
                return -EFAULT;
            if (i2c_smbus_write_byte_data(tcs_client,ENABLE_REGISTER, value) < 0) // ENABLE
                return -EIO;
            printk("TCS34725: Set ENABLE = 0x%02X\n", value);
            break;

        default:
            return -EINVAL;
    }

    return 0;
}
