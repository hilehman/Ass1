
#include "../Include/Session.h"
#include <iterator>

using json = nlohmann::json;

Session::Session(const std::string &configFilePath): content(), actionsLog(), userMap(), activeUser(), words() {
    User *user;
    user = new LengthRecommenderUser("default");
    activeUser = user;
    userMap.insert({activeUser->getName(), activeUser});

// read Json file

    json json1;
    std::ifstream i(configFilePath);
    i >> json1;
    long id = 1;
    for (int i = 0; i < (signed) json1["movies"].size(); i++) {// goes on all movies and create tags vector
        std::vector<std::string> tags;
        std::string name = json1["movies"][i]["name"];
        int length = json1["movies"][i]["length"];
        for (unsigned int j = 0; j < json1["movies"][i]["tags"].size(); j++) {
            tags.push_back(json1["movies"][i]["tags"][j]);
        }
        Movie *mov = new Movie(id, name, length, tags);// creat a movie object and insert it to content vector
        content.push_back(mov);
        id++;
    }

    for (int i = 0; i < (signed) json1["tv_series"].size(); i++) { //goes on all episodes and create tags vector
        std::string name = json1["tv_series"][i]["name"];
        int episode_length = json1["tv_series"][i]["episode_length"];
        std::vector<std::string> tags;
        for (unsigned int j = 0; j < json1["tv_series"][i]["tags"].size(); j++) {
            tags.push_back(json1["tv_series"][i]["tags"][j]);
        }
        for (int h = 0; h <(signed) json1["tv_series"][i]["seasons"].size(); h++) { //insert all tvseries to content vector : episode after episodes, season after season (chronologyc)
            for (int k = 0; k < json1["tv_series"][i]["seasons"][h]; k++) {
                Episode *epi = new Episode(id, name, episode_length, h + 1, k + 1, tags);
                content.push_back(epi);
                if (h < (signed) json1["tv_series"][i]["seasons"].size() && k < json1["tv_series"][i]["seasons"][h]) { //if there is next episode - set next episode
                    epi->setNextEpisodeId(id + 1);
                }
                id++;
            }
        }
    }
}

// -----------------------------------------------end of json----------------------------------------------------------

// -----------------------------------------------start----------------------------------------------------------------

void Session::start() {
    std::cout << "SPLFLIX is now on!" << std::endl;
    bool goOn = true;
    while (goOn) {

        std::string phrase;
        std::string oneWord;
        std::getline(std::cin, phrase);
        std::stringstream s(phrase);

        char space = ' '; // define the delimiter to split by
        while (std::getline(s, oneWord, space)) {
            words.push_back(oneWord);
        }
        s.clear();

        BaseAction *action;

        if (words[0].compare("createuser") == 0) {
            action = new CreateUser();
            action->act(*this);
            actionsLog.push_back(action);
        }
        else if (words[0].compare("changeuser") == 0) {
            action = new ChangeActiveUser();
            action->act(*this);
            actionsLog.push_back(action);
        }
        else if (words[0].compare("deleteuser") == 0) {
            action = new DeleteUser();
            action->act(*this);
            actionsLog.push_back(action);
        }
        else if (words[0].compare("dupuser") == 0) {
            action = new DuplicateUser;
            action->act(*this);
            actionsLog.push_back(action);
        }
        else if (words[0].compare("watch") == 0) {
            action = new Watch;
            action->act(*this);//inserts the action to the actionLog at action "Watch"
        }
        else if (words[0].compare("content") == 0) {
            action = new PrintContentList;
            action->act(*this);
            actionsLog.push_back(action);
        }
        else if (words[0].compare("watchhist") == 0) {
            action = new PrintWatchHistory;
            action->act(*this);
            actionsLog.push_back(action);
        }
        else if (words[0].compare("log") == 0) {
            action = new PrintActionsLog;
            action->act(*this);
            actionsLog.push_back(action);
        }
        else if (words[0].compare("exit") == 0) {
            action = new Exit;
            action->act(*this);
            goOn = false;// stops the While loop and returns to main.cpp
            actionsLog.push_back(action);
        }
        else std::cout << "wrong input, try again";

        words.clear();  //erase words
        std::cout << std::endl;
    }
}


std::vector<BaseAction *> Session::getActionsLog() {
    return actionsLog;
}


bool Session::isUserExist(std::string i_name) { // checks if given name exists in userMap;
    return (userMap.count(i_name)!=0); //checks if given key exist, returns boolean value
}


void Session::insertNewUser(std::string m_name, User *m_user) { // inserts new user into userMap
    userMap.insert({m_name, m_user});
}


void Session::insertNewAction(BaseAction *m_action) { // inserts new action into actionsLog (vector of BaseAction*)
    actionsLog.push_back(m_action);
}


void Session::setActiveUser(User *m_user) {
    activeUser = m_user;
}


std::unordered_map<std::string, User* > Session::getUserMap() {
    return userMap;
}


std::vector<std::string> Session::getWords() {
    return words;
}


std::vector<Watchable *> Session::getContent() {
    return content;
}


User *Session::getActiveUser() {
    return activeUser;
}


bool Session::isYes() {  // return TRUE if user enters Y, else return False
    std::string c;
    std::getline(std::cin, c);
    return (c.compare("y") == 0);
}


Watchable *Session::giveContentByTag(std::string tagName) {
    Watchable *ans = nullptr;
    bool stillsearch = true;
    bool moveToNextCon = false;
    for (unsigned int i = 0; i < content.size() && stillsearch; i++) {
        moveToNextCon=false;
        for (unsigned int j = 0; j < content.at(i)->getTags().size() && stillsearch && !moveToNextCon; j++) {
            if (content.at(i)->getTags().at(j).compare(tagName) == 0) {
                moveToNextCon=true;
                stillsearch =  !(activeUser->notExistInHistory(*this, i + 1));
                if (!stillsearch){
                    ans = content.at(i);
                }
            }
        }
    }
    return ans;
}


void Session::eraseUserFromUserMap(std::string userName) {
    delete(userMap.find(userName)->second);
    userMap.find(userName)->second = nullptr;
    userMap.erase(userName);
}


// -----------------------------------------------destractors----------------------------------------------------------


Session::~Session() {
    clean();
}

//help func to destractor

void Session::clean() {
    for (auto x: content) {
        if (x != nullptr) {
            delete (x);
        }
    }
    content.clear();

    for (auto x: actionsLog) {
        if (x != nullptr) {
            delete (x);
        }
    }
    actionsLog.clear();

    for (std::unordered_map<std::string, User *>::iterator itMap = userMap.begin(); itMap != userMap.end(); itMap++) {
        if (itMap->second != nullptr) {
            delete (itMap->second);
        }
    }
    userMap.clear();
    words.clear();
}


//..........................................copy constructor........................................


Session::Session(const Session &other) :content(),actionsLog(),userMap(),activeUser(), words(other.words) {//:content(),actionsLog(),userMap(),activeUser(), words(other.words)
    copy(other);
}

//help func for copy constructor

void Session::copy(const Session &other) {
    std::string username = other.activeUser->getName();
    for (auto con :other.content) {
        this->content.push_back(con->copy());
    }

    for (auto actLog : other.actionsLog) {
        this->actionsLog.push_back(actLog->copy());
    }

    for (auto o_user : other.userMap) {
        this->userMap.insert(std::pair<std::string,User*>(o_user.first, o_user.second->copy()));
    }

    activeUser = userMap.at(username);
}


//..........................................copy assignment operator........................................


Session &Session::operator=(Session &other) {
    if (this != &other) {
        clean();
        copy(other);
    }
    return *this;
}


//..........................................move constructor........................................


Session::Session(Session &&other): content(other.content), actionsLog(other.actionsLog), userMap(other.userMap), activeUser(other.activeUser), words(other.words) {
    steal(other);
}

void Session::steal(Session &other) {
    for (auto &x : content) {
        x = nullptr;
    }
    for (auto &x : actionsLog) {
        x = nullptr;
    }
    for (std::unordered_map<std::string, User *>::iterator itMap = userMap.begin(); itMap != userMap.end(); itMap++) {
        itMap->second = nullptr;
    }
    activeUser = nullptr;
}


//..........................................move assignment operator........................................


Session &Session::operator=(Session &&other) {
    if (this != &other) {
        clean();
        steal(other);
    }
    return *this;
}

