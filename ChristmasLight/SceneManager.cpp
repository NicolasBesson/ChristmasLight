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

#include "SceneManager.h"

// For scene animation step update indicator
#define SCENE_LED			0

/// <summary>
/// Initialize the SceneManager
/// </summary>
void SceneManagerClass::init()
{
	// Clear Original status
	sceneStatus = 0;

	// Default state
	currentState = STATE_UNDEFINED;
}

/// <summary>
/// Check for Front scene update
/// </summary>
/// <returns>true for update</returns>
bool SceneManagerClass::isSceneUpdated()
{
	if (bitRead(sceneStatus, SCENE_LED))
	{
		bitWrite(sceneStatus, SCENE_LED, false);
		return true;
	}
	
	return false;
}

/// <summary>
/// Retrieve the next step
/// </summary>
void SceneManagerClass::nextSceneStep()
{
	if (currentState == STATE_LIGHT_ON)
	{
		ledAnimation = AnimationPlayer::GetLightOn_Next();
	}
	else
	{
		ledAnimation = ledAnimation->nextAnimation;
	}
	bitWrite(sceneStatus, SCENE_LED, true);
}

/// <summary>
/// Retrieve the scene duration
/// </summary>
/// <returns>Scene duration in milliseconds</returns>
unsigned long SceneManagerClass::getSceneStepDuration() const
{
	return ledAnimation->animationStep->StepDuration;
}

/// <summary>
/// Update the LED Stripes based on the current scene
/// </summary>
/// <param name="ledStripe">LED stripe</param>
void SceneManagerClass::updateStripes(Adafruit_NeoPixel *ledStripe)
{
	PixelColor *pixel;

	// Update the pixels color
	for (uint8_t index = 0; index < LED_STRIPE_NUMLED; index++)
	{
		pixel = &ledAnimation->animationStep->Pixels[index];
		ledStripe->setPixelColor(index, pixel->Red, pixel->Green, pixel->Blue);
	}
}

/// <summary>
/// Light ON Scene
/// </summary>
inline void SceneManagerClass::LightOn()
{
	ledAnimation = AnimationPlayer::GetLightOn();

	bitWrite(sceneStatus, SCENE_LED, true);

}

/// <summary>
/// Light OFF Scene
/// </summary>
inline void SceneManagerClass::LightOff()
{
	ledAnimation = AnimationPlayer::GetLightOff();

	bitWrite(sceneStatus, SCENE_LED, true);
}

/// <summary>
/// Update the Scene based on button ButtonState
/// </summary>
/// <param name="actionButton">Action Button current state</param>
void SceneManagerClass::updateScene(ButtonState actionButton)
{
	// Check transition candidates based on the Button pressed
	switch (currentState)
	{
	case STATE_UNDEFINED:
		newState = STATE_LIGHT_ON;
		break;

	case STATE_LIGHT_OFF:
		if (actionButton == SHORT_PRESSURE)
		{
			newState = STATE_LIGHT_ON;
		}
		break;

	case STATE_LIGHT_ON:
		if (actionButton == SHORT_PRESSURE)
		{
			newState = STATE_LIGHT_OFF;
		}
		break;

	}

	// Stay in current state nothing else to do
	if (currentState == newState) 
	{
		return;
	}

	// Switch to that state
	switch (newState)
	{
	case STATE_LIGHT_OFF:
		LightOff();
		break;

	case STATE_LIGHT_ON:
		LightOn();
		break;
	}

	currentState = newState;
}

/// <summary>
/// Scene Manager
/// </summary>
SceneManagerClass SceneManager;
