#include "Container.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;

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
}
Souradnice najdiKralovnu(Container *c){
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

// vraci true pokud je v s-tem sloupci nejaka dana figurka
bool jeVeSloupciFigurka(int s, int fig, Container * c){
    int ** pole = c->getPole();
    int n = c->getSize();
    for(int i = 0; i < n; i++){
        if(pole[i][s] == fig) return true;
    }
    return false;
}

bool jeVRadkuFigurka(int r, int fig, Container * c){
    int ** pole = c->getPole();
    int n = c->getSize();
    for(int i = 0; i < n; i++){
        if(pole[r][i] == fig) return true;
    }
    return false;
}

// Pro pripadnou optimalizaci pri hledani radku a sloupcu s nejvetsim ptencialem vyberu figurek
int pocetFigurekVRadku(int r, Container * c){
    int count = 0;
    int ** pole = c->getPole();
    int n = c->getSize();
    for(int i = 0; i < n; i++){
        if(pole[r][i] == 1) count++;
    }
    return count;
}

int pocetFigurekVSloupci(int s, Container * c){
    int count = 0;
    int ** pole = c->getPole();
    int n = c->getSize();
    for(int i = 0; i < n; i++){
        if(pole[i][s] == 1) count++;
    }
    return count;
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
        if(pole[x][i] == 8){
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
          if(pole[x][i] == 8){
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
Souradnice * hledejVSloupci(Souradnice s, Container * c, Souradnice * f){
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


bool tahVezi(Container * c){
    // Hleda figurky v dosahu veze, pokud najde, skoci a vrati true
    // Pokud nenajde figurky v dosahu, zustava stat a vraci false
    
    Souradnice sVez = najdiVez(c);
    Souradnice * found = new Souradnice[2];
    
    // Skok veze ve sloupci
    found = hledejVRadku(sVez,c,found);
    int n = c->getCount();
    if (found[0].x != -1){
        presunFigurku(found[0],sVez,4,c);
        c->setCount(n-1);
        c->addPrice(10);
        return true;
    }
    
    if (found[1].x != -1){
        presunFigurku(found[1],sVez,4,c);
        c->setCount(n-1);
        c->addPrice(10);
        return true;
    }
    
    // Skok veze v radku
    found = hledejVSloupci(sVez,c,found);
    if (found[0].x != -1){
        presunFigurku(found[0],sVez,4,c);
        c->setCount(n-1);
        c->addPrice(10);
        return true;
    }
    
    if (found[1].x != -1){
        presunFigurku(found[1],sVez,4,c);
        c->setCount(n-1);
        c->addPrice(10);
        return true;
    }
    
    return false;
}

bool tahKralovnou(Container * c){
    // Hleda figurkz v dosahu / pokud najde, skoci a vrati true
    // pokud nenajde, nehejbe se a vrati false
    // Mozna by bylo optimalnejsi dat prednost sikmejm skokum
    
    Souradnice sKralovna = najdiKralovnu(c);
    Souradnice * found = new Souradnice[2];
    
    // Skok kralovny v radku
    found = hledejVRadku(sKralovna,c,found);
    int n = c->getCount();
    if (found[0].x != -1){
        presunFigurku(found[0],sKralovna,8,c);
        c->setCount(n-1);
        c->addPrice(15);
        return true;
    }
    
    if (found[1].x != -1){
        presunFigurku(found[1],sKralovna,8,c);
        c->setCount(n-1);
        c->addPrice(15);
        return true;
    }
    
    // Skok kralovny v sloupci
    found = hledejVSloupci(sKralovna,c,found);
    if (found[0].x != -1){
        presunFigurku(found[0],sKralovna,8,c);
        c->setCount(n-1);
        c->addPrice(15);
        return true;
    }
    
    if (found[1].x != -1){
        presunFigurku(found[1],sKralovna,8,c);
        c->setCount(n-1);
        c->addPrice(15);
        return true;
    }
    
    // Skok kralovny sikmo 1
    found = hledejSikmo1(sKralovna,c,found);
    if (found[0].x != -1){
        presunFigurku(found[0],sKralovna,8,c);
        c->setCount(n-1);
        c->addPrice(15);
        return true;
    }
    
    if (found[1].x != -1){
        presunFigurku(found[1],sKralovna,8,c);
        c->setCount(n-1);
        c->addPrice(15);
        return true;
    }
    
    // Skok kralovny sikmo 2
    found = hledejSikmo2(sKralovna,c,found);
    if (found[0].x != -1){
        presunFigurku(found[0],sKralovna,8,c);
        c->setCount(n-1);
        c->addPrice(15);
        return true;
    }
    
    if (found[1].x != -1){
        presunFigurku(found[1],sKralovna,8,c);
        c->setCount(n-1);
        c->addPrice(15);
        return true;
    }
    
    return false;
}

bool presunVez(Container * c){
    Souradnice sVez = najdiVez(c);
    Souradnice * found = new Souradnice[2];
    
    //Souradnice sKralovna = najdiKralovnu(c);
    // Vlastne nebude potreba hledat radky bez kralovny protoze kdyby na nem byly figurky tak je kralovna uz veme
    int line = 0;
    while(!jeVRadkuFigurka(line,1,c) || (line == c->getSize())){
        line++;
    }
    // V line je radek s figurkou
    
    Souradnice target(line,sVez.y);
    
    presunFigurku(target,sVez,4,c);
}

bool tah(Container * c){
    // skocit vezi
    if (tahVezi(c)){
        c->print();
        return true;
    }
    
    // skocit kralovnou
    if (tahKralovnou(c)){
        c->print();
        return true;
    }
    
    // presunout vez
    presunVez(c);
    
}