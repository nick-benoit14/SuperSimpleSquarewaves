
/*

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

cycle_count = 10 (low frequency)               cycle_count = 5                  cycle_count = 1 (high frequency)

__________----------__________                 _____-----_____-----_____        _-_-_-_-_-_-_-_-




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

*/

#include <iostream>
#include <stdio.h>
#include <math.h>
#include "portaudio.h"
#define NUM_SECONDS   (4)
#define SAMPLE_RATE   (44100)




typedef struct
{
    float HIGH;
    float LOW;
}
paTestData;

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    /* Cast data passed through stream to our structure. */

    paTestData *data = (paTestData*)userData;


    int *out = (int*)outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning. */


/* Caution:  cycle_count / 2 must be less than framesPerBuffer or else you will have a distorted sqaure wave */
int cycle_position = 0; //track position on cycle
int cycle_count = 64; //change frequency by altering this value. lower values = higher pitch and vice-versa

for( i=0; i<framesPerBuffer; i++ )
{
if(cycle_position <= cycle_count){ /*Write Low Value to output buffer*/
*out++ = data->LOW; /*increment output buffer counter and write Low Value*/
cycle_position++; /*increment position on cycle*/
std::cout << "_"; /*crude visualization in terminal with standard out*/
}


else{   /*Write HIGH Value to output buffer*/
*out++ = data->HIGH; /*increment output buffer counter and write High Value*/
cycle_position++; /*increment position on cycle*/
std::cout << "-"; /*crude visualization in terminal with standard out*/
if(cycle_position == cycle_count * 2)cycle_position = 0; /*reset position on cycle*/
}}
    return 0;
}

/*******************************************************************/
static paTestData data;
int main(void);
int main(void)
{
    PaStream *stream;
    PaError err;




    printf("PortAudio Test:\n");
    /* Initialize our data for use by callback. */

    data.HIGH = 5.0f;
    data.LOW = -5.0f;
    /* Initialize library before making any other calls. */
    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream( &stream,
                                0,          /* no input channels */
                                1,          /* stereo output */
                                paFloat32,  /* 32 bit floating point output */
                                SAMPLE_RATE,
                                256,        /* frames per buffer */
                                patestCallback,
                                &data );
    if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;

    /* Sleep for several seconds. */

    Pa_Sleep(NUM_SECONDS*1000);

    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;
    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;
    Pa_Terminate();
    printf("Test finished.\n");
    return err;
error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return err;
}
