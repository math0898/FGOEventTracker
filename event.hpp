#ifndef SUGAKU_EVENT
#define SUGAKU_EVENT

#include <string>

class Event {

    private:
        std::string displayname;
        long uuid;
        

    public:
        std::string inline getDisplayname () {
            return displayname;
        }
};

#endif
