/* 
 * File:   main.cpp
 * Author: dawe
 *
 * Created on September 24, 2012, 9:37 AM
 */

#include <cstdlib>
#include <iostream>
#include <stack>
#include "Container.h"
#include "common.h"

using namespace std;

/*
 * 
 */




int main(int argc, char** argv) {
    stack <Container*> zasobnik;
    int size = 10;
    int k = 19;
    Container * test = new Container(size,k);
    Container * best = new Container(size,k);
    best->setResult(k * 20);
    
     
   
    test->setX(Souradnice(1,1),4);
    test->setX(Souradnice(6,6),8);
    
    test->setX(Souradnice(4,1),1);
    test->setX(Souradnice(1,0),1);
    test->setX(Souradnice(1,3),1);
    test->setX(Souradnice(0,1),1);
    
    test->setX(Souradnice(5,5),1);
    test->setX(Souradnice(5,7),1);
    test->setX(Souradnice(7,5),1);
    test->setX(Souradnice(7,7),1);
    
    test->setX(Souradnice(6,5),1);
    test->setX(Souradnice(6,7),1);
    test->setX(Souradnice(7,6),1);
    test->setX(Souradnice(7,6),1);
    test->setX(Souradnice(9,9),1);

      
     
    // init 
    zasobnik.push(test);
    test->print();
    int max = 0;
    
    while(!zasobnik.empty())
    {
        
                
        Container *top = zasobnik.top();
        zasobnik.pop();       
        
        if(zasobnik.size() > max) max = zasobnik.size();
        if(zbyvaFigurek(top) == 0){
            if(top->getResult() < best->getResult()){
                best = top;
                cout << "newbest" << best->getResult() << endl;
            
            }
            //cout << top->getResult() << " " << best->getResult() << endl;
        } 
        else {
        
        
        Souradnice *branch = new Souradnice[4+8+size+1];
        int *fig = new int[13+size];
        Souradnice vez = najdiVez(top);           
        if(vez.x == -1 || vez.y == -1 ){
            continue;
        }
        Souradnice kralovna = najdiKralovnu(top); 
        
        hledejVRadku(vez,top,branch);
        hledejVsloupci(vez,top,branch+2);
        for(int i = 0; i < 4; i++){
            if(branch[i].fig == -1)branch[i].fig = 4;
        }
        // pokud existuje pro pohyb veze, branchuj, jinak hledej pro vez;
        
        if(!branch[0].isValid() && !branch[1].isValid()){
            
          hledejVRadku(kralovna,top,branch+4);
          hledejVsloupci(kralovna,top,branch+6);
          hledejSikmo1(kralovna,top,branch+8);
          hledejSikmo2(kralovna,top,branch+10);
          int maxr = 0, maxs = 0; int cr = -1;int cs = -1;int c = 0;
          for(int i = 0; i < size; i++){
             int r = jeVRadkuFigurka(i,top);
             int s = jeVeSloupciFigurka(i,top);
             if(r > maxr){maxr = r; cr = i;}
             if(s > maxs){maxs = s; cs = i;}
          }
          
          //top->print();
          if (maxr >= maxs){
              for(int i = 0; i < size; i++){
                  if(maxr == jeVRadkuFigurka(i,top)){
                      branch[12+size-(c++)] = Souradnice(i,vez.y,4);
                  }
              }
          } 
          if ( maxr < maxs){
              for(int i = 0; i < size; i++){
                  if(maxs == jeVeSloupciFigurka(i,top)){
                     // cout << i << "," << vez.y << endl;
                      branch[12+size-(c++)] = Souradnice(vez.x,i,4);
                  }
              }
          } 
          //cout << endl;
            
          for(int i = 0; i < 12; i++){
            if(branch[i].fig == -1)branch[i].fig = 8;
          }
        }/*
        cout << "\n-------------------------------------\n";
        cout << "-------------------------------------\n";
        vez.print();
        top->print();
        cout << max << endl;*/
        for(int i = 12+size; i>= 0; i--){
            if(branch[i].isValid()){
                /*cout << i << "--";
                branch[i].print();*/
                Container *newc = new Container(size,k);
                newc->setResult(top->getResult());
                Souradnice s = vez;
                if(branch[i].fig == 8) s = kralovna;
                newc->setPole(top->getPole());
                presunFigurku(branch[i],s,branch[i].fig,newc);
                //cout << zasobnik.size() << endl;
                newc->addResult(10);
                if(branch[i].fig == 8) newc->addResult(5);
                //newc->print();
                if(zbyvaFigurek(newc) > 0){
                    int minPrice = newc->getResult() + (10 * zbyvaFigurek(newc));
                    if(minPrice < best->getResult()){
                       zasobnik.push(newc); 
                    }
                }
                if(best->getResult() > newc->getResult() && zbyvaFigurek(newc) == 0){
                    best = newc;
                    cout << "newbest" << best->getResult() << endl;
                }
                //cout << best->getResult() << " " << newc->getResult() << " " << zbyvaFigurek(newc) << endl;
                
            }
            
        }
        
        }
        
                
    }
    best->print();
    cout << best->getResult();
    cout <<"max-stack-size:" << max << endl;
        
        
}
