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
    
    this->historyVQ = new int[2*n*n];
    this->historyCount = 0;
    
    pole = new int[k];
    for(int i = 0; i < k; i++) pole[i] = -1;
    
} 

Container::Container(const Container& orig) {
    
}

Container::~Container() { 
    delete [] pole;
    delete [] historyVQ;
}
void Container::printf(){
    cout <<  "K(" << kralovna << ") -- V(" << vez << ")" << endl;
    for(int i = 0; i < (n*n); i++){
        if(kralovna == i) cout << 8;
        else if(vez == i) cout << 4;
        else if( this->isFig(i) ) cout << 1;
        else cout << 0;
        
        if(i % n == n-1) cout << endl;
        else cout << " ";
        
     }
    cout << endl;
}
void Container::print(){
   for(int i = 0; i < this->k; i++){
       int y = pole[i]%n;
       int x = pole[i]/n;
     cout << '('<< pole[i] << "[" << x << "," << y << "]" << ")";    
     }
   cout << "\nresult: " << this->result     << endl;
   cout << "limit:  " << this->upperLimit << endl;
   
}
void Container::printTahCount(){
    cout << endl << "Bylo potreba " << this->tahCount << " tahu!" << endl << endl << endl;
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
    //this->historyQV[this->historyCount] = pos;
}
void Container::setKral(int pos){
    this->kralovna = pos;
    //this->historyQV[this->historyCount] = pos;
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
void Container::setTahCount(int count){
    this->tahCount = count;
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

void Container::setHistoryQV(int* history){
    for (int i = 0; i < 2*n*n; i++){
        this->historyVQ[i] = history[i];
    }
}

void Container::setInitialHistory(int Q, int V){
    historyVQ[0] = V;
    historyVQ[1] = Q;
    historyCount = 2;
}

void Container::posunFigurku(int dest, int fig){
    if(fig == 4){
        vez = dest;
        
        this->historyVQ[historyCount] = dest;
        this->historyVQ[historyCount+1] = -1;
        this->historyVQ[historyCount+2] = -2; //break
        this->historyCount = this->historyCount + 2;
        
        this->tahCount++;
    }
    else if(fig == 8){
        kralovna = dest;
        
        this->historyVQ[historyCount] = -1;
        this->historyVQ[historyCount+1] = dest;
        this->historyVQ[historyCount+2] = -2; //break
        this->historyCount = this->historyCount + 2;
        
        this->tahCount++;
    }
    else {
        cout << "error";
    }
    if(this->isOne(dest)){
        for(int i = 0; i < k; i++){
            if(pole[i] == dest)
                pole[i] = -1;
        }
    }
}

void Container::posunFigurkuBezHistorie(int dest, int fig){
    if(fig == 4){
        vez = dest;
    }
    else if(fig == 8){
        kralovna = dest;
    }
    else {
        cout << "error";
    }
    if(this->isOne(dest)){
        for(int i = 0; i < k; i++){
            if(pole[i] == dest)
                pole[i] = -1;
        }
    }
}

void Container::printHistroy(){ 
    cout << "Tahy: ";
    for (int i = 0; i < (2*n*n); i++){
        if (historyVQ[i] == -2) break;
        if (historyVQ[i] == -1) cout << "x> -> ";
        
        else cout << historyVQ[i] << " -> ";
    }
    cout << "END" << endl;
    
}

