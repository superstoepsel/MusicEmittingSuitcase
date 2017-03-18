/* This is the code for the MES, the Music Emitting Suitcase. As the internal PULLUPs of my Arduino Mega did not work well, 
 * I had to manually build in PULLUP resistors to get a stable signal.  
 */
//include NeoPixel library
#include <Adafruit_NeoPixel.h>
#include <wavTrigger.h> //I altered the file so that I can use the hardware Serial Port 1 on the Arduino Mega. This makes including the AltSoftSerial library redundant.

//define LED Data: Which PIN, how many LEDs
const int LEDstrip_pin = A7;
const int NUMPIXELS = 40;

//create a to-dimensional adressing matrix for later use
int LEDmatrix[8][5] = 
{
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
uint32_t white = LEDstrip.Color(255,255,100);
uint32_t green = LEDstrip.Color(0,255,0);
uint32_t red = LEDstrip.Color(255,0,0);
uint32_t blue = LEDstrip.Color(0,0,255);
uint32_t orange = LEDstrip.Color(255,100,0);
uint32_t yellow = LEDstrip.Color(255,200,0);
uint32_t purple = LEDstrip.Color(255,0,255);
uint32_t nothing = LEDstrip.Color(0,0,0);

//define Button Pins in a two-dimensional matrix for later use
int ButtonMatrix [8][5] = 
{
  {8,7,6,5,4},  
  {3,2,14,15,16}, 
  {17,11,10,20,21},
  {22,23,24,25,26},
  {27,28,29,30,31},
  {32,33,34,35,36},
  {37,38,39,40,41},
  {42,43,44,45,46},
};


//define potentiometer pin
int potPin = A8;

//initialize the wavTrigger object
wavTrigger wTrig; 


void setup() 
{
 //declare In- and Outputs
  for(int r = 0; r < 8; r++)
  {
    for (int c=0; c<5; c++)
    {
      pinMode (ButtonMatrix[r][c], INPUT);
    }
  }
  
  pinMode (potPin, INPUT);
  pinMode (LEDstrip_pin, OUTPUT);
  
  //initialize LED strip as Neopixel outputs
  LEDstrip.begin();
  LEDstrip.show();
  
  //set Brightness of LEDs to 1/3
  LEDstrip.setBrightness(100);
  
  //initialize serial communication with the WAV trigger
  wTrig.start();
}


void loop() 
{
  //read the value of the potentiometer to determine speed of the beat line every lap  
  int delayval = analogRead(potPin);
  
  //light up row after row 
  for(int r = 0; r < 8; r++)
  {
    buttoncheck(); //check for pressed buttons (balls), light up respective leds
    for (int c=0; c<5; c++) 
    {
      if( digitalRead( ButtonMatrix[r][c] ) == HIGH )
      {
        LEDstrip.setPixelColor(LEDmatrix[r][c], green); //light every non-pressed switch in row in green
      }
      
    }
    
    LEDstrip.show();  
    playsounds(r); //play 
    delay(delayval);
  
    //switch off LED 0-4, check switches, light up LED 5-9
    for (int c=4; c>=0; c--)
    {
      if( digitalRead( ButtonMatrix[r][c] ) == HIGH )
      {
        LEDstrip.setPixelColor(LEDmatrix[r][c], nothing); //switch off every non-pressed led in row
      }
    } 
    LEDstrip.show();  
  }
}


//function for checking if switches are pressed and enlight the respective LED in the right color of the column in the grid.
void buttoncheck()
{ 
  //checking the first column for pressed switches and set the respective LEDs to blue  
  uint32_t color;
  for(int c=0;c<5;c++)
  {
    for(int r=0;r<8;r++)
    {
      if(c==0)
      {
        color = blue;
      }else if(c==1)
      {
        color = purple;
      }else if(c==2)
      {
        color = red;
      }else if(c==3)
      {
        color = orange;
      }else if(c==4)
      {
        color = yellow;
      }
      
      if(digitalRead(ButtonMatrix[r][c]) == LOW)
      {
        LEDstrip.setPixelColor(LEDmatrix[r][c], color);
        LEDstrip.show();
      } else 
      {
        LEDstrip.setPixelColor(LEDmatrix[r][c], nothing);
        LEDstrip.show();
      }
   }    
  }
 
}

//function for playing the sounds in the right time and turning the respective LED white
void playsounds(int nextBeat)
{ 
  int TrackNumber [5] = {1,2,3,4,5}; // list of the Track numbers for every column
  for (int c=0;c<5;c++)
  {
    for(int r=0;r<8;r++)
    {
      if (r == nextBeat)
      {
        if(digitalRead(ButtonMatrix[r][c]) == LOW )
        {
          wTrig.trackPlayPoly (TrackNumber[c]);
          LEDstrip.setPixelColor(LEDmatrix [r][c], white);
          LEDstrip.show();
        }
      }
    }
  }
}
