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

struct Container {
public: 
    Container();
    Container(int n, int k);
    Container(const Container& orig);
    virtual ~Container();
    
    void printf();
    void print();
    void printTahCount();
    void recursivePrint();
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
    void posunFigurku(int dest, int fig);
    void posunFigurkuBezHistorie(int dest, int fig);
    int getTahCount(){return this->tahCount;};
    void setTahCount(int count);
    
    void printHistroy();
    int * getHistoryQV(){ return this->historyVQ;};
    int getHistoryCount(){return this->historyCount;};
    void setHistoryQV(int * history);
    void setInitialHistory(int Q, int V);
    void setHistoryCount(int count){this->historyCount = count;};

private:
    int n;
    int k;
    int * pole;
    
    //Container * original;
    
    int result;
    int upperLimit;
    int counter;
    int tahCount;
    int vez;
    int kralovna;
    
    int * historyVQ;
    
    //int * historyVez;
    //int * historyKralovna;
    int historyCount;
    
};

#endif	/* CONTAINER_H */

