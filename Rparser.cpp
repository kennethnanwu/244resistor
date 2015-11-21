/* private arguments:
 * 
 * string line, command
 * 
 * public:
 * 
 * int maxNodeNumber, maxResistors, fromNode, toNode, nodeId
 * string resistorName
 * double resistance
 */

#include "Rparser.h"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
 #include "NodeList.h"
#include "easygl.h"

using namespace std;


parser::parser(){
    
}
parser::~parser(){
    
}
string parser::checkInput() {  

    getline(cin, line);

    if(cin.eof()) {
        cout<<endl;
        return "eof";
    }

    stringstream inputLine(line);
    inputLine >> command;

//insertR
    if(command == "insertR"){
        
        if (inputLine.eof()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }

        inputLine >> resistorName;
        if (resistorName == "all")
        {
            cout<<"> Error: resistor name cannot be the keyword \"all\""<<endl;
            return "error";
        }
        if (inputLine.eof()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }

        inputLine >> resistance;

        if(inputLine.fail()){
            cout<<"> Error: invalid argument"<<endl;
            return "error";
        }

        if (inputLine.eof()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }
        if(resistance < 0){
            cout<<"> Error: negative resistance"<<endl;
            return "error";
        }

        inputLine >> fromNode;

        if(inputLine.fail()){
            cout<<"> Error: invalid argument"<<endl;
            return "error";
        }

        if( (inputLine.peek() != '\n') && (inputLine.peek() != ' ') && (inputLine.peek() !='\r') && (inputLine.peek() != '\t') && (inputLine.peek() != -1)){
            cout<<"> Error: invalid argument"<<endl;
            return "error";
        }
 
        if (inputLine.eof()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }

        inputLine >> toNode;

        if( inputLine.fail() ){
            cout<<"> Error: invalid argument"<<endl;
            return "error";
        }

         if((inputLine.peek() != '\n') && (inputLine.peek() != ' ') && (inputLine.peek() !='\r') && (inputLine.peek() != '\t') && (inputLine.peek() != -1)){
            cout<<"> Error: invalid argument"<<endl;
            return "error";
        }
        
        if(fromNode == toNode){
            cout<<"> Error: both terminals of resistor connect to node "<<fromNode<<endl;
            return "error";
        }
        
        string checkWhiteSpace;
        inputLine >> checkWhiteSpace;
        if ( !(inputLine.fail()) ){
            cout<<"> Error: too many arguments"<<endl;
            return "error";
        }
        
        return "insertR";
    }

//modifyR
    else if(command == "modifyR"){
        if (inputLine.eof()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }

        inputLine >> resistorName;
        
        if (resistorName == "all")
        {
            cout<<"> Error: resistor name cannot be the keyword \"all\""<<endl;
            return "error";
        }
        if (inputLine.eof()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }


        inputLine >> resistance;
        if( inputLine.fail() ){
            cout<<"> Error: invalid argument"<<endl;
            return "error";
        }
        if(resistance < 0){
            cout<<"> Error: negative resistance"<<endl;
            return "error";
        }
        
        string checkWhiteSpace;
        inputLine >> checkWhiteSpace;
        if ( !(inputLine.fail()) ){
            cout<<"> Error: too many arguments"<<endl;
            return "error";
        }
        
        return "modifyR";
    }

//printR
    else if(command == "printR"){
        if (inputLine.eof()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }

        inputLine >> resistorName;
        if ( (inputLine.fail()) ){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }

        string checkWhiteSpace;
        inputLine >> checkWhiteSpace;
        if ( !(inputLine.fail()) ){
            cout<<"> Error: too many arguments"<<endl;
            return "error";
        }

        if (resistorName == "all")
            return "error";
        else
            return "printR";
    }

//printNode
    else if(command == "printNode"){
        if (inputLine.eof()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }

        string printNode;

        inputLine >> printNode;
        if ( (inputLine.fail()) ){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }
        if(printNode == "all") {
            return "printAllNode";
        }
        if(printNode != "all"){
            stringstream nodeString(printNode);
            nodeString >> nodeId;
            if(nodeString.fail()){
                cout<<"> Error: invalid argument"<<endl;
                return "error";
            }
        }

        string checkWhiteSpace;
        inputLine >> checkWhiteSpace;
        if ( !(inputLine.fail()) ){
            cout<<"> Error: too many arguments"<<endl;
            return "error";
        }

        return "printNode";
        
    }

//deleteR
    else if(command == "deleteR"){
        if (inputLine.eof()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }

        inputLine >> resistorName;
        
        if( inputLine.fail()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }

        string checkWhiteSpace;
        inputLine >> checkWhiteSpace;
        if ( !(inputLine.fail()) ){
            cout<<"> Error: too many arguments"<<endl;
            return "error";
        }

        if (resistorName != "all")
        {
            return "deleteR";
        }
        else{
            return "deleteAllR";
        }
    }
        
//setV
    else if(command == "setV"){
    	if (inputLine.eof()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }
	inputLine>>nodeId;
	if ( (inputLine.fail()) ){
            cout<<"> Error: invalid argument"<<endl;
            return "error";
        }
	inputLine >> voltage;
	if( inputLine.fail() ){
            cout<<"> Error: invalid argument"<<endl;
            return "error";
        }
	
	string checkWhiteSpace;
        inputLine >> checkWhiteSpace;
        if ( !(inputLine.fail()) ){
            cout<<"> Error: too many arguments"<<endl;
            return "error";
        }

	return "setV";
    }

//unsetV

    else if(command == "unsetV"){
    	if (inputLine.eof()){
            cout<<"> Error: too few arguments"<<endl;
            return "error";
        }
	inputLine>>nodeId;
	if ( (inputLine.fail()) ){
            cout<<"> Error: invalid argument"<<endl;
            return "error";
        }
	string checkWhiteSpace;
        inputLine >> checkWhiteSpace;
        if ( !(inputLine.fail()) ){
            cout<<"> Error: too many arguments"<<endl;
            return "error";
        }

	return "unsetV";
    }

//solve
	
    else if(command == "solve"){
        string checkWhiteSpace;
        inputLine >> checkWhiteSpace;
        if ( !(inputLine.fail()) ){
            cout<<"> Error: too many arguments"<<endl;
            return "error";
        }
        
	return "solve";
    }

//draw

    else if(command == "draw"){
        string checkWhiteSpace;
        inputLine >> checkWhiteSpace;
        if ( !(inputLine.fail()) ){
            cout<<"> Error: too many arguments"<<endl;
            return "error";
        }

        cout<<"> Draw: control passed to graphics window"<<endl;
        
        return "draw";
    }
    
// the command is invalid   
    else{
        cout<<"> Error: invalid command"<<endl;
        return "error";
    }

    return 0;
}

