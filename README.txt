This simple square wave generator utilizes cross platform audio library PortAudio.
More information and tutorials are available at www.portaudio.com. This code was
adapted from the paex_saw.c example available on the website and included  the zip
download under portaudio/examples/paex_saw.c.

Super Simple Squarewaves will output a simple square wave, and portaudio will handle
using the native api of your OS to play it on your speakers as well as output a simple
and crude visualization of the wave via standard output to the terminal.
_____-----_____-----_____-----           ___ = LOW   --- = HIGH

In order to alter the frequency/pitch of the square wave change the variable
cycle_count located in the pa_testCallback function.

A lower value will result in a higher frequency - A higher value will result in a lower frequency

cycle_count = 10 (low frequency)
__________----------__________


cycle_count = 5
_____-----_____-----_____


cycle_count = 1 (high frequency)
_-_-_-_-_-_-_-_-




 Using Port Audio (from port audio website)
  **download and install portaudio
    *Write a callback function that will be called by PortAudio when audio processing is needed.
    *Initialize the PA library and open a stream for audio I/O.
    *Start the stream. Your callback function will be now be called repeatedly by PA in the background.
    *In your callback you can read audio data from the inputBuffer and/or write data to the outputBuffer.
    *Stop the stream by returning 1 from your callback, or by calling a stop function.
    *Close the stream and terminate the library.


Compiling for Ubuntu

g++ superSimpleSquareWaves.cpp -o SuperSimpleSquare libportaudio.a -ljack -lpthread -lasound -lm

portaudio.com has instructions for compiling for other OS.

I am new to audio programming and would love any input and/or suggestions.

    Happy coding!

-Nick Benoit May 7, 2015
nick.benoit14@gmail.com
