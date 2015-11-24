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

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "AnimationPlayer.h"
#include "Animations.h"

#define SIN_MAX_INDEX 128

// From http://www.daycounter.com/Calculators/Sine-Generator-Calculator2.phtml
const uint8_t sinus[SIN_MAX_INDEX] PROGMEM = {
	15, 16, 16, 17, 18, 19, 19, 20,
	21, 21, 22, 23, 23, 24, 25, 25,
	26, 26, 27, 27, 27, 28, 28, 29,
	29, 29, 29, 30, 30, 30, 30, 30,
	30, 30, 30, 30, 30, 30, 29, 29,
	29, 29, 28, 28, 27, 27, 27, 26,
	26, 25, 25, 24, 23, 23, 22, 21,
	21, 20, 19, 19, 18, 17, 16, 16,
	15, 14, 14, 13, 12, 11, 11, 10,
	9, 9, 8, 7, 7, 6, 5, 5,
	4, 4, 3, 3, 3, 2, 2, 1,
	1, 1, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 2, 2, 3, 3, 3, 4,
	4, 5, 5, 6, 7, 7, 8, 9,
	9, 10, 11, 11, 12, 13, 14, 14
};

//
AnimationStep currentAnnimationStep = { 0 };

//
Animation currentAnnimation = { 0 };


/// <summary>
/// Light On for accessor
/// </summary>
/// <returns>Animation</returns>
const Animation* AnimationPlayer::GetLightOn()
{
	if (currentAnnimation.animationStep == NULL)
	{
		currentAnnimation.animationStep = &currentAnnimationStep;
		currentAnnimation.nextAnimation = &currentAnnimation;
	}

	// Intialize the step state
	currentAnnimationStep = stepOn1;

	return &currentAnnimation;
}
uint8_t sinIndex = 0;

/// <summary>
/// Light On for accessor
/// </summary>
/// <returns>Animation</returns>
const Animation* AnimationPlayer::GetLightOn_Next()
{
	uint8_t sin = pgm_read_byte(&sinus[sinIndex]);
	//uint8_t sin = sinus[sinIndex];
	PixelColor *pixel = NULL;

	// Update every pixel
	for (uint8_t index = 0; index < LED_STRIPE_NUMLED; index++)
	{
		pixel = &currentAnnimation.animationStep->Pixels[index];
		pixel->Red = stepOn1.Pixels[index].Red + (min(255 - stepOn1.Pixels[index].Red, sin) * 0.25);
		pixel->Green = stepOn1.Pixels[index].Green + min(255 - stepOn1.Pixels[index].Green, sin);
		//pixel->Blue = stepOn1.Pixels[index].Blue + min(255 - stepOn1.Pixels[index].Blue, sin);
	}

	//	
	sinIndex = ++sinIndex % SIN_MAX_INDEX;

	return &currentAnnimation;
}

/// <summary>
/// Light Off for accessor
/// </summary>
/// <returns>Animation</returns>
const Animation* AnimationPlayer::GetLightOff()
{
	return &animationOff;
}
