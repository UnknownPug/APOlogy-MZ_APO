/**
 * @file text_handler.h
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Text printing handler
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */

#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H

#define CHAR_HEIGHT 14

#define OFFSET1 8
#define OFFSET2 4

#define COUNTDOWN_PERIOD 60

#include "font_types.h"
#include "peripherals_handler.h"

extern font_descriptor_t *fdes; /*!< Pointer to a font descriptor */

extern int countdownTimer;
extern int currentCountdownState;

/**
 * Initializes the string width
\ */
int string_width(char *str); 

/**
 * Initializes the char width
\ */
int char_width(int ch);

/**
 * Prints a scaled pixel
\ */
void print_scaled_pixel(int x, int y, uint16_t color, int scaling);

/**
 * Prints a single character
\ */
void print_character(int x, int y, char ch, uint16_t color, int scaling);

/**
 * Prints a text string
\ */
void print_char_string(int x, int y, char *line, int scaling, int kerning, uint16_t color);

#endif
