#ifndef D7S_H
# define D7S_H

void d7s_init();
void d7s_set_number(uint16_t n);

# define D7S_SELECT_0 (uint8_t)~(1 << 7)
# define D7S_SELECT_1 ~(1 << 6)
# define D7S_SELECT_2 ~(1 << 5)
# define D7S_SELECT_3 ~(1 << 4)
# define D7S_SELECT_MASK 0xF0

# define D7S_PRINT_0 0b00111111
# define D7S_PRINT_1 0b00000110
# define D7S_PRINT_2 0b01011011
# define D7S_PRINT_3 0b01001111
# define D7S_PRINT_4 0b01100110
# define D7S_PRINT_5 0b01101101
# define D7S_PRINT_6 0b01111101
# define D7S_PRINT_7 0b00000111
# define D7S_PRINT_8 0b01111111
# define D7S_PRINT_9 0b01101111
# define D7S_PRINT_DASH 0b01000000
# define D7S_PRINT_CLEAR 0b00000000

#endif
