/* 
 * File:   Container.h
 * Author: dawe
 *
 * Created on September 24, 2012, 11:58 AM
 */

#ifndef CONTAINER_H
#define	CONTAINER_H

class Container {
public:
    Container();
    Container(int n, int k);
    Container(const Container& orig);
    virtual ~Container();
    
    void print();
    
private:
    int n;
    int k;
    int ** pole;
    
    int result;
    
    Container * predek;
    
    /* 
     * prazdne pole = 0
     * figurky 1
     * kralovna 8
     * vez      4
     
     */
};

#endif	/* CONTAINER_H */

