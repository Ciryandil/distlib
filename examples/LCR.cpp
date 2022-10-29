#include <iostream>
#include <src/Graph.h>

struct UID {

    public:

        int uid;

        UID(int uid) {

            this->uid = uid;

        }

        int getUID() {

            return uid;

        }

        void setUID(int uid) {

            this->uid = uid;

        }

        friend std::ostream& operator<<(std::ostream &os, const UID &uid) {

            os<<"UID : %d\n", uid.uid;
            return os;
        }

};

class LCRProcess: public Process {

    private:

        int uid;
        int maxUID;
        bool leader;

    public:

        LCRProcess(int uid) {

            this->uid = uid;
            this->maxUID = uid;
            this->leader = false;

        }

        void sendMessages() {

            if(leader == true) {
                return;
            } 
            UID *maxSeen = new UID(maxUID);
            
            for(Process *p : out_nbrs) {

                    char *msg = reinterpret_cast<char*>(maxSeen) ;
                    Message *m = new Message(msg);
                    p->receiveMessage(m);

            }

        }

        void transition() {

            if(leader == true) {
                return;
            }

            for(Message *m : inMessages) {

                char *msg = m->getMessage();
                UID *nbrUID = reinterpret_cast<UID*>(msg); 
                int uidval = nbrUID->getUID();
                if(uidval > maxUID) {

                    maxUID = uidval;

                }

                else if(uidval == uid) {

                    leader = true;
                    std::cout<<"Process with UID "<<uid<<" declares itself leader\n";

                }

            }

        }

};

int main() {

    Graph ringGraph;

    for(int i = 0; i < 10; i++) {

        Process *p = new LCRProcess(rand());
        ringGraph.addProcess(p);

    }

    for(int i = 0; i < 10; i++) {

        ringGraph.connect(i, (i+1) % 10);

    }

    for(int i = 0; i <= 10; i++) {

        std::cout<<"Round "<<i<<"\n";
        ringGraph.simRound();

    }

    return 0;

}

