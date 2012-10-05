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
    this->upperLimit = 20*k;
    this->n = n;
    this->k = k;
    this->counter = 0;
    this->result = 0;
    this->vez = -1;
    this->kralovna = -1;
    //history = new Souradnice[n*n];
    pole = new int[k];
    for(int i = 0; i < k; i++) pole[i] = -1;
} 

Container::Container(const Container& orig) {
    
}

Container::~Container() { 
    delete [] pole;
    delete [] history;
}
void Container::printf(){
    for(int i = 0; i < (n*n); i++){
        if(vez == i) cout << 4;
        else if(kralovna == i) cout << 8;
        else if( this->isFig(i) ) cout << 1;
        else cout << 0;
        
        if(i % n == n-1) cout << endl;
        else cout << " ";
        
     }
}
void Container::print(){
   for(int i = 0; i < this->k; i++){
       int y = pole[i]%n;
       int x = pole[i]/n;
     cout << pole[i] << "[" << x << "," << y << "]" << endl;    
     }
   cout << "result: " << this->result     << endl;
   cout << "limit:  " << this->upperLimit << endl;
   
}
bool Container::isOne(int pos){
    
    for(int i = 0; i < this->k; i++){
        if(pole[i] == pos) return true;
    }
    return false;
}
bool Container::isFig(int pos){
    if(vez == pos || kralovna == pos) return true;
    for(int i = 0; i < this->k; i++){
        if(pole[i] == pos) return true;
    }
    return false;
}
int Container::getKral(){
    return this->kralovna;
}
int Container::getVez(){
    return this->vez;
}
void Container::setVez(int pos){
    this->vez = pos;
}
void Container::setKral(int pos){
    this->kralovna = pos;
}
void Container::addFig(int pos){
    this->pole[this->counter++] = pos; 
}
int Container::getSize(){
    return this->n;
}
int * Container::getPole(){
    return this->pole;
}
void Container::setPole(int * pole){
    for(int i = 0; i < k; i++){
        this->pole[i] = pole[i];
    }
}
int Container::zbyvaFigurek(){
    int counter = 0;
    for(int i = 0; i < k; i++){
        if(this->pole[i] != -1) counter++;
    }
    return counter;
}

void Container::posunFigurku(int dest, int orig, int fig){
    if(fig == 4) vez = dest;
    else if(fig == 8) kralovna = dest;
    if(this->isOne(dest)){
        for(int i = 0; i < k; i++){
            if(pole[i] == dest)
                pole[i] = -1;
        }
    }
}