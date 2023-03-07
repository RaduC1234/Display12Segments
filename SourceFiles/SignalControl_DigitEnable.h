/* 
 * File:   AsciiCharacterLedPattern.h
 * Author: Radu
 *
 * Created on June 20, 2021, 5:50 PM
 */

#ifndef SIGNALCONTROLDIGITENABLE_H
#define	SIGNALCONTROLDIGITENABLE_H

typedef struct 
{
    unsigned char port_A_load;
    unsigned char port_B_load;
    unsigned char port_C_load;
    unsigned char port_D_load;
    unsigned char port_E_load;
    
}DigitEnable_ElecticalWiring;


// This enumeration holds all the possible digit control HW signals used on 12 Digit Board 
typedef enum 
{                      
 Digit_00_Signal = 0, // 
 Digit_01_Signal ,    // 
 Digit_02_Signal ,    // 
 Digit_03_Signal ,    // 
 Digit_04_Signal ,    // 
 Digit_05_Signal ,    // 
 Digit_06_Signal ,    // 
 Digit_07_Signal ,    // 

 Digit___Maxxxx  // 
    
}DigitEnableSignals;


#define TOTAL_DIGITS     Digit___Maxxxx

void ConvertDigitEnableToPortLoad(unsigned char DigitIndex, DigitEnable_ElecticalWiring *outputPTR);

#endif	/* LEDACTUATION_H */

