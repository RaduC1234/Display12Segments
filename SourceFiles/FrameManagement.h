/* 
 * File:   LedActuation.h
 * Author: Radu
 *
 * Created on June 20, 2021, 5:44 PM
 */

#ifndef FRAMEMANAGEMENT_H
#define	FRAMEMANAGEMENT_H

#include "TextProcessing.h"

#define	TOTAL_LED_CELLS 8

typedef struct 
{
    unsigned char * StringToBePrinted;
    unsigned char StringStartOffset;//this member defines the starting character in the given string from which the characters are displayed.
    unsigned char StringDisplayLength;// number of characters desired to be displayed , starting from StringStartOffset onwards 
    unsigned char DigitOffset;// this offset identifies the starting digit for the displayed text
    

}General_StringInput;

typedef struct 
{
    General_PortLoad PortLoad_For_Digit_00;
    General_PortLoad PortLoad_For_Digit_01;
    General_PortLoad PortLoad_For_Digit_02;
    General_PortLoad PortLoad_For_Digit_03;
    General_PortLoad PortLoad_For_Digit_04;
    General_PortLoad PortLoad_For_Digit_05;
    General_PortLoad PortLoad_For_Digit_06;
    General_PortLoad PortLoad_For_Digit_07;
}FullFramePortsLoad;


void FM_InitInternalData (void) ;
unsigned char TranslateString(General_StringInput StringInput);
void GetFullFramePortLoads(FullFramePortsLoad * PortLoadsForFullFrame);

#endif	/* PORTACTUATION_H */

