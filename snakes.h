/**
 * @file snakes.c
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Snakes handling, structures declaration
 * @date 2021-06-01
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */
#ifndef SNAKES_H
#define SNAKES_H

#include <stdbool.h>

#include "body.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "text_handler.h"
#include "menu.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

struct COORD
{
    int X;
    int Y;
}; /*!< Coordinates structure */

struct Body
{
    int dir;
    int x;
    int y;
}; /*!< Snake body block structure */

struct Snake
{
    int points;
    int direction;
    int x_start;
    int y_start;
    int type;
    struct COORD head;
    struct Body body[SNAKE_MAX_LEN];
    bool move_blocked;
    struct COORD target_fruit;
}; /*!< Snake main structure */

extern int h_x; /*!< Number of the gamefield cells - width */
extern int h_y; /*!< Number of the gamefield cells - height */

void init_snakes();

struct Snake randomize_spawn(struct Snake snake);

struct Snake move_player_snake(struct Snake snake);

int get_random_int(int min, int max);

struct Snake get_dir(struct Snake snake);

struct Snake fruit_handler(struct Snake snake);

struct Snake move_enemy_snake(struct Snake snake);

struct Snake set_target_fruit(struct Snake snake);

struct Snake enemy_get_direction(struct Snake snake);

bool fruit_exists(struct COORD fruit);

bool is_obstacles(struct Snake snake);

void snake_touched(struct Snake snake);

#endif