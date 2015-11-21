/* 
 * File:   Resistor.h
 * Author: Kenneth
 *
 * Created on October 10, 2015, 8:13 PM
 */

#ifndef RESISTOR_H
#define	RESISTOR_H

#include <iostream>
#include <string>
#include "easygl.h"
using namespace std;

class Resistor{
	friend class ResistorList;
    friend class Node;
    friend class NodeList;
private:
    double resistance;
    string name;
    int endpointNodeIDs[2];
    Resistor* nextRes;

public:
    Resistor(string name_, double resistance_, int endpoints_[2]);
    // rIndex is the index of this resistor in the resistor array
    // endpoints_ holds the node indeces to which this resistor connects
    
    Resistor();
    
    ~Resistor();
    
    string getName() const; //returns the name
    double getResistance() const; //returns the resistance;
    
    void setResistance(double resistance_);
    
    void print() const;
    void draw_res(easygl& window, int from, int to, int res_count);
};

#endif	/* RESISTOR_H */

