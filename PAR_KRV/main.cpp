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
    // 110 ~ 3m
    //114 ~ 16m
    int size = 114;
    int k = (size * (size - 1)) / 2;
    stack<Container *> zasobnik;
    Container * test = new Container(size, k);
    Container * best = new Container(size, k);
    best->setResult(k * 20);
    double start = clock();
    cout << start << endl;


    test->setVez(33);
    test->setKral(15);
    for (int i = 0; i < k - 1; i++) {
        int rand = randInt(size * size);
        if (!test->isFig(rand)) {
            test->addFig(rand);
        } else i--;
    }

    cout << "init state" << endl;
    test->printf();
    zasobnik.push(test);
    int pocet = 0;
    int pocet_d = 0;

    while (!zasobnik.empty()) {
        Container * top = zasobnik.top();
        zasobnik.pop();
        double part = clock();
        
        cout << part << " ";
        cout << zasobnik.size() << " ";
        cout << (top->getResult() + top->zbyvaFigurek()*10) << " - " << best->getResult() << " " ;
        cout << pocet << " / " << pocet_d << endl;
        
        int mincena = top->getResult() + (top->zbyvaFigurek()*10);
        if (mincena > best->getResult() - 10) delete top;
        else {
            int * branch = new int[12 + size];
            for (int i = 0; i < 12 + size; i++) {
                branch[i] = -1;
            }
            int kral = top->getKral();
            int vez = top->getVez();

            hledejVSloupci(vez, top, branch);
            hledejVRadku(vez, top, branch);

            //prvni redukce = pokud muze vez, nema cenu delat neco jineho. check = true <=> vez muze
            bool check1 = false;
            for (int i = 0; i < 4; i++) {
                if (branch[i] != -1) check1 = true;
            }
            if (!check1) {
                hledejVSloupci(kral, top, (branch + 4));
                hledejVRadku(kral, top, (branch + 4));
                hledejSikmo1(kral, top, (branch + 4));
                hledejSikmo2(kral, top, (branch + 4));
                int maxr = 0, maxs = 0;
                for (int i = 0; i < size; i++) {
                    int s = jeVeSloupciFigurka(i, top);
                    int r = jeVRadkuFigurka(i*size, top);
                    maxr = max(maxr, r);
                    maxs = max(maxs, s);
                }
                //cout << "max" << maxr << " " << maxs << endl;
                int br_pointer = 12;
                if (maxr >= maxs) {
                    for (int i = 0; i < size; i++) {
                        if (jeVRadkuFigurka(i * size, top) == maxr) {
                            branch[br_pointer++] = (vez + (size * (i - (vez / size))));

                        }
                    }
                } else {
                    for (int i = 0; i < size; i++) {
                        if (jeVeSloupciFigurka(i, top) == maxs) {
                            branch[br_pointer++] = ((vez / size) * size) + i;
                            // branchuj do i=teho sloupce
                        }
                    }
                }

            }
            /*for (int i = 12+size; i>=0; i--){
                cout << i << " " << branch[i] << "   ";
            }
            cout << endl;*/

            for (int i = 12 + size; i >= 0; i--) {
                if (branch[i] != -1 && branch[i] != kral && branch[i] != vez) {
                    //cout << i << ":" << branch[i] << " ";

                    Container *newc = new Container(size, k);
                    pocet++;
                    newc->setResult(top->getResult());
                    newc->setPole(top->getPole());
                    newc->setKral(top->getKral());
                    newc->setVez(top->getVez());
                    newc->addResult(10);

                    if (i < 4 || i > 12) {
                        newc->posunFigurku(branch[i], vez, 4);
                    } else {
                        newc->posunFigurku(branch[i], kral, 8);
                    }
                    //cout << endl << newc->zbyvaFigurek() << endl;
                    //newc->printf();
                    if (newc->zbyvaFigurek() > 0) {
                        int minPrice = newc->getResult() + (10 * newc->zbyvaFigurek());
                        if (minPrice < best->getResult()) {
                            zasobnik.push(newc);
                            //cout << "pushed" << endl;

                        }
                    } else if (best->getResult() > newc->getResult() && newc->zbyvaFigurek() == 0) {
                        best->setPole(newc->getPole());
                        best->setResult(newc->getResult());
                        best->setKral(newc->getKral());
                        best->setVez(newc->getVez());
                        cout << "newbest" << best->getResult() << endl;
                        best->printf();
                        delete newc;
                        pocet_d++;
                        
                    } else {
                        delete newc;
                        pocet_d++;
                    };
                }
            }
            pocet_d++;
            delete branch;
            delete top;
        }
    }
    cout << "vytvoreno / zniceno = " << pocet << " / " << pocet_d << endl;
    cout << "best:" << endl;
    best->printf();

}

