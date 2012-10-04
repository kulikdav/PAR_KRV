#include "Container.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;





int zbyvaFigurek(Container *c){
    int ** p = c->getPole();
    int counter = 0;
    for(int i=0; i < c->getSize(); i++){
        for(int j=0; j < c->getSize(); j++){
           if(p[i][j] == 1) counter++;   
        }
    }
    return counter;
    
}
int randInt(int max = 10){
    srand((unsigned)time(NULL)); 
    int r = rand(); 
    return r % max; 
}

Souradnice * randSouradnice(int max, Souradnice *s ){
    
    s->x = randInt(max);
    s->y = randInt(max);
    return s;
}

Souradnice najdiVez(Container *c){
    int n = c->getSize();
    int ** pole = c->getPole();
    int fig = 4;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(pole[i][j] == fig) return Souradnice(i,j);
        }
    }
    //c->print();
    
    return Souradnice(-1,-1);
}
Souradnice  najdiKralovnu(Container *c){
    int n = c->getSize();
    int ** pole = c->getPole();
    int fig = 8;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(pole[i][j] == fig) return Souradnice(i,j);
        }
    }
}

void presunFigurku(Souradnice s, Souradnice origin, int fig, Container * c){
    c->setX(s, fig);
    c->setX(origin, 0);
}
// vraci pocet figurek ve sloupci
int jeVeSloupciFigurka(int s, Container * c){
    int ** pole = c->getPole();
    int n = c->getSize();
    int counter = 0;
    for(int i = 0; i < n; i++){
        if(pole[i][s] == 1) counter++;
    }
    return counter;
}
// -||- v radku
int jeVRadkuFigurka(int r, Container * c){
    int ** pole = c->getPole();
    int n = c->getSize();
    int counter = 0;
    for(int i = 0; i < n; i++){
        if(pole[r][i] == 1) counter++;
    }
    
    return counter;
}


//   hledej \ diagonalu
Souradnice * hledejSikmo1(Souradnice s, Container * c, Souradnice * f){
    int x = s.x;
    int y = s.y;
    int n = c->getSize();
    int ** pole = c->getPole();
    for(int i = 0 ; i < 2; i++){
        f[i] = Souradnice(-1,-1);
    }
    
    // vlevo nahore
    if(y > 0 && x > 0){
        int i = x-1;
        int j = y-1;
        while( i >= 0 && j >= 0){  
       //     cout << "[" << i << "," << j << "]" << endl;  
            if(pole[i][j] == 4){
                break;
            }
            if(pole[i][j] == 1){
                f[0] = Souradnice(i,j);
                break;
            }
            i--;j--;
        }
    }
    // vpravo dole
    if(y < (n-1) && x < (n-1)){
        int i = x+1;
        int j = y+1;
        while( i < n && j < n){  
     //       cout << "[" << i << "," << j << "]" << endl;    
            if(pole[i][j] == 4){
                break;
            }
            if(pole[i][j] == 1){
                
                f[1] = Souradnice(i,j);
                break;
            }
            i++;j++;
        }
    }
    
    return f;
}
// hledej / diagonalu
Souradnice * hledejSikmo2(Souradnice s, Container * c, Souradnice * f){
    int x = s.x;
    int y = s.y;
    int n = c->getSize();
    int ** pole = c->getPole();
    for(int i = 0 ; i < 2; i++){
        f[i] = Souradnice(-1,-1);
    }
    
    // vlevo dole
    if(y > 0 && x < (n-1)){
        int i = x+1;
        int j = y-1;
        while( i < n && j >= 0){  
            //cout << "[" << i << "," << j << "]" << endl;    
            if(pole[i][j] == 4){
                break;
            }
            if(pole[i][j] == 1){
                f[0] = Souradnice(i,j);
                break;
            }
            i++;j--;
        }
    }
    // vpravo nahore
    if(x > 0 && y < (n-1)){
        int i = x-1;
        int j = y+1;
        while( j < n && i >= 0){  
            //cout << "[" << i << "," << j << "]" << endl;    
            if(pole[i][j] == 4){
                break;
            }
            if(pole[i][j] == 1){
                f[1] = Souradnice(i,j);
                break;
            }
            i--;j++;
        }
    }
    return f;
}

Souradnice * hledejVRadku(Souradnice s, Container * c, Souradnice * f){
    int x = s.x;
    int y = s.y;
    int n = c->getSize();
    int ** pole = c->getPole();
    for(int i = 0 ; i < 2; i++){
        f[i] = Souradnice(-1,-1);
    }
    
    // vlevo
    if(y > 0){
    for(int i = y-1; i >= 0; i--){
        if(pole[x][i] == 8 || pole[x][i] == 4){
            break;
        }
        if(pole[x][i] == 1){
            Souradnice d(x,i);
            f[0] = d;
            //cout << "[" << x << "," << i << "]" << endl;    
            break;
        }
    }
    }
    // vpravo
    if(y < (n-1)){
      for(int i = y+1; i < n; i++){
          if(pole[x][i] == 8 || pole[x][i] == 4){
              break;
          }
          if(pole[x][i] == 1){
            Souradnice d(x,i);
            f[1] = d;
            //cout << "[" << x << "," << i << "]" << endl;               
            break;
        }
      }
    }
    
    return f;
}
Souradnice * hledejVsloupci(Souradnice s, Container * c, Souradnice * f){
    int x = s.x;
    int y = s.y;
    int n = c->getSize();
    int ** pole = c->getPole();
    for(int i = 0 ; i < 2; i++){
        f[i] = Souradnice(-1,-1);
    }
    // nahore
    if(x > 0){
      for(int i = x-1; i >= 0; i--){
          if( pole[i][y] == 4 )break;
        if(pole[i][y] == 1){
            Souradnice d(i,y);
            f[0] = d;
            //cout << "[" << x << "," << i << "]" << endl;               
            break;
        }
      }
    }
    // dole
    if(x < (n-1)){
      for(int i = x+1; i < n; i++){
        if( pole[i][y] == 4 )break;
        if(pole[i][y] == 1){
            Souradnice d(i,y);
            f[1] = d;
            //cout << "[" << x << "," << i << "]" << endl;               
            break;
        }
      }
    }
    return f;
}
