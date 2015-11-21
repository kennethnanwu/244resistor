#include "Resistor.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>

/* private arguments:
 * 
 * double resistance; 
 * string name;
 * int endpointNodeIDs[2], resistorCount;
 */
extern float node_strip_wide;
extern float bottom_top_space;
extern float left_right_space;
extern float space_between_res;

Resistor::Resistor( string name_, double resistance_, int endpoints_[]){
    name = name_;
    resistance = resistance_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
    nextRes=NULL;
}

Resistor::Resistor(){
    
}

Resistor::~Resistor(){
    delete nextRes;
    nextRes = NULL;
}

string Resistor::getName() const{
    return name;
}

double Resistor::getResistance() const{
    return resistance;
}

void Resistor::setResistance(double resistance_){
    resistance = resistance_;
}


void Resistor::print() const{
    cout.width(20);
    cout<<std::left<<name;
    cout.width(8);
    cout<<std::right<<resistance;
    cout<<" Ohms "<<endpointNodeIDs[0]<<" -> "<<endpointNodeIDs[1]<<endl;
}

void Resistor::draw_res(easygl& window, int from, int to, int res_count){        
    int node_diff = to - from;
    float centre_of_res = left_right_space + 50 + (from * node_strip_wide) + (node_diff * node_strip_wide / 2);
    
    window.gl_setcolor(BLACK);
    window.gl_drawline( left_right_space + 50 + from * node_strip_wide, 
                        bottom_top_space + space_between_res * res_count,
                        centre_of_res - 200,
                        bottom_top_space + space_between_res * res_count);
    
    window.gl_fillarc (left_right_space + 50 + from * node_strip_wide,
                        bottom_top_space + space_between_res * res_count,
                        30,
                        0,
			360);

    window.gl_setcolor(RED);
    window.gl_fillrect(centre_of_res - 200,
                        bottom_top_space + space_between_res * res_count - 50,
                        centre_of_res + 200,
                        bottom_top_space + space_between_res * res_count + 50);

    window.gl_setcolor(BLACK);
    window.gl_drawline(centre_of_res + 200,
                        bottom_top_space + space_between_res * res_count,
                        left_right_space + 50 + to * 900,
                        bottom_top_space + space_between_res * res_count);
    
    window.gl_fillarc (left_right_space + 50 + to * 900,
                        bottom_top_space + space_between_res * res_count,
                        30,
                        0,
			360);

    stringstream print_res_info;
    print_res_info<<name<<"("<<resistance<<" Ohm)";
    stringstream ss;
    ss<<name<<"("<<resistance<<" Ohm)";
    window.gl_setfontsize(30);
    window.gl_drawtext(centre_of_res, 
                        700 + res_count * space_between_res, 
                        ss.str());
        
}   
    

