#include "Graph.h"

void Graph::addProcess(Process *process) {
    
    processes[processes.size()] = process;

}

void Graph::setProcess(int idx, Process *process) {

    processes[idx] = process;
}

void Graph::removeProcess(int idx) {

    Process *toDelete = processes[idx];
    processes[idx] = nullptr;
    delete(toDelete);
}

void Graph::simRound() {         

    for(std::map<int, Process*>::iterator itr = processes.begin(); itr != processes.end(); ++itr) {
        
        Process *p = itr->second;
        p->sendMessages(); 
        
    }

    for(std::map<int, Process*>::iterator itr = processes.begin(); itr != processes.end(); ++itr) {
        
        Process *p = itr->second;
        p->transition(); 
        
    }

}