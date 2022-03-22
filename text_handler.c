/**
 * @file text_handler.c
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Text printing handler
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 * 
 */

#include "text_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

font_descriptor_t *fdes;

int char_width(int ch)
{
    int width;

    if (!fdes->width)
        width = fdes->maxwidth;
    else
        width = fdes->width[ch - fdes->firstchar];

    return width;
}

int string_width(char *str)
{
    int i = 0;
    int w = 0;
    while (str[i] != '\0')
    {
        w += char_width(str[i]);
        ++i;
    }
    return w;
}

void print_scaled_pixel(int x, int y, uint16_t color, int scaling)
{
    int i, j;
    for (i = 0; i < scaling; i++)
    {
        for (j = 0; j < scaling; j++)
        {
            print_pixel(x + i, y + j, color);
        }
    }
}

void print_character(int x, int y, char ch, uint16_t color, int scaling)
{
    int w = char_width(ch);
    const font_bits_t *ptr;
    if ((ch >= fdes->firstchar) && (ch - fdes->firstchar < fdes->size))
    {
        if (fdes->offset)
        {
            ptr = &fdes->bits[fdes->offset[ch - fdes->firstchar]];
        }
        else
        {
            int bw = (fdes->maxwidth + 15) / 16;
            ptr = &fdes->bits[(ch - fdes->firstchar) * bw * fdes->height];
        }
        int i, j;
        for (i = 0; i < fdes->height; i++)
        {
            font_bits_t val = *ptr;
            for (j = 0; j < w; j++)
            {
                if ((val & 0x8000) != 0)
                {
                    print_scaled_pixel(x + scaling * j, y + scaling * i, color, scaling);
                }
                val <<= 1;
            }
            ptr++;
        }
    }
}

void print_char_string(int x, int y, char *string, int scaling, int space, uint16_t color)
{
    int new_x_pos = 0;
    while (*string != '\0')
    {
        print_character(x + (new_x_pos), y, *(string), color, scaling);
        new_x_pos += (char_width(*(string)) + space) * scaling;
        string++;
    }
}
