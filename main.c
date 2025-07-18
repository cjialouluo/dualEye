#include <stdio.h>
#include "gc9d01.h"
#include "spi.h"
#include "gpio.h"
#include "defaultEye.h"

// 新增：显示眼睛图片的函数
void display_eye() {
    int cropStartX = (SCLERA_WIDTH - 160) / 2;
    int cropStartY = (SCLERA_HEIGHT - 160) / 2;

    // 设置窗口
    write_cmd(0x2A); // 列地址
    write_data16(0);
    write_data16(159);

    write_cmd(0x2B); // 行地址
    write_data16(0);
    write_data16(159);

    write_cmd(0x2C); // 写入GRAM

    for (int y = 0; y < 160; y++) {
        for (int x = 0; x < 160; x++) {
            int sourceIndex = (cropStartY + y) * SCLERA_WIDTH + (cropStartX + x);
            uint16_t pixel = sclera[sourceIndex];
            write_data16(pixel);
        }
    }
}

int main() {
    printf("GC9D01 SPI Display Init Start\n");

    if (spi_init("/dev/spidev1.0") < 0) {
        fprintf(stderr, "SPI init failed\n");
        return 1;
    }

    if (gpio_init() < 0) {
        fprintf(stderr, "GPIO init failed\n");
        return 1;
    }

    gc9d01_init();
    gpio_set_bl(1);

    // 显示眼睛图片
    display_eye();

    printf("Done. Eye image should be displayed.\n");
    return 0;
}
