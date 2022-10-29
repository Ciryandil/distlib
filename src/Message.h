#include <string>

class Message {
    private:
    
        std::string buffer;

    public:
        
        Message(char *msg);

        char*  getMessage();

        void setMessage(char *msg);

};