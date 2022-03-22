/**
 * @file images.h
 * @author Ivan Teslenko, Dmytro Rastvorov
 * @brief Image patterns constants
 * @date 2021-06-01
 * 
 * @copyright CVUT-FEL-OI (c) 2021
 *  
 */
#ifndef IMAGES_H
#define IMAGES_H

typedef struct Img
{
    int type;
    int pix[10][10];
    int color1;
    int color2;
    int color3;
    int color4;
} img; /*!< Image container */

extern img Banana; /*!< Fruit image */
extern img Snake; /*!< Player snake head image with top direction */ 
extern img E_Snake; /*!< Enemy snake head image with top direction */ 
extern img Wall; /*!< Wall block image */ 
extern img Body_Snake; /*!< Player snake block image */ 
extern img E_Body_Snake; /*!< Enemy snake block image */

#endif