# MusicEmittingSuitcase
In this respository, you can find all the files I used to build up the MES. 
You can also find the code of the LES, the first Prototype without sounds. 

The code of the MES is processed by an Arduino Mega that communicates with a WAV trigger from Sparkfun to produce sound. The WAV trigger is available here: https://www.sparkfun.com/products/13660

In the folder "Sounds" are the sounds used in the introduction video of the MES, correctly formatted for use with the WAV trigger. 
In the folder "Libraries" you can find the libraries the code uses, one for communication with the LED strip and one for the WAV trigger. To enable Serial communication, the library of the WAV trigger was slightly changed to be able to use Serial Port 1 on the Arduino Mega.
The folder "LES" simply contains the code of the previous version of the MES and is not important in this case, just for the sake of completeness...

If you use the code of the Arduino, keep in mind that I manually built in physical pullup-resistors for the switches, the internal pullups of the Arduino are not activated through the sketch. 
