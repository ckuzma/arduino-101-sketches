# arduino-101-sketches
![Arduino 101 with onboard LED blinking.](https://github.com/ckuzma/arduino-101-sketches/blob/master/photos/tapflash.gif)

## Description
A collection of sketches written specifically for the Arduino 101, taking advantage of the [Intel Curie](http://www.intel.com/content/www/us/en/wearables/wearable-soc.html)'s accelerometers and gyroscopes.

## Sketches
### [TapFlashTest](https://github.com/ckuzma/arduino-101-sketches/blob/master/sketches/TapFlashTest/TapFlashTest.ino)
The first test sketch written specifically for the Arduino 101. When a tap is detected, the onboard LED blinks.

### [TapBeatMatch](https://github.com/ckuzma/arduino-101-sketches/blob/master/sketches/TapBeatMatch/TapBeatMatch.ino)
![Arduino 101 matching tap tempo.](https://github.com/ckuzma/arduino-101-sketches/blob/master/photos/tempo.gif)

Synchronizes the flashing of lights to the beat of taps. Set the Arduino 101 on a table, wait for it to start its initial blink, then tap the table to a steady tempo for a few seconds. Stop tapping and the built-in LED will continue flashing at the same rate as your taps.

### [SeismicReader](https://github.com/ckuzma/arduino-101-sketches/blob/master/sketches/SeismicReader/SeismicReader.ino) + [Python visualizer](https://github.com/ckuzma/arduino-101-sketches/blob/master/python/CurieGraph.py)
![Graphed data from Arduino 101.](https://github.com/ckuzma/arduino-101-sketches/blob/master/photos/graphed_data.png)

Makes use of the Curie module's 6-axis motion detection in order to identify seismic activity. Python script connects to the Arduino via USB to plot the data in real time and also saves readings to CSV for later analysis.

### [VibrationLighting](https://github.com/ckuzma/arduino-101-sketches/blob/master/sketches/VibrationLighting/VibrationLighting.ino)
![Double-tap Arduino 101 video.](https://github.com/ckuzma/arduino-101-sketches/blob/master/photos/double-tap.gif)

Originally designed to detect approaching footsteps and turn on power when someone is nearby, this was changed to detect double-taps instead because of a poor signal-to-noise ratio.

## Contest Acknowledgement
I was provided a Arduino 101 development board as part of [my project submission](https://www.hackster.io/kuzma/motion-sensitive-circuit-control-via-intel-curie-b6db0a) for the [*Arduino 101 - Invent Your Future!*](https://www.hackster.io/contests/Intel-Arduino-101) contest on [Hackster.io](https://www.hackster.io/). These sketches are being written as part of my project submission.
