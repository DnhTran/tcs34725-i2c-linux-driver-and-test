# Tên module
obj-m += TCS34725.o

# Các file nguồn tạo thành module
TCS34725-objs := TCS34725_main.o TCS34725_ioctl.o

# Đường dẫn build kernel module
KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

# Luật build chính
all:
	make -C $(KDIR) M=$(PWD) modules

# Luật clean
clean:
	make -C $(KDIR) M=$(PWD) clean
