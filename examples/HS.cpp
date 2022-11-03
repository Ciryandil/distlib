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

        int hops;

    public:

        LeaderSearch(int uid, int hops, int senderNode) {

            this->uid = uid;
            this->hops = hops;
            this->messageType = SEARCH;
            this->senderNode = senderNode;

        }

        LeaderSearch(int uid, int senderNode, MessageType messageType, int hops) {

            this->uid = uid;
            this->senderNode = senderNode;
            this->messageType = messageType;
            this->hops = hops;

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

        int getHops() const {

            return hops;

        }

        void setHops(int hops) {

            this->hops = hops;
            
        }

        friend std::ostream& operator<<(std::ostream &os, const LeaderSearch &msg) {
            
            std::string message;
            if(msg.getMessageType() == SEARCH) {

                message = "[ MESSAGE TYPE: SEARCH | UID: " + std::to_string(msg.getUID()) 
                + " | SENDER NODE: " + std::to_string(msg.getSenderNode()) + " | HOPCOUNT: " + std::to_string(msg.getHops()) +" ] ";

            } else {

                message = "[ MESSAGE TYPE: DECLARATION | LEADER UID: " + std::to_string(msg.getUID()) 
                            + " | LEADER NODE: " + std::to_string(msg.getSenderNode()) + " ] ";

            }

            os<<message;
            return os;
        }

};

class HSProcess: public Process {

    private:

        int uid;
        int maxUID;
        int phase;
        bool leader;
        bool seenLeader;
        bool phaseChanged;
        bool leftReceived;
        bool rightReceived;
        LeaderSearch *leaderDeclaration;

    public:

        HSProcess(int uid) {

            this->uid = uid;
            this->maxUID = uid;
            this->phase = 0;
            this->leader = false;
            this->active = true;
            this->seenLeader = false;
            this->leaderDeclaration = nullptr;
            this->phaseChanged = true;
            this->leftReceived = false;
            this->rightReceived = false;
        }

        bool isPhaseChanged() {

            return phaseChanged;

        }

        void sendMessages() {

            if(leader || seenLeader) {

                for(Process *p : out_nbrs) {
                    
                    std::cout<<"Process at node "<<node<<": Sending Leader Declaration to neighbour at index "<<p->getNode()<<"...\n"
                                <<"Declaration Message: "<<*leaderDeclaration<<"\n\n";
                    void *msg = static_cast<void*>(leaderDeclaration);
                    p->receiveMessage(msg);

                }

                active = false;
                return;

            }

            if(!phaseChanged) {

                return;

            }
            

            LeaderSearch *maxSeenLeft = new LeaderSearch(uid, (1<<phase), node);
            LeaderSearch *maxSeenRight = new LeaderSearch(uid, (1<<phase), node);
            phaseChanged = false;

            std::set<Process*>::iterator itr = out_nbrs.begin(); 
            Process *leftP = *itr;
            void *msgL = static_cast<void*>(maxSeenLeft);
            leftReceived = false;
            std::cout<<"Process at node "<<node<<": Sending message "<<*maxSeenLeft<<" to neighbour at index "<<leftP->getNode()<<"...\n\n";
            leftP->receiveMessage(msgL);

            itr++;

            if(itr == out_nbrs.end())
                return;

            Process *rightP = *itr;
            void *msgR = static_cast<void*>(maxSeenRight);
            rightReceived = false;          
            rightP->receiveMessage(msgR);
            std::cout<<"Process at node "<<node<<": Sending message "<<*maxSeenRight<<" to neighbour at index "<<rightP->getNode()<<"...\n\n";

        }

        void transition() {

            std::set<Process*>::iterator itr = in_nbrs.begin(); 
            Process *leftP = *itr;
            itr++;
            Process *rightP = *itr;

            if(itr == in_nbrs.end())
                rightReceived = true;

            while(!inMessages.empty()) {

                void *msg = inMessages.front();
                inMessages.pop();
                LeaderSearch *nbrMsg = static_cast<LeaderSearch*>(msg);
                std::cout<<"Process at node "<<node<<": Received message: "<<*nbrMsg<<"\n\n";
                if(nbrMsg->getMessageType() == DECLARATION) {

                    leaderDeclaration = nbrMsg;
                    seenLeader = true;
                    std::cout<<"Process at node "<<node<<": Received Leader Declaration from Process with UID: "<<nbrMsg->getUID()<<
                                " located at node "<<nbrMsg->getSenderNode()<<"\n\n";

                    return;

                } 
                int uidval = nbrMsg->getUID();
                int sender = nbrMsg->getSenderNode();
                int hops = nbrMsg->getHops();
                if(uid < uidval && hops > 1) {

                    nbrMsg->setHops(hops-1);
                    nbrMsg->setSenderNode(node);
                    
                    if(sender == leftP->getNode() && rightP != nullptr) {

                        rightP->receiveMessage(msg);

                    } else {

                        leftP->receiveMessage(msg);

                    }
                    

                } else if(uid < uidval && hops == 1) {

                    nbrMsg->setHops(0);
                    nbrMsg->setSenderNode(node);

                    if(sender == leftP->getNode()) {

                        leftP->receiveMessage(msg);

                    } else if(rightP != nullptr) {

                        rightP->receiveMessage(msg);

                    }
                } else if(uidval == uid) {
                    
                    if(hops > 0)
                    {
                        leader = true;
                        leaderDeclaration = new LeaderSearch(uid, node, DECLARATION, 1<<(phase+1));
                    } else if(sender == leftP->getNode()) {
                        
                        leftReceived = true;
                        
                    } else {
                        
                        rightReceived = true;

                    }

                } else if(hops == 0) {

                    if(sender == leftP->getNode() && rightP != nullptr) {
                        
                        rightP->receiveMessage(msg);

                    } else if(rightP != nullptr && sender == rightP->getNode()) {

                        leftP->receiveMessage(msg);

                    }

                } 
            }
            if(leftReceived && rightReceived) {

                phase++;
                phaseChanged = true; 
                std::cout<<"Process at node "<<node<<" moves to phase "<<phase<<"\n\n";
              

            }

        }

};

int main() {

    SyncGraph ringGraph;
    int numProcesses = 3;
    for(int i = 0; i < numProcesses; i++) {

        Process *p = new HSProcess(rand());
        ringGraph.addProcess(p);

    }

    for(int i = 0; i < numProcesses; i++) {

        ringGraph.connect(i, (i+1) % numProcesses);
        ringGraph.connect((i+1)%numProcesses, i);
    }

    ringGraph.simulate();

    return 0;

}

