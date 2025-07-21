#include "spi.h"
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>

static int spi_fd = -1;

int spi_init(const char *device) {
    spi_fd = open(device, O_RDWR);
    if (spi_fd < 0) return -1;

    uint8_t mode = SPI_MODE_0;
    uint32_t speed = 10000000;
    uint8_t bits = 8;

    ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);

    return 0;
}

int spi_write(const void *data, int len) {
    return write(spi_fd, data, len);
}
