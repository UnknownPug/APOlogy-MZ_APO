/**
 * @file game_handler.c
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Initializing and handling the game states
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */
#include "game_handler.h"

struct timespec delay = {.tv_sec = 0, .tv_nsec = 1000 * 1000000};
int game_speed = 500 * 1000000;
bool text_animation_flag;
bool move_animation_flag;

uint16_t *pixels;
uint8_t *lcd_memory;
uint8_t *peripherals_memory;

void handle_state()
{
    switch (state)
    {
    case 0:
        main_selection_handler();
        break;
    
    case 1:
        player = get_dir(player);
        if (move_animation_flag)
        {
            refresh_game();
            show_points(player.points);
        }
        init_exit_menu();
        break;

    case -1:
        exit_selection_handler();
        break;

    case -2:
        lose_selection_handler();
        break;
    
    case -3:
        win_selection_handler();
        break;
    }
}

void init_font()
{
    fdes = &font_winFreeSystem14x16;
    scaling = 8;
}

void init_delay()
{
    delay.tv_sec = 0;
    delay.tv_nsec = 20 * 1000000;
    text_animation_flag = false;
}

void init_gamehandler()
{
    init_memory();
    init_leds();
    init_knobs();
    init_screen();
    init_delay();
    init_font();
}
