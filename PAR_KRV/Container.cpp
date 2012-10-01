/* 
 * File:   Container.cpp
 * Author: dawe
 * 
 * Created on September 24, 2012, 11:58 AM
 */

#include "Container.h"
#include <iostream>

using namespace std;



Container::Container() {
}

Container::Container(int n, int figCount){
    if( n < 5) cout << "n je mimo povoleny rozsah";
    
    result = 0;
    
    //pole = new int[n][n];
    
     pole = new int*[n];
     for(int i = 0; i < n; i++){
         pole[i] = new int[n];
     }
     
     for(int i = 0; i < n; i++){
         for(int j = 0; j < n; j++){
             pole[i][j] = 0;
         }
     }
     
     this->n = n;
     if(n > figCount || ((n*(n+1)/2)) < figCount ){
         cout << "figCount je mimo povoleny rozsah";     
     }else  k = figCount;
    
}

Container::Container(const Container& orig) {
}

Container::~Container() {
}

void Container::print(){
   for(int i = 0; i < n; i++){
         for(int j = 0; j < n; j++){
             cout << pole[i][j] << " ";
         }
         cout << endl;
     }
   cout << "Figurek: " << k << " Cena: " << result << endl;
}

void Container::setX(Souradnice s, int fig){
    pole[s.x][s.y] = fig;
}
int ** Container::getPole(){
    return this->pole;
}

int Container::getSize(){
    return this->n;
}

void Container::setCount(int newK){
    k = newK;
}

int Container::getCount(){
    return k;
}

void Container::addPrice(int i){
    result = result + i;
}