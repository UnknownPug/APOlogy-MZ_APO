/**
 * @file main.c
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Main game file, contains the infinite loop
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */

#define _POSIX_C_SOURCE 200112L

#include "game_handler.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    init_gamehandler();
    init_main_menu();

    printf("The game started...\n");
    while (1)
    {
        move_animation_flag = false;

        move_animation_timer();
        text_animation_timer();

        update_peripherals();
        handle_state();
    }
}
