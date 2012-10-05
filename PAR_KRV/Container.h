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
    int pos;
};

struct Container {
public: 
    Container();
    Container(int n, int k);
    Container(const Container& orig);
    virtual ~Container();
    
    void printf();
    void print();
    int getK();
    int getSize();
    bool isFig(int pos);
    int getVez();
    int getKral();
    void setVez(int pos);
    void setKral(int pos);
    void addFig(int pos);
    bool isOne(int pos);
    int * getPole();
    void setPole(int * pole);
    int getResult(){return this->result;}
    void setResult(int res){this->result = res;}
    void addResult(int add){this->result += add;}
    int zbyvaFigurek();
    void posunFigurku(int dest, int orig, int fig);
    
private:
    int n;
    int k;
    int * pole;
    
    int result;
    int upperLimit;
    Souradnice * history;
    int counter;
    int vez;
    int kralovna;
    /* 
     * prazdne pole = 0
     * figurky 1
     * kralovna 8
     * vez      4
     
     */
};

#endif	/* CONTAINER_H */

