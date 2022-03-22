/**
 * @file menu.h
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Creating menu window, initializating buttons
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */
#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

#include "colors.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "graphics.h"
#include "game_field.h"
#include "peripherals_handler.h"

extern int difficulty; /*!< Selected difficulty level */
extern int state; /*!< Current state of the game */
extern int main_selected_button; 

/**
 * Initializes the main menu GUI and sets the game state
\ */
void init_main_menu();

/**
 * Processes the main menu button selection
\ */
void main_select_button(int number);

/**
 * Processes the main menu button unselection
\ */
void main_unselect_button(int number);

/**
 * Main menu selection handler.
 * Operates all the actions in this state.
\ */
void main_selection_handler();

/**
 * Initializes the lose window
 * and prepares all the GUI and hardware states.
\ */
void lose_handler();

/**
 * Handles the selection in the lose window
 * from the hardware
\ */
void lose_selection_handler();

/**
 * Initializes the win window
 * and prepares all the GUI and hardware states.
\ */
void win_handler();

/**
 * Handles the selection in the win window
 * from the hardware
\ */
void win_selection_handler();

#endif
