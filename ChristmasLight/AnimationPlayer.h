/////////////////////////////////   License  //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Copyright 2015 Nicolas BESSON - BeeAtHome
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _ANNIMATIONPLAYER_H
#define _ANNIMATIONPLAYER_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Stripes.h"



#define R(x) ((uint8_t)(((uint32_t)x >> 16) & 0xFF))
#define G(x) ((uint8_t)(((uint32_t)x >>  8) & 0xFF))
#define B(x) ((uint8_t)(((uint32_t)x >>  0) & 0xFF))

#define COLOR_PIXEL(colorPixel)  { R(colorPixel), G(colorPixel), B(colorPixel) }
#define RGB_PIXEL(r,g,b) (uint32_t)(((uint32_t)(r & 0xFF) << 16)| ((uint32_t)(g & 0xFF) <<  8) | ((uint32_t)(b & 0xFF) <<  0))

//
#define BLACK	RGB_PIXEL(0,0,0)		// Black
#define COLOR1	RGB_PIXEL(150,35,0)	// Yellow
#define COLOR2	RGB_PIXEL(185,88,0)	// Orange



/// <summary>
/// LED Pixel description
/// </summary>
struct PixelColor
{
	uint8_t  Red;	// Red
	uint8_t  Green;	// Green
	uint8_t  Blue;	// Blue
};

/// <summary>
/// Front Step
/// </summary>
struct AnimationStep
{
	unsigned long StepDuration;	// Step Duration in ms
	PixelColor Pixels[LED_STRIPE_NUMLED];		// Step Pixels color
};

/// <summary>
/// Front Animation
/// </summary>
struct Animation
{
	AnimationStep *animationStep;	// Front Step
	Animation *nextAnimation;		// Next Front animation
};

/// <summary>
/// Animation player
/// </summary>
class AnimationPlayer
{
public:
	// Light On
	static const Animation* GetLightOn();

	// Light On
	static const Animation* GetLightOn_Next();

	// Light Off
	static const Animation* GetLightOff();
};

#endif // _ANNIMATIONPLAYER_H
