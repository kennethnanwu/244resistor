/* 
 * File:   ResistorList.h
 * Author: wunan7
 *
 * Created on October 31, 2015, 2:39 PM
 */

#ifndef RESISTORLIST_H
#define	RESISTORLIST_H

#include <iostream>
#include <string>
#include <sstream>
#include "Resistor.h"

using namespace std;

class ResistorList{
	friend class Node;
        friend class NodeList;
	private:
		Resistor* resHead;
	public:
		ResistorList(){resHead=NULL;}
		~ResistorList(){delete resHead;}

};



#endif	/* RESISTORLIST_H */