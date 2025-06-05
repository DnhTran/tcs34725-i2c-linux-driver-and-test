
# tcs34725-i2c-linux-driver-and-test

TCS34725 I2C color sensor driver for Linux platforms with integration time, gain, and color data read support.

**Author**  
- Trần Cao Quốc Định 


📍 **University**: HCMC University of Technology and Education – HCMUTE  
📅 **Created**: *05/2025*

---

## 📘 Introduction

**TCS34725 Linux Driver**  
This is a Linux driver for the TCS34725 color sensor using I2C communication. The driver allows users to interact with the sensor through standard APIs like `read`, `write`, and `ioctl` from user space. The TCS34725 sensor can measure four color channels (Clear, Red, Green, Blue) with a 16-bit resolution per channel, providing accurate color data for applications in varying lighting conditions.

### Features
- ✅ Reading and configuring the color sensor data over I2C.  
- ✅ Providing `ioctl` commands to configure the sensor (enable, set integration time, adjust gain).  
- ✅ Sample test application for user-space interaction.

> This driver is suitable for embedded projects or Linux software needing accurate color detection.

---

## 🛠️ Setting up the Driver

**Project Structure:**
```
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
└── README.md                   # Project documentation
```

---

### ⚙️ 1. Building and Inserting the Driver
```bash
make
sudo insmod tcs34725.ko
```

---

### 🌳 2. Device Tree Registration

**Add a sensor node to DTS:**
```dts
&i2c1 {
    tcs34725@29 {
        compatible = "taos,tcs34725";
        reg = <0x29>;
    };
};
```

---

### 📁 3. Device Node
After inserting the driver, a character device is created:
```bash
/dev/TCS34725
ls -l /dev/TCS34725
```

---

## 🔧 Device Driver API

The kernel module exposes a character device interface at `/dev/TCS34725`.

- `open()` / `release()` – Open or close the device file.  
- `read()` – Read sensor data from the driver.  
- `write()` – Write string to driver (only logs; no hardware control).  
- `ioctl()` – Configure sensor settings.

---

## 🧪 Running the Test Application
```bash
gcc test_driver.c -o test_driver
sudo ./test_driver
```

---

## 🔌 Hardware Connection

**TCS34725 → I2C Host (e.g., Raspberry Pi)**

| TCS34725 Pin | Description        | Connect to Host             |
|--------------|--------------------|-----------------------------|
| VIN / VCC    | Power Supply        | 3.3V or 5V                  |
| GND          | Ground              | GND                         |
| SDA          | I2C Data Line       | SDA (e.g., GPIO2 on Pi)     |
| SCL          | I2C Clock Line      | SCL (e.g., GPIO3 on Pi)     |
| INT (opt.)   | Interrupt Output    | Optional (not used)         |

---

## 🧭 I2C Address
Default I2C address: `0x29`  
Defined in `tcs34725-overlay.dts`.

---

## 📌 Notes

- Enable I2C interface (`raspi-config` or manually).  
- Load `i2c-dev` module:
  ```bash
  sudo modprobe i2c-dev
  ```
- If `/dev/TCS34725` not created:
  - Check if overlay is loaded.
  - Inspect kernel log:
    ```bash
    dmesg | grep tcs34725
    ```
