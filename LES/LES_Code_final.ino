//This is a first draft of the program for my Music Table. 
//Because of technical Limitations of the Hardware (Music Shield and its poorly documented libraries),
//it isn´t able to play sounds. 
//I tried to activate the internal PULLUP for my switches, but some Pins on the Arduino board din´t work with it, 
//so I had to manually build in PULLUP resistors to get a stable signal.

//include NeoPixel library
#include <Adafruit_NeoPixel.h>

//define LED Data: Which PIN, how many LEDs
const int LEDstrip_pin = A7;

const int NUMPIXELS = 40;

//create a to-dimensional adressing matrix for later use
int LEDmatrix[8][5] = {
    {4,3,2,1,0},      //The LEDstring is put into the suitcase in snake format, so to address the right row, LED numbers had to be adjusted.
    {5,6,7,8,9},
    {14,13,12,11,10},
    {15,16,17,18,19},
    {24,23,22,21,20},
    {25,26,27,28,29},
    {34,33,32,31,30},
    {35,36,37,38,39},
  };

//initialize NeoPixel string
Adafruit_NeoPixel LEDstrip = Adafruit_NeoPixel(NUMPIXELS, LEDstrip_pin, NEO_GRB + NEO_KHZ800);

//set up colors for later use
uint32_t white = LEDstrip.Color(255,255,255);
uint32_t green = LEDstrip.Color(0,255,0);
uint32_t red = LEDstrip.Color(255,0,0);
uint32_t blue = LEDstrip.Color(0,0,255);
uint32_t orange = LEDstrip.Color(255,100,0);
uint32_t yellow = LEDstrip.Color(255,200,50);
uint32_t purple = LEDstrip.Color(255,0,255);
uint32_t nothing = LEDstrip.Color(0,0,0);

//define Button Pins in a two-dimensional matrix for later use
int ButtonMatrix [8][5] = {
  {2,42,43,44,45},  //pin numbers are that strange due to the pins the music shield used (it is still sitting on the Arduino, though it is not used).
  {46,47,9,48,49},
  {52,53,14,15,16},
  {17,18,19,20,21},
  {22,23,24,25,26},
  {27,28,29,30,31},
  {32,33,34,35,36},
  {37,38,39,40,41},
};

//define potentiometer pin
int potPin = A8;

//define other variables
int delayval = analogRead(potPin);
int r; //value to reach the right switch row
int c; //variable to reach the right switch column
int i; //variable to reacht the right LEDs


void setup() {
//define Buttons and potentiometer as Inputs
pinMode (ButtonMatrix[8][5], INPUT);
pinMode (potPin, INPUT);

//initialize LED strip as Neopixel outputs
LEDstrip.begin();
LEDstrip.show();

//set Brightness of LEDs to 1/3
LEDstrip.setBrightness(100);
}


void loop() {
//read the value of the potentiometer to determine speed of the beat line every lap  
  delayval = analogRead(potPin);
  
//check if switches are pressed
  buttoncheck();
  
//light up LED 0-4
    for (i=0; i<5; i++){
      LEDstrip.setPixelColor(i, green);
      LEDstrip.show();
      }   
//wait adjusted time (beat)
  delay(delayval);
  
//switch off LED 0-4, check switches, light up LED 5-9
    for (i=4; i>=0; i--){
        LEDstrip.setPixelColor(i, nothing);
        LEDstrip.show();
      } 
  buttoncheck();
    for (i=5; i<10; i++){
      LEDstrip.setPixelColor(i, green);
      LEDstrip.show();
      } 
  
//wait adjusted time (beat)
  delay(delayval);
  
//switch off LED 5-9, check switches, light up LED6-14
    for (i=9; i>=5; i--){
      LEDstrip.setPixelColor(i, nothing);
      LEDstrip.show();
      } 
  buttoncheck();
    for (i=10; i<15; i++){
      LEDstrip.setPixelColor(i, green);
      LEDstrip.show();
      }  
  
//wait adjusted time (beat)
  delay(delayval);
  
//switch off LED 10-14, check switches, light up LED15-19
    for (i=14; i>=10; i--){
      LEDstrip.setPixelColor(i, nothing);
      LEDstrip.show();
      } 
  buttoncheck();
    for (i=15; i<20; i++){
      LEDstrip.setPixelColor(i, green);
      LEDstrip.show();
      }  
  
//wait adjusted time (beat)
  delay(delayval);
  
//switch off LED 15-19, check switches, light up LED 20-24
    for (i=19; i>=15; i--){
      LEDstrip.setPixelColor(i, nothing);
      LEDstrip.show();
      } 
  buttoncheck();
    for (i=20; i<25; i++){
      LEDstrip.setPixelColor(i, green);
      LEDstrip.show();
      }  
  
//wait adjusted time (beat)
  delay(delayval);
  
//switch off LED 20-24, check switches, light up LED25-29
    for (i=24; i>=20; i--){
      LEDstrip.setPixelColor(i, nothing);
      LEDstrip.show();
      } 
  buttoncheck();
    for (i=25; i<30; i++){
      LEDstrip.setPixelColor(i, green);
      LEDstrip.show();
      }  
  
//wait adjusted time (beat)
  delay(delayval);
  
//switch off LED 25-29, check switches, light up LED 30-34
    for (i=29; i>=25; i--){
      LEDstrip.setPixelColor(i, nothing);
      LEDstrip.show();
      } 
  buttoncheck();
    for (i=30; i<35; i++){
      LEDstrip.setPixelColor(i, green);
      LEDstrip.show();
      }  
  
//wait adjusted time (beat)
  delay(delayval);
  
//switch off LED 30-34, check switches, light up LED 35-39
    for (i=34; i>=30; i--){
      LEDstrip.setPixelColor(i, nothing);
      LEDstrip.show();
      } 
  buttoncheck();
    for (i=35; i<40; i++){
      LEDstrip.setPixelColor(i, green);
      LEDstrip.show();
      }  
  
//wait adjusted time (beat)
  delay(delayval);
  
//switch off LED 35-39, check switches
    for (i=4; i>=0; i--){
      LEDstrip.setPixelColor(i, nothing);
      LEDstrip.show();
      } 
  buttoncheck(); 
}


//function for checking if switches are pressed and enlight the respective LED in the right color of the column in the grid.
void buttoncheck(){ 

//checking the first column for pressed switches and set the respective LEDs to blue  
  c=0;
  for(r=0;r<8;r++){
    if(digitalRead(ButtonMatrix[r][c]) == LOW){
      LEDstrip.setPixelColor(LEDmatrix[r][c], blue);
      LEDstrip.show();
      } else {
        LEDstrip.setPixelColor(LEDmatrix[r][c], nothing);
        LEDstrip.show();
      }
  }
  
//checking the second column for pressed switches and set the respective LEDs to purple  
  c=1;
  for(r=0;r<8;r++){
    if(digitalRead(ButtonMatrix[r][c]) == LOW ){
      LEDstrip.setPixelColor(LEDmatrix[r][c], purple);
      LEDstrip.show();
      }
      else{
        LEDstrip.setPixelColor(LEDmatrix[r][c], nothing);
        LEDstrip.show();
      }
  }

//checking the third column for pressed switches and set the respective LEDs to red    
  c=2;
  for(r=0;r<8;r++){
    if(digitalRead(ButtonMatrix[r][c]) == LOW ){
      LEDstrip.setPixelColor(LEDmatrix[r][c], red);
      LEDstrip.show();
      }
      else{
        LEDstrip.setPixelColor(LEDmatrix[r][c], nothing);
        LEDstrip.show();
      }
  }

//checking the fourth column for pressed switches and set the respective LEDs to orange  
 c=3;
  for(r=0;r<8;r++){
    if(digitalRead(ButtonMatrix[r][c]) == LOW ){
      LEDstrip.setPixelColor(LEDmatrix[r][c], orange);
      LEDstrip.show();
      }
      else{
        LEDstrip.setPixelColor(LEDmatrix[r][c], nothing);
        LEDstrip.show();
      }
  }

//checking the fifth column for pressed switches and set the respective LEDs to yellow  
  c=4;
  for(r=0;r<8;r++){
    if(digitalRead(ButtonMatrix[r][c]) == LOW ){
      LEDstrip.setPixelColor(LEDmatrix[r][c], yellow);
      LEDstrip.show();
     }
      else{
        LEDstrip.setPixelColor(LEDmatrix[r][c], nothing);
        LEDstrip.show();
      }
  }
  
  }



