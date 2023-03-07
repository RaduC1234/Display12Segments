#include "TextProcessing.h"
#include "AsciiCharacterLedPattern.h"
#include "SignalControl_DigitEnable.h"
#include "SignalControl_SegmentEnable.h"
#include <xc.h>

#define	TOTAL_MAPPED_ASCII_CHARACTERS TOTAL_LED_ASCII
#define	TOTAL_LED_DIGITS_ON_THE_BOARD TOTAL_DIGITS

//this array holds port loads responsible for segment enable signals only 
General_PortLoad PortLoad_AllCharacters_Array [TOTAL_MAPPED_ASCII_CHARACTERS];
//this array holds port loads responsible for digit enable signals only 
General_PortLoad PortLoad_AllLEdDigits_Array  [TOTAL_LED_DIGITS_ON_THE_BOARD];

//This typedef variable holds the port loads after converting a character into port loads 
SegmentEnable_ElecticalWiring ASCII_Letter_PortLoads;
//This typedef variable holds the port loads after converting a digit index  into port loads 
DigitEnable_ElecticalWiring Digit_Enable_PortLoads;

unsigned char LocalAsciiHexVal = 0; 
unsigned int LocalSegmentCodePattern = 0; 
unsigned char LocalDataInitFlag = 0 ; 

void InitializeInternalData(void)
{
    unsigned char LoopCounter = 0 ; 
    
    for(LoopCounter = 0; LoopCounter < TOTAL_MAPPED_ASCII_CHARACTERS; LoopCounter++)
    {
        PortLoad_AllCharacters_Array[LoopCounter].port_A_load = 0;
        PortLoad_AllCharacters_Array[LoopCounter].port_B_load = 0;
        PortLoad_AllCharacters_Array[LoopCounter].port_C_load = 0;
        PortLoad_AllCharacters_Array[LoopCounter].port_D_load = 0;
        PortLoad_AllCharacters_Array[LoopCounter].port_E_load = 0;     
    }
    
    for(LoopCounter = 0; LoopCounter < TOTAL_LED_DIGITS_ON_THE_BOARD; LoopCounter++)
    {
        PortLoad_AllLEdDigits_Array[LoopCounter].port_A_load = 0;
        PortLoad_AllLEdDigits_Array[LoopCounter].port_B_load = 0;
        PortLoad_AllLEdDigits_Array[LoopCounter].port_C_load = 0;
        PortLoad_AllLEdDigits_Array[LoopCounter].port_D_load = 0;
        PortLoad_AllLEdDigits_Array[LoopCounter].port_E_load = 0;   
    }
    
    for(LoopCounter = 0; LoopCounter < TOTAL_MAPPED_ASCII_CHARACTERS; LoopCounter++)
    {
        //Get mapped Letter 
        LocalAsciiHexVal = GetHexValOfAscii(LoopCounter);
        //Get segment code pattern  mapped to this letter 
        LocalSegmentCodePattern = GetASCIIToSegmentPattern(LocalAsciiHexVal);
        //Get PortLoads to be put in MCU ports in order to display the needed segments in digit
        ConvertPatternToPortLoad(LocalSegmentCodePattern, &ASCII_Letter_PortLoads);
        //Put All the port loads into local array 
        PortLoad_AllCharacters_Array[LoopCounter].port_A_load = ASCII_Letter_PortLoads.port_A_load;
        PortLoad_AllCharacters_Array[LoopCounter].port_B_load = ASCII_Letter_PortLoads.port_B_load;
        PortLoad_AllCharacters_Array[LoopCounter].port_C_load = ASCII_Letter_PortLoads.port_C_load;
        PortLoad_AllCharacters_Array[LoopCounter].port_D_load = ASCII_Letter_PortLoads.port_D_load;
        PortLoad_AllCharacters_Array[LoopCounter].port_E_load = ASCII_Letter_PortLoads.port_E_load;   
    }
    
    for(LoopCounter = 0; LoopCounter < TOTAL_LED_DIGITS_ON_THE_BOARD; LoopCounter++)
    {
        //Get PortLoads to be put in MCU ports in order to turn on the High side driver for the current digit
        ConvertDigitEnableToPortLoad(LoopCounter, &Digit_Enable_PortLoads);
        //Put All the port loads into local array 
        PortLoad_AllLEdDigits_Array[LoopCounter].port_A_load = Digit_Enable_PortLoads.port_A_load;
        PortLoad_AllLEdDigits_Array[LoopCounter].port_B_load = Digit_Enable_PortLoads.port_B_load;
        PortLoad_AllLEdDigits_Array[LoopCounter].port_C_load = Digit_Enable_PortLoads.port_C_load;
        PortLoad_AllLEdDigits_Array[LoopCounter].port_D_load = Digit_Enable_PortLoads.port_D_load;
        PortLoad_AllLEdDigits_Array[LoopCounter].port_E_load = Digit_Enable_PortLoads.port_E_load;   
    }
    
    LocalDataInitFlag = 1; 
}

void GetPortLoadsForAsciiLetter(unsigned char ASCII_character , General_PortLoad *outputPTR)
{
    if(ASCII_character < TOTAL_MAPPED_ASCII_CHARACTERS)
    {
        if(LocalDataInitFlag == 1)
        {
            outputPTR->port_A_load = PortLoad_AllCharacters_Array[ASCII_character].port_A_load;
            outputPTR->port_B_load = PortLoad_AllCharacters_Array[ASCII_character].port_B_load;
            outputPTR->port_C_load = PortLoad_AllCharacters_Array[ASCII_character].port_C_load;
            outputPTR->port_D_load = PortLoad_AllCharacters_Array[ASCII_character].port_D_load;
            outputPTR->port_E_load = PortLoad_AllCharacters_Array[ASCII_character].port_E_load;  


        }
        else
        {
            outputPTR->port_A_load = 0;
            outputPTR->port_B_load = 0;
            outputPTR->port_C_load = 0;
            outputPTR->port_D_load = 0;
            outputPTR->port_E_load = 0;  
        }
    }
    else
    {
        
    }
}

void GetPortLoadsForDigitEnable(unsigned char Digit_Index , General_PortLoad *outputPTR)
{
    if(Digit_Index < TOTAL_LED_DIGITS_ON_THE_BOARD)
    {
        if(LocalDataInitFlag == 1)
        {
            outputPTR->port_A_load = PortLoad_AllLEdDigits_Array[Digit_Index].port_A_load;
            outputPTR->port_B_load = PortLoad_AllLEdDigits_Array[Digit_Index].port_B_load;
            outputPTR->port_C_load = PortLoad_AllLEdDigits_Array[Digit_Index].port_C_load;
            outputPTR->port_D_load = PortLoad_AllLEdDigits_Array[Digit_Index].port_D_load;
            outputPTR->port_E_load = PortLoad_AllLEdDigits_Array[Digit_Index].port_E_load;  


        }
        else
        {
            outputPTR->port_A_load = 0;
            outputPTR->port_B_load = 0;
            outputPTR->port_C_load = 0;
            outputPTR->port_D_load = 0;
            outputPTR->port_E_load = 0;  
        }
    }
    else
    {
        
    }
}

