#ifndef LIGHT_H
# define LIGHT_H

void	init_LED(void);
void	LED_turnoff_b(void);
void	LED_turnoff_d(void);
void	LED_waiting_state(void);
void	LED_player_ready_state(void);
uint8_t	LED_countdown(void);
void	LED_show_winner(void);
void	LED_show_loser(void);

#endif
