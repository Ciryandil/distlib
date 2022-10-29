#include <map>
#include "Process.h"

class Graph {
    
    private:

        std::map<int, Process*> processes;

    public:

        void addProcess(Process *process); 

        void setProcess(int idx, Process *process);

        void removeProcess(int idx);

        void connect(int idx1, int idx2);

        void simRound();

};
