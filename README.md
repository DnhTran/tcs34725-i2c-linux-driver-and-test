# tcs34725-i2c-linux-driver-and-test
TCS34725 I2C color sensor driver for Linux platforms with integration time, gain, and color data read support.
Author
Trần Cao Quốc Định  22145019 
Đinh Công Khải      22146020
Trần Trung Kiên     22146026
📍 University:HCMC University of Technology and Education – HCMUTE
📅 Created: [05/2025]

📘 Introduction
TCS34725 Linux Driver
This is a Linux driver for the TCS34725 color sensor using I2C communication. The driver allows users to interact with the sensor through standard APIs like read, write, and ioctl from user space. The TCS34725 sensor can measure four color channels (Clear, Red, Green, Blue) with a 16-bit resolution per channel, providing accurate color data for applications in varying lighting conditions.

The driver supports:
+ Reading and configuring the color sensor data over I2C.
+ Providing ioctl commands to configure the sensor, such as enabling the sensor, setting integration time, and adjusting gain.
+ A sample test application to easily interact with the sensor from user space.
This driver is suitable for embedded projects or software development on Linux platforms that require accurate color detection using a sensor.

🛠️ Setting driver
tcs34725-linux-driver/
├── src/
│   ├── TCS34725_main.c         # Main driver source
│   ├── TCS34725_ioctl.c        # ioctl handling implementation
│   ├── TCS34725_ioctl.h        # ioctl command definitions
│   └── Makefile                # Kernel module build file
├── dts/
│   └── tcs34725-overlay.dts    # Device Tree Source file
├── test/
│   └── test_driver.c           # User-space test application
├── README.md                   # Project documentation

Run the following commands:
⚙️ 1. Building and Inserting the Driver
make
sudo insmod tcs34725.ko
🌳 2. Device Tree Registration
// Add a sensor node to the Device Tree Source (DTS):
&i2c1 {
    tcs34725@29 {
        compatible = "taos,tcs34725";
        reg = <0x29>;
    };
};
📁 3. Device Node
// Once the driver is inserted, a character device will be created at:
/dev/TCS34725
// Check if the device exists:
ls -l /dev/TCS34725


🔧 Device Driver API
The TCS34725 Linux kernel module exposes a standard character device interface at /dev/TCS34725. Below are the file operations supported:

1. open() / release()
Open or close the device file.
2. read()
Read sensor data from the driver.
3. write()
Write a string to the driver (currently only logs the string to the kernel log; does not control hardware).
4. ioctl()

🧪 Running the Test Application
// Compile and run the test_driver.c program:
gcc test_driver.c -o test_driver
sudo ./test_driver

🔌 Hardware Connection Diagram
📷 TCS34725 -> I2C Host (e.g., Raspberry Pi)
TCS34725 Pin	   Description	       Connect to Host
VIN / VCC	       Power Supply	       3.3V or 5V (depending on board)
GND	             Ground	             GND
SDA	             I2C Data Line	     SDA (e.g., GPIO2 on Raspberry Pi)
SCL	             I2C Clock Line	     SCL (e.g., GPIO3 on Raspberry Pi)
INT (optional)	 Interrupt Output	   Not used (optional)

🧭 I2C Address
Default I2C address of the TCS34725 sensor is 0x29.
This is configured in the Device Tree overlay file tcs34725-overlay.dts.


📌 Notes
//Make sure the I2C interface is enabled on your system.
//Load i2c-dev module if not already loaded:

sudo modprobe i2c-dev
//If /dev/TCS34725 is not created, check:
//Device Tree overlay is applied correctly.

dmesg logs for kernel errors.



