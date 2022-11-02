#include<string>
#include<iostream>
using namespace std;
enum MessageType {SEARCH, DECLARATION};
struct LeaderSearch {

    private:

        int senderNode;

        int uid;

        MessageType messageType; 

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

int main()
{
    LeaderSearch *a = new LeaderSearch(1232249);
    LeaderSearch *b = new LeaderSearch(1232249, 12, DECLARATION);
    cout<<reinterpret_cast<char*>(a)<<" "<<reinterpret_cast<char*>(b)<<"\n";
}