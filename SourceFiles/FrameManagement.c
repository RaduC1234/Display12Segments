
#include <xc.h>
#include "FrameManagement.h"
#include "TextProcessing.h"

void Setup_GPIO (void) ;
void FM_PortLoadsStitcher ( unsigned char DigitOffset , unsigned char TotalDigitStitch) ;
void FM_GetTranslatedString ( FullFramePortsLoad * PortLoadsForFullFrame) ;
void FM_PortLoadsTransfer ( void ) ;

General_PortLoad FM_LocalPortLoadArray_Seg[TOTAL_LED_CELLS];
General_PortLoad FM_LocalPortLoadArray_Dig[TOTAL_LED_CELLS];
General_PortLoad FM_LocalPortLoadArray_AllSig[TOTAL_LED_CELLS];

General_PortLoad FM_TemporaryUsePortLoadBuffer;
FullFramePortsLoad FM_FullFramePortLoadBuffer;

       
void FM_InitInternalData (void) 
{
    unsigned char LoopCounter = 0;
    
    //Initialize internal data of Lower LAyer 
    InitializeInternalData();
    
    //Configure the involved ports 
    Setup_GPIO () ;
    
    //fill the Digit Control PortLoads Local Array , as this one stays constant as the letters change
    for(LoopCounter  = 0 ; LoopCounter < TOTAL_LED_CELLS ; LoopCounter++)
    {
        //Get the port Loads for current digit in the loop into GeneralUsePortLoadBuffer 
        GetPortLoadsForDigitEnable(LoopCounter , &FM_TemporaryUsePortLoadBuffer);
        //Store The port loads from buffer into DigitPortLoadsArray 
        FM_LocalPortLoadArray_Dig[LoopCounter].port_A_load = FM_TemporaryUsePortLoadBuffer.port_A_load;
        FM_LocalPortLoadArray_Dig[LoopCounter].port_B_load = FM_TemporaryUsePortLoadBuffer.port_B_load;
        FM_LocalPortLoadArray_Dig[LoopCounter].port_C_load = FM_TemporaryUsePortLoadBuffer.port_C_load;
        FM_LocalPortLoadArray_Dig[LoopCounter].port_D_load = FM_TemporaryUsePortLoadBuffer.port_D_load;
        FM_LocalPortLoadArray_Dig[LoopCounter].port_E_load = FM_TemporaryUsePortLoadBuffer.port_E_load;
    }
    
    //Turn OFF All Segments 
    for(LoopCounter  = 0 ; LoopCounter < TOTAL_LED_CELLS ; LoopCounter++)
    {
        FM_LocalPortLoadArray_Seg[LoopCounter].port_A_load = 0;
        FM_LocalPortLoadArray_Seg[LoopCounter].port_B_load = 0;
        FM_LocalPortLoadArray_Seg[LoopCounter].port_C_load = 0;
        FM_LocalPortLoadArray_Seg[LoopCounter].port_D_load = 0;
        FM_LocalPortLoadArray_Seg[LoopCounter].port_E_load = 0;
    }
}

unsigned char TranslateString(General_StringInput StringInput)
{
    unsigned char Output = 0; 
    unsigned char DesiredDisplayedStringLength  = 0; 
    unsigned char AvailableLedDigits  = 0; 
    unsigned char LoopCounter = 0; 
    unsigned char CurrentAsciiCharacter = 0;
    unsigned char CurrentAsciiLetterOffset = 0;
    unsigned char * StringPtr;
    
    //Verify some input data .....
    if((StringInput.DigitOffset >=  TOTAL_LED_CELLS )||(StringInput.StringDisplayLength > TOTAL_LED_CELLS) )
    {
        Output = 0; //Reflect error. Digit offset greater than Maximum digits available = 12; 
    }
    else
    {
        //Verify some input data .....
        DesiredDisplayedStringLength  = StringInput.StringDisplayLength; 
        AvailableLedDigits  = TOTAL_LED_CELLS - StringInput.DigitOffset; 
    
        if(DesiredDisplayedStringLength > AvailableLedDigits )
        {
            //Reflect error. Desired string to be displayed is longer than remaining digits after Total digits - offset digits 
            Output = 0; 
        }
        else
        {
            //Reflect success.
            Output = 1;
            //Get the string pointer 
            StringPtr = StringInput.StringToBePrinted;
            //Parse the string and translate every current letter into port Loads
            for(LoopCounter  = 0 ; LoopCounter < DesiredDisplayedStringLength ; LoopCounter++)
            {
                // Get the Position of the current ASCII letter to be translated 
                CurrentAsciiLetterOffset = LoopCounter + StringInput.StringStartOffset;
                //Extract the letter to transform into Port Loads out of the Given String
                CurrentAsciiCharacter = StringPtr[CurrentAsciiLetterOffset];
                //Convert this letter into port load values 
                GetPortLoadsForAsciiLetter(CurrentAsciiCharacter , &FM_TemporaryUsePortLoadBuffer);
                        //Store The port loads from PortLoadbuffer into SegmentPortLoadsArray 
                        //For storing, use the offset indicated by user as digit offset 
                FM_LocalPortLoadArray_Seg[LoopCounter + StringInput.DigitOffset].port_A_load = FM_TemporaryUsePortLoadBuffer.port_A_load;
                FM_LocalPortLoadArray_Seg[LoopCounter + StringInput.DigitOffset].port_B_load = FM_TemporaryUsePortLoadBuffer.port_B_load;
                FM_LocalPortLoadArray_Seg[LoopCounter + StringInput.DigitOffset].port_C_load = FM_TemporaryUsePortLoadBuffer.port_C_load;
                FM_LocalPortLoadArray_Seg[LoopCounter + StringInput.DigitOffset].port_D_load = FM_TemporaryUsePortLoadBuffer.port_D_load;
                FM_LocalPortLoadArray_Seg[LoopCounter + StringInput.DigitOffset].port_E_load = FM_TemporaryUsePortLoadBuffer.port_E_load;
            }
                //Now stitch together the bits for digit control and the bits for segment control 
            FM_PortLoadsStitcher ( StringInput.DigitOffset , DesiredDisplayedStringLength) ;  
            //Transfer port loads 
            FM_PortLoadsTransfer ();
        }
    }
    
    return Output;
}

void FM_PortLoadsStitcher ( unsigned char DigitOffset , unsigned char TotalDigitStitch) 
{
    unsigned char LoopCounter = 0; 
    
    unsigned char LocalStitchedPortLoad_A = 0; 
    unsigned char LocalStitchedPortLoad_B = 0; 
    unsigned char LocalStitchedPortLoad_C = 0; 
    unsigned char LocalStitchedPortLoad_D = 0; 
    unsigned char LocalStitchedPortLoad_E = 0; 
    
    unsigned char SinglePortLoadValue_DIG_A = 0; 
    unsigned char SinglePortLoadValue_DIG_B = 0;
    unsigned char SinglePortLoadValue_DIG_C = 0;
    unsigned char SinglePortLoadValue_DIG_D = 0;
    unsigned char SinglePortLoadValue_DIG_E = 0;

    unsigned char SinglePortLoadValue_SEG_A = 0; 
    unsigned char SinglePortLoadValue_SEG_B = 0; 
    unsigned char SinglePortLoadValue_SEG_C = 0; 
    unsigned char SinglePortLoadValue_SEG_D = 0; 
    unsigned char SinglePortLoadValue_SEG_E = 0; 

    if(    (DigitOffset >=  TOTAL_LED_CELLS )||
           (TotalDigitStitch > TOTAL_LED_CELLS) || 
           (TotalDigitStitch >   ( TOTAL_LED_CELLS - DigitOffset )      )              
       )
    {
        //Reflect error. Digit offset greater than Maximum digits available = 12; 
    }
    else
    {
                    //Now stitch together the bits for digit control and the bits for segment control 
        for(LoopCounter  = 0 ; LoopCounter < TotalDigitStitch ; LoopCounter++)
        {
            // extract the port values for ports a, b, c ,d ,e holding Digit enable signals 
            SinglePortLoadValue_DIG_A = FM_LocalPortLoadArray_Dig[LoopCounter + DigitOffset].port_A_load;
            SinglePortLoadValue_DIG_B = FM_LocalPortLoadArray_Dig[LoopCounter + DigitOffset].port_B_load;
            SinglePortLoadValue_DIG_C = FM_LocalPortLoadArray_Dig[LoopCounter + DigitOffset].port_C_load;
            SinglePortLoadValue_DIG_D = FM_LocalPortLoadArray_Dig[LoopCounter + DigitOffset].port_D_load;
            SinglePortLoadValue_DIG_E = FM_LocalPortLoadArray_Dig[LoopCounter + DigitOffset].port_E_load;
            // extract the port values for ports a, b, c ,d ,e holding Segment enable signals 
            SinglePortLoadValue_SEG_A = FM_LocalPortLoadArray_Seg[LoopCounter + DigitOffset].port_A_load;; 
            SinglePortLoadValue_SEG_B = FM_LocalPortLoadArray_Seg[LoopCounter + DigitOffset].port_B_load;; 
            SinglePortLoadValue_SEG_C = FM_LocalPortLoadArray_Seg[LoopCounter + DigitOffset].port_C_load;; 
            SinglePortLoadValue_SEG_D = FM_LocalPortLoadArray_Seg[LoopCounter + DigitOffset].port_D_load;; 
            SinglePortLoadValue_SEG_E = FM_LocalPortLoadArray_Seg[LoopCounter + DigitOffset].port_E_load;; 
            // stitch together the segment enable signal bytes and the digit enable bytes for all ports a, b, c ,d e 
            LocalStitchedPortLoad_A = SinglePortLoadValue_DIG_A | SinglePortLoadValue_SEG_A; 
            LocalStitchedPortLoad_B = SinglePortLoadValue_DIG_B | SinglePortLoadValue_SEG_B; 
            LocalStitchedPortLoad_C = SinglePortLoadValue_DIG_C | SinglePortLoadValue_SEG_C; 
            LocalStitchedPortLoad_D = SinglePortLoadValue_DIG_D | SinglePortLoadValue_SEG_D; 
            LocalStitchedPortLoad_E = SinglePortLoadValue_DIG_E | SinglePortLoadValue_SEG_E; 
            //Now store the stitched values in the array of general port loads 
            FM_LocalPortLoadArray_AllSig[LoopCounter + DigitOffset].port_A_load = LocalStitchedPortLoad_A;
            FM_LocalPortLoadArray_AllSig[LoopCounter + DigitOffset].port_B_load = LocalStitchedPortLoad_B;
            FM_LocalPortLoadArray_AllSig[LoopCounter + DigitOffset].port_C_load = LocalStitchedPortLoad_C;
            FM_LocalPortLoadArray_AllSig[LoopCounter + DigitOffset].port_D_load = LocalStitchedPortLoad_D;
            FM_LocalPortLoadArray_AllSig[LoopCounter + DigitOffset].port_E_load = LocalStitchedPortLoad_E;
        }
    }
}

void FM_PortLoadsTransfer (void) 
{
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_00.port_A_load = FM_LocalPortLoadArray_AllSig[ 0].port_A_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_00.port_B_load = FM_LocalPortLoadArray_AllSig[ 0].port_B_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_00.port_C_load = FM_LocalPortLoadArray_AllSig[ 0].port_C_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_00.port_D_load = FM_LocalPortLoadArray_AllSig[ 0].port_D_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_00.port_E_load = FM_LocalPortLoadArray_AllSig[ 0].port_E_load;
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_01.port_A_load = FM_LocalPortLoadArray_AllSig[ 1].port_A_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_01.port_B_load = FM_LocalPortLoadArray_AllSig[ 1].port_B_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_01.port_C_load = FM_LocalPortLoadArray_AllSig[ 1].port_C_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_01.port_D_load = FM_LocalPortLoadArray_AllSig[ 1].port_D_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_01.port_E_load = FM_LocalPortLoadArray_AllSig[ 1].port_E_load;
     //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_02.port_A_load = FM_LocalPortLoadArray_AllSig[ 2].port_A_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_02.port_B_load = FM_LocalPortLoadArray_AllSig[ 2].port_B_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_02.port_C_load = FM_LocalPortLoadArray_AllSig[ 2].port_C_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_02.port_D_load = FM_LocalPortLoadArray_AllSig[ 2].port_D_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_02.port_E_load = FM_LocalPortLoadArray_AllSig[ 2].port_E_load;
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_03.port_A_load = FM_LocalPortLoadArray_AllSig[ 3].port_A_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_03.port_B_load = FM_LocalPortLoadArray_AllSig[ 3].port_B_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_03.port_C_load = FM_LocalPortLoadArray_AllSig[ 3].port_C_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_03.port_D_load = FM_LocalPortLoadArray_AllSig[ 3].port_D_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_03.port_E_load = FM_LocalPortLoadArray_AllSig[ 3].port_E_load;
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_04.port_A_load = FM_LocalPortLoadArray_AllSig[ 4].port_A_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_04.port_B_load = FM_LocalPortLoadArray_AllSig[ 4].port_B_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_04.port_C_load = FM_LocalPortLoadArray_AllSig[ 4].port_C_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_04.port_D_load = FM_LocalPortLoadArray_AllSig[ 4].port_D_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_04.port_E_load = FM_LocalPortLoadArray_AllSig[ 4].port_E_load;
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_05.port_A_load = FM_LocalPortLoadArray_AllSig[ 5].port_A_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_05.port_B_load = FM_LocalPortLoadArray_AllSig[ 5].port_B_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_05.port_C_load = FM_LocalPortLoadArray_AllSig[ 5].port_C_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_05.port_D_load = FM_LocalPortLoadArray_AllSig[ 5].port_D_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_05.port_E_load = FM_LocalPortLoadArray_AllSig[ 5].port_E_load;
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_06.port_A_load = FM_LocalPortLoadArray_AllSig[ 6].port_A_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_06.port_B_load = FM_LocalPortLoadArray_AllSig[ 6].port_B_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_06.port_C_load = FM_LocalPortLoadArray_AllSig[ 6].port_C_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_06.port_D_load = FM_LocalPortLoadArray_AllSig[ 6].port_D_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_06.port_E_load = FM_LocalPortLoadArray_AllSig[ 6].port_E_load;   
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_07.port_A_load = FM_LocalPortLoadArray_AllSig[ 7].port_A_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_07.port_B_load = FM_LocalPortLoadArray_AllSig[ 7].port_B_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_07.port_C_load = FM_LocalPortLoadArray_AllSig[ 7].port_C_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_07.port_D_load = FM_LocalPortLoadArray_AllSig[ 7].port_D_load;
    FM_FullFramePortLoadBuffer.PortLoad_For_Digit_07.port_E_load = FM_LocalPortLoadArray_AllSig[ 7].port_E_load;
    }

void GetFullFramePortLoads(FullFramePortsLoad * PortLoadsForFullFrame) 
{
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    PortLoadsForFullFrame->PortLoad_For_Digit_00.port_A_load = FM_LocalPortLoadArray_AllSig[ 0].port_A_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_00.port_B_load = FM_LocalPortLoadArray_AllSig[ 0].port_B_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_00.port_C_load = FM_LocalPortLoadArray_AllSig[ 0].port_C_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_00.port_D_load = FM_LocalPortLoadArray_AllSig[ 0].port_D_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_00.port_E_load = FM_LocalPortLoadArray_AllSig[ 0].port_E_load;
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    PortLoadsForFullFrame->PortLoad_For_Digit_01.port_A_load = FM_LocalPortLoadArray_AllSig[ 1].port_A_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_01.port_B_load = FM_LocalPortLoadArray_AllSig[ 1].port_B_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_01.port_C_load = FM_LocalPortLoadArray_AllSig[ 1].port_C_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_01.port_D_load = FM_LocalPortLoadArray_AllSig[ 1].port_D_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_01.port_E_load = FM_LocalPortLoadArray_AllSig[ 1].port_E_load;
     //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    PortLoadsForFullFrame->PortLoad_For_Digit_02.port_A_load = FM_LocalPortLoadArray_AllSig[ 2].port_A_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_02.port_B_load = FM_LocalPortLoadArray_AllSig[ 2].port_B_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_02.port_C_load = FM_LocalPortLoadArray_AllSig[ 2].port_C_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_02.port_D_load = FM_LocalPortLoadArray_AllSig[ 2].port_D_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_02.port_E_load = FM_LocalPortLoadArray_AllSig[ 2].port_E_load;
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    PortLoadsForFullFrame->PortLoad_For_Digit_03.port_A_load = FM_LocalPortLoadArray_AllSig[ 3].port_A_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_03.port_B_load = FM_LocalPortLoadArray_AllSig[ 3].port_B_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_03.port_C_load = FM_LocalPortLoadArray_AllSig[ 3].port_C_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_03.port_D_load = FM_LocalPortLoadArray_AllSig[ 3].port_D_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_03.port_E_load = FM_LocalPortLoadArray_AllSig[ 3].port_E_load;
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    PortLoadsForFullFrame->PortLoad_For_Digit_04.port_A_load = FM_LocalPortLoadArray_AllSig[ 4].port_A_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_04.port_B_load = FM_LocalPortLoadArray_AllSig[ 4].port_B_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_04.port_C_load = FM_LocalPortLoadArray_AllSig[ 4].port_C_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_04.port_D_load = FM_LocalPortLoadArray_AllSig[ 4].port_D_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_04.port_E_load = FM_LocalPortLoadArray_AllSig[ 4].port_E_load;
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    PortLoadsForFullFrame->PortLoad_For_Digit_05.port_A_load = FM_LocalPortLoadArray_AllSig[ 5].port_A_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_05.port_B_load = FM_LocalPortLoadArray_AllSig[ 5].port_B_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_05.port_C_load = FM_LocalPortLoadArray_AllSig[ 5].port_C_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_05.port_D_load = FM_LocalPortLoadArray_AllSig[ 5].port_D_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_05.port_E_load = FM_LocalPortLoadArray_AllSig[ 5].port_E_load;
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    PortLoadsForFullFrame->PortLoad_For_Digit_06.port_A_load = FM_LocalPortLoadArray_AllSig[ 6].port_A_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_06.port_B_load = FM_LocalPortLoadArray_AllSig[ 6].port_B_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_06.port_C_load = FM_LocalPortLoadArray_AllSig[ 6].port_C_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_06.port_D_load = FM_LocalPortLoadArray_AllSig[ 6].port_D_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_06.port_E_load = FM_LocalPortLoadArray_AllSig[ 6].port_E_load;   
    //Now put the port loads of port  a, b , c , d , e into GeneralPortLoad Struct Member assigned to Digit 00 in the Full Frame Local Buffer ;
    PortLoadsForFullFrame->PortLoad_For_Digit_07.port_A_load = FM_LocalPortLoadArray_AllSig[ 7].port_A_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_07.port_B_load = FM_LocalPortLoadArray_AllSig[ 7].port_B_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_07.port_C_load = FM_LocalPortLoadArray_AllSig[ 7].port_C_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_07.port_D_load = FM_LocalPortLoadArray_AllSig[ 7].port_D_load;
    PortLoadsForFullFrame->PortLoad_For_Digit_07.port_E_load = FM_LocalPortLoadArray_AllSig[ 7].port_E_load;

}