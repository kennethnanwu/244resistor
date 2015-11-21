#include <iomanip>
#include "NodeList.h"
#include "Resistor.h"
#include "Node.h"
#include "ResistorList.h"

#define MIN_ITERATION_CHANGE 0.0001

using namespace std;

float node_strip_wide=900.0;
float space_between_res=400.0;
float left_right_space=400.0;
float bottom_top_space=800.0;

void NodeList::draw(easygl& window){
    solve();
    window.gl_clearscreen();//clear the area
    //iterate over nodes, calling appropriate draw functions
    //iterate over resistors, calling appropriate draw functions
    //these functions will use new member variables that store drawing coordinates
    //for each node and resistor
    Node* nodep = nodeHead;
    int node_num = 0;
    int res_num = 0;
    while(nodep != NULL){
        node_num++;
        Resistor* resp;
        resp = nodep->resList.resHead;
        while(resp != NULL){
            res_num++;
            resp = resp->nextRes;
        }
        nodep = nodep->nextNode;
    }
    res_num = res_num/2;

    nodep = nodeHead;
    //tell drae res and draw node which node and res are they drawing
    int node_count = 0;
    int res_count = 0;

    while(nodep != NULL){
        nodep->draw_node_strips(window, node_count, res_num);
        node_count++;
        nodep = nodep->nextNode;
    }
    
    nodep = nodeHead;
    while(nodep != NULL){
        

        Resistor* resp = nodep->resList.resHead;
        while(resp != NULL){
            if(resp->endpointNodeIDs[0] > nodep->nodeId || resp->endpointNodeIDs[1] > nodep->nodeId){
                
                int smaller_node, bigger_node;
                if(resp->endpointNodeIDs[0] < resp->endpointNodeIDs[1]){
                    smaller_node = resp->endpointNodeIDs[0];
                    bigger_node = resp->endpointNodeIDs[1];
                }

                else if(resp->endpointNodeIDs[0] > resp->endpointNodeIDs[1]){
                    smaller_node = resp->endpointNodeIDs[1];
                    bigger_node = resp->endpointNodeIDs[0];
                }

                Node* check_node_num =  nodeHead;//check the sequence of this node in the node list
                
                int from = 0, to = 0;
                
                while(check_node_num != NULL){
                    if(check_node_num->nodeId == smaller_node)
                        break;
                    
                    else{
                        ++from;
                        check_node_num = check_node_num->nextNode;
                    }
                }
                
                check_node_num =  nodeHead;//set back to the beginning
                while(check_node_num != NULL){
                    if(check_node_num->nodeId == bigger_node)
                        break;
                    
                    else{
                        ++to;
                        check_node_num = check_node_num->nextNode;
                    }
                }

                resp->draw_res(window, from, to, res_count);
                res_count++;
            }

            resp = resp->nextRes;
        }

        nodep = nodep->nextNode;
    }

}

void NodeList::set_draw_coords(float& xleft, float& ybottom, float& xright, float& ytop){
    //ierate over nodes and resistors, setting drawing coordinate member variables
    //return the minimum and maximum coordinates you will use, so they can be passed to the easygl package via set_world_coordinates().
    Node* nodep = nodeHead;
    int num_of_node=0, num_of_res=0;
    while(nodep != NULL){
        num_of_node++;

        Resistor* resp = nodep->resList.resHead;
        while(resp != NULL){
            num_of_res++;
            resp = resp->nextRes;
        }

        nodep = nodep->nextNode;
    }
    xleft = 0.0;
    ybottom = 0.0;
    xright = node_strip_wide*num_of_node;
    ytop = bottom_top_space + 400 + 400 * ( (num_of_res / 2) + 1 );
}

bool NodeList::VisSet(){ //check if any nodes have a set voltage
    Node* nodep = nodeHead;
    while(nodep != NULL){
        if(nodep->flag_setV == 1)
            return true;
        
        nodep = nodep->nextNode;
    }
    return false;
}

bool NodeList::checkNodeExist(int nodeId_) const{
	Node* nodep = nodeHead;
        while(nodep != NULL){
            if( nodep->nodeId == nodeId_){
                return true;
            }
            else{
                nodep = nodep->nextNode;
            }
        }
	return false;
}

void NodeList::addNode(int nodeId_){
    if(checkNodeExist(nodeId_))
        return;
    
    Node* newNode = new Node(nodeId_);
    Node* nodep = nodeHead;
    Node* prevNode = NULL;//the node before nodep
    
    while(nodep != NULL && nodep->nodeId < nodeId_){
        prevNode = nodep;
        nodep = nodep->nextNode;
    }
    
    newNode->nextNode = nodep;
    if(prevNode==NULL){
        nodeHead = newNode;// no Node in the node list, or this nodeId is the smallest, insert at head
    }
    else
        prevNode->nextNode = newNode;
}

bool NodeList::checkResName(string resName_) const{
	Node* nodep = nodeHead;
	while(nodep != NULL){
		if (nodep->checkResName(resName_))
		{
			return true;
		}
		nodep = nodep->nextNode;
	}
	return false;
}

void NodeList::addResToNode(int nodeId1_, int nodeId2_, string resName_, double resistance_){
    Node* nodep1 = nodeHead;
    while(nodep1->nodeId != nodeId1_){
        nodep1=nodep1->nextNode;
    }
    nodep1->addResistor(nodeId1_, nodeId2_, resName_, resistance_);
    
    Node* nodep2 = nodeHead;
    while(nodep2->nodeId != nodeId2_){
        nodep2=nodep2->nextNode;
    }
    nodep2->addResistor(nodeId1_, nodeId2_, resName_, resistance_);
}

double NodeList::get_resistance(string resName_) const{
    Node* nodep = nodeHead;
    while(nodep != NULL){
        Resistor* resp = nodep->resList.resHead;
        while(resp != NULL){
            if(resp->getName() == resName_)
                return resp->getResistance();
            resp = resp->nextRes;
        }
        nodep = nodep->nextNode;
    }
}

void NodeList::changeResistance(string resName_, double resistance_){
    Node* nodep = nodeHead;
    while(nodep != NULL){
        Resistor* resp = nodep->resList.resHead;
        while(resp != NULL){
            if(resp->getName() == resName_)
                resp->setResistance(resistance_);
            resp = resp->nextRes;
        }
        nodep = nodep->nextNode;
    }
}

void NodeList::printRes(string resName_) const{
    Node* nodep = nodeHead;
    while(nodep != NULL){
        Resistor* resp = nodep->resList.resHead;
        while(resp != NULL){
            if(resp->getName() == resName_){
                resp->print();
                return;
            }
            resp = resp->nextRes;
        }
        nodep = nodep->nextNode;
    }
}

void NodeList::printAllNode() const{
    Node* nodep = nodeHead;
    while(nodep != NULL){
        if(nodep->numRes != 0){
            nodep->print();
        }
        else if(nodep->flag_setV == 1){
            nodep->printV();
        }
        
        nodep = nodep->nextNode;
    }
}

void NodeList::printNode(int nodeId_) const{
    Node* nodep = nodeHead;
    while(nodep != NULL){
        if(nodep->nodeId == nodeId_ && nodep->numRes != 0)
            nodep->print();
        else if(nodep->nodeId == nodeId_ && nodep->flag_setV == 1){
            nodep->printV();
        }
        nodep = nodep->nextNode;
    }
}

void NodeList::deleteAll(){ 
    Node* nodep = nodeHead;
    Node* prevNodep = NULL;
    while(nodep != NULL){
        nodep->numRes = 0;
        //if this node is not set a voltage
        if(nodep->flag_setV == 0){ // if this node has no set voltage, then delete it 
            if(prevNodep == NULL){ //it is the first node in the node list
                nodeHead = nodep->nextNode;
                Node* deleteThisNode = nodep;
                nodep = nodeHead;
                deleteThisNode->nextNode = NULL;
                delete deleteThisNode;
                deleteThisNode = NULL;
            }
            else{ // if previous node ptr is not NULL, then let its nextNode points to the next node of the current node
                prevNodep->nextNode = nodep->nextNode;
                Node* deleteThisNode = nodep;
                nodep = prevNodep->nextNode;
                deleteThisNode->nextNode = NULL;
                delete deleteThisNode;
                deleteThisNode = NULL;
            }
        }
        
        else{//this node has a set voltage, do nothing, go to next node
            delete nodep->resList.resHead;
            nodep->resList.resHead = NULL;
            prevNodep = nodep;
            nodep = nodep->nextNode;
        }
    }
}

bool NodeList::deleteR(string resName_){
    int flag_deleteR = 0;//this is used to determine which line should we output, if there is this resistor name then we delete it and set this flag to 1
    Node* nodep = nodeHead;
    while(nodep != NULL){
        Resistor* resp = nodep->resList.resHead;
        Resistor* prevRes = NULL;
        while(resp != NULL){
            if(resp->getName() == resName_){
                flag_deleteR = 1;//resistor found, now we gonna delete it
                nodep->numRes = (nodep->numRes) - 1; // delete a resistor in this node, so decrement the resistor count
                if(prevRes == NULL)
                    nodep->resList.resHead = resp->nextRes;
                else
                    prevRes->nextRes = resp->nextRes;
                
                resp->nextRes = NULL;
                delete resp;
                resp = NULL;
                break;
            }
            prevRes = resp;
            resp = resp->nextRes;
        }
        nodep = nodep->nextNode;
    }
    
    
    if(flag_deleteR == 1)
        return true;
    else
        return false;
}

void NodeList::setV(int nodeId_, double voltage_){
    addNode(nodeId_);
    Node* nodep = nodeHead;
    while(nodep != NULL){
        if(nodep->nodeId == nodeId_){
            nodep->voltage = voltage_;
            nodep->flag_setV = 1;
            cout<<fixed;
            cout<<setprecision(2);
            cout<<"> Set: node "<<nodeId_<<" to "<<voltage_<<" Volts"<<endl;
            return;
        }
        nodep = nodep->nextNode;
    }

}

void NodeList::unsetV(int nodeId_){
    Node* nodep = nodeHead;
    while(nodep != NULL){
        if(nodep->nodeId == nodeId_){
            nodep->voltage = 0;
            nodep->flag_setV = 0;
        }
        nodep = nodep->nextNode;
    }
}

bool NodeList::solve(){
    double largestChange=0;//true - means lower than minimal change
    if( !VisSet() ){
        return false;
    }
    
    else{
        do{ //loop through the node list recursively when the largest change among nodes is larger than 0.0001
            largestChange = 0;
            Node* nodep = nodeHead;//starts from the first node for every new loop
            while( nodep != NULL){//loop through the list from the first node
                if(nodep->flag_setV == 0 && nodep->numRes != 0){//if the voltage if not set, and there is at least one resistor, then we need to calculate the voltage
                    
                    double oldV = nodep->voltage; //save the original voltage before the calculation, later this is used to compare with the calculated value to see if it's smaller then the min change
                    double totalR = 0.0; // value of 1/(sum 1/R)
                    double totali = 0.0; //sum of V/R
                    
                    Resistor* resp = nodep->resList.resHead; //start from the first resistor in this node
                    while(resp != NULL){ //first we loop through the resList in this node, calculate the value of (sum 1/R) first
                        totalR += 1/ (resp->getResistance()); // 1/R

                        int anotherNodeId = resp->endpointNodeIDs[0];
                        if(anotherNodeId == nodep->nodeId)
                            anotherNodeId = resp->endpointNodeIDs[1];//check the nodeId of the other node that this resistor is connected to

                        
                        Node* anotherNode = nodeHead;
                        while(anotherNode->nodeId != anotherNodeId){ // go to the other node that this resistor is connected to
                            anotherNode = anotherNode->nextNode;
                        }
                        totali += (anotherNode->voltage) / resp->resistance; // get its voltage and calculate  V/R
                        
                        resp = resp->nextRes;
                    }
                    totalR = 1/totalR; //then calculate 1/(sum 1/R)
                    
                    //now we have 1/(sum 1/R) and sum of V/R, multiply them
                    nodep->voltage = totalR*totali;
                    //if the voltage change on this node is larger than the largestChange, then store it as the largest change
                    if(fabs( (nodep->voltage) - oldV ) > largestChange)
                        largestChange = fabs( (nodep->voltage) - oldV);
                }
                nodep = nodep->nextNode;
            }
        }while( largestChange > 0.0001 );
    }
    
    bool flag_doPrintSolveNode = false;//go through the node list once to determine if solve should be print.  if no node have resistor connected to it, then print error message
    Node* nodep = nodeHead;

    while(nodep != NULL){
        if( nodep->numRes > 0)
            flag_doPrintSolveNode = true; // if there is at least one node has resistor, then the solve should be print, otherwise print error message
        
        nodep = nodep->nextNode;
    }
    
    if(flag_doPrintSolveNode == false)
        return false;
        
    else
        return true;
}