/**
 * @file menu.c
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Creating menu window, initializating buttons
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */

#include "menu.h"

int main_selected_button;
int difficulty;
int state;

void init_main_menu()
{
    clear_screen();
    print_char_string(25, 20, "APOLOGY", 6, 1, RED);
    main_select_button(0);
    main_unselect_button(1);
    main_unselect_button(2);
    main_unselect_button(3);
    state = 0;
    lose_flag = false;
    win_flag = false;
    render_screen(lcd_memory);
}

void main_select_button(int number)
{
    main_selected_button = number;
    switch (number)
    {
    case 0:
        create_button(50, 120, BTN_WIDTH, BTN_HEIGHT, "1.KIDDO", BLACK, GREEN);
        break;
    case 1:
        create_button(50, 170, BTN_WIDTH, BTN_HEIGHT, "2.MASTER", BLACK, GREEN);
        break;
    case 2:
        create_button(50, 220, BTN_WIDTH, BTN_HEIGHT, "3.SNAKE GOD", BLACK, GREEN);
        break;
    case 3:
        create_button(50, 270, BTN_WIDTH, BTN_HEIGHT, "EXIT", BLACK, GREEN);
        break;
    }
}
void main_unselect_button(int number)
{
    switch (number)
    {
    case 0:
        create_button(50, 120, BTN_WIDTH, BTN_HEIGHT, "1.KIDDO", RED, WHITE);
        break;
    case 1:
        create_button(50, 170, BTN_WIDTH, BTN_HEIGHT, "2.MASTER", RED, WHITE);
        break;
    case 2:
        create_button(50, 220, BTN_WIDTH, BTN_HEIGHT, "3.SNAKE GOD", RED, WHITE);
        break;
    case 3:
        create_button(50, 270, BTN_WIDTH, BTN_HEIGHT, "EXIT", WHITE, RED);
        break;
    }
}
void main_selection_handler()
{
    lose_flag = false;
    win_flag = false;

    if (red_knob_click)
    {
        main_unselect_button(main_selected_button);
        main_selected_button = (main_selected_button + 1) % 4;
        main_select_button(main_selected_button);
        render_screen(lcd_memory);
        blink_rgb(1, RED_LED);
    }
    else if (blue_knob_click)
    {
        main_unselect_button(main_selected_button);
        main_selected_button = mod(main_selected_button - 1, 4);
        main_select_button(main_selected_button);
        render_screen(lcd_memory);
        blink_rgb(0, BLUE_LED);
    }
    else if (green_knob_click)
    {
        light_line();
        switch (main_selected_button)
        {
        case 0:
            init_game();
            difficulty = 0;
            game_speed = 500 * 1000000;
            break;
        case 1:
            init_game();
            difficulty = 1;
            game_speed = 300 * 1000000;

            break;
        case 2:
            init_game();
            difficulty = 2;
            game_speed = 100 * 1000000;
            break;
        case 3:
            peripherals_shutdown();
            exit(0);
            break;
        }
    }
}

void lose_handler()
{
    lose_flag = true;

    clear_screen();
    create_rectangle(85, 80, 325, 100, RED);
    print_char_string(110, 110, "YOU LOSE", 3, 3, BLACK);
    char *points_string = (char *)malloc(40 * sizeof(char));
    sprintf(points_string, "Your score is % 2d points", player.points + 1);
    print_char_string(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + 120, points_string, 1, 2, RED);
    sprintf(points_string, "The enemy score is % 2d points", enemy.points + 1);
    print_char_string(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + 150, points_string, 1, 2, BLUE);
    render_screen(lcd_memory);
    state = -2;
    free(points_string);
}

void lose_selection_handler()
{
    *rgb1 = RED_LED;
    *rgb2 = RED_LED;
    
    if (text_animation_flag)
        print_char_string(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + 190, "PRESS ANY BUTTON TO LEAVE", 1, 2, YELLOW);
    else
        print_char_string(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + 190, "PRESS ANY BUTTON TO LEAVE", 1, 2, BLACK);
    
    render_screen(lcd_memory);
    if (red_knob_click || green_knob_click || blue_knob_click)
    {
        peripherals_shutdown();
        init_gamehandler();
        init_main_menu();
    }
}
void win_handler()
{
    win_flag = true;

    clear_screen();
    create_rectangle(85, 80, 295, 100, GREEN);
    print_char_string(110, 110, "YOU WIN", 3, 3, WHITE);
    char *points_string = (char *)malloc(40 * sizeof(char));
    sprintf(points_string, "Your score is % 2d points", player.points + 1);
    print_char_string(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + 120, points_string, 1, 2, RED);
    sprintf(points_string, "The enemy score is % 2d points", enemy.points + 1);
    print_char_string(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + 150, points_string, 1, 2, BLUE);
    render_screen(lcd_memory);
    state = -3;
    free(points_string);
}
void win_selection_handler()
{
    *rgb1 = GREEN_LED;
    *rgb2 = GREEN_LED;

    if (text_animation_flag)
        print_char_string(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + 190, "PRESS ANY BUTTON TO LEAVE", 1, 2, YELLOW);
    else
        print_char_string(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + 190, "PRESS ANY BUTTON TO LEAVE", 1, 2, BLACK);

    render_screen(lcd_memory);
    if (red_knob_click || green_knob_click || blue_knob_click)
    {
        peripherals_shutdown();
        init_gamehandler();
        init_main_menu();
    }
}
