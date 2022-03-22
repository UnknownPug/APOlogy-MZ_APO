/**
 * @file peripherals_handler.c
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief  Initializing and interaction with hardware
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */

#include "peripherals_handler.h"

uint16_t *pixels;
uint8_t *lcd_memory;

bool red_knob_click;
bool green_knob_click;
bool blue_knob_click;

volatile uint32_t *knobs_state;
volatile uint32_t *line;
volatile uint32_t *rgb1;
volatile uint32_t *rgb2;

uint8_t *peripherals_memory;
uint8_t knob_data;
uint8_t red_knob_data;
uint8_t green_knob_data;
uint8_t blue_knob_data;

int scaling;

bool active_led;

void print_pixel(int x, int y, uint16_t color)
{
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
    {
        pixels[x + SCREEN_WIDTH * y] = color;
    }
}

void clear_screen()
{
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        pixels[i] = BLACK;
    }
}

void render_screen(uint8_t *lcd_memory)
{
    parlcd_write_cmd(lcd_memory, 0x2c);
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        parlcd_write_data(lcd_memory, pixels[i]);
    }
}

void update_peripherals()
{
    char red_knob_value = knob_data & 0b100;
    char green_knob_value = knob_data & 0b010;
    char blue_knob_value = knob_data & 0b001;

    red_knob_click = false;
    green_knob_click = false;
    blue_knob_click = false;

    knob_data = (*knobs_state) >> 24;
    red_knob_data = (*knobs_state >> 16) & 0xFF;
    green_knob_data = (*knobs_state >> 8) & 0xFF;
    blue_knob_data = *knobs_state & 0xFF;

    if (red_knob_value - (knob_data & 0b100) == 0b100)
    {
        red_knob_click = true;
    }
    if (green_knob_value - (knob_data & 0b010) == 0b010)
    {
        green_knob_click = true;
    }
    if (blue_knob_value - (knob_data & 0b001) == 0b001)
    {
        blue_knob_click = true;
    }
}

void init_memory()
{
    pixels = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint16_t));
    if (pixels == NULL)
    {
        fprintf(stderr, "Memory allocation error - screen");
        exit(ERR_CODE);
    }
    lcd_memory = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    if (lcd_memory == NULL)
    {
        fprintf(stderr, "Memory allocation error - lcd_memory");
        exit(ERR_CODE);
    }
    peripherals_memory = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (peripherals_memory == NULL)
    {
        fprintf(stderr, "Peripherals memory initializing error!\n");
        exit(-1);
    }
    red_knob_click = false;
    green_knob_click = false;
    blue_knob_click = false;
}

void init_screen()
{
    parlcd_write_cmd(lcd_memory, 0x2c);
    int ptr = 0;
    uint32_t c;
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            c = 0;
            pixels[ptr] = c;
            parlcd_write_data(lcd_memory, pixels[ptr++]);
        }
    }
}

void init_knobs()
{
    knobs_state = (volatile uint32_t *)(peripherals_memory + SPILED_REG_KNOBS_8BIT_o);
}

void init_leds()
{
    line = (volatile uint32_t *)(peripherals_memory + SPILED_REG_LED_LINE_o);
    rgb1 = (volatile uint32_t *)(peripherals_memory + SPILED_REG_LED_RGB1_o);
    rgb2 = (volatile uint32_t *)(peripherals_memory + SPILED_REG_LED_RGB2_o);
    active_led = false;
}

void blink_rgb(int number, uint32_t color)
{
    if (number == 1)
    {
        *rgb1 = color;
    }
    else
    {
        *rgb2 = color;
    }
    clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
    if (number == 1)
    {
        *rgb1 = BLACK;
    }
    else
    {
        *rgb2 = BLACK;
    }
}

void animated_leds(uint32_t color)
{
    if (text_animation_flag)
    {
        if (active_led)
            *rgb1 = color;
        else
            *rgb2 = color;
    }
    else
    {
        *rgb1 = BLACK;
        *rgb2 = BLACK;
        active_led = !active_led;
    }
}

void light_line()
{
    *line = 0xFFFFFFFF;
    clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
    *line = 0x00000000;
}

void show_points(int points)
{
    uint32_t value = 0x0;

    for (int i = 1; i <= 32; i++)
    {
        if (i <= points - 1)
        {
            value += 1;
        }

        if (i != 32)
        {
            value <<= 1;
        }
    }
    *line = value;
}

void peripherals_shutdown()
{
    *line = 0x00000000;
    *rgb1 = BLACK;
    *rgb2 = BLACK;
    clear_screen();
    render_screen(lcd_memory);
}