/*
 * Programme Armus - Équipe P24
 * Création : 01/10/2014
 * Modifié  : 02/10/2014
 */
#ifndef CAPTEURCOULEUR_H
#define CAPTEURCOULEUR_H

#include <iostream>
#include <libarmus.h>
#include <cmath>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <map>

struct RgbColor
{
		int r;
		int g;
		int b;
};
struct HsbColor
{
		float hue;
		float saturation;
		float brightness;
};

#define ADJD_S371_QR999_SADR 	0x74
#define CAP_RED					0x6
#define CAP_GREEN				0x7
#define CAP_BLUE				0x8
#define CAP_CLEAR				0x9
#define INTEGRATION_RED			10
#define INTEGRATION_GREEN		12
#define INTEGRATION_BLUE		14
#define INTEGRATION_CLEAR		16
#define ADJD_REG_CTRL			0
#define ADJD_REG_CONFIG			1
#define DATA_RED_LO				64
#define DATA_GREEN_LO			66
#define DATA_BLUE_LO			68
#define DATA_CLEAR_LO			70

#define CTRL_GSSR				0
#define CTRL_GOFS				1

#define CONFIG_TOFS				0

void initCapteurI2C();
RgbColor getColorI2C();
RgbColor getColorAnalog();

#endif
