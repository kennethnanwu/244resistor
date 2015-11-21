/* 
 * File:   NodeList.h
 * Author: wunan7
 *
 * Created on October 31, 2015, 2:40 PM
 */

#ifndef NODELIST_H
#define	NODELIST_H

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include "Node.h"
#include "easygl.h"

using namespace std;

class NodeList{
private:
	Node* nodeHead;
        bool VisSet();

public:
	NodeList(){nodeHead=NULL;}
	~NodeList(){delete nodeHead;}

	bool checkNodeExist(int nodeId_) const;
	void addNode(int nodeId_);
	bool checkResName(string resName_) const;
        void addResToNode(int nodeId1_, int nodeId2_, string resName_, double resistance_);
        double get_resistance(string resName_) const;
        void changeResistance(string resName_, double resistance_);
        void printRes(string resName_) const;
        void printAllNode() const;
        void printNode(int nodeId_) const;
        void deleteAll();
        bool deleteR(string resName_);
        void setV(int nodeId_, double voltage_);
        void unsetV(int nodeId_);
        bool solve();
        void draw(easygl& window);
        void set_draw_coords(float& xleft, float& ybottom, float& xright, float& ytop);
        Node* get_nodeHead(){return nodeHead;}

};

#endif	/* NODELIST_H */

