/**
 * @file graphics.h
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Graphics functions
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 * 
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "text_handler.h"
#include "images.h"

extern struct timespec tstart; /*!< Movement animation timer start */
extern struct timespec tend; /*!< Movement animation timer end */
extern struct timespec t_anim_start; /*!< Text animation timer start */
extern struct timespec t_anim_start; /*!< Text animation timer end */

/**
 * Creates a button with defined parameters.
 * x, y - coordinates of the left upper corner
 * h,w - height and width of the button
 * sign - text string
 * color_text - color of the text
 * color_bg - color of the background
\ */
void create_button(int x, int y, int w, int h, char *sign, int16_t color_text, int16_t color_bg);

/**
 * Creates a rectangle with defined parameters.
 * x, y - coordinates of the left upper corner
 * h,w - height and width of the button
 * color - color of the background
\ */
void create_rectangle(int x, int y, int w, int h, int16_t color);

/**
 * Modulo function defined for negatives
\ */
int mod(int x, int y);

/**
 * Handles the text_animation_flag state to avoid using
 * sleep() methods.
\ */
void text_animation_timer();


/**
 * Handles the move_animation_flag state to avoid using
 * sleep() methods.
\ */
void move_animation_timer();


/**
 * Gets the distance between a fruit and the snake's head
\ */
int get_distance(int x1, int y1, int x2, int y2);

/**
 * Prints an image with specified parameters
\ */
void print_image(int x, int y, int type, int scaling);

/**
 * Rotates the image matrix clockwise
\ */
void rotate_clockwise(int N, int matrix[N][N]);

/**
 * Rotates the image matrix anticlockwise
\ */
void rotate_anti_clockwise(int N, int matrix[N][N]);

/**
 * Rotates the image (e.g. snake head) 
 * to get the specified direction
\ */
void prepare_img(int N, int img[N][N], int dir);

#endif