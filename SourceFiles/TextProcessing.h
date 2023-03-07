/* 
 * File:   LedActuation.h
 * Author: Radu
 *
 * Created on June 20, 2021, 5:44 PM
 */

#ifndef TEXTPROCESSING_H
#define	TEXTPROCESSING_H



typedef struct 
{
    unsigned char port_A_load;
    unsigned char port_B_load;
    unsigned char port_C_load;
    unsigned char port_D_load;
    unsigned char port_E_load;
    
}General_PortLoad;

void InitializeInternalData(void);
void GetPortLoadsForAsciiLetter(unsigned char ASCII_character , General_PortLoad *outputPTR);
void GetPortLoadsForDigitEnable(unsigned char Digit_Index     , General_PortLoad *outputPTR);

#endif	/* LEDACTUATION_H */

