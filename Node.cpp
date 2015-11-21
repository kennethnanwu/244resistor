#include "Node.h"
#include "Resistor.h"
#include "ResistorList.h"
#include <iomanip>
#include "NodeList.h"
/* private arguments:
 * 
 * int numRes;
 * int resIDArray[MAX_RESISTOR_PER_NODE];
 */
using namespace std;

extern float node_strip_wide;
extern float bottom_top_space;
extern float left_right_space;
extern float space_between_res;

Node::Node(int nodeId_){
    numRes = 0;
    nodeId = nodeId_;
    flag_setV = 0;
    resList.resHead = NULL;
    nextNode=NULL;
    voltage = 0;
}

Node::~Node(){
    delete resList.resHead;
    resList.resHead = NULL;
    delete nextNode;
}

int Node::get_nodeId(){ return nodeId;}

double Node::get_voltage(){ return voltage;}
Node* Node::get_nextNode(){ return nextNode;}

void Node::addResistor(int nodeId1_, int nodeId2_, string resName_, double resistance_){
    ++numRes;
    int endpoints[2];
    endpoints[0] = nodeId1_;
    endpoints[1] = nodeId2_;
    Resistor* newRes=new Resistor(resName_, resistance_, endpoints);
    Resistor* resp = resList.resHead;
    Resistor* preRes = NULL;
    while(resp != NULL){
        preRes = resp;
        resp = resp->nextRes;
    }
    if(preRes == NULL){ //no resistor in the list, insert at head
        resList.resHead = newRes;
    }
    else
        preRes->nextRes = newRes;
}

    

void Node::print() const{
    cout<<"Connections at node "<<nodeId<<": "<<numRes<<" resistor(s)"<<endl;
    Resistor* resp = resList.resHead;
    while(resp != NULL){
        cout<<"  ";
        resp->print();
        resp = resp->nextRes;
    }
}
bool Node::checkResName(string resName_) const{
    Resistor* resp = resList.resHead;
    while(resp != NULL){
        if(resp->getName() == resName_){
            return true;
        }
        else 
            resp = resp->nextRes;
    }
    return false;
}

void Node::printV() const{
    cout<<fixed;
    cout<<setprecision(2);
    cout<<"Connections at node "<<nodeId<<": "<<voltage<<" V"<<endl;
}

void Node::draw_node_strips(easygl& window, int node_count, int res_num){
    window.gl_setcolor(LIGHTGREY);
    window.gl_fillrect( left_right_space + node_strip_wide * node_count, 400.0, 400.0 + node_strip_wide * node_count + 100, 400.0 + bottom_top_space + 400*res_num);

    window.gl_setfontsize(30);
    window.gl_setcolor(BLACK);
    stringstream print_node_num;
    print_node_num<<"Node"<<nodeId;
    window.gl_drawtext(left_right_space + node_strip_wide * node_count + 50 , 250.0, print_node_num.str());

    stringstream print_voltage;
    print_voltage<<voltage<<"V";
    window.gl_drawtext(left_right_space + node_strip_wide * node_count + 50, 100, print_voltage.str());
}


