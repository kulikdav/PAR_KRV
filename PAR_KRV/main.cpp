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
    Container * test = new Container(10,10);
    Container * best;
    
     
   
    test->setX(Souradnice(3,3),4);
    test->setX(Souradnice(3,1),8);
    test->setX(Souradnice(1,1),1);
    test->setX(Souradnice(3,6),1);
    test->setX(Souradnice(3,5),1);
    test->setX(Souradnice(4,2),1);
    test->setX(Souradnice(5,2),1);
    test->setX(Souradnice(6,2),1);
    test->setX(Souradnice(7,6),1);
    
    
    
    
    
    
    
    
      
    
    // init 
    zasobnik.push(test);
    test->print();
    while(!zasobnik.empty())
    {
        
        // seber vrsek zasobniku
        Container * top = zasobnik.top();
        zasobnik.pop();
        //cout << zbyvaFigurek(top);
        // if container-k == 0 konec
        //top->print();
        
        // if reseni > 2*k konec 
        
        // je mensi narocnost nez nejlepsi nalezena - uloz 
        
        
        
        
        
        
        Souradnice *branch = new Souradnice[12];
        int counter = 0;
        
        
        // seber vezi
        Souradnice vez = najdiVez(top);
        
        //vez.print();
        Souradnice *radek = new Souradnice[2];
        Souradnice *sloupec = new Souradnice[2];
        Souradnice *diag1 = new Souradnice[2];
        Souradnice *diag2 = new Souradnice[2];
        
        radek = hledejVRadku(vez,top,radek);
        sloupec = hledejVsloupci(vez,top,sloupec);
        if(radek[0].isValid()) branch[counter++] = radek[0];
        if(radek[1].isValid()) branch[counter++] = radek[1];
        if(sloupec[0].isValid()) branch[counter++] = sloupec[0];
        if(sloupec[1].isValid()) branch[counter++] = sloupec[1];
        int delimiter = counter;
        
        
        
        
           // k = k - 1
           // koukni se kde muzes sebrat
           // pro kazdou moznost seber + uloz na zasobnik
        // seber kralovnou
        
        Souradnice kralovna = najdiKralovnu(top);
            radek = hledejVRadku(kralovna,top,radek);
            sloupec = hledejVsloupci(kralovna,top,sloupec);
            diag1 = hledejSikmo1(kralovna,top,diag1);
            diag2 = hledejSikmo2(kralovna,top,diag2);
        if(radek[0].isValid()) branch[counter++] = radek[0];
        if(radek[1].isValid()) branch[counter++] = radek[1];
        if(sloupec[0].isValid()) branch[counter++] = sloupec[0];
        if(sloupec[1].isValid()) branch[counter++] = sloupec[1];
        if(diag1[0].isValid()) branch[counter++] = diag1[0];
        if(diag1[1].isValid()) branch[counter++] = diag1[1];
        if(diag2[0].isValid()) branch[counter++] = diag2[0];
        if(diag2[1].isValid()) branch[counter++] = diag2[1];    
        int delimiter2 = counter;    
            
         //hejbni vezi
        if(delimiter == 0){
            //top->print();
            for(int i = 0; i < top->getSize(); i++){
                if(jeVeSloupciFigurka(i,top) > 0 && i != vez.y){
                    //if(top->getValue(vez.x,i) != 8){
                      branch[counter++] = Souradnice(vez.x,i);
                    
                    // dodelat hledani radku ve kterem jsou 1 ( sloupec = kralovna.y);
                }
                //cout << "sloupec" << i << ": " << jeVeSloupciFigurka(i,top) << endl;
                
            }
        }
            
            
             // hejbej se jen kam to ma smysl  
             // hledej maximum z jevsloupci/jevradku, pokud se tam muzes hnout
             // hledej jen sloupce kde jsou figurky
             // kdyz ve stejnem radku je kralovna hledej radky 
        
        int fig = 4;
        Souradnice posun = vez;
        
        for(int i = 0; i<counter; i++){
            
            if(i == delimiter) {fig = 8;posun = kralovna;}
            if(i == delimiter2){fig = 4;posun = vez;}
            //cout << fig;
            //branch[i].print();
            Container * c = new Container(top->getSize(), top->getK());
            c->setPole(top->getPole());
            c->setResult(top->getResult());
            if(fig == 4) c->addResult(10);
            else c->addResult(15);
            if( c->getValue(branch[i].x,branch[i].y) != 4 && c->getValue(branch[i].x,branch[i].y) != 8){
              //cout << "skacu: [" << branch[i].x << "," << branch[i].y << "], value=" << c->getValue(branch[i].x,branch[i].y) << endl;
                //fig + "[" + branch[i].x + "," branch[i].y + "];"
                Souradnice s;
                s.x = branch[i].x; s.y = branch[i].y; s.fig=fig;
                c->addHistory(s);
                
              presunFigurku(branch[i],posun,fig,c);
            } else { 
                cout << "error " << c->getValue(branch[i].x,branch[i].y) << endl;
                cout << "Q:";
                kralovna.print();
                        
                
                c->print();
                break;
            }
            
            
            //c->print();
            if(!c->overLimit() && zbyvaFigurek(c) > 0){
              zasobnik.push(c);
            }
            else if(best == NULL || best->getResult() > c->getResult()){
                best = c;
            }
            
        }   
        
    }
    cout << "BEST:" << endl;
        best->print();
        Souradnice * result = best->getHistory();
        for(int i = 0 ; i < best->getCounter(); i++){
            result[i].print();
        }
        
}
