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

using namespace std;

/*
 * 
 */



int main(int argc, char** argv) {
    stack <Container> zasobnik;
    Container *test = new Container(5,10);
    Container * best;
    Souradnice s;
    s.x = 0;
    s.y = 0;
    test->setX(s,5);
    test->print();
    
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
