#include "PortActuation.h"
#include "FrameManagement.h"
#include <xc.h>

#define	TOTAL_PORTS_AVAILABLE_IN_MCU 5

void DrHi_Delay (void) ;

// this array holds the "port_A_load" involved in controlling all the 12 Digits 
unsigned char Port_A_load_Digit_0_11[TOTAL_LED_CELLS] = {0,0,0,0,   0,0,0,0,   };
// this array holds the "port_B_load" involved in controlling all the 12 Digits 
unsigned char Port_B_load_Digit_0_11[TOTAL_LED_CELLS] = {0,0,0,0,   0,0,0,0,   };
// this array holds the "port_C_load" involved in controlling all the 12 Digits 
unsigned char Port_C_load_Digit_0_11[TOTAL_LED_CELLS] = {0,0,0,0,   0,0,0,0,   };
// this array holds the "port_D_load" involved in controlling all the 12 Digits 
unsigned char Port_D_load_Digit_0_11[TOTAL_LED_CELLS] = {0,0,0,0,   0,0,0,0,   };
// this array holds the "port_E_load" involved in controlling all the 12 Digits 
unsigned char Port_E_load_Digit_0_11[TOTAL_LED_CELLS] = {0,0,0,0,   0,0,0,0,   };

FullFramePortsLoad PA_LocalFrameBuffer;
unsigned int PA_MicrosecondsDelay = 0 ;  

void Setup_GPIO (void) 
{
    ANSELA = 0 ; 
    ANSELB = 0 ; 
    ANSELC = 0 ; 
    ANSELD = 0 ; 
    ANSELE = 0 ;
    
    TRISA = 0 ; 
    TRISB = 0 ; 
    TRISC = 0 ; 
    TRISD = 0 ; 
    TRISE = 0 ; 
    
    PORTA = 0 ;
    PORTB = 0 ;
    PORTC = 0 ;
    PORTD = 0 ;
    PORTE = 0 ;
}

void ConfigureMultiplexSpeed(unsigned int MultiplexSpeed_Microsec)
{
    PA_MicrosecondsDelay = MultiplexSpeed_Microsec;
}

void RefreshPortInformation(void)
{
    //Get PortLoads From Lower Layer 
    GetFullFramePortLoads(&PA_LocalFrameBuffer);
    //Fill Local Arrays
    Port_A_load_Digit_0_11[ 0] = PA_LocalFrameBuffer.PortLoad_For_Digit_00.port_A_load;
    Port_A_load_Digit_0_11[ 1] = PA_LocalFrameBuffer.PortLoad_For_Digit_01.port_A_load;
    Port_A_load_Digit_0_11[ 2] = PA_LocalFrameBuffer.PortLoad_For_Digit_02.port_A_load;
    Port_A_load_Digit_0_11[ 3] = PA_LocalFrameBuffer.PortLoad_For_Digit_03.port_A_load;
    Port_A_load_Digit_0_11[ 4] = PA_LocalFrameBuffer.PortLoad_For_Digit_04.port_A_load;
    Port_A_load_Digit_0_11[ 5] = PA_LocalFrameBuffer.PortLoad_For_Digit_05.port_A_load;
    Port_A_load_Digit_0_11[ 6] = PA_LocalFrameBuffer.PortLoad_For_Digit_06.port_A_load;
    Port_A_load_Digit_0_11[ 7] = PA_LocalFrameBuffer.PortLoad_For_Digit_07.port_A_load;

     
    Port_B_load_Digit_0_11[ 0] = PA_LocalFrameBuffer.PortLoad_For_Digit_00.port_B_load;
    Port_B_load_Digit_0_11[ 1] = PA_LocalFrameBuffer.PortLoad_For_Digit_01.port_B_load;
    Port_B_load_Digit_0_11[ 2] = PA_LocalFrameBuffer.PortLoad_For_Digit_02.port_B_load;
    Port_B_load_Digit_0_11[ 3] = PA_LocalFrameBuffer.PortLoad_For_Digit_03.port_B_load;
    Port_B_load_Digit_0_11[ 4] = PA_LocalFrameBuffer.PortLoad_For_Digit_04.port_B_load;
    Port_B_load_Digit_0_11[ 5] = PA_LocalFrameBuffer.PortLoad_For_Digit_05.port_B_load;
    Port_B_load_Digit_0_11[ 6] = PA_LocalFrameBuffer.PortLoad_For_Digit_06.port_B_load;
    Port_B_load_Digit_0_11[ 7] = PA_LocalFrameBuffer.PortLoad_For_Digit_07.port_B_load;

    
    Port_C_load_Digit_0_11[ 0] = PA_LocalFrameBuffer.PortLoad_For_Digit_00.port_C_load;
    Port_C_load_Digit_0_11[ 1] = PA_LocalFrameBuffer.PortLoad_For_Digit_01.port_C_load;
    Port_C_load_Digit_0_11[ 2] = PA_LocalFrameBuffer.PortLoad_For_Digit_02.port_C_load;
    Port_C_load_Digit_0_11[ 3] = PA_LocalFrameBuffer.PortLoad_For_Digit_03.port_C_load;
    Port_C_load_Digit_0_11[ 4] = PA_LocalFrameBuffer.PortLoad_For_Digit_04.port_C_load;
    Port_C_load_Digit_0_11[ 5] = PA_LocalFrameBuffer.PortLoad_For_Digit_05.port_C_load;
    Port_C_load_Digit_0_11[ 6] = PA_LocalFrameBuffer.PortLoad_For_Digit_06.port_C_load;
    Port_C_load_Digit_0_11[ 7] = PA_LocalFrameBuffer.PortLoad_For_Digit_07.port_C_load;

    
    Port_D_load_Digit_0_11[ 0] = PA_LocalFrameBuffer.PortLoad_For_Digit_00.port_D_load;
    Port_D_load_Digit_0_11[ 1] = PA_LocalFrameBuffer.PortLoad_For_Digit_01.port_D_load;
    Port_D_load_Digit_0_11[ 2] = PA_LocalFrameBuffer.PortLoad_For_Digit_02.port_D_load;
    Port_D_load_Digit_0_11[ 3] = PA_LocalFrameBuffer.PortLoad_For_Digit_03.port_D_load;
    Port_D_load_Digit_0_11[ 4] = PA_LocalFrameBuffer.PortLoad_For_Digit_04.port_D_load;
    Port_D_load_Digit_0_11[ 5] = PA_LocalFrameBuffer.PortLoad_For_Digit_05.port_D_load;
    Port_D_load_Digit_0_11[ 6] = PA_LocalFrameBuffer.PortLoad_For_Digit_06.port_D_load;
    Port_D_load_Digit_0_11[ 7] = PA_LocalFrameBuffer.PortLoad_For_Digit_07.port_D_load;

    
    Port_E_load_Digit_0_11[ 0] = PA_LocalFrameBuffer.PortLoad_For_Digit_00.port_E_load;
    Port_E_load_Digit_0_11[ 1] = PA_LocalFrameBuffer.PortLoad_For_Digit_01.port_E_load;
    Port_E_load_Digit_0_11[ 2] = PA_LocalFrameBuffer.PortLoad_For_Digit_02.port_E_load;
    Port_E_load_Digit_0_11[ 3] = PA_LocalFrameBuffer.PortLoad_For_Digit_03.port_E_load;
    Port_E_load_Digit_0_11[ 4] = PA_LocalFrameBuffer.PortLoad_For_Digit_04.port_E_load;
    Port_E_load_Digit_0_11[ 5] = PA_LocalFrameBuffer.PortLoad_For_Digit_05.port_E_load;
    Port_E_load_Digit_0_11[ 6] = PA_LocalFrameBuffer.PortLoad_For_Digit_06.port_E_load;
    Port_E_load_Digit_0_11[ 7] = PA_LocalFrameBuffer.PortLoad_For_Digit_07.port_E_load;

}

void CyclicFramePrint(void)
{
    unsigned char LoopCounter = 0 ; 
    
    for(LoopCounter = 0; LoopCounter < TOTAL_LED_CELLS; LoopCounter++)
    {
        PORTA = Port_A_load_Digit_0_11[LoopCounter];
        PORTB = Port_B_load_Digit_0_11[LoopCounter];
        PORTC = Port_C_load_Digit_0_11[LoopCounter];
        PORTD = Port_D_load_Digit_0_11[LoopCounter];
        PORTE = Port_E_load_Digit_0_11[LoopCounter];
        
        DrHi_Delay ();
    }
}

void DrHi_Delay (void) 
{
    unsigned int Inner_Loop; 
    unsigned int Outer_Loop; 
    unsigned int DummyValue = 0 ; ; 
    
    for(Outer_Loop = 0 ; Outer_Loop < 50 ; Outer_Loop++)
    {
        for(Inner_Loop = 0 ; Inner_Loop < 50 ; Inner_Loop++)
        {
            DummyValue = 1;; 
        }
    }
}