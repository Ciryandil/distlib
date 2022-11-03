#include <iostream>
#include "Graph.h"
#include <thread>

void SyncGraph::simulate() {         

    int activeCount = processes.size();
    int roundCount = 1;
    while(activeCount > 0) {

        std::cout<<"Round: "<<roundCount<<"\n\n";
        std::thread threads[activeCount];
        int threadCount = 0;
        for(std::map<int, Process*>::iterator itr = processes.begin(); itr != processes.end(); ++itr) {

            Process *p = itr->second;
            
            if(!(p->isActive())) {
            
                activeCount--;
                continue;
            }
            
            std::cout<<"Process at node "<<p->getNode()<<" sends messages: \n\n";
            threads[threadCount++] = std::thread(&Process::sendMessages, p); 
            
        }

        for(int i = 0; i < threadCount; i++)
        {
            threads[i].join();
        }

        threadCount = 0;

        for(std::map<int, Process*>::iterator itr = processes.begin(); itr != processes.end(); ++itr) {
            
            Process *p = itr->second;

            if(!(p->isActive())) {

                continue;

            }

            std::cout<<"Process at node "<<p->getNode()<<" examines received messages: \n\n";
            threads[threadCount++] = std::thread(&Process::transition, p);
            
        }

        for(int i = 0; i < threadCount; i++)
        {
            threads[i].join();
        }

        roundCount++;

    }
}