/* 
 * File:   common.h
 * Author: dawe
 *
 * Created on September 24, 2012, 3:15 PM
 */

#ifndef COMMON_H
#define	COMMON_H


int randInt(int max);
Souradnice * randSouradnice(int size, Souradnice * s);
void presunFigurku(Souradnice s, Souradnice origin, int fig, Container * c);
bool jeVeSloupciFigurka(int s, Container * c);
bool jeVRadkuFigurka(int r, Container * c);
Souradnice * hledejSikmo1(Souradnice s, Container * c, Souradnice * f);
Souradnice * hledejSikmo2(Souradnice s, Container * c, Souradnice * f);
Souradnice * hledejVRadku(Souradnice s, Container * c, Souradnice * f);
Souradnice * hledejVsloupci(Souradnice s, Container * c, Souradnice * f);

#endif	/* COMMON_H */

