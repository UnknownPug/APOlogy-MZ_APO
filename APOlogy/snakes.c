/**
 * @file snakes.c
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Snakes handling
 * @date 2021-06-01
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */
#include "snakes.h"

int h_x = SCREEN_WIDTH / CELL_SIZE;
int h_y = SCREEN_HEIGHT / CELL_SIZE;

void init_snakes()
{
    player.type = 1;
    player.direction = 0;
    player.points = 0;
    player = randomize_spawn(player);
    player = init_body(player);
    player.move_blocked = false;
    enemy.direction = 0;
    enemy.points = 0;
    enemy.type = 2;
    enemy = randomize_spawn(enemy);
    enemy = init_body(enemy);
    enemy.move_blocked = false;
}

struct Snake randomize_spawn(struct Snake snake)
{
    int x_min, x_max;
    int y_min, y_max;
    if (snake.type == 5)
    {
        x_min = 2;
        y_min = 4;
        x_max = h_x - x_min;
        y_max = h_y - y_min;
    }
    else
    {
        x_min = 5;
        y_min = 7;
        x_max = h_x - x_min;
        y_max = h_y - y_min;
    }

    do
    {
        snake.x_start = get_random_int(x_min, x_max);
        snake.y_start = get_random_int(y_min, y_max);
    } while (field[snake.y_start * h_x + snake.x_start] != 0);

    snake.head.X = snake.x_start;
    snake.head.Y = snake.y_start;
    field[snake.y_start * h_x + snake.x_start] = snake.type;

    return snake;
}

int get_random_int(int min, int max)
{
    return (rand() % ((max + 1) - min) + min);
}

struct Snake move_player_snake(struct Snake snake)
{
    snake_touched(snake);
    field[snake.head.Y * h_x + snake.head.X] = 0;
    snake = apply_dir(snake);
    snake = fruit_handler(snake);

    if (!is_borders(snake.head.X, snake.head.Y))
        field[snake.head.Y * h_x + snake.head.X] = snake.type;
    else
        lose_handler();

    if (snake.points == 32)
        win_handler();

    snake_touched(snake);
    return snake;
}

struct Snake get_dir(struct Snake snake)
{
    if (!snake.move_blocked)
    {
        if (blue_knob_click)
        {
            snake.move_blocked = true;
            snake.direction = mod(snake.direction + 1, 4);
        }
        else if (red_knob_click)
        {
            snake.move_blocked = true;
            snake.direction = mod(snake.direction - 1, 4);
        }
    }
    return snake;
}

struct Snake fruit_handler(struct Snake snake)
{
    if (field[snake.head.Y * h_x + snake.head.X] == 5)
    {
        snake.points++;
        respawn_fruit();
    }
    return snake;
}

void snake_touched(struct Snake snake)
{
    int opp_type;

    if (snake.type == 1)
        opp_type = 2;
    else
        opp_type = 1;

    int val = field[snake.head.Y * h_x + snake.head.X];

    if (val == opp_type || val == opp_type * 11 || val == snake.type * 11)
    {
        if (snake.type == 1)
            lose_handler();
        else
            win_handler();
    }
}

struct Snake move_enemy_snake(struct Snake snake)
{
    snake_touched(snake);
    field[snake.head.Y * h_x + snake.head.X] = 0;

    if (!fruit_exists(snake.target_fruit))
        snake = set_target_fruit(snake);

    snake = enemy_get_direction(snake);
    snake = correct_dir(snake);

    snake = fruit_handler(snake);

    if (snake.points == 32)
        lose_handler();

    snake_touched(snake);
    field[snake.head.Y * h_x + snake.head.X] = snake.type;
    return snake;
}

struct Snake enemy_get_direction(struct Snake snake)
{
    int dx = snake.target_fruit.X - snake.head.X;
    int dy = snake.target_fruit.Y - snake.head.Y;
    if (abs(dx) >= abs(dy))
    {
        if (dx > 0)
            snake.direction = 1;
        else if (dx < 0)
            snake.direction = 3;
    }
    else
    {
        if (dy > 0)
            snake.direction = 2;
        else if (dy < 0)
            snake.direction = 0;
    }
    return snake;
}

struct Snake set_target_fruit(struct Snake snake)
{
    int min_dist = 0;
    int cell_value = 0;
    int dist = 0;
    int counter = 0;
    bool comparison;
    for (int i = 0; i < h_y; i++)
    {
        for (int j = 0; j < h_x; j++)
        {
            cell_value = field[i * h_x + j];
            if (cell_value == 5)
            {
                dist = get_distance(snake.head.X, snake.head.Y, j, i);
                if (counter == 0)
                    min_dist = dist;

                if (game_speed == 100 * 1000000)
                    comparison = dist <= min_dist;
                else
                    comparison = dist >= min_dist;

                if (comparison)
                {
                    min_dist = dist;
                    snake.target_fruit.X = j;
                    snake.target_fruit.Y = i;
                }
                counter++;
            }
        }
    }
    return snake;
}

bool fruit_exists(struct COORD fruit)
{
    return (field[fruit.Y * h_x + fruit.X] == 5);
}
