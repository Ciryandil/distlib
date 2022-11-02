#include <string>

class Message {
    private:
    
        void *ptr;

    public:
        
        Message(void *ptr);

        void*  getMessage();

        void setMessage(void *msg);

};