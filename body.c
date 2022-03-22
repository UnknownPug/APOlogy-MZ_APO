/**
 * @file body.c
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Handling the body of a snake
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */
#include "body.h"

struct Snake init_body(struct Snake snake)
{
    for (int i = 0; i < SNAKE_MAX_LEN; i++)
    {
        snake.body[i].dir = 0;
        snake.body[i].x = snake.x_start;
        snake.body[i].y = snake.y_start + 1 + i;
    }
    return snake;
}

struct Snake move_body(struct Snake snake)
{
    clean_body(snake);
    for (int i = 0; i < SNAKE_MAX_LEN; i++)
    {
        switch (snake.body[i].dir)
        {
        case 0:
            snake.body[i].y--;
            break;
        case 1:
            snake.body[i].x++;
            break;
        case 2:
            snake.body[i].y++;
            break;
        case 3:
            snake.body[i].x--;
            break;
        }
    }

    display_body(snake);
    snake = move_nodes_in_body(snake);
    snake = body_dir_handler(snake);

    return snake;
}

void display_body(struct Snake snake)
{
    for (int i = 0; i < snake.points; i++)
        field[snake.body[i].y * h_x + snake.body[i].x] = snake.type * 11;
}
void clean_body(struct Snake snake)
{
    for (int i = 0; i < snake.points; i++)
        field[snake.body[i].y * h_x + snake.body[i].x] = 0;
}

struct Snake body_dir_handler(struct Snake snake)
{
    if (snake.body[0].dir != snake.direction)
    {
        snake.body[0].dir = snake.direction;
    }
    return snake;
}
struct Snake move_nodes_in_body(struct Snake snake)
{
    int prev = snake.body[0].dir;
    for (int i = 0; i < SNAKE_MAX_LEN; i++)
    {
        int tmp = snake.body[i].dir;
        snake.body[i].dir = prev;
        prev = tmp;
    }
    return snake;
}

struct Snake apply_dir(struct Snake snake)
{
    switch (snake.direction)
    {
    case 0:
        snake.head.Y--;
        break;
    case 1:
        snake.head.X++;
        break;
    case 2:
        snake.head.Y++;
        break;
    case 3:
        snake.head.X--;
        break;
    }
    return snake;
}

struct Snake correct_dir(struct Snake snake)
{
    struct Snake temp = snake;
    int dir = snake.direction;
    temp = apply_dir(temp);
    bool is_free = false;
    int val = field[temp.head.Y * h_x + temp.head.X];
    int counter = 0;
    if (val == snake.type * 11 || val == player.type * 11 || val == player.type)
    {
        do
        {
            struct Snake try = snake;
            dir = get_random_int(0, 3);
            try.direction = dir;
            try = apply_dir(try);
            int try_val = field[try.head.Y * h_x + try.head.X];
            is_free = (try_val != snake.type * 11 && try_val != player.type * 11 && try_val != player.type && try_val != -1);
            counter++;
            if (counter == 20)
                break;
        } while (!is_free);
    }
    snake.direction = dir;
    snake = apply_dir(snake);
    return snake;
}