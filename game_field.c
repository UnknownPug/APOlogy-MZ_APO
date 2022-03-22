/**
 * @file game_field.c
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Creating and handling all the events on the gamefield
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */
#include "game_field.h"

bool lose_flag;
bool win_flag;

int *field;
struct Snake player;
struct Snake enemy;

void init_game()
{
    state = 1;
    clear_screen();
    init_field();
    fill_borders();
    init_snakes();
    init_fruits();
    enemy = set_target_fruit(enemy);
    render_game();
    render_screen(lcd_memory);
}

void init_field()
{
    field = (int *)calloc(h_x * h_y, sizeof(int));
}

void fill_borders()
{
    for (int i = 0; i < h_y; i++)
    {
        if ((i >= 0 && i <= 2) || i == h_y - 1)
            for (int j = 0; j < h_x; j++)
                field[i * h_x + j] = -1;
        else
        {
            field[i * h_x] = -1;
            field[(i + 1) * h_x - 1] = -1;
        }
    }
}

void init_fruits()
{
    for (int i = 0; i < FRUIT_NUMBER; i++)
        respawn_fruit();
}

void respawn_fruit()
{
    struct Snake fruit;
    fruit.type = 5;
    randomize_spawn(fruit);
}

void render_game()
{
    for (int i = 0; i < h_y; i++)
    {
        for (int j = 0; j < h_x; j++)
        {
            switch (field[i * h_x + j])
            {
            case -1:
                print_image(j * CELL_SIZE, i * CELL_SIZE, -1, 1);
                break;
            case 1:
                print_image(j * CELL_SIZE, i * CELL_SIZE, 1, 1);
                break;
            case 0:
                create_rectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
                break;
            case 5:
                print_image(j * CELL_SIZE, i * CELL_SIZE, 5, 1);
                break;
            case 2:
                print_image(j * CELL_SIZE, i * CELL_SIZE, 2, 1);
                break;
            case 11:
                print_image(j * CELL_SIZE, i * CELL_SIZE, 11, 1);
                break;
            case 22:
                print_image(j * CELL_SIZE, i * CELL_SIZE, 22, 1);
                break;
            }
        }
    }
}

bool is_borders(int x, int y)
{
    if (x == h_x - 1 || x == 0 || y == h_y - 1 || y == 2)
        return true;
    else
        return false;
}

void points_display_lcd()
{
    char *warning_string = (char *)malloc(39 * sizeof(char));

    if (enemy.points > player.points)
        sprintf(warning_string, "The enemy is % 2d points ahead!", enemy.points - player.points);

    if (text_animation_flag)
        print_char_string(100, 8, warning_string, 1, 3, YELLOW);

    sprintf(warning_string, "%2d", player.points);
    create_rectangle(18, 0, 40, 30, RED);
    print_char_string(15, 2, warning_string, 2, 3, WHITE);
    sprintf(warning_string, "%2d", enemy.points);
    create_rectangle(SCREEN_WIDTH - 52, 0, 40, 30, BLUE);
    print_char_string(SCREEN_WIDTH - 55, 2, warning_string, 2, 3, WHITE);

    free(warning_string);
}

void refresh_game()
{
    player = move_player_snake(player);
    player = move_body(player);
    
    enemy = move_enemy_snake(enemy);
    enemy = move_body(enemy);

    if (!lose_flag && !win_flag)
    {
        animated_leds(ARCADE_LED);
        render_game();
        points_display_lcd();
        render_screen(lcd_memory);
    }
}
