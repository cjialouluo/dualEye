#include "gpio.h"
#include <gpiod.h>
#include <stdio.h>
 
#define CHIP "gpiochip1"
// gpio.c
#define GPIO_DC   262
#define GPIO_RES  264
#define GPIO_CS   267
#define GPIO_BL   266

static struct gpiod_chip *chip;
static struct gpiod_line *dc, *res, *cs, *bl;

int gpio_init() {
    chip = gpiod_chip_open_by_name(CHIP);
    if (!chip) { fprintf(stderr, "gpiod_chip_open_by_name failed\n"); return -1; }

    dc = gpiod_chip_get_line(chip, GPIO_DC);
    res = gpiod_chip_get_line(chip, GPIO_RES);
    cs = gpiod_chip_get_line(chip, GPIO_CS);
    bl = gpiod_chip_get_line(chip, GPIO_BL);

    if (!dc || !res || !cs || !bl) {
        fprintf(stderr, "gpiod_chip_get_line failed: dc=%p res=%p cs=%p bl=%p\n", dc, res, cs, bl);
        return -1;
    }

    gpiod_line_request_output(dc, "dc", 0);
    gpiod_line_request_output(res, "res", 1);
    gpiod_line_request_output(cs, "cs", 1);
    gpiod_line_request_output(bl, "bl", 1);

    return 0;
}

void gpio_set_dc(int val)  { gpiod_line_set_value(dc, val); }
void gpio_set_res(int val) { gpiod_line_set_value(res, val); }
void gpio_set_cs(int val)  { gpiod_line_set_value(cs, val); }
void gpio_set_bl(int val)  { gpiod_line_set_value(bl, val); }
