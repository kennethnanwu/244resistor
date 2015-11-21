/* 
 * File:   main.cpp
 * Author: Nan Wu
 *
 * Created on October 9, 2015, 8:12 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "Node.h"
#include "Resistor.h"
#include "Rparser.h"
#include "NodeList.h"
#include "easygl.h"
#include <iomanip>

using namespace std;

easygl window("Resistor display", WHITE);
NodeList* gb_NodeListPtr;

void parse_draw( NodeList& nodeList){
    float xleft, ybottom, xright, ytop;
    nodeList.set_draw_coords(xleft,ybottom,xright,ytop);//compute drawing coordinates for each nodelist & resistor
    window.set_world_coordinates(xleft,ybottom,xright,ytop);
    gb_NodeListPtr = &nodeList;//set up global pointer
    nodeList.draw(window); //draw the network

    window.gl_event_loop();//this function will not return untile the "Proceed" button is pushed
    cout<<"Draw: complete; responding to commands again"<<endl;

}

void easygl::drawscreen(){
    gb_NodeListPtr->draw(window);
}

int main() {
    NodeList nodelist;
            
    while(1){
      
        parser user_input;
        string returnStatement = user_input.checkInput();
        
        if ( returnStatement == "eof"){
            
            cout<<"> "<<endl;
            break;
        }
        
        else if ( returnStatement == "error"){ //if any error input, continue ask for command
            continue;
        }
        
        
// insertR command
        if ( returnStatement == "insertR"){
            int endpoint[2];
            endpoint[0] = user_input.get_fromNode();
            endpoint[1] = user_input.get_toNode();      

            if( nodelist.checkResName(user_input.get_resistorName()) ){
                cout<<"> Error: resistor "<<user_input.get_resistorName()<<" already exists"<<endl;
                continue;
            }
                
            else{ // if this name is not included, then initialize a resistor for this name
                nodelist.addNode(endpoint[0]);
                nodelist.addNode(endpoint[1]);
                nodelist.addResToNode(endpoint[0],endpoint[1], user_input.get_resistorName(), user_input.get_resistance());
                }
            
            cout<<fixed;
            cout<<setprecision(2);
            cout<<"> Inserted: resistor "<<user_input.get_resistorName()<<" "<<user_input.get_resistance()<<" Ohms "<<user_input.get_fromNode()<<" -> "<<user_input.get_toNode()<<endl;
            continue;
        }
        
// modifyR command
        else if ( returnStatement == "modifyR"){
            
            if ( nodelist.checkResName(user_input.get_resistorName()) ){
                double oldResistance = nodelist.get_resistance(user_input.get_resistorName());// save the resistance before it's modified, it will later be used in output
                nodelist.changeResistance(user_input.get_resistorName(), user_input.get_resistance() );
                cout<<"> Modified: resistor "<<user_input.get_resistorName()<<" from "<<oldResistance<<" Ohms to "<<user_input.get_resistance()<<" Ohms"<<endl;
                continue;
            }

            else{ //no resistor is modified, so the name is invalid
                cout<<"> Error: resistor "<<user_input.get_resistorName()<<" not found"<<endl;
                continue;
            }
        }

// printR command        
        else if ( returnStatement == "printR"){
            if( !nodelist.checkResName(user_input.get_resistorName()) ){ // there is no this name in the array
                cout<<"> Error: resistor "<<user_input.get_resistorName()<<" not found"<<endl;
                continue;
            }
            
            else{
            cout<<"> Print:"<<endl;
            nodelist.printRes(user_input.get_resistorName());
            }
            
            continue;
        }
        
// printNode all command
        else if ( returnStatement == "printAllNode"){
            cout<<"> Print:"<<endl;
            nodelist.printAllNode();
            continue;
        }
        
// printNode command
        else if ( returnStatement == "printNode"){
            cout<<"> Print:"<<endl;
            nodelist.printNode(user_input.get_nodeId());
            continue;
        }
        
// deleteR all command
        else if ( returnStatement == "deleteAllR"){ //delete the resistor array and the nodelist array, set resistor count back to 0, dynamically allocate new array for the pointers
            nodelist.deleteAll();
            cout<<"> Deleted: all resistors"<<endl;
            continue;
        }
        
// deleteR command
        else if( returnStatement == "deleteR"){
            if(nodelist.deleteR(user_input.get_resistorName()))
                cout<<"> Deleted: resistor "<<user_input.get_resistorName()<<endl;
            else
                cout<<"> Error: resistor "<<user_input.get_resistorName()<<" not found"<<endl;
            continue;
        }
// set voltage 
        else if(returnStatement == "setV"){
            nodelist.setV(user_input.get_nodeId(), user_input.get_voltage());
            continue;
        }
        
// unset voltage
        else if(returnStatement == "unsetV"){
            nodelist.unsetV(user_input.get_nodeId());
            cout<<"> Unset: the solver will determine the voltage of node "<<user_input.get_nodeId()<<endl;
            continue;
        }
        
// solve
        else if(returnStatement == "solve"){
            if(nodelist.solve()){
                Node* nodep = nodelist.get_nodeHead(); //let node ptr points back to the head of the list
                cout<<"> Solve:"<<endl;
                while(nodep != NULL){
                    cout<<"  Node "<<nodep->get_nodeId()<<": "<<setprecision(2)<<nodep->get_voltage()<<" V"<<endl;
                    nodep = nodep->get_nextNode();
                    }
                continue;
            }
            else{
                cout<<"> Error: no nodes have their voltage set"<<endl;
                continue;
            }
        }

//draw
        else if(returnStatement == "draw"){
            parse_draw(nodelist);
            continue;
        }
    }
    
    return 0;
}
