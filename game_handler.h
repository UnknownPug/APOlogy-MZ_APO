/**
 * @file game_handler.h
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Initializing and handling the game states
 * @date 2021-06-01
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */
#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "exit_menu.h"
#include "colors.h"
#include "constants.h"
#include "font_types.h"
#include "menu.h"
#include "game_field.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "peripherals_handler.h"
#include "text_handler.h"
#include "snakes.h"

extern int game_speed; /*!< Speed of the game refreshing in ns */
extern struct timespec delay; /*!< Delay time for the LEDs blinking */

extern bool text_animation_flag; /*!< Animation flag. True = text can be displayed */
extern bool move_animation_flag; /*!< Animation flag. True = snakes can move */

extern uint16_t *pixels; /*!< Contains all the pixels in the screen */
extern uint8_t *lcd_memory; /*!< Contains the LCD memory to interact with hardware */
extern uint8_t *peripherals_memory; /*!< Contains the peripherals memory to interact with hardware */

/**
 * Switch function that handles the current state
 * of the game.
\ */
void handle_state();

/**
 * Font initialization.
\ */
void init_font();

/**
 * Delay initialization.
\ */
void init_delay();

/**
 * Initializing all the functions to start the game.
\ */
void init_gamehandler();

#endif