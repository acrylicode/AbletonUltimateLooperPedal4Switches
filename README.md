If you have an arduino pro micro and 4 footswitches, this repo is for you.

Clone the repo, open the .ino file in the Arduino IDE, upload the sketch (you might need to install the Liquid_crystal_I2C library if you want to use the screen)

Select in the "Tool" > "board" > "Arduino Leonardo"
Then select the right port in "Tool" > "port"

Once the sketch is uploaded open Ableton.

Step 1:

Configure the Arduino Leonardo as MIDI input in "Live" > "Preferences" > "MIDI" > "Input: Arduino Leonardo" > On On On

Step 2:

Configure Exclusive Arm. "Live" > "Preferences" > "Record" > "Exclusive" > "Arm"

Step 3:

Create 4 audio tracks and add a Looper Device to each Track

Step 4: 

Map the midi signals for arming and selecting each track (same signal to arm and select track)
That means for the first track CMD + M , select the "Arm" Button (Red record button in the track) and hold the first pedal switch. On release the arm button should be mapped, we want to map this same signal to select the first track, then CMD + M and click on the Track name and then hold again the first button. 

Repeat the process for each track

Step 5:

Map all looper buttons for each track.

Hold the first pedal button, (this should select and arm the first track) , you should see the looper device, then map the buttons with single click however you like
Repeat for all tracks 

Done

Optional:

This code also send midi notes for double clicks for each channel, you may use this for activating drums or vst effects.
Enjoy 
