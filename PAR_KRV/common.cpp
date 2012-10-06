#include "Container.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;

int randInt(int max = 10){
    //srand((unsigned)time(NULL)); 
    int r = rand(); 
    return r % max; 
}



// vraci pocet figurek ve sloupci ve kterem je s
int jeVeSloupciFigurka(int s, Container * c){
    int size = c->getSize();
    // najdi si sloupec
    int mod = s%size;
    int counter = 0;
    for(int i = mod; i < size*size; i+=size){
        if(c->isOne(i)) counter++;
    }
    return counter;
}
// -||- v radku
int jeVRadkuFigurka(int r, Container * c){
    int size = c->getSize();
    // najdi si radek
    int mod = r/size;
    int counter = 0;
    for(int i = mod*size; i < ((mod*size)+size);i++ ){
        if(c->isOne(i)) counter++;
    }
    return counter;
    
}


//   hledej \ diagonalu
void hledejSikmo1(int from, Container * c, int * f){
    int size = c->getSize();
    int l_h = -1;
    int p_s = -1;
    
    int x = from / size;
    int y = from % size;
    int delimiter = min(x,y);
    int delimiter2 = size - (max(x,y))-1;
    
    int pointer = from;
    for(int i = 0; i < delimiter; i++){
        pointer -= (size+1);
        if(c->isOne(pointer)){
            l_h = pointer;
            break;
        }
        else if(c->isFig(pointer)){
            break;
        }
    }
    pointer = from;
    for(int i = 0; i < delimiter2; i++){
        pointer += (size+1);
        if(c->isOne(pointer)){
            p_s = pointer;
            break;
        }
        else if(c->isFig(pointer)){
            break;
        }
    }
    f[4] = l_h;
    f[5] = p_s;
}
// hledej / diagonalu
void hledejSikmo2(int from, Container * c, int * f){
  int size = c->getSize();
    int l_s = -1;
    int p_h = -1;
    
    int x = from / size;
    int y = size - (from % size) -1;
    int delimiter = min(x,y);
    int delimiter2 = size - (max(x,y))-1;
    
    int pointer = from;
    for(int i = 0; i < delimiter; i++){
        pointer -= (size-1);
        if(c->isOne(pointer)){
            l_s = pointer;
            break;
        }
        else if(c->isFig(pointer)){
            break;
        }
    }
    pointer = from;
    for(int i = 0; i < delimiter2; i++){
        pointer += (size-1);
        if(c->isOne(pointer)){
            p_h = pointer;
            break;
        }
        else if(c->isFig(pointer)){
            break;
        }
    }
    f[6] = l_s;
    f[7] = p_h;
}

void hledejVRadku(int from, Container *c, int * x){
    int vlevo = -1;
    int vpravo = -1;
    int size = c->getSize();
    
    int pointer = from;
    while(vlevo == -1){
        if(pointer%size == 0 || pointer <= 0) break;
        pointer--;
        if(c->isOne(pointer)){
            vlevo = pointer;
            break;
        }
        else if(c->isFig(pointer))break;
    }
    pointer = from;
    while(vpravo == -1){
        if(pointer%size == (size-1)) break;
        pointer++;
        if(c->isOne(pointer)){
          vpravo = pointer;
          break;
        }
        else if(c->isFig(pointer))break; 
    }
    x[0] = vlevo;
    x[1] = vpravo;
    
}
void hledejVSloupci(int from, Container *c, int *x){
    int nahore = -1;
    int dole = -1;
    int size = c->getSize();
    // nahore
    int pointer = from;
    while(nahore == -1){
        if(pointer < 0 ) break;
        pointer -= size;
        if(c->isOne(pointer)) nahore = pointer;
        else if(c->isFig(pointer))break;
    }
    
    // dole
    pointer = from;
    while(dole == -1){
        if(pointer > size*size) break;
        pointer += size;
        if(c->isOne(pointer)) dole = pointer;
        else if(c->isFig(pointer))break;
    }
    x[2] = nahore;
    x[3] = dole;
}
