#include <string>
#include <set>
#include <vector>
#include "Message.h"

class Process {

    protected:
    
        std::set<Process*> out_nbrs;
        std::set<Process*> in_nbrs;
        std::vector<Message*> inMessages;

    public:

        ~Process();

        void addNeighbour(Process *nbr);

        void removeNeighbour(Process *nbr);

        void receiveMessage(Message *message);
        
        virtual void sendMessages() = 0;

        virtual void transition() = 0;


};