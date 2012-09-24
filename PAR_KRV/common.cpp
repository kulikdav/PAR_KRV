#include "Container.h"

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

void hledejVRadku(int x, int y){
    int i = 0;
}
void hledejVsloupci(int x, int y);
