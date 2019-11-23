#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"

class User;
class Watchable;

class Session{
public:
    Session(const std::string &configFilePath);
    ~Session();
    void start();
private:
    std::vector<Watchable*> content;// to here mesharsherim the movies + json
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;// list of users
    User* activeUser;// the active user, when we do func start - default.
};
#endif