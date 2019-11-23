#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"
#include <json.h>
#include <fstream>


class User;
class Watchable;

class Session{
public:
    Session(const std::string &configFilePath){
        using json = nlohmann::json;
        std::ifstream i(configFilePath);
    };
    ~Session();
    void start(){
        std::cout << "Hello, World!" << std::endl;



    }
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
};
#endif