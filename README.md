# MusicEmittingSuitcase
In this respository, you can find all the files I used to build up the MES. 
You can also find the code of the LES, the first Prototype without sounds. 

The code of the MES is processed by an Arduino Mega that communicates with a WAV trigger from Sparkfun to produce sound. 

In the folder "Sounds" are the sounds used in the introduction video of the MES, correctly formatted to use on the WAV trigger. 
In the folder "Libraries" you can find the libraries the code uses, one for communication with the LED strip and one for the WAV trigger. To enable Serial communication, the library of the WAV trigger was slightly changed to be able to use Serial Port 1 on the Arduino Mega. 
