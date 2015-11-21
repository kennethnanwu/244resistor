/* 
 * File:   Rparser.h
 * Author: Kenneth
 *
 * Created on October 11, 2015, 11:53 AM
 */

#ifndef RPARSER_H
#define	RPARSER_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class parser{
private:
    string line, command;

    int fromNode, toNode, nodeId;
    double resistance, voltage;
    string resistorName;
    
    
public:
    parser();
    ~parser();
    
    string checkInput();
    
    int get_fromNode(){return fromNode;}
    int get_toNode(){return toNode;}
    int get_nodeId(){return nodeId;}
    double get_voltage(){return voltage;}
    double get_resistance(){return resistance;}
    string get_resistorName(){return resistorName;}
    
};


#endif	/* RPARSER_H */
    
    //inertR
    //string resistorName
    //double resistance
    //int fromNode, toNode
    
    //modifyR
    //string resistorName
    //double resistance
    
    //printR
    //string resistorName
    
    //printNode
    //int nodeId
    //all
    
    //deleteR
    //resistor name
    //all
    
    //setV
    //int nodeId
    //double voltage
    //
    //unsetV
    //int nodeId
    //
    //solve
    //no arg
    
