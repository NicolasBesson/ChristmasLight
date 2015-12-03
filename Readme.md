# Introduction
The Christmas Lightning project is a low cost solution based on an ATTiny 85 Micro Controller and Neopixel that can be used to add some lightning to any Christmas element. The project implement a glowing effect that simulate the light of a standard candle.

The original target Christmas element is a Christmas creche, but any other usage is possible. Leave me a message on the usage your are targeting.

# Before you start
Before you start, you have to ensure that you have enough knowledge on the way to read an electronic schematic, build hardware and program an ATTiny Micro Controller.

Also note that the current gloving effect can probably more realistic, by implementing a more complex and randomized algorithm, but the provided implementation is fitting the ambiance target for this project.

# Building the hardware
The hardware is minimalistic as the Neopixel and ATTiny are embedding all the discrete that you normally use to driver RGB LED.

![Christmas light schematic](/Hardware/ChristmasLight_schéma.png)

The device is powered by an external 5V power supply (J-Power) that needs to be adjusted depending on the number of pixels that need to be driven. The project uses 6 Neopixel devices (J-LEDStripe) that are chained together (originally from the same LED stripe) It is usual, when driving Neopixels, to estimate the total maximum required current to use a 60 mA current required per LED (data from Neopixel controller for a full bright White color). So for a total of 6 devices, you need a minimum of 360 mA (6 x 60 mA) on 5V.

The user can interact with the lightning system, using a switch button (J-Action) in order to switch to a different lightning mode, see Building the software paragraph for details. Connecting this switch is optional as the default mode enabled when the device starts is the candle mode.

You won't find any PCB layout, as I'm using through hole prototyping board, developed under Fritzing software.

![Christmas light through hole prototyping board](/Hardware/ChristmasLight_bb.png)

So the required parts to build you own are:

* ATTiny85
* 2 x 10 kOhms resistors
* 1 x 380 Ohms resistor
* 2 x 1 000 µF capacitors
* 1 x 10 µF capacitor
* 6 x Neopixels
* 1 x switch button (optional)
* 1 x 5V 500mA power supply

![Christmas light mounted](/Hardware/ChristmasLight_mounted.jpg)

# Building the software
The ATTiny 85 is a really cool Micro Controller that have 8 K of Flash and 512 B of RAM to run any kind of C or C++ software. This gives some space to run a simple software and for this reason some optimization are required.

The project has been developed in C++ in order to reuse and give more flexibility in case of development of new features.

AdaFruit is providing a library to driver the Neopixel devices, that you can directly integrate in your Arduino IDE. But this code has been designed to support various mode in order to address major use cases. The source code repository is containing an optimized version that works only with the Neopixels that I have selected and might not work if you choose a different one.

The Neopixel device requires specific timer that can't be reach when using the ATTiny 85 in 4 Mhz (its default configuration) and therefore requires to use the 8 Mhz mode. So it is mandatory to burn the correct fuses in the ATTIny before deploying the firmware. This can be done from the Arduino IDE by selecting the ATTiny 85 target and selecting the clock frequency to 8 Mhz (internal).

The hardware push button (J-Action), is optional but allows you to switch between the modes of the system, and for now only two modes are implemented, the candle light effect, and the off state (no light). But is really easy to add more mode if required by modifying the SceneManagerClass::updateScene function. Short and long button pressure can be detected and used in the state machine to trigger state transitions.

Check out the Candle effect testing video : [Christmas Light Candle Effect](https://www.youtube.com/watch?v=YgP5hc2EMMU)
