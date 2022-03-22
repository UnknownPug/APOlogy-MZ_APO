/**
 * @file game_field.h
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Creating and handling all the events on the gamefield
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 */
#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <stdbool.h>
#include "body.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "text_handler.h"
#include "menu.h"
#include "snakes.h"

extern int *field; /*!< Game field array */
extern struct Snake player; /*!< Player snake data structure */
extern struct Snake enemy; /*!< Enemy snake data structure */

extern bool lose_flag; /*!< Indicates the lose state */
extern bool win_flag; /*!< Indicates the win state */

/**
 * Initializes the game.
\ */
void init_game();

/**
 * Initializes the gamefield.
\ */
void init_field();

/**
 * Fills the game boundaries on the gamefield.
\ */
void fill_borders();

/**
 * Converts the gamefield array into pixels.
\ */
void render_game();

/**
 * Initializes fruits on the gamefield when the game
 * starts.
\ */
void init_fruits();

/**
 * Respawns a fruit in a random unoccupied location
 * on the gamefield.
\ */
void respawn_fruit();

/**
 * Checks if there are borders on the following
 * coordinates.
\ */
bool is_borders(int x, int y);

/**
 * Refreshes the game field by processing all the moves
 * and other events on the field.
\ */
void refresh_game();

/**
 * Displays the players' points on the panel above.
\ */
void points_display_lcd();

#endif
