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
    this->result = 0;
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
     
     
     if(n > k || ((n*(n+1)/2)) < k ){
         cout << "k je mimo povoleny rozsah";     
     }
    
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
   cout << "result: " << this->result     << endl;
   cout << "limit:  " << this->upperLimit << endl;
   
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
int Container::getK(){
    return this->k;
}
int Container::getResult(){
    return this->result;
}
int Container::getUpperLimit(){
    return this->upperLimit;
}
void Container::addResult(int add){
    this->result += add;
}
void Container::setPole(int** p){
    pole = new int*[n];
     for(int i = 0; i < n; i++){
         pole[i] = new int[n];
     }
     
     for(int i = 0; i < n; i++){
         for(int j = 0; j < n; j++){
             pole[i][j] = p[i][j];
         }
     }
}
bool Container::overLimit(){
    if(this->result > this->upperLimit){
        return true;
    }
    return false;
}
void Container::setResult(int res){
    this->result = res;
}
int Container::getValue(int x, int y){
    return this->pole[x][y];
}