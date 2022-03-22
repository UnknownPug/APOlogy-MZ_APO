/**
 * @file body.h
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Handling the body of a snake
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */
#ifndef EXIT_MENU_H
#define EXIT_MENU_H

#include "snakes.h"

/**
 * Initializes the snake body tiles
 */
struct Snake init_body (struct Snake snake);

/**
 * Moves the whole snake body on the gamefield
 */
struct Snake move_body (struct Snake snake);

/**
 * Adds an active part of a body to the gamefield
 */
void display_body(struct Snake snake);

/**
 * Removes an active part of a body from the gamefield
 */
void clean_body(struct Snake snake);

/**
 * Handles the direction of the first block of the body
 */
struct Snake body_dir_handler (struct Snake snake);

/**
 * Moves the nodes inside the body during a new turn
 */
struct Snake move_nodes_in_body (struct Snake snake);

/**
 * Changes the snake coordinates 
 * according to the direction number
 */
struct Snake apply_dir (struct Snake snake);

/**
 * Corrects the direction of the AI.
 * The main idea is to avoid unwanted collisions.
 * AI tries to move in a random direction if the
 * collision is possible.
 */
struct Snake correct_dir (struct Snake snake);

#endif