#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "impact_data.h"

const uint8_t num_chars_per_disp[]={7,7,7,5};
const uint8_t *fonts[]={impact};

void arranque(void);
void print(void);

int main() {
    stdio_init_all();

    // arranque de pins de uso 
    arranque();

    // Impresion en pantalla oled 
    print();

    return 0;
}


void arranque(void) {
    i2c_init(i2c1, 400000);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);
}


void print(void) {
    const char *words[]= {"ARR"};

    ssd1306_t disp;
    disp.external_vcc=false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    ssd1306_clear(&disp);
    char buf[8];

    for(;;) {
        
        for(int i=0; i<sizeof(words)/sizeof(char *); ++i) {
            ssd1306_draw_string(&disp, 25, 25, 2, words[i]);
            ssd1306_show(&disp);
            sleep_ms(800);
            ssd1306_clear(&disp);
        }        
    }
}
