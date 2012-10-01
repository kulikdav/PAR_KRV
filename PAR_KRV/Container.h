/* 
 * File:   Container.h
 * Author: dawe
 *
 * Created on September 24, 2012, 11:58 AM
 */
#include <iostream>
using namespace std;

#ifndef CONTAINER_H
#define	CONTAINER_H

  struct Souradnice{
    //Řádek
    int x;
    // Sloupec
    int y;
    Souradnice(){
        this->x = 0;
        this->y = 0;
    }
    Souradnice(int x, int y){
        this->x = x;
        this->y = y;
    }
    void print(){
        cout << "[" << this->x << "," << this->y << "]" << endl;
    }
};

class Container {
public:
    
  
    
    Container();
    Container(int n, int k);
    Container(const Container& orig);
    virtual ~Container();
    
    void print();
    void setX(Souradnice s, int fig);
    int getSize();
    void setCount(int newK);
    int ** getPole();
    
    int getCount();
    void addPrice(int i);
    
    
private:
    int n;
    int k;
    int ** pole;
    
    int result;
    
    Container * predek;
    
    /* 
     * prazdne pole = 0
     * figurky 1
     * kralovna 8
     * vez      4
     
     */
};

#endif	/* CONTAINER_H */

