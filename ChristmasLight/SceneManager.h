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

#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Adafruit_NeoPixel.h"
#include "Button.h"
#include "AnimationPlayer.h"

/// <summary>
/// Scene Manager State Machine states
/// </summary>
enum SceneState : uint8_t
{
	STATE_LIGHT_OFF = 0,				// Light OFF
	STATE_LIGHT_ON = 10,				// Light ON
	STATE_UNDEFINED = 255				// Undefined state
};

/// <summary>
/// Scene Manager
/// </summary>
class SceneManagerClass
{
 private:
	 enum SceneState currentState = STATE_UNDEFINED;	// Current State
	 enum SceneState newState = STATE_UNDEFINED;		// New Reached State
	 unsigned long timerStart = 0;						// Timer
	 unsigned long timerDuration = 0;					// Timer Duration
	 unsigned long longPressTimerStart = 0;				// Long pressure Timer
	 unsigned long longPressDebounceTimerDuration = 0;	// Long pressure Timer Duration
	 uint8_t sceneStatus = 0;								// Internal Scene status for stripes updates detections

	 const Animation *ledAnimation = NULL;		// Front animation
	 
 public:
	 /// <summary>
	 /// Initialize the SceneManager
	 /// </summary>
	void init();

	/// <summary>
	/// Update the Scene based on button ButtonState
	/// </summary>
	/// <param name="actionButton">Action Button current state</param>
	void updateScene(ButtonState actionButton);
	
	/// <summary>
	/// Check for scene update
	/// </summary>
	/// <returns>true for update</returns>
	bool isSceneUpdated();
	
	/// <summary>
	/// Retrieve the next step
	/// </summary>
	void nextSceneStep();
	
	/// <summary>
	/// Retrieve the scene duration
	/// </summary>
	/// <returns>Scene duration in milliseconds</returns>
	unsigned long getSceneStepDuration() const;

	/// <summary>
	/// Update the LED Stripe based on the current scene
	/// </summary>
	/// <param name="ledStripe">Front LED stripe</param>
	void updateStripes(Adafruit_NeoPixel *ledStripe);

 private:
	/// <summary>
	/// Light ON Scene
	/// </summary>
	void LightOn();
	
	/// <summary>
	/// Light OFF Scene
	/// </summary>
	void LightOff();
};

extern SceneManagerClass SceneManager;

#endif // _SCENEMANAGER_H
