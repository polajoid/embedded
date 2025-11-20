#ifndef LED_H
# define LED_H

void led_init();
void led_gpio_init();

void led_display_bin(uint8_t nb);

void led_check_state();
void led_gpio_check_state();
void led_i2c_check_state();


extern uint8_t g_led_i2c_states;


# define NB_GPIO_LED 4
# define D1 PB0
# define D2 PB1
# define D3 PB2
# define D4 PB4

# define LED_I2C_D9 3
# define LED_I2C_D10 2
# define LED_I2C_D11 1

#endif
