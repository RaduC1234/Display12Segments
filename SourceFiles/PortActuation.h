/* 
 * File:   LedActuation.h
 * Author: Radu
 *
 * Created on June 20, 2021, 5:44 PM
 */

#ifndef PORTACTUATION_H
#define	PORTACTUATION_H

void Setup_GPIO (void) ;
void ConfigureMultiplexSpeed(unsigned int MultiplexSpeed_Microsec);
void RefreshPortInformation(void);

void CyclicFramePrint(void);

#endif	/* PORTACTUATION_H */

