
#include "SignalControl_SegmentEnable.h"
#include <xc.h>

// This enumeration holds all the possible segment control HW signals used for 14 Segment LED digit
typedef enum 
{                      
 Segment_A__Signal = 0, // 
 Segment_B__Signal ,    // 
 Segment_C__Signal ,    // 
 Segment_D__Signal ,    // 
 Segment_E__Signal ,    // 
 Segment_F__Signal ,    // 
 Segment_G1_Signal ,    // 
 Segment_G2_Signal ,    // 
 Segment_H__Signal ,    // 
 Segment_I__Signal ,    // 
 Segment_J__Signal ,    // 
 Segment_K__Signal ,    // 
 Segment_L__Signal ,    // 
 Segment_M__Signal ,    // 
         
 SegmentSignal_Maxxxx  // 
    
}SegmentEnableSignals;

// This struct binds Segment Enable HW signals to the 
//assigned Bits of the assigned Ports belonging to MCU ( See Schematic )
typedef struct 
{
    SegmentEnableSignals        Signal_Identifier;
    unsigned char               PortIdentifier;
    unsigned char               BitIdentifier;
    
}SegmentEnable_SignalDefinition;

#define TOTAL_SEGMENTS   SegmentSignal_Maxxxx
#define TOTAL_SEGMENT_MCU_PORTS  5

#define SEGMENT_PORT_A_IDENTIFER 0
#define SEGMENT_PORT_B_IDENTIFER 1
#define SEGMENT_PORT_C_IDENTIFER 2
#define SEGMENT_PORT_D_IDENTIFER 3
#define SEGMENT_PORT_E_IDENTIFER 4

#define SEGMENT_BIT_0_IDENTIFER 0
#define SEGMENT_BIT_1_IDENTIFER 1
#define SEGMENT_BIT_2_IDENTIFER 2
#define SEGMENT_BIT_3_IDENTIFER 3
#define SEGMENT_BIT_4_IDENTIFER 4
#define SEGMENT_BIT_5_IDENTIFER 5
#define SEGMENT_BIT_6_IDENTIFER 6
#define SEGMENT_BIT_7_IDENTIFER 7

// a | b | c | d | e | f | g1 | g2 | h | i | j | k | l | m | n.a. | n.a. |
#define BITWISEMASK_SEGMENT_A  0b1000000000000000
#define BITWISEMASK_SEGMENT_B  0b0100000000000000
#define BITWISEMASK_SEGMENT_C  0b0010000000000000
#define BITWISEMASK_SEGMENT_D  0b0001000000000000
#define BITWISEMASK_SEGMENT_E  0b0000100000000000
#define BITWISEMASK_SEGMENT_F  0b0000010000000000
#define BITWISEMASK_SEGMENT_G1 0b0000001000000000
#define BITWISEMASK_SEGMENT_G2 0b0000000100000000
#define BITWISEMASK_SEGMENT_H  0b0000000010000000
#define BITWISEMASK_SEGMENT_I  0b0000000001000000
#define BITWISEMASK_SEGMENT_J  0b0000000000100000
#define BITWISEMASK_SEGMENT_K  0b0000000000010000
#define BITWISEMASK_SEGMENT_L  0b0000000000001000
#define BITWISEMASK_SEGMENT_M  0b0000000000000100

#define LED_IN_PORT_BITWISEMASK_BIT_0  0b00000001 
#define LED_IN_PORT_BITWISEMASK_BIT_1  0b00000010 
#define LED_IN_PORT_BITWISEMASK_BIT_2  0b00000100 
#define LED_IN_PORT_BITWISEMASK_BIT_3  0b00001000 
#define LED_IN_PORT_BITWISEMASK_BIT_4  0b00010000 
#define LED_IN_PORT_BITWISEMASK_BIT_5  0b00100000 
#define LED_IN_PORT_BITWISEMASK_BIT_6  0b01000000 
#define LED_IN_PORT_BITWISEMASK_BIT_7  0b10000000 

// Mapping of Digit Enable HW signals to Bits in Ports (See schematic )  Seg DP = RE2
const SegmentEnable_SignalDefinition SegmentEnableDefinitionArray[TOTAL_SEGMENTS] = 
{
    //Signal_Identifier        ,   PortIdentifier    ,    BitIdentifier   },
    {Segment_A__Signal         ,   SEGMENT_PORT_D_IDENTIFER  ,   SEGMENT_BIT_1_IDENTIFER },// SEGMENT_A__SIGNAL_RD1----  //
    {Segment_B__Signal         ,   SEGMENT_PORT_D_IDENTIFER  ,   SEGMENT_BIT_2_IDENTIFER },// SEGMENT_B__SIGNAL_RD2----  //
    {Segment_C__Signal         ,   SEGMENT_PORT_D_IDENTIFER  ,   SEGMENT_BIT_3_IDENTIFER },// SEGMENT_C__SIGNAL_RD3----  //
    {Segment_D__Signal         ,   SEGMENT_PORT_D_IDENTIFER  ,   SEGMENT_BIT_4_IDENTIFER },// SEGMENT_D__SIGNAL_RD4----  //
    {Segment_E__Signal         ,   SEGMENT_PORT_D_IDENTIFER  ,   SEGMENT_BIT_5_IDENTIFER },// SEGMENT_E__SIGNAL_RD5----  //
    {Segment_F__Signal         ,   SEGMENT_PORT_D_IDENTIFER  ,   SEGMENT_BIT_6_IDENTIFER },// SEGMENT_F__SIGNAL_RD6----  //
    {Segment_G1_Signal         ,   SEGMENT_PORT_E_IDENTIFER  ,   SEGMENT_BIT_0_IDENTIFER },// SEGMENT_G1_SIGNAL_RE0----  //
    {Segment_G2_Signal         ,   SEGMENT_PORT_A_IDENTIFER  ,   SEGMENT_BIT_1_IDENTIFER },// SEGMENT_G2_SIGNAL_RA1----  //
    {Segment_H__Signal         ,   SEGMENT_PORT_E_IDENTIFER  ,   SEGMENT_BIT_1_IDENTIFER },// SEGMENT_H__SIGNAL_RE1----  //
    {Segment_I__Signal         ,   SEGMENT_PORT_D_IDENTIFER  ,   SEGMENT_BIT_7_IDENTIFER },// SEGMENT_I__SIGNAL_RD7----  //
    {Segment_J__Signal         ,   SEGMENT_PORT_A_IDENTIFER  ,   SEGMENT_BIT_6_IDENTIFER },// SEGMENT_J__SIGNAL_RA6----  //
    {Segment_K__Signal         ,   SEGMENT_PORT_A_IDENTIFER  ,   SEGMENT_BIT_4_IDENTIFER },// SEGMENT_K__SIGNAL_RA4----  //
    {Segment_L__Signal         ,   SEGMENT_PORT_A_IDENTIFER  ,   SEGMENT_BIT_3_IDENTIFER },// SEGMENT_L__SIGNAL_RA3----  //
    {Segment_M__Signal         ,   SEGMENT_PORT_A_IDENTIFER  ,   SEGMENT_BIT_2_IDENTIFER },// SEGMENT_M__SIGNAL_RA2----  //
};

const unsigned int SegmentBitWiseMaskArray[TOTAL_SEGMENTS] =
{
        BITWISEMASK_SEGMENT_A ,
        BITWISEMASK_SEGMENT_B ,
        BITWISEMASK_SEGMENT_C ,
        BITWISEMASK_SEGMENT_D ,
        BITWISEMASK_SEGMENT_E ,
        BITWISEMASK_SEGMENT_F ,
        BITWISEMASK_SEGMENT_G1,
        BITWISEMASK_SEGMENT_G2,
        BITWISEMASK_SEGMENT_H ,
        BITWISEMASK_SEGMENT_I ,
        BITWISEMASK_SEGMENT_J ,
        BITWISEMASK_SEGMENT_K ,
        BITWISEMASK_SEGMENT_L ,
        BITWISEMASK_SEGMENT_M   
};

const unsigned char SEG_LED_InPort_BitwiseMaskArray[8] = 
{ 
        LED_IN_PORT_BITWISEMASK_BIT_0,
        LED_IN_PORT_BITWISEMASK_BIT_1,
        LED_IN_PORT_BITWISEMASK_BIT_2,
        LED_IN_PORT_BITWISEMASK_BIT_3,
        LED_IN_PORT_BITWISEMASK_BIT_4,
        LED_IN_PORT_BITWISEMASK_BIT_5,
        LED_IN_PORT_BITWISEMASK_BIT_6,
        LED_IN_PORT_BITWISEMASK_BIT_7,
};
//This array holds the byte values to be written in all ports. 
//The order is byte for port A --> element zero , then for Port B, then for port C and so on. 
unsigned char SEG_PortsABCDE_LoadsArray[TOTAL_SEGMENT_MCU_PORTS] = 
{ 
        0, // load for PORTA   
        0, // load for PORTB   
        0, // load for PORTC   
        0, // load for PORTD   
        0, // load for PORTE   

};
                                                                
void ConvertPatternToPortLoad(unsigned int convertionPattern, SegmentEnable_ElecticalWiring *outputPTR)
{
    unsigned char i;
    unsigned char portIndicator;
    unsigned char bitIndicator;
    unsigned int  SegOfPattern_BitwiseMask;
    unsigned char LedInPort_BitwiseMask;

    SEG_PortsABCDE_LoadsArray[SEGMENT_PORT_A_IDENTIFER] = 0;
    SEG_PortsABCDE_LoadsArray[SEGMENT_PORT_B_IDENTIFER] = 0;
    SEG_PortsABCDE_LoadsArray[SEGMENT_PORT_C_IDENTIFER] = 0;
    SEG_PortsABCDE_LoadsArray[SEGMENT_PORT_D_IDENTIFER] = 0;
    SEG_PortsABCDE_LoadsArray[SEGMENT_PORT_E_IDENTIFER] = 0;  
        
    for (int i = 0; i < TOTAL_SEGMENTS; i++)
    {
        portIndicator = SegmentEnableDefinitionArray[i].PortIdentifier;
        bitIndicator = SegmentEnableDefinitionArray[i].BitIdentifier;
        SegOfPattern_BitwiseMask  = SegmentBitWiseMaskArray[i];
        LedInPort_BitwiseMask     = SEG_LED_InPort_BitwiseMaskArray[bitIndicator];

        //Check if the current segment is needed in the pattern
        if ((convertionPattern & SegOfPattern_BitwiseMask) == SegOfPattern_BitwiseMask)
        {
            // This segment is needed in the pattern, turn the LED ON 
            SEG_PortsABCDE_LoadsArray[portIndicator] = SEG_PortsABCDE_LoadsArray[portIndicator] | LedInPort_BitwiseMask;
        }
        else
        {
            // This segment is NOT needed in the pattern, turn this LED OFF
            SEG_PortsABCDE_LoadsArray[portIndicator] = SEG_PortsABCDE_LoadsArray[portIndicator] & (~LedInPort_BitwiseMask);
        }
    }

    outputPTR->port_A_load = SEG_PortsABCDE_LoadsArray[SEGMENT_PORT_A_IDENTIFER];
    outputPTR->port_B_load = SEG_PortsABCDE_LoadsArray[SEGMENT_PORT_B_IDENTIFER];
    outputPTR->port_C_load = SEG_PortsABCDE_LoadsArray[SEGMENT_PORT_C_IDENTIFER];
    outputPTR->port_D_load = SEG_PortsABCDE_LoadsArray[SEGMENT_PORT_D_IDENTIFER];
    outputPTR->port_E_load = SEG_PortsABCDE_LoadsArray[SEGMENT_PORT_E_IDENTIFER];
}