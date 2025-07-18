#ifndef SPI_H
#define SPI_H

int spi_init(const char *device);
int spi_write(const void *data, int len);

#endif