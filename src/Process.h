#include <string>
#include <set>
#include <vector>
#include "Message.h"

class Process {

    private:
    
        std::set<Process*> out_nbrs;
        std::set<Process*> in_nbrs;
        std::vector<Message*> inMessages;
        std::vector<Message*> outMessages;

    public:

        ~Process();

        void addNeighbour(Process *nbr);

        void removeNeighbour(Process *nbr);

        void receiveMessage(Message *message);
        
        virtual void sendMessages() = 0;

        virtual void transition() = 0;


};