/* 
 * File:   AsciiCharacterLedPattern.h
 * Author: Radu
 *
 * Created on June 20, 2021, 5:44 PM
 */

#ifndef ASCIICHARACTERLEDPATTERN_H
#define	ASCIICHARACTERLEDPATTERN_H

#define TOTAL_LED_ASCII 128
// a | b | c | d | e | f | g1 | g2 | h | i | j | k | l | m | dp |
#define _NA_CHARACTER_PATTERN 0b0000000000000000

unsigned int GetASCIIToSegmentPattern(unsigned char ASCII_Letter);
unsigned char GetHexValOfAscii(unsigned char Index_Of_ASCII_Letter);

#endif	/* LEDACTUATION_H */

