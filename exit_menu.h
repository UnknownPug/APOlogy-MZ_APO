/**
 * @file exit_menu.h
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Exit menu and pause handling
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */

#ifndef EXIT_MENU_H
#define EXIT_MENU_H

#include <stdbool.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "menu.h"

/**
 * Exit menu initializing...
 * Loads graphics and contents.
 */
void init_exit_menu();

/**
 * Processes the button selection graphics.
 */
void exit_select_button(int number);

/**
 * Processes the button unselection graphics.
 */
void exit_unselect_button(int number);

/**
 * Exit menu selection handler.
 * Handles the pause state and the buttons pressed.
 */
void exit_selection_handler();

#endif