/**
 * @file graphics.c
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Graphics functions
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */

#include "graphics.h"

struct timespec tstart = {0, 0},
                tend = {0, 0},
                t_anim_start = {0, 0},
                t_anim_end = {0, 0};

void create_button(int x, int y, int w, int h, char *sign, int16_t color_text, int16_t color_bg)
{
    create_rectangle(x, y, w, h, color_bg);
    print_char_string(x + 10, y + h / 3, sign, 1, 4, color_text);
}

void create_rectangle(int x, int y, int w, int h, int16_t color)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            pixels[(i + y) * SCREEN_WIDTH + j + x] = color;
        }
    }
}

//Modulo function for defind negatives
int mod(int x, int y)
{

    int t = x - ((x / y) * y);
    if (t < 0)
    {
        t += y;
    }
    return t;
}

void text_animation_timer()
{
    if (t_anim_start.tv_sec == 0 && t_anim_start.tv_nsec == 0)
        clock_gettime(CLOCK_MONOTONIC, &t_anim_start);
    clock_gettime(CLOCK_MONOTONIC, &t_anim_end);
    if ((t_anim_end.tv_sec - t_anim_start.tv_sec) * 1000000000 + (t_anim_end.tv_nsec - t_anim_start.tv_nsec) >= TEXT_ANIMATION_SPEED)
    {
        text_animation_flag = !text_animation_flag;
        t_anim_start.tv_nsec = 0;
        t_anim_start.tv_sec = 0;
    }
}

void move_animation_timer()
{
    if (tstart.tv_sec == 0 && tstart.tv_nsec == 0)
        clock_gettime(CLOCK_MONOTONIC, &tstart);
    clock_gettime(CLOCK_MONOTONIC, &tend);
    if ((tend.tv_sec - tstart.tv_sec) * 1000000000 + (tend.tv_nsec - tstart.tv_nsec) >= game_speed)
    {
        player.move_blocked = false;
        enemy.move_blocked = false;
        move_animation_flag = true;
        tstart.tv_nsec = 0;
        tstart.tv_sec = 0;
    }
}

int get_distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void print_image(int x, int y, int type, int scaling)
{
    img image;
    uint16_t color;

    switch (type)
    {
    case 1:
        image = Snake;
        prepare_img(10, image.pix, player.direction);
        break;
    case 2:
        image = E_Snake;
        prepare_img(10, image.pix, enemy.direction);
        break;
    case -1:
        image = Wall;
        break;
    case 11:
        image = Body_Snake;
        break;
    case 22:
        image = E_Body_Snake;
        break;
    default:
        image = Banana;
        break;
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            switch (image.pix[i][j])
            {
            case 1:
                color = image.color1;
                break;
            case 2:
                color = image.color2;
                break;
            case 3:
                color = image.color3;
                break;
            case 4:
                color = image.color4;
                break;
            default:
                color = BLACK;
                break;
            }
            print_scaled_pixel(x + j, y + i, color, scaling);
        }
    }
}

void rotate_clockwise(int N, int matrix[N][N])
{
    // Traverse each cycle
    for (int i = 0; i < N / 2; i++)
    {
        for (int j = i; j < N - i - 1; j++)
        {
            // Swap elements of each cycle
            // in clockwise direction
            int temp = matrix[i][j];
            matrix[i][j] = matrix[N - 1 - j][i];
            matrix[N - 1 - j][i] = matrix[N - 1 - i][N - 1 - j];
            matrix[N - 1 - i][N - 1 - j] = matrix[j][N - 1 - i];
            matrix[j][N - 1 - i] = temp;
        }
    }
}

void rotate_anti_clockwise(int N, int matrix[N][N])
{
    // Consider all squares one by one
    for (int x = 0; x < N / 2; x++)
    {
        // Consider elements in group
        // of 4 in current square
        for (int y = x; y < N - x - 1; y++)
        {
            // Store current cell in
            // temp variable
            int temp = matrix[x][y];

            // Move values from right to top
            matrix[x][y] = matrix[y][N - 1 - x];

            // Move values from bottom to right
            matrix[y][N - 1 - x] = matrix[N - 1 - x][N - 1 - y];

            // Move values from left to bottom
            matrix[N - 1 - x][N - 1 - y] = matrix[N - 1 - y][x];

            // Assign temp to left
            matrix[N - 1 - y][x] = temp;
        }
    }
}

void prepare_img(int N, int img[N][N], int dir)
{
    switch (dir)
    {
    case 1:
        rotate_clockwise(10, img);
        break;
    case 2:
        rotate_clockwise(10, img);
        rotate_clockwise(10, img);
        break;
    case 3:
        rotate_anti_clockwise(10, img);
        break;
    default:
        break;
    }
}
