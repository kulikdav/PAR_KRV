/* 
 * File:   main.cpp
 * Author: dawe
 *
 * Created on October 3, 2012, 12:40 PM
 */

#include <cstdlib>
#include <iostream>
#include <stack>
#include "Container.h"
#include "common.h"
#include <time.h>

using namespace std;

int main(int argc, char** argv) {
    // k = 2*size
    // 14 ~ 24s
    // 16 ~ 1m34
    // 17 ~ 
    
    int size = 17;
    //int k = (size * (size - 1)) / 2;
    int k = 2 * size;
    int best_possible = k * 10;
    stack<Container *> zasobnik;
    Container * test = new Container(size, k);
    Container * best = new Container(size, k);
    best->setResult(k * 20);

    cout << "initial best: " << best->getResult() << " " << k << endl;
    cout << "best_possible: " << best_possible << endl;
    test->setVez(3);
    test->setKral(0);
    for (int i = 0; i < k; i++) {
        int rand = randInt(size * size);
        if (!test->isFig(rand)) {
            test->addFig(rand);
        } else i--;
    }

    cout << "init state:" << endl;
    test->printf();
    zasobnik.push(test);
    int p = 0;
    int pd = 0;

    while (!zasobnik.empty()) {
        Container * top = zasobnik.top();
        zasobnik.pop();



        //top->printf();


        if (top->zbyvaFigurek() == 0 && top->getResult() < best->getResult()) {
            best->setResult(top->getResult());
            cout << "newbest found: " << best->getResult() << " " << zasobnik.size() << endl;
            if (best->getResult() == best_possible) {
                cout << "nalezena spodni mez" << endl;
                break;
            }

        }


        int mincena = top->getResult() + (top->zbyvaFigurek()*10);
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
                        ps->posunFigurku(branchvez[i], 4);
                        ps->addResult(10);
                        int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                        if (cena < best->getResult()) {
                            zasobnik.push(ps);
                        } else {
                            pd++;
                            delete ps;
                        }
                    }
                }
            } else {
                for (int i = 0; i < 8; i++) {
                    if (branchkral[i] != -1) {
                        Container *ps = new Container(size, k);
                        p++;
                        ps->setKral(top->getKral());
                        ps->setResult(top->getResult());
                        ps->setVez(top->getVez());
                        ps->setPole(top->getPole());
                        ps->posunFigurku(branchkral[i], 8);
                        ps->addResult(15);
                        int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                        if (cena < best->getResult()) {
                            zasobnik.push(ps);
                        } else {
                            delete ps;
                            pd++;
                        }
                    }
                }
                for (int i = 0; i < size; i++) {
                    if (posunRadek[i] == 1) {
                        Container *ps = new Container(size, k);
                        p++;
                        ps->setKral(top->getKral());
                        ps->setResult(top->getResult());
                        ps->setVez(top->getVez());
                        ps->setPole(top->getPole());
                        ps->posunFigurku(((x * size) + i), 4);
                        ps->addResult(10);
                        int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                        if (cena < best->getResult()) {
                            zasobnik.push(ps);
                        } else {
                            delete ps;
                            pd++;
                        }
                    }
                }
                for(int i = 0; i < size; i++){
                    if(posunSloup[i] != -1){
                        Container *ps = new Container(size, k);
                        p++;
                        ps->setKral(top->getKral());
                        ps->setResult(top->getResult());
                        ps->setVez(top->getVez());
                        ps->setPole(top->getPole());
                        ps->posunFigurku(posunSloup[i], 4);
                        ps->addResult(10);
                        int cena = (ps->getResult() + (ps->zbyvaFigurek()*10));
                        if (cena < best->getResult()) {
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
}