#include <stdint.h>
#ifndef GC9D01_H
#define GC9D01_H
#include <stdint.h>

void write_cmd(uint8_t cmd);
void write_data16(uint16_t data);
void gc9d01_init();
void gc9d01_fill_color(uint16_t color);

#endif
