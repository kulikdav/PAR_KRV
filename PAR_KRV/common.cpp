#include "Container.h"
#include <iostream>
using namespace std;

int randInt(){
  return 0;   
}

void presunFigurku(Souradnice s, Souradnice origin, int fig, Container * c){
    c->setX(s, fig);
    c->setX(origin, 0);
}

Souradnice * hledejkriz(){
    Souradnice * found;
}
Souradnice * hledejdiag(){
    Souradnice * found; 
}

Souradnice * hledejVRadku(Souradnice s, Container * c){
    int x = s.x;
    int n = c->getSize();
    int ** pole = c->getPole();
    int counter = 0;
    Souradnice found [n];
    for(int i = 0 ; i < n; i++){
        found[i] = Souradnice(-1,-1);
    }
    for(int i = 0; i < n; i++){
        if(pole[x][i] == 1){
            Souradnice d(x,i);
            found[counter++] = d;
            cout << "[" << x << "," << i << "]" << endl;    
        }
    }
    return found;
}
Souradnice * hledejVsloupci(Souradnice s, Container * c){
    int y = s.y;
    int n = c->getSize();
    int ** pole = c->getPole();
    int counter = 0;
    Souradnice found [n];
    for(int i = 0 ; i < n; i++){
        found[i] = Souradnice(-1,-1);
    }
    for(int i = 0; i < n; i++){
        cout << "[" << i << "," << y << "]" << endl;    
        if(pole[i][y] == 1){
            Souradnice d(i,y);
            found[counter++] = d;
            
        }
    }
    return found;
}
