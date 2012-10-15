/* 
 * File:   main.cpp
 * Author: dawe
 *
 * Created on October 3, 2012, 12:40 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include "Container.h"
#include "common.h"

using namespace std;

#define SOUBOR "data/TestFile-(11x11)-65.txt"

int main(int argc, char** argv) {

    int size,k,Q,V;

    char *inname = SOUBOR;
    ifstream infile(inname);
    
    int * figures = NULL;

    if (!infile) {
        cout << "There was a problem opening file "
             << inname
             << " for reading."
             << endl;
        return 0;
    } else {
        cout << "Opened " << inname << " for reading." << endl;
        infile >> size;
        infile >> k;
        infile >> Q;
        infile >> V;
        
        figures = new int[k];
        int i = 0;
        
        while ((!infile.eof())&&(i<k)){
            infile >> figures[i];
            i++;
        }
        
        cout << "From " << k << " expected figures, " << i << " was loaded." << endl;

    }

    int best_possible = k * 10;
    stack<Container *> zasobnik;
    Container * start = new Container(size, k);
    Container * best = new Container(size, k);
    best->setResult(k * 20);

    cout << "initial best: " << best->getResult() << " " << k << endl;
    cout << "best_possible: " << best_possible << endl;

    start->setVez(V);
    start->setKral(Q);
    
    start->setInitialHistory(Q,V);
    
    for (int i = 0; i < k; i++) {
        start->addFig(figures[i]);
    }

    cout << "init state:" << endl;
    start->printf();
    Container * printex = start;
    zasobnik.push(start);
    int p = 0;
    int pd = 0;

    // Hlavní programová smyčka
    
    while (!zasobnik.empty()) {
        Container * top = zasobnik.top();
        zasobnik.pop();
        if (top->zbyvaFigurek() == 0 && top->getResult() < best->getResult()) {
            best->setResult(top->getResult());
            best->setKral(top->getKral());
            best->setVez(top->getVez());
            best->setPole(top->getPole());
            best->setHistoryCount(top->getHistoryCount());
            best->setHistoryQV(top->getHistoryQV());
//            best->setHistoryV(top->getHistoryV());
            best->setTahCount(top->getTahCount());
            //best->setOrigContainer(top->getOriginal());
            //best->setOriginalPole(top->getOriginalPole());
            cout << "newbest found: " << best->getResult() << " " << zasobnik.size() << endl;
            if (best->getResult() == best_possible) {
                cout << "nalezena spodni mez" << endl;
                break;
            }
        }
        int mincena = top->getResult() + (top->zbyvaFigurek()*10);
        //cout << mincena << endl;
        if (mincena >= k * 20) {
            break;
        }
        //cout << zasobnik.size() << " " << top->getResult() << " " << top->zbyvaFigurek() << "   " << best->getResult() << " " << p << " " << pd << endl;
        if (mincena >= best->getResult()) {
            delete top;
            pd++;
        } else {
            int * branchvez = new int [4];
            int * branchkral = new int [8];
            int vez = top->getVez();
            int kral = top->getKral();
            //vez
            hledejVRadku(vez, top, branchvez);
            hledejVSloupci(vez, top, branchvez);
            //kralovna
            hledejVRadku(kral, top, branchkral);
            hledejVSloupci(kral, top, branchkral);
            hledejSikmo1(kral, top, branchkral);
            hledejSikmo2(kral, top, branchkral);
            //// posun veze
            int * posunSloup = new int [size];
            int * posunRadek = new int [size];
            for (int i = 0; i < size; i++) {
                posunRadek[i] = 0;
            }
            for (int i = 0; i < size; i++) {
                posunSloup[i] = -1;
            }
            int x = vez / size;
            int y = vez % size;
            int ky = kral % size;

            // posun vlevo
            for (int i = y - 1; i >= 0; i--) {
                if (top->isFig(vez - y + i)) break;
                if (jeVeSloupciFigurka(i, top) > 0)
                    posunRadek[i] = 1;
            }
            // posun vpravo
            for (int i = y + 1; i < size; i++) {
                if (top->isFig(vez + i)) break;
                if (jeVeSloupciFigurka(i, top) > 0)
                    posunRadek[i] = 1;
            }
            // posun nahorudolu
            if (posunRadek[ky] == 1) {
                for (int j = 0; j < size; j++) {
                    if (top->isOne(ky + (j * size))) {
                        posunSloup[j] = y + (j * size);
                    }
                }
            }

            bool checkvez = false;
            for (int i = 0; i < 4; i++) {
                if (branchvez[i] != -1) checkvez = true;
            }
            if (checkvez) {
                for (int i = 0; i < 4; i++) {
                    if (branchvez[i] != -1) {
                        Container *ps = new Container(size, k);
                        p++;
                        ps->setKral(top->getKral());
                        ps->setResult(top->getResult());
                        ps->setVez(top->getVez());
                        ps->setPole(top->getPole());
                        ps->setHistoryCount(top->getHistoryCount());
                        ps->setHistoryQV(top->getHistoryQV());
//                        ps->setHistoryV(top->getHistoryV());
                        ps->setTahCount(top->getTahCount());
                        //ps->setOriginalPole(top->getOriginalPole());
                        ps->posunFigurku(branchvez[i], 4);
                        ps->addResult(10);
                        int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                        if (cena < best->getResult()) {
                        //if (cena < k * 20) {
                            //ps->setOrigContainer(top->getThis());
                            zasobnik.push(ps);
                        } else {
                            pd++;
                            delete ps;
                        }
                    }
                }
            } else {
                for (int i = 0; i < size; i++) {
                    if (posunRadek[i] == 1) {
                        Container *ps = new Container(size, k);
                        p++;
                        ps->setKral(top->getKral());
                        ps->setResult(top->getResult());
                        ps->setVez(top->getVez());
                        ps->setPole(top->getPole());
                        ps->setHistoryCount(top->getHistoryCount());
                        ps->setHistoryQV(top->getHistoryQV());
//                        ps->setHistoryV(top->getHistoryV());
                        ps->setTahCount(top->getTahCount());
                        //ps->setOriginalPole(top->getOriginalPole());
                        ps->posunFigurku(((x * size) + i), 4);
                        ps->addResult(10);
                        int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                        if (cena < best->getResult()) {
                        //if (cena < k * 20) {
                            //ps->setOrigContainer(top->getThis());
                            zasobnik.push(ps);
                        } else {
                            delete ps;
                            pd++;
                        }
                    }
                }
                for (int i = 0; i < size; i++) {
                    if (posunSloup[i] != -1) {
                        Container *ps = new Container(size, k);
                        p++;
                        ps->setKral(top->getKral());
                        ps->setResult(top->getResult());
                        ps->setVez(top->getVez());
                        ps->setPole(top->getPole());
                        ps->setHistoryCount(top->getHistoryCount());
                        ps->setHistoryQV(top->getHistoryQV());
//                        ps->setHistoryV(top->getHistoryV());
                        ps->setTahCount(top->getTahCount());
                        //ps->setOriginalPole(top->getOriginalPole());
                        ps->posunFigurku(posunSloup[i], 4);
                        ps->addResult(10);
                        int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                        if (cena < best->getResult()) {
                        //if (cena < k * 20) {
                            //ps->setOrigContainer(top->getThis());
                            zasobnik.push(ps);
                        } else {
                            delete ps;
                            pd++;
                        }
                    }
                }
                for (int i = 0; i < 8; i++) {
                    if (branchkral[i] != -1) {
                        Container *ps = new Container(size, k);
                        p++;
                        ps->setKral(top->getKral());
                        ps->setResult(top->getResult());
                        ps->setVez(top->getVez());
                        ps->setPole(top->getPole());
                        ps->setHistoryCount(top->getHistoryCount());
                        ps->setHistoryQV(top->getHistoryQV());
//                        ps->setHistoryV(top->getHistoryV());
                        ps->setTahCount(top->getTahCount());
                        //ps->setOriginalPole(top->getOriginalPole());
                        ps->posunFigurku(branchkral[i], 8);
                        ps->addResult(15);
                        int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                        if (cena < best->getResult()) {
                        //if (cena < k * 20) {
                            //ps->setOrigContainer(top->getThis());
                            zasobnik.push(ps);
                        } else {
                            delete ps;
                            pd++;
                        }
                    }
                }
            }
            // uklid
            delete branchvez;
            delete branchkral;
            delete posunSloup;
            delete posunRadek;
            delete top;
            pd++;

        }
    }
    cout << "best: " << best->getResult();
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    best->printf();
    best->printHistroy();
    best->printTahCount();
    
    cout << "Rozpis tahu: " << endl;
    
    int * tahy = best->getHistoryQV();
    
    int i = 2;
    printex->printf();
    
    while(tahy[i] != -2){
        // every two fields apply
        //VK VK VK VK VK
        // Věž
        if (tahy[i] != -1){
            cout << "Vez skace na pole " << tahy[i] << endl;
            printex->posunFigurkuBezHistorie(tahy[i],4);
        }
        i++;
        
        // Královna
        if (tahy[i] != -1){
            cout << "Kralovna skace na pole " << tahy[i] << endl;
            printex->posunFigurkuBezHistorie(tahy[i],8);
        }
        
        i++;
        
        printex->printf();
    }
}

