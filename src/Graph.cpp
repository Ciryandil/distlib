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

void Graph::simulate() {         

    int activeCount = processes.size();
    int roundCount = 1;
    while(activeCount > 0) {

        std::cout<<"Round: "<<roundCount<<"\n\n";

        for(std::map<int, Process*>::iterator itr = processes.begin(); itr != processes.end(); ++itr) {

            Process *p = itr->second;
            
            if(!(p->isActive())) {
            
                activeCount--;
                continue;
            }
            
            std::cout<<"Process at node "<<p->getNode()<<" sends messages: \n\n";
            p->sendMessages(); 
            
        }

        for(std::map<int, Process*>::iterator itr = processes.begin(); itr != processes.end(); ++itr) {
            
            Process *p = itr->second;

            if(!(p->isActive())) {

                continue;

            }

            std::cout<<"Process at node "<<p->getNode()<<" examines received messages: \n\n";
            p->transition();
            
        }

        roundCount++;

    }
}
