#include <string>
#include <set>
#include <queue>

class Process {

    protected:
    
        std::set<Process*> out_nbrs;
        std::set<Process*> in_nbrs;
        std::queue<void*> inMessages;
        int node = -1;
        bool active;

    public:

        ~Process();

        int getNode();

        void setNode(int node);

        bool isActive();

        void addNeighbour(Process *nbr);

        void removeNeighbour(Process *nbr);

        void receiveMessage(void *message);
        
        virtual void sendMessages() = 0;

        virtual void transition() = 0;


};