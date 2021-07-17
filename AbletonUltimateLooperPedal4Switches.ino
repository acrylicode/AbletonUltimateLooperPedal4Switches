#include "ButtonV2.h"
#include "MIDIUSB.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
// Usage Line 0 is first line , Line 1 is second. Set cursor(0,0) means put the cursor in the first line in the first character
//clearLine(0);
//lcd.setCursor(0,0);
//lcd.print("Single click pressed");


ButtonV2 button1;
ButtonV2 button2;
ButtonV2 button3;
ButtonV2 button4;

const byte button1Pin = 8;
String previousbutton1State = "";

const byte button2Pin = 7;
String previousbutton2State = "";

const byte button3Pin = 6;
String previousbutton3State = "";

const byte button4Pin = 5;
String previousbutton4State = "";

// ARRAYS FOR ABLETON, EACH BUTTON HAS AN ARRAY OF 4 different notes
int notesButton1[] = { 59, 60, 61, 62};
int notesButton2[] = { 63, 64, 65, 66};
int notesButton3[] = { 67, 68, 69, 70};
int notesButton4[] = { 71, 72, 73, 74};

int notesButton1DoubleClick[] = { 79, 80, 81, 82};
int notesButton2DoubleClick[] = { 83, 84, 85, 86};
int notesButton3DoubleClick[] = { 87, 88, 89, 90};
int notesButton4DoubleClick[] = { 91, 92, 93, 94};

int armTracksNotes[] = {75, 76, 77, 78}; // when each channel is activated the corresponding note of this array is sent

byte channelIndex = 0;


void setup()
{
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
  Serial.begin(115200);

  lcd.init();                      
  lcd.backlight();
  
  button1.SetStateAndTime(LOW, 600);
  button2.SetStateAndTime(LOW, 600);
  button3.SetStateAndTime(LOW, 600);
  button4.SetStateAndTime(LOW, 600);
}

void loop()
{
  evaluateAbletonButton1();
  evaluateAbletonButton2();
  evaluateAbletonButton3();
  evaluateAbletonButton4();
}

// ABLETON FUNC

void evaluateAbletonButton1(){
  byte button1ResponseType = button1.CheckButton(button1Pin); // current time and length of time to press the button as many times as you can ie. 1.5 seconds
  String currentStatebutton1State = "";
  int noteToSendSingleClick = notesButton1[channelIndex];
  int noteToSendDoubleClick = notesButton1DoubleClick[channelIndex];
  switch (button1ResponseType)
  {
    case PRESSED:
      sendNote(noteToSendSingleClick);
      break;
    case DOUBLE_PRESSED:
      sendNote(noteToSendDoubleClick);
      break;
     case MULTI_PRESSED :
      sendNote(noteToSendDoubleClick);
      break;
    case HELD:
      previousbutton1State = "HELD";
      currentStatebutton1State = "HELD";
      break;
     default:
      break;
  }
  if(currentStatebutton1State == "" && previousbutton1State == "HELD"){
    // On release button 1
    previousbutton1State = "";
    setChannelIndexAndSendArmTrackNote(0);
  } 
}

void evaluateAbletonButton2(){
  byte button2ResponseType = button2.CheckButton(button2Pin); // current time and length of time to press the button as many times as you can ie. 1.5 seconds
  String currentStatebutton2State = "";
  int noteToSendSingleClick = notesButton2[channelIndex];
  int noteToSendDoubleClick = notesButton2DoubleClick[channelIndex];
  switch (button2ResponseType)
  {
     case PRESSED:
      sendNote(noteToSendSingleClick);
      break;
    case DOUBLE_PRESSED:
      sendNote(noteToSendDoubleClick);
      break;
     case MULTI_PRESSED :
      sendNote(noteToSendDoubleClick);
      break;
    case HELD:
      previousbutton2State = "HELD";
      currentStatebutton2State = "HELD";
      break;
     default:
      break;
  }
  if(currentStatebutton2State == "" && previousbutton2State == "HELD"){
    // On release button 2
    previousbutton2State = "";
    setChannelIndexAndSendArmTrackNote(1);
  } 
}

void evaluateAbletonButton3(){
  byte button3ResponseType = button3.CheckButton(button3Pin); // current time and length of time to press the button as many times as you can ie. 1.5 seconds
  String currentStatebutton3State = "";
  int noteToSendSingleClick = notesButton3[channelIndex];
  int noteToSendDoubleClick = notesButton3DoubleClick[channelIndex];
  switch (button3ResponseType)
  {
    case PRESSED:
      sendNote(noteToSendSingleClick);
      break;
    case DOUBLE_PRESSED:
      sendNote(noteToSendDoubleClick);
      break;
     case MULTI_PRESSED :
      sendNote(noteToSendDoubleClick);
      break;
     case HELD:
      previousbutton3State = "HELD";
      currentStatebutton3State = "HELD";
      break;
     default:
      break;
  }

  if(currentStatebutton3State == "" && previousbutton3State == "HELD"){
    // On release button 1
    previousbutton3State = "";
    setChannelIndexAndSendArmTrackNote(2);
  } 
}

void evaluateAbletonButton4(){
  byte button4ResponseType = button4.CheckButton(button4Pin); // current time and length of time to press the button as many times as you can ie. 1.5 seconds
  String currentStatebutton4State = "";
  int noteToSendSingleClick = notesButton4[channelIndex];
  int noteToSendDoubleClick = notesButton4DoubleClick[channelIndex];
  switch (button4ResponseType)
  {
    case PRESSED:
      sendNote(noteToSendSingleClick);
      break;
    case DOUBLE_PRESSED:
      sendNote(noteToSendDoubleClick);
      break;
     case MULTI_PRESSED :
      sendNote(noteToSendDoubleClick);
      break;
     case HELD:
      previousbutton4State = "HELD";
      currentStatebutton4State = "HELD";
      break;
     default:
      break;
  }

  if(currentStatebutton4State == "" && previousbutton4State == "HELD"){
    // On release button 4
    previousbutton4State = "";

    setChannelIndexAndSendArmTrackNote(3);
  } 
  
}

void clearLine(int index){
  lcd.setCursor(0, index);
  lcd.print("                ");
}

void setChannelIndexAndSendArmTrackNote(byte newChannelIndex){
   channelIndex = newChannelIndex;
   byte armTrackNote = armTracksNotes[channelIndex];
   sendNote(armTrackNote);
}

void sendNote(byte noteToSend){
   noteOn(0, noteToSend, 64);
   delay(1);
   noteOff(0, noteToSend, 64);
}

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

// Example Channel 0, middle C, normal velocity
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
  //Serial.println("Pitch On : " + effectNames[index] + " , pitch " + String(effectPitches[index]));
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
  //Serial.println("Pitch Off : " + effectNames[index] + " , pitch " + String(effectPitches[index]));
}
