/* 
 * File:   common.h
 * Author: dawe
 *
 * Created on September 24, 2012, 3:15 PM
 */

#ifndef COMMON_H
#define	COMMON_H


int randInt(int max);
bool jeVeSloupciFigurka(int s, Container * c);
bool jeVRadkuFigurka(int r, Container * c);
void hledejSikmo1(int from, Container * c, int * f);
void hledejSikmo2(int from, Container * c, int * f);
void hledejVRadku(int from, Container * c, int * x);
void hledejVSloupci(int from, Container * c, int * x);

#endif	/* COMMON_H */

