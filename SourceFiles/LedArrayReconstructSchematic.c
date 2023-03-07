/*
 * File:   Led_Array_PicKit4.c
 * Author: Radu
 *
 * Created on June 21, 2021, 6:32 PM
 */
// PIC18F47Q10 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config FEXTOSC = OFF           // External Oscillator mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_64MHZ // Power-up default value for COSC bits (HFINTOSC with HFFRQ = 64 MHz and CDIV = 1:1)

// CONFIG1H
#pragma config CLKOUTEN = OFF // Clock Out Enable bit (CLKOUT function is disabled)
#pragma config CSWEN = ON     // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON     // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

// CONFIG2L
#pragma config MCLRE = EXTMCLR // Master Clear Enable bit (MCLR pin (RE3) is MCLR)
#pragma config PWRTE = OFF     // Power-up Timer Enable bit (Power up timer disabled)
#pragma config LPBOREN = OFF   // Low-power BOR enable bit (Low power BOR is disabled)
#pragma config BOREN = SBORDIS // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG2H
#pragma config BORV = VBOR_190 // Brown Out Reset Voltage selection bits (Brown-out Reset Voltage (VBOR) set to 1.90V)
#pragma config ZCD = OFF       // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON    // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config XINST = OFF     // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31 // WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF         // WDT operating mode (WDT Disabled)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7 // WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC       // WDT input clock selector (Software Control)

// CONFIG4L
#pragma config WRT0 = OFF // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF // Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)
#pragma config WRT4 = OFF // Write Protection Block 4 (Block 4 (010000-013FFFh) not write-protected)
#pragma config WRT5 = OFF // Write Protection Block 5 (Block 5 (014000-017FFFh) not write-protected)
#pragma config WRT6 = OFF // Write Protection Block 6 (Block 6 (018000-01BFFFh) not write-protected)
#pragma config WRT7 = OFF // Write Protection Block 7 (Block 7 (01C000-01FFFFh) not write-protected)

// CONFIG4H
#pragma config WRTC = OFF // Configuration Register Write Protection bit (Configuration registers (300000-30000Bh) not write-protected)
#pragma config WRTB = OFF // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config SCANE = ON // Scanner Enable bit (Scanner module is available for use, SCANMD bit can control the module)
#pragma config LVP = ON   // Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)

// CONFIG5L
#pragma config CP = OFF  // UserNVM Program Memory Code Protection bit (UserNVM code protection disabled)
#pragma config CPD = OFF // DataNVM Memory Code Protection bit (DataNVM code protection disabled)

// CONFIG5H

// CONFIG6L
#pragma config EBTR0 = OFF // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR4 = OFF // Table Read Protection Block 4 (Block 4 (010000-013FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR5 = OFF // Table Read Protection Block 5 (Block 5 (014000-017FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR6 = OFF // Table Read Protection Block 6 (Block 6 (018000-01BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR7 = OFF // Table Read Protection Block 7 (Block 7 (01C000-01FFFFh) not protected from table reads executed in other blocks)

// CONFIG6H
#pragma config EBTRB = OFF // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "PortActuation.h"
#include "FrameManagement.h"

void TextUpdate(void);
void TextSwitch(unsigned char index);

void PortTest(void);

unsigned char LocalStringArray_00[] = "  RADU  ";
unsigned char LocalStringArray_01[] = " ANDREI ";
unsigned char LocalStringArray_02[] = "CAPATINA";
unsigned char LocalStringArray_03[] = "DESIGNED";
unsigned char LocalStringArray_04[] = "  THIS  ";
unsigned char LocalStringArray_05[] = " DISPLAY";
unsigned char FunctionResponse = 0;

General_StringInput StringConfig;

unsigned int TextCycle = 0;
unsigned int TextFlag = 0;
unsigned char TextIndicator = 0;

/*
 *
 */
int main(int argc, char **argv)
{
    Setup_GPIO();
    FM_InitInternalData();
    // PortTest();

    while (1)
    {
        TextUpdate();

        CyclicFramePrint();
    }
    return (EXIT_SUCCESS);
}

void TextUpdate(void)
{
    if (TextCycle < 50)
    {
        TextCycle++;
    }
    else
    {
        TextCycle = 0;
    }

    if (TextCycle == 0)
    {

        if (TextIndicator < 6)
        {
            TextIndicator++;
        }
        else
        {
            TextIndicator = 0;
        }

        TextSwitch(TextIndicator);

        FunctionResponse = TranslateString(StringConfig);

        if (FunctionResponse == 1)
        {
            RefreshPortInformation();
        }
        else
        {
        }
    }
    else
    {
    }
}

void TextSwitch(unsigned char index)
{
    switch (index)
    {
    case 0:
    {
        StringConfig.StringToBePrinted = LocalStringArray_00;
    }

    break;

    case 1:
    {
        StringConfig.StringToBePrinted = LocalStringArray_01;
    }
    break;

    case 2:
    {
        StringConfig.StringToBePrinted = LocalStringArray_02;
    }
    break;

    case 3:
    {
        StringConfig.StringToBePrinted = LocalStringArray_03;
    }
    break;

    case 4:
    {
        StringConfig.StringToBePrinted = LocalStringArray_04;
    }
    break;

    case 5:
    {
        StringConfig.StringToBePrinted = LocalStringArray_05;
    }
    break;

    default:
        break;
    }

    StringConfig.DigitOffset = 0;
    StringConfig.StringDisplayLength = 8;
    StringConfig.StringStartOffset = 0;
}

// for debug only
void PortTest(void)
{
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;

    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;

    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;

    PORTA = 0b01000000;
    PORTB = 0b00000010;
    PORTC = 0b00000000;
    PORTD = 0b00000000;
    PORTE = 0b00000000;
}