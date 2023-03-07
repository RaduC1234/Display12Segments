/* 
 * File:   SignalControl_SegmentEnable.h
 * Author: Radu
 *
 * Created on June 20, 2021, 5:50 PM
 */

#ifndef SIGNALCONTROLSEGMENTENABLE_H
#define	SIGNALCONTROLSEGMENTENABLE_H

typedef struct 
{
    unsigned char port_A_load;
    unsigned char port_B_load;
    unsigned char port_C_load;
    unsigned char port_D_load;
    unsigned char port_E_load;
    
}SegmentEnable_ElecticalWiring;

void ConvertPatternToPortLoad(unsigned int convertionPattern, SegmentEnable_ElecticalWiring *outputPTR);

#endif	/* LEDACTUATION_H */

