#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../Include/Action.h"
#include "../Include/User.h"
#include "../Include/Json.h"
#include "../Include/Watchable.h"



class User;
class Watchable;
class BaseAction;
class Session{

public:
    Session(const std::string &configFilePath);
    ~Session();
    void start();
    std::vector<BaseAction*> getActionsLog();
    bool isUserExist(std::string i_name);
    void insertNewUser(std::string m_name, User *m_user);
    void insertNewAction(BaseAction *m_action);
    std::unordered_map<std::string, User *> getUserMap();
    void setActiveUser(User *m_user);
    std::vector<std::string> splitIntoWords(std::stringstream phrase);
    std::vector<std::string> getWords();
    std::vector<Watchable *> getContent();
    User* getActiveUser();
    bool isYes();
    Watchable* giveContentByTag(std::string);
    void eraseUserFromUserMap(std::string userName);
    Session(Session &&other);// move constructor
    void clean();// needed to destructor
    void steal(Session &other); //needed to move constructor
    Session& operator=(Session && other);// move assignment operator
    Session& operator=(/*const*/ Session & other);//copy assignment operator
    void copy(const Session &other);//needed to move constructor
    Session( const Session& other);// copy constructor

private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;// list of users
    User* activeUser;
    std::vector<std::string> words;// vector of the user's input
};

#endif