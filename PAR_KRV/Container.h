/* 
 * File:   Container.h
 * Author: dawe
 *
 * Created on September 24, 2012, 11:58 AM
 */
#include <iostream>
#include <string>
using namespace std;

#ifndef CONTAINER_H
#define	CONTAINER_H

  struct Souradnice{
    int fig;
    int x;
    int y;
    Souradnice(){
        this->x = -1;
        this->y = -1;
        this->fig = -1;
    }
    Souradnice(int x, int y){
        this->x = x;
        this->y = y;
        this->fig = -1;
    }
    Souradnice(int x, int y, int fig){
        this->x = x;
        this->y = y;
        this->fig = fig;
    }
    void print(){
        if(this->x != -1 && this->y != -1){
          if(this->fig > 0) cout << fig;
          cout << "[" << this->x << "," << this->y << "]" << endl;
        }
    }
    bool isValid(){
        if(this->x != -1 && this->y != -1) return true;
        return false;
    }
    
};

struct Container {
public:
    
  
    
    Container();
    Container(int n, int k);
    Container(const Container& orig);
    virtual ~Container();
    
    void print();
    void setX(Souradnice s, int fig);
    int getK();
    int getSize();
    int ** getPole();
    int getResult();
    int getUpperLimit();
    void setPole(int ** p);
    void setHistory(Souradnice * s);
    void setResult(int res);
    void addResult(int add);
    bool overLimit();
    int getValue(int x, int y);
    Souradnice * getHistory();
    void addHistory(Souradnice s);
    int getCounter(){return this->counter;}
    void setCounter(int c){ this->counter = c;}
    
    
    
    
private:
    int n;
    int k;
    int ** pole;
    
    int result;
    int upperLimit;
    Souradnice * history;
    int counter;
    /* 
     * prazdne pole = 0
     * figurky 1
     * kralovna 8
     * vez      4
     
     */
};

#endif	/* CONTAINER_H */

