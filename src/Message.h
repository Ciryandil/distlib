#include <string>

class Message {
    private:

        std::string receiverId;

    public:

        virtual void print() = 0;


};