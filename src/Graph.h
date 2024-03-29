#include <map>
#include "Process.h"

class Graph {
    
    protected:

        std::map<int, Process*> processes;

    public:

        void addProcess(Process *process); 

        void setProcess(int idx, Process *process);

        void removeProcess(int idx);

        void connect(int idx1, int idx2);

        virtual void simulate() = 0;

};

class SyncGraph: public Graph {

    public:
    
        void simulate();

};
