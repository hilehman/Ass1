

#include <vector>
#include <unordered_map>
#include <string>

#include "../Include/Action.h"
#include "../Include/Session.h"
#include "../Include/User.h"

class User;
class Watchable;

Session::Session(const std::string &configFilePath) {

}

void Session::start() {
    std::cout<<"SPLFLIX is now on!"<<std::endl;
    activeUser = new LengthRecommenderUser("default");//should do call to destractor
    userMap.insert({activeUser->getName(), activeUser});//put in the table
    // not done yet
}


/*
std::vector<Watchable*> content;// to here mesharsherim the movies + json
std::vector<BaseAction*> actionsLog;
std::unordered_map<std::string,User*> userMap;// list of users
User* activeUser;// the active user, when we do func start - default.
};
#endif*/
