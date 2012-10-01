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
    stack <Container> zasobnik;
    int k = 8;
 
    
    Container *test = new Container(10,10);
    Container * best;
    
    Souradnice kralovna(2,2);
    test->setX(kralovna,8);
    //test->setX(Souradnice(4,4),1);
    Souradnice vez(3,3);
    test->setX(vez,4);
    Souradnice *s2 = new Souradnice(-1,-1);
    
    for(int i = 0; i < k; i ++){
        s2 = randSouradnice(10,s2);
        int ** pole = test->getPole();
        if(pole[s2->x][s2->y] == 0)
          test->setX(Souradnice(s2->x,s2->y),1);
        else i--;
    }  
    test->print();/*
    Souradnice * found = new Souradnice[2];
    found = hledejVRadku(s,test,found);
    cout  << "v radku" << endl;
    found[0].print();
    found[1].print();
    found = hledejVsloupci(s,test,found);
    cout  << "v sloupci" << endl;
    found[0].print();
    found[1].print();
    found = hledejSikmo1(s,test,found);
    cout  << "sikmo \\" << endl;
    found[0].print();
    found[1].print();
    found = hledejSikmo2(s,test,found);
    cout  << "sikmo /" << endl;
    found[0].print();
    found[1].print();
   */
    for(int i = 0; i < 5; i++){
        cout << "v " << i << " radku ";
        if(jeVRadkuFigurka(i,test)) cout << "je ";
        else cout << "neni ";
        cout << "figurka" << endl;
    }
    cout << endl;
    for(int i = 0; i < 5; i++){
        cout << "v " << i << " sloupci ";
        if(jeVeSloupciFigurka(i,test)) cout << "je ";
        else cout << "neni ";
        cout << "figurka" << endl;
    }
    
    cout << "kralovna: " ;
    Souradnice sk = najdiKralovnu(test);
    sk.print();
    Souradnice * found = new Souradnice[2];
    found = hledejVRadku(sk,test,found);
    cout  << "v radku" << endl;
    found[0].print();
    found[1].print();
    found = hledejVSloupci(sk,test,found);
    cout  << "v sloupci" << endl;
    found[0].print();
    found[1].print();
    found = hledejSikmo1(sk,test,found);
    cout  << "sikmo \\" << endl;
    found[0].print();
    found[1].print();
    found = hledejSikmo2(sk,test,found);
    cout  << "sikmo /" << endl;
    found[0].print();
    found[1].print();
    
    cout << "vez: " ;
    Souradnice sv = najdiVez(test);
    sv.print();
    found = hledejVRadku(sv,test,found);
    cout  << "v radku" << endl;
    found[0].print();
    found[1].print();
    found = hledejVSloupci(sv,test,found);
    cout  << "v sloupci" << endl;
    found[0].print();
    found[1].print();

    
    
    

    
    
    // init 
    
    {
        // seber vrsek zasobniku
        
        // if container-k == 0 konec
        // if reseni > 2*k konec 
        // je mensi narocnost nez nejlepsi nalezena - uloz 
        
        
        
        
        
        // seber vezi
           // koukni se kde muzes sebrat
           // pro kazdou moznost seber + uloz na zasobnik
        // seber kralovnou
        
        // hejbni vezi
           // hejbej se jen kam to ma smysl  
             // hledej jen sloupce kde jsou figurky
             // kdyz ve stejnem radku je kralovna hledej radky 
    }
    
    
    
    
    
    
}
