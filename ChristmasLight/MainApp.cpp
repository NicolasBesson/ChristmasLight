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

#include "MainApp.h"
#include "SceneManager.h"

MainAppClass MainApp;

/// <summary>
/// Front Timer callback function
/// </summary>
void loadScene_callback()
{
	MainApp.loadSceneCallback();
}

/// <summary>
/// Main application intialization
/// </summary>
void MainAppClass::init()
{
	// Initialize the LED Stripe	
	ledLight.begin();

	// Initialize the timer
	appTimer.configureTimer(SCENE_TIMER_STRIPES, 2 * 1000, loadScene_callback);

	// Clear the LED Stripe
	ledLight.show();
}

/// <summary>
/// Main application loop
/// </summary>
void MainAppClass::loop()
{
	// Update the button state
	ButtonState actionButtonState = actionButton.getButtonState();

	// Update the scene based on button state
	SceneManager.updateScene(actionButtonState);

	// Reset short press state
	actionButton.clearButtonState();

	// Handle scene updates
	// Updates occurs on Timer elapsed and call to updateScene
	if (SceneManager.isSceneUpdated() == true)
	{
		// update the timer for current step duration
		appTimer.updateTimer(SCENE_TIMER_STRIPES, SceneManager.getSceneStepDuration());
	
		// Update the LED Stripe
		SceneManager.updateStripes(&ledLight);

		// Display the LED Stripe
		ledLight.show();
	}

	// Update time info
	appTimer.run();
}

/// <summary>
/// Load next Front Scene step
/// </summary>
inline void MainAppClass::loadSceneCallback()
{
	SceneManager.nextSceneStep();
}
