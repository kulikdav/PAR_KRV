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
    
     int k = 2;
    Souradnice s(2,2);
    test->setX(s,8);
    test->setX(Souradnice(4,4),1);
    test->setX(Souradnice(0,0),1);
    test->setX(Souradnice(0,2),1);
    Souradnice sv(4,3);
    test->setX(sv,4);
    Souradnice *s2 = new Souradnice(-1,-1);
    for(int i = 0; i < k; i ++){
        s2 = randSouradnice(10,s2); 
        int ** pole = test->getPole();
        if(pole[s2->x][s2->y] == 0)
          test->setX(Souradnice(s2->x,s2->y),1);
        else i--;
    }  
    
    // init 
    zasobnik.push(test);
    while(!zasobnik.empty())
    {
        // seber vrsek zasobniku
        Container * top = zasobnik.top();
        zasobnik.pop();
        // if container-k == 0 konec
        //top->print();
        if(top->getK() == 0) break;
        // if reseni > 2*k konec 
        if(top->getK() >= top->getUpperLimit()) break;
        // je mensi narocnost nez nejlepsi nalezena - uloz 
        
        
        
        
        
        
        Souradnice *branch = new Souradnice[12];
        int counter = 0;
        
        
        // seber vezi
        Souradnice vez = najdiVez(top);
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
            for(int n = 0; n < top->getSize(); n++){
                if(jeVeSloupciFigurka(n,top) > 0 && n != vez.y )
                    if(n != kralovna.x)branch[counter++] = Souradnice(vez.x,n);
                    else {
                        for(int i = 0; i < top->getSize(); i++){
                            if(top->getPole()[i][n] == 1){
                                branch[counter++] = Souradnice(i,vez.y);
                            }
                        }
                    }
            }
            
             // hejbej se jen kam to ma smysl  
             // hledej maximum z jevsloupci/jevradku, pokud se tam muzes hnout
             // hledej jen sloupce kde jsou figurky
             // kdyz ve stejnem radku je kralovna hledej radky 
        top->print();
        int fig = 4;
        Souradnice posun = vez;
        cout << "-----------------------"<<endl;
        for(int i = 0; i<counter; i++){
            
            if(i == delimiter) {fig = 8;posun = kralovna;}
            if(i == delimiter2){fig = 4;posun = vez;}
            cout << fig << " ";
            branch[i].print();
            presunFigurku(branch[i],posun,fig,top);
            top->print();
            zasobnik.push(top);
            top->setX(vez,4);
            top->setX(kralovna,8);
            top->setX(branch[i],1);
            
        }    
    }
    
    
    
    
    
    
}
