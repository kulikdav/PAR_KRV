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

Container::Container(int n, int k){
    if( n < 5) cout << "n je mimo povoleny rozsah";
    
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
     if(n > k || ((n*(n+1)/2)) < k ){
         cout << "k je mimo povoleny rozsah";     
     }else  this->k = k;
    
}

Container::Container(const Container& orig) {
}

Container::~Container() {
}

void Container::print(){
   for(int i = 0; i < this->n; i++){
         for(int j = 0; j < this->n; j++){
             cout << pole[i][j] << " ";
         }
         cout << endl;
     }
}
