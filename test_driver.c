#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include <errno.h>  // Để xử lý lỗi errno

#define DEVICE_PATH "/dev/TCS34725"

// IOCTL command definitions
#define IOCTL_MAGIC         'T'
#define IOCTL_SET_ATIME     _IOW(IOCTL_MAGIC, 1, uint8_t)
#define IOCTL_SET_GAIN      _IOW(IOCTL_MAGIC, 2, uint8_t)
#define IOCTL_ENABLE_SENSOR _IOW(IOCTL_MAGIC, 3, uint8_t)

static volatile int keep_running = 1;

void int_handler(int dummy) {
    keep_running = 0;
}

int main() {
    int fd;
    char buffer[128];
    ssize_t bytesRead;
    uint8_t atime = 0xEB;   // Integration time
    uint8_t gain  = 0x01;   // Gain = 4x
    uint8_t enable = 0x03;  // Power on + ADC enable

    signal(SIGINT, int_handler);  // Handle Ctrl+C

    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return EXIT_FAILURE;
    }

    if (ioctl(fd, IOCTL_ENABLE_SENSOR, &enable) < 0)
        perror("IOCTL_ENABLE_SENSOR failed");
    if (ioctl(fd, IOCTL_SET_ATIME, &atime) < 0)
        perror("IOCTL_SET_ATIME failed");
    if (ioctl(fd, IOCTL_SET_GAIN, &gain) < 0)
        perror("IOCTL_SET_GAIN failed");

    while (keep_running) {
        sleep(1); // Wait for data

        bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            printf("Sensor Data: %s", buffer);
        } else if (bytesRead == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            // Dữ liệu chưa sẵn sàng – không in lỗi
            printf("Waiting for valid sensor data...\n");
            continue;
        } else {
            perror("Read failed");
            break;
        }
    }

    close(fd);
    printf("\nExited gracefully\n");
    return EXIT_SUCCESS;
}
