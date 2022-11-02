#include "Process.h"

Process::~Process() {
    
    for(Process *p : this->in_nbrs) {
    
        p->removeNeighbour(this);
    
    }

}

int Process::getNode() {

    return node;

}

void Process::setNode(int node) {

    this->node = node;

}

bool Process::isActive() {

    return active;
    
}

void Process::addNeighbour(Process *nbr) {
    
    out_nbrs.insert(nbr);
    nbr->in_nbrs.insert(this);
}

void Process::removeNeighbour(Process *nbr) {

    out_nbrs.erase(nbr);
    nbr->in_nbrs.erase(this);

}

void Process::receiveMessage(void *message) {

    inMessages.push(message);
    
}


     