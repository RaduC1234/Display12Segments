
#include "SignalControl_DigitEnable.h"
#include <xc.h>



// This struct binds Digit Enable HW signals to the 
//assigned Bits of the assigned Ports belonging to MCU ( See Schematic )
typedef struct 
{
    DigitEnableSignals          Signal_Identifier;
    unsigned char               PortIdentifier;
    unsigned char               BitIdentifier;
    
}DigitEnable_SignalDefinition;



#define TOTAL_DIGIT_MCU_PORTS  5

#define DIGIT_PORT_A_IDENTIFER 0
#define DIGIT_PORT_B_IDENTIFER 1
#define DIGIT_PORT_C_IDENTIFER 2
#define DIGIT_PORT_D_IDENTIFER 3
#define DIGIT_PORT_E_IDENTIFER 4

#define DIGIT_BIT_0_IDENTIFER 0
#define DIGIT_BIT_1_IDENTIFER 1
#define DIGIT_BIT_2_IDENTIFER 2
#define DIGIT_BIT_3_IDENTIFER 3
#define DIGIT_BIT_4_IDENTIFER 4
#define DIGIT_BIT_5_IDENTIFER 5
#define DIGIT_BIT_6_IDENTIFER 6
#define DIGIT_BIT_7_IDENTIFER 7

#define DIGIT_IN_PORT_BITWISEMASK_BIT_0  0b00000001 
#define DIGIT_IN_PORT_BITWISEMASK_BIT_1  0b00000010 
#define DIGIT_IN_PORT_BITWISEMASK_BIT_2  0b00000100 
#define DIGIT_IN_PORT_BITWISEMASK_BIT_3  0b00001000 
#define DIGIT_IN_PORT_BITWISEMASK_BIT_4  0b00010000 
#define DIGIT_IN_PORT_BITWISEMASK_BIT_5  0b00100000 
#define DIGIT_IN_PORT_BITWISEMASK_BIT_6  0b01000000 
#define DIGIT_IN_PORT_BITWISEMASK_BIT_7  0b10000000 


// Mapping of Segment Enable HW signals to Bits in Ports (See schematic )
const DigitEnable_SignalDefinition DigitEnableDefinitionArray[TOTAL_DIGITS] = 
{
    //Signal_Identifier      ,    PortIdentifier          ,    BitIdentifier   } },
    {Digit_00_Signal         ,    DIGIT_PORT_C_IDENTIFER  ,    DIGIT_BIT_0_IDENTIFER  },// DIGIT_EN_00_SIGNAL_RC0---  //
    {Digit_01_Signal         ,    DIGIT_PORT_C_IDENTIFER  ,    DIGIT_BIT_1_IDENTIFER  },// DIGIT_EN_01_SIGNAL_RC1---  //
    {Digit_02_Signal         ,    DIGIT_PORT_C_IDENTIFER  ,    DIGIT_BIT_2_IDENTIFER  },// DIGIT_EN_02_SIGNAL_RC2---  //
    {Digit_03_Signal         ,    DIGIT_PORT_B_IDENTIFER  ,    DIGIT_BIT_5_IDENTIFER  },// DIGIT_EN_03_SIGNAL_RB5---  //
    {Digit_04_Signal         ,    DIGIT_PORT_B_IDENTIFER  ,    DIGIT_BIT_4_IDENTIFER  },// DIGIT_EN_04_SIGNAL_RB4---  //
    {Digit_05_Signal         ,    DIGIT_PORT_B_IDENTIFER  ,    DIGIT_BIT_3_IDENTIFER  },// DIGIT_EN_05_SIGNAL_RB3---  //
    {Digit_06_Signal         ,    DIGIT_PORT_B_IDENTIFER  ,    DIGIT_BIT_2_IDENTIFER  },// DIGIT_EN_06_SIGNAL_RB2---  //
    {Digit_07_Signal         ,    DIGIT_PORT_B_IDENTIFER  ,    DIGIT_BIT_1_IDENTIFER  },// DIGIT_EN_07_SIGNAL_RB1---  //
};

const unsigned char DIG_InPort_BitwiseMaskArray[8] = 
{ 
        DIGIT_IN_PORT_BITWISEMASK_BIT_0,
        DIGIT_IN_PORT_BITWISEMASK_BIT_1,
        DIGIT_IN_PORT_BITWISEMASK_BIT_2,
        DIGIT_IN_PORT_BITWISEMASK_BIT_3,
        DIGIT_IN_PORT_BITWISEMASK_BIT_4,
        DIGIT_IN_PORT_BITWISEMASK_BIT_5,
        DIGIT_IN_PORT_BITWISEMASK_BIT_6,
        DIGIT_IN_PORT_BITWISEMASK_BIT_7,
};

unsigned char DIG_PortsABCDE_LoadsArray[TOTAL_DIGIT_MCU_PORTS] = 
{ 
        0, // load for PORTA   
        0, // load for PORTB   
        0, // load for PORTC   
        0, // load for PORTD   
        0, // load for PORTE 
};
                                                                
void ConvertDigitEnableToPortLoad(unsigned char DigitIndex, DigitEnable_ElecticalWiring *outputPTR)
{
    unsigned char portIndicator;
    unsigned char bitIndicator;
    unsigned char DigInPort_BitwiseMask;

    DIG_PortsABCDE_LoadsArray[DIGIT_PORT_A_IDENTIFER] = 0;
    DIG_PortsABCDE_LoadsArray[DIGIT_PORT_B_IDENTIFER] = 0;
    DIG_PortsABCDE_LoadsArray[DIGIT_PORT_C_IDENTIFER] = 0;
    DIG_PortsABCDE_LoadsArray[DIGIT_PORT_D_IDENTIFER] = 0;
    DIG_PortsABCDE_LoadsArray[DIGIT_PORT_E_IDENTIFER] = 0;  
        
    if(DigitIndex < TOTAL_DIGITS )
    {
        portIndicator = DigitEnableDefinitionArray[DigitIndex].PortIdentifier;
        bitIndicator = DigitEnableDefinitionArray[DigitIndex].BitIdentifier;
     
        DigInPort_BitwiseMask     = DIG_InPort_BitwiseMaskArray[bitIndicator];
        
        // This segment is needed in the pattern, turn the signal
        DIG_PortsABCDE_LoadsArray[portIndicator] = DIG_PortsABCDE_LoadsArray[portIndicator] | DigInPort_BitwiseMask;
    }
    else
    {
        
    }

   outputPTR->port_A_load = DIG_PortsABCDE_LoadsArray[DIGIT_PORT_A_IDENTIFER];
   outputPTR->port_B_load = DIG_PortsABCDE_LoadsArray[DIGIT_PORT_B_IDENTIFER];
   outputPTR->port_C_load = DIG_PortsABCDE_LoadsArray[DIGIT_PORT_C_IDENTIFER];
   outputPTR->port_D_load = DIG_PortsABCDE_LoadsArray[DIGIT_PORT_D_IDENTIFER];
   outputPTR->port_E_load = DIG_PortsABCDE_LoadsArray[DIGIT_PORT_E_IDENTIFER];
}