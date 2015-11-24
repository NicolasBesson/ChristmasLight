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

#ifndef _MAINAPP_H
#define _MAINAPP_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Adafruit_NeoPixel.h"
#include "Timer.h"
#include "Button.h"
#include "Stripes.h"

// LED Stripes configuration
// See Stripes.h

// Buttons configuration
#define BUTTON_ACTION_PIN				2

#define BUTTON_DEBOUNCE_TIMEOUT			10
#define BUTTON_STATE_TIMEOUT			200
#define BUTTON_HOLD_TIMEOUT				(1 * 1000)

// Scenes timer index
#define SCENE_TIMER_STRIPES			0

class MainAppClass
{
private:
	// Front LED Stripe
	Adafruit_NeoPixel ledLight		= Adafruit_NeoPixel(LED_STRIPE_NUMLED,		LED_STRIPE_PIN,		NEO_GRB + NEO_KHZ800);

	// Action Button
	Button actionButton = Button(BUTTON_ACTION_PIN, BUTTON_DEBOUNCE_TIMEOUT, BUTTON_HOLD_TIMEOUT, BUTTON_STATE_TIMEOUT, BUTTON_PULLUP);
		
	// Time list
	Timer appTimer = Timer();

public:
	/// <summary>
	/// Main application intialization
	/// </summary>
	void init();

	/// <summary>
	/// Main application loop
	/// </summary>
	void loop();

	/// <summary>
	/// Load next Scene step
	/// </summary>
	static void loadSceneCallback();
};

extern MainAppClass MainApp;

#endif // _MAINAPP_H
