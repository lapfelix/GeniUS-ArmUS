//
//  colorConvert.cpp
//  colorConversion
//
//  Created by Felix Lapalme on 2014-10-26.
//  Copyright (c) 2014 Felix Lapalme. All rights reserved.
//

#include "colorConvert.h"
#include <cstdlib>
#include <math.h>

//source de la fonction originale non adaptee: http://lolengine.net/blog/2013/01/13/fast-rgb-to-hsv
HsbColor RGBtoHSB(RgbColor colorsIntRGB)
{
	//chaque channel du rgb d'input est un int de 0 à 255 (en theorie)
	//ici on le convertit en float de 0 à 1

	//TODO: ici j'inverse VOLONTAIREMENT le bleu et le vert. à arranger.
    float colorsRGB[3] = {colorsIntRGB.r/255.f, colorsIntRGB.b/255.f, colorsIntRGB.g/255.f};

    HsbColor colorsHSB;
    
    float r = colorsRGB[0], g = colorsRGB[1], b = colorsRGB[2];

    float K = 0.f;

    if (g < b)
    {
        //std::swap(g, b);
        float tmp = g;
                g = b;
                b = tmp;


        K = -1.f;
    }

    if (r < g)
    {
        //std::swap(r, g);
    	float tmp = r;
    	        r = g;
    	        g = tmp;

        K = -2.f / 6.f - K;

    }

    float chroma = r - min(g, b);
    colorsHSB.hue = fabs(K + (g - b) / (6.f * chroma + 1e-20f));
    colorsHSB.saturation = chroma / (r + 1e-20f);
    colorsHSB.brightness = r;

    return colorsHSB;
}
