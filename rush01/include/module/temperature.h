#ifndef TEMPERATURE_H
# define TEMPERATURE_H

void temperature_init();

uint16_t temperature_c_update();
uint16_t temperature_f_update();
uint16_t temperature_humidity_update();

#endif
