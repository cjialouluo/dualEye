#include "gc9d01.h"
#include <stdint.h>
#include "spi.h"
#include "gpio.h"
#include <unistd.h>

void write_cmd(uint8_t cmd) {
    gpio_set_dc(0);
    gpio_set_cs(0);
    spi_write(&cmd, 1);
    gpio_set_cs(1);
}

static void write_data(uint8_t data) {
    gpio_set_dc(1);
    gpio_set_cs(0);
    spi_write(&data, 1);
    gpio_set_cs(1);
}

void write_data16(uint16_t data) {
    uint8_t buf[2] = {data >> 8, data & 0xFF};
    gpio_set_dc(1);
    gpio_set_cs(0);
    spi_write(buf, 2);
    gpio_set_cs(1);
}

void gc9d01_init() {
    gpio_set_res(0);
    usleep(100000);
    gpio_set_res(1);
    usleep(100000);

    write_cmd(0xFE);
    write_cmd(0xEF);

    write_cmd(0x80); write_data(0xFF);
    write_cmd(0x81); write_data(0xFF);
    write_cmd(0x82); write_data(0xFF);
    write_cmd(0x83); write_data(0xFF);
    write_cmd(0x84); write_data(0xFF);
    write_cmd(0x85); write_data(0xFF);
    write_cmd(0x86); write_data(0xFF);
    write_cmd(0x87); write_data(0xFF);
    write_cmd(0x88); write_data(0xFF);
    write_cmd(0x89); write_data(0xFF);
    write_cmd(0x8A); write_data(0xFF);
    write_cmd(0x8B); write_data(0xFF);
    write_cmd(0x8C); write_data(0xFF);
    write_cmd(0x8D); write_data(0xFF);
    write_cmd(0x8E); write_data(0xFF);
    write_cmd(0x8F); write_data(0xFF);

    write_cmd(0x3A); write_data(0x05);
    write_cmd(0xEC); write_data(0x01);

    write_cmd(0x74);
    write_data(0x02); write_data(0x0E); write_data(0x00); write_data(0x00);
    write_data(0x00); write_data(0x00); write_data(0x00);

    write_cmd(0x98); write_data(0x3E);
    write_cmd(0x99); write_data(0x3E);

    write_cmd(0xB5); write_data(0x0D); write_data(0x0D);

    write_cmd(0x60); write_data(0x38); write_data(0x0F); write_data(0x79); write_data(0x67);
    write_cmd(0x61); write_data(0x38); write_data(0x11); write_data(0x79); write_data(0x67);

    write_cmd(0x64); write_data(0x38); write_data(0x17); write_data(0x71); write_data(0x5F); write_data(0x79); write_data(0x67);
    write_cmd(0x65); write_data(0x38); write_data(0x13); write_data(0x71); write_data(0x5B); write_data(0x79); write_data(0x67);

    write_cmd(0x6A); write_data(0x00); write_data(0x00);

    write_cmd(0x6C);
    write_data(0x22); write_data(0x02); write_data(0x22); write_data(0x02);
    write_data(0x22); write_data(0x22); write_data(0x50);

    write_cmd(0x6E);
    write_data(0x03); write_data(0x03); write_data(0x01); write_data(0x01);
    write_data(0x00); write_data(0x00); write_data(0x0f); write_data(0x0f);
    write_data(0x0d); write_data(0x0d); write_data(0x0b); write_data(0x0b);
    write_data(0x09); write_data(0x09); write_data(0x00); write_data(0x00);
    write_data(0x00); write_data(0x00); write_data(0x0a); write_data(0x0a);
    write_data(0x0c); write_data(0x0c); write_data(0x0e); write_data(0x0e);
    write_data(0x10); write_data(0x10); write_data(0x00); write_data(0x00);
    write_data(0x02); write_data(0x02); write_data(0x04); write_data(0x04);

    write_cmd(0xbf); write_data(0x01);
    write_cmd(0xF9); write_data(0x40);

    write_cmd(0x9b); write_data(0x3b);
    write_cmd(0x93); write_data(0x33); write_data(0x7f); write_data(0x00);

    write_cmd(0x7E); write_data(0x30);

    write_cmd(0x70); write_data(0x0d); write_data(0x02); write_data(0x08); write_data(0x0d); write_data(0x02); write_data(0x08);
    write_cmd(0x71); write_data(0x0d); write_data(0x02); write_data(0x08);

    write_cmd(0x91); write_data(0x0E); write_data(0x09);

    write_cmd(0xc3); write_data(0x19);
    write_cmd(0xc4); write_data(0x19);
    write_cmd(0xc9); write_data(0x3c);

    write_cmd(0xf0); write_data(0x53); write_data(0x15); write_data(0x0a); write_data(0x04); write_data(0x00); write_data(0x3e);
    write_cmd(0xf2); write_data(0x53); write_data(0x15); write_data(0x0a); write_data(0x04); write_data(0x00); write_data(0x3a);

    write_cmd(0xf1); write_data(0x56); write_data(0xa8); write_data(0x7f); write_data(0x33); write_data(0x34); write_data(0x5f);
    write_cmd(0xf3); write_data(0x52); write_data(0xa4); write_data(0x7f); write_data(0x33); write_data(0x34); write_data(0xdf);

    write_cmd(0x36); write_data(0x00);

    write_cmd(0x11);
    usleep(200000); // delay(200)

    write_cmd(0x29);
    write_cmd(0x2C);
}

void gc9d01_fill_color(uint16_t color) {
    write_cmd(0x2A); // column addr set
    write_data16(0);
    write_data16(159);

    write_cmd(0x2B); // row addr set
    write_data16(0);
    write_data16(159);

    write_cmd(0x2C); // write to RAM

    for (int i = 0; i < 160 * 160; ++i)
        write_data16(color);
}
