#include "Graph.h"
#include <iostream>

void Graph::addProcess(Process *process) {
    
    int idx = processes.size();
    processes[processes.size()] = process;
    process->setNode(idx); 

}

void Graph::setProcess(int idx, Process *process) {

    processes[idx] = process;
    process->setNode(idx);
}

void Graph::removeProcess(int idx) {

    Process *toDelete = processes[idx];
    processes[idx] = nullptr;
    delete(toDelete);
}

void Graph::connect(int idx1, int idx2) {

    Process *from = processes[idx1];
    Process *to = processes[idx2];
    
    if(to == nullptr || from == nullptr)
        return;
    
    from->addNeighbour(to);

}



