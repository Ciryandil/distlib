#include <iostream>
#include <src/Graph.h>
#include <algorithm>
#include <string>

enum MessageType {SEARCH, DECLARATION};

class LeaderSearch {

    private:

        MessageType messageType; 

        int uid;

        int senderNode;

    public:

        LeaderSearch(int uid) {

            this->uid = uid;
            this->senderNode = -1;
            this->messageType = SEARCH;

        }

        LeaderSearch(int uid, int senderNode, MessageType messageType) {

            this->uid = uid;
            this->senderNode = senderNode;
            this->messageType = messageType;

        }

        int getUID() const {

            return uid;

        }

        void setUID(int uid) {

            this->uid = uid;

        }

        MessageType getMessageType() const {

            return messageType;

        }

        void setMessageType(MessageType messageType) {

            this->messageType = messageType;

        }

        int getSenderNode() const {

            return senderNode;

        }

        void setSenderNode(int senderNode) {

            this->senderNode = senderNode;

        }

        friend std::ostream& operator<<(std::ostream &os, const LeaderSearch &msg) {
            
            std::string message;
            if(msg.getMessageType() == SEARCH) {

                message = "[ MESSAGE TYPE: SEARCH | UID: " + std::to_string(msg.getUID()) + " ] ";

            } else {

                message = "[ MESSAGE TYPE: DECLARATION | LEADER UID: " + std::to_string(msg.getUID()) 
                            + " | LEADER NODE: " + std::to_string(msg.getSenderNode()) + " ] ";

            }

            os<<message;
            return os;
        }

};

class LCRProcess: public Process {

    private:

        int uid;
        int maxUID;
        bool leader;
        bool seenLeader;
        LeaderSearch *leaderDeclaration;

    public:

        LCRProcess(int uid) {

            this->uid = uid;
            this->maxUID = uid;
            this->leader = false;
            this->active = true;
            this->seenLeader = false;
            this->leaderDeclaration = nullptr;

        }

        void sendMessages() {

            if(leader || seenLeader) {

                for(Process *p : out_nbrs) {
                    
                    std::cout<<"Sending Leader Declaration to neighbour at index "<<p->getNode()<<"...\n";
                    std::cout<<"Declaration Message: "<<*leaderDeclaration<<"\n\n";
                    void *msg = static_cast<void*>(leaderDeclaration);
                    p->receiveMessage(msg);

                }

                active = false;
                return;

            }

            LeaderSearch *maxSeen = new LeaderSearch(maxUID);
            
            for(Process *p : out_nbrs) {
            
                    std::cout<<"Sending message "<<*maxSeen<<" to neighbour at index "<<p->getNode()<<"...\n\n";
                    void *msg = static_cast<void*>(maxSeen);
                    p->receiveMessage(msg);

            }

        }

        void transition() {

            int maxInUID = -1;
            while(!inMessages.empty()) {

                void *msg = inMessages.front();
                inMessages.pop();
                LeaderSearch *nbrMsg = static_cast<LeaderSearch*>(msg);
                std::cout<<"Received message: "<<*nbrMsg<<"\n\n";

                if(nbrMsg->getMessageType() == DECLARATION) {

                    leaderDeclaration = nbrMsg;
                    seenLeader = true;
                    std::cout<<"Received Leader Declaration from Process with UID: "<<nbrMsg->getUID()<<" located at node "<<nbrMsg->getSenderNode()<<"\n\n";

                    return;

                } 
                int uidval = nbrMsg->getUID();
                maxInUID = std::max(maxInUID, uidval);
                delete(nbrMsg);
                
            }
            if(maxInUID > maxUID) {

                maxUID = maxInUID;
                std::cout<<"Largest seen UID changes to "<<maxUID<<"\n\n";

            }
            
            else if(maxInUID == uid) {

                leader = true;
                std::cout<<"Received own UID. Process at node "<<node<<" declares itself leader\n\n";
                leaderDeclaration = new LeaderSearch(this->uid, this->node, DECLARATION);
                
            }
            else {

                std::cout<<"Largest seen UID remains "<<maxUID<<"\n\n";

            }

        }

};

int main() {

    Graph ringGraph;
    int numProcesses = 2;
    for(int i = 0; i < numProcesses; i++) {

        Process *p = new LCRProcess(rand());
        ringGraph.addProcess(p);

    }

    for(int i = 0; i < numProcesses; i++) {

        ringGraph.connect(i, (i+1) % numProcesses);

    }

        
        ringGraph.simulate();


    return 0;

}

