/* 
 * File:   Node.h
 * Author: Kenneth
 *
 * Created on October 10, 2015, 8:13 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <string>
#include <iostream>
#include "ResistorList.h"
#include "easygl.h"
using namespace std;

class Node{
    friend class NodeList;
private:
    int numRes;//number of resistors currently connected
    Node* nextNode;
    ResistorList resList;
    int nodeId;
    int flag_setV;
    double voltage;
public:
    Node(int nodeId_);
    ~Node();
    
    void addResistor(int nodeId1_, int nodeId2_, string resName_, double resistance_);
    //updates resIDArray to show the resistor in position rIndex in
    //the resistor array is now connected to this node
    //returns true if successful
    
    void print() const;
    //prints the whole node
    //nodeIndex is the position of this node in the node array
    bool checkResName(string resName_) const;
    
    void printV() const;

    void draw_node_strips(easygl& window, int node_num, int res_num);
    int get_nodeId();
    double get_voltage();
    Node* get_nextNode();

};

#endif	/* NODE_H */

