/**
 * @file exit_menu.c
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Exit menu and pause handling
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */

#include "exit_menu.h"

int exit_selected_button;

void init_exit_menu()
{
    if (green_knob_click)
    {
        state = -1;
        clear_screen(lcd_memory);
        print_char_string(50, SCREEN_HEIGHT / 2 - 50, "ARE YOU SURE YOU WANT TO EXIT?", 1, 3, WHITE);
        exit_select_button(0);
        exit_unselect_button(1);
        render_screen(lcd_memory);
    }
}
void exit_select_button(int number)
{
    exit_selected_button = number;
    switch (number)
    {
    case 0:
        create_button(50, SCREEN_HEIGHT / 2, BTN_EXIT_WIDTH, BTN_HEIGHT, "YES", WHITE, GREEN);
        break;
    case 1:
        create_button(50 + BTN_WIDTH + 50, SCREEN_HEIGHT / 2, BTN_EXIT_WIDTH, BTN_HEIGHT, "NO", WHITE, GREEN);
        break;
    }
}
void exit_unselect_button(int number)
{
    switch (number)
    {
    case 0:
        create_button(50, SCREEN_HEIGHT / 2, BTN_EXIT_WIDTH, BTN_HEIGHT, "YES", RED, WHITE);
        break;
    case 1:
        create_button(50 + BTN_WIDTH + 50, SCREEN_HEIGHT / 2, BTN_EXIT_WIDTH, BTN_HEIGHT, "NO", RED, WHITE);
        break;
    }
}
void exit_selection_handler()
{
    if (red_knob_click)
    {
        exit_unselect_button(exit_selected_button);
        exit_selected_button = (exit_selected_button + 1) % 2;
        exit_select_button(exit_selected_button);
        render_screen(lcd_memory);
    }
    else if (blue_knob_click)
    {
        exit_unselect_button(exit_selected_button);
        exit_selected_button = mod(exit_selected_button - 1, 2);
        exit_select_button(exit_selected_button);
        render_screen(lcd_memory);
    }
    else if (green_knob_click)
    {
        switch (exit_selected_button)
        {
        case 0:
            init_gamehandler();
            init_main_menu();
            break;
        case 1:
            state = 1;
            clear_screen();
            render_game();
            render_screen(lcd_memory);
            break;
        }
    }
}
