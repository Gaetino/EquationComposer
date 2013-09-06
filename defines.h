#ifndef defines_h
#define defines_h

#define MAX_CV 4095
#define MID_CV 2047

// Pin definitions
#define PIN_EQU 0
#define PIN_SR 1
#define PIN_PARAM_1 2
#define PIN_PARAM_2 3
#define PIN_PARAM_3 4
#define PIN_MOD 5
#define PIN_RESET 22

// ADAC and Analog Read values
#define MAX_ADC_VALUE 1023         // This should be 2^ANALOG_READ_RESOLUTION - 1
#define ANALOG_READ_RESOLUTION 10  // Typical values are 8, 10 or 12
#define MAX_CV_VALUE 255           // Maximum internal module control voltage value
#define MAX_AUDIO_VALUE 4095       // Maximum value of audio signals (2^12)-1

// Assorted definitions
#define NUMBER_OF_EQUATIONS 37
#define NUMBER_OF_SYNTHS 2
#define SAMPLE_RATE 44100.0

// These are readable constants for use
// when indexing the inputs[] array
#define EQ_INPUT 0
#define SR_INPUT 1
#define MOD_INPUT 2
#define PARAM1_INPUT 3
#define PARAM2_INPUT 4
#define PARAM3_INPUT 5
#define RESET_INPUT 6



#endif
