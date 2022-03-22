/**
 * @file peripherals_handler.h
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief  Initializing and interaction with hardware
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */
#ifndef PERIPHERALS_HANDLER_H
#define PERIPHERALS_HANDLER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "colors.h"
#include "constants.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "game_handler.h"

extern bool red_knob_click;
extern bool green_knob_click;
extern bool blue_knob_click;

extern volatile uint32_t *knobs_state;
extern volatile uint32_t *line;
extern volatile uint32_t *rgb1;
extern volatile uint32_t *rgb2;

uint8_t knob_data;
uint8_t red_knob_data;
uint8_t green_knob_data;
uint8_t blue_knob_data;

extern int scaling;
extern bool active_led;

/**
 * Prints a pixel in specified coordinates
\ */
void print_pixel(int x, int y, uint16_t color);

/**
 * Clears the whole screen by filling with black
 * each pixel in pixels array.
\ */
void clear_screen();

/**
 * Renders the screen by "sending" pixels data to the hardware
\ */
void render_screen(uint8_t *lcd_memory);

/**
 * Updates all the peripherals data
\ */
void update_peripherals();

/**
 * Initializes peripherals memory
\ */
void init_memory();

/**
 * Initializes screen
\ */
void init_screen();

/**
 * Initializes knobs
\ */
void init_knobs();

/**
 * Initializes leds
\ */
void init_leds();

/**
 * Blinks with a single RGB LED specified by a number.
 * 0 - right LED
 * 1 - left LED
\ */
void blink_rgb(int number, uint32_t color);

/**
 * Blinks with a whole LED line
\ */
void light_line();

/**
 * Shows player's points on the LED line
\ */
void show_points(int points);

/**
 * Shuts down all the peripherals
\ */
void peripherals_shutdown();

/**
 * Blinking leds during the game
\ */
void animated_leds(uint32_t color);

#endif