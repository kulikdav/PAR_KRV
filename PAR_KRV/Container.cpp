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
    
    pole = new int[k];
    for(int i = 0; i < k; i++) pole[i] = -1;
    
} 

Container::Container(int n, int k, Container * orig){
    this->original = orig;
    
    this->upperLimit = 20*k;
    this->n = n;
    this->k = k;
    this->counter = 0;
    this->result = 0;
    this->vez = -1;
    this->kralovna = -1;
    
    pole = new int[k];
    for(int i = 0; i < k; i++) pole[i] = -1;
} 

Container::Container(const Container& orig) {
    
}

Container::~Container() { 
    delete [] pole;
}
void Container::printf(){
    cout << endl << "K(" << kralovna << ") -- V(" << vez << ")" << endl;
    for(int i = 0; i < (n*n); i++){
        if(kralovna == i) cout << 8;
        else if(vez == i) cout << 4;
        else if( this->isFig(i) ) cout << 1;
        else cout << 0;
        
        if(i % n == n-1) cout << endl;
        else cout << " ";
        
     }
    cout << endl << "Bylo potreba " << this->tahCount << " tahu!" << endl;
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
    //this->historyVez[this->historyCount] = pos;
}
void Container::setKral(int pos){
    this->kralovna = pos;
    //this->historyKralovna[this->historyCount] = pos;
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
//void Container::setOriginalPole(int * pole){
//    for(int i = 0; i < k; i++){
//        this->originalPole[i] = pole[i];
//    }
//}
int Container::zbyvaFigurek(){
    int counter = 0;
    for(int i = 0; i < k; i++){
        if(this->pole[i] != -1) counter++;
    }
    return counter;
}

//void Container::setHistoryQ(int* hist){
//    for (int i = 0; i < n*n; i++){
//        this->historyKralovna[i] = hist[i];
//    }
//}
//
//void Container::setHistoryV(int* hist){
//    for (int i = 0; i < n*n; i++){
//        this->historyVez[i] = hist[i];
//    }
//}
//
//void Container::setSpecificHistory(int fig, int histCount, int pos){
//    if(fig == 8){
//        this->historyKralovna[histCount] = pos;
//    } else if (fig == 4){
//        this->historyVez[histCount] = pos;
//    }
//}

void Container::posunFigurku(int dest, int fig){
    if(fig == 4){
        vez = dest;
//        this->historyVez[historyCount] = dest;
//        this->historyVez[historyCount+1] = -2;
//        this->historyKralovna[historyCount] = -1;
//        this->historyKralovna[historyCount+1] = -2;
//        this->historyCount++;
        this->tahCount++;
    }
    else if(fig == 8){
        kralovna = dest;
//        this->historyKralovna[historyCount] = dest;
//        this->historyKralovna[historyCount+1] = -2;
//        this->historyVez[historyCount] = -1;
//        this->historyVez[historyCount+1] = -2;
//        this->historyCount++;
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

//void Container::printHistroy(){ 
//    cout << "Tahy vezi:      ";
//    for (int i = 0; i < (n*n); i++){
//        if (historyVez[i] == -2) break;
//        if (historyVez[i] == -1) cout << "-> -> ";
//        
//        else cout << historyVez[i] << " -> ";
//    }
//    cout << "END" << endl;
//    
//    cout << "Tahy kralovnou: ";
//    for (int i = 0; i < (n*n); i++){
//        if (historyKralovna[i] == -2) break;
//        if (historyKralovna[i] == -1) cout << "-> -> ";
//        
//        else cout << historyKralovna[i] << " -> ";
//    }
//    cout << "END" << endl;
//}

void Container::recursivePrint(){
    this->printf();
    if (this->original != NULL){
        this->original->recursivePrint();
    }
}
