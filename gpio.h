#ifndef GPIO_H
#define GPIO_H

int gpio_init();
void gpio_set_dc(int val);
void gpio_set_res(int val);
void gpio_set_cs(int val);
void gpio_set_bl(int val);

#endif