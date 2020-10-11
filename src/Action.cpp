#include "../Include/Action.h"

#include <utility>
#include "../Include/Session.h"

BaseAction::BaseAction() :  errorMsg(""), status(PENDING), userName(), algorithmName(){}

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::setStatus(ActionStatus m_status) {
    status = m_status;
}

void BaseAction::error(const std::string &errorMsg) {
    status = ERROR;
    this->errorMsg = errorMsg;
    std::cout << "Error" << errorMsg << std::endl;
}

std::string BaseAction::getErrorMsg() const {
    return errorMsg;
}

ActionStatus BaseAction::getStatus() const {
    return status;
}

std::string BaseAction::getGetErrorMsg() const {
    return getErrorMsg();
}

BaseAction::~BaseAction() {}


//----------------------------------------------CreateUser-------------------------------------------------------


void CreateUser::act(Session &sess) {
    std::vector<std::string> s;
    s = sess.getWords();
    setUserName(s.at(1)); // find the second word and check that it works
    setAlgorithmName(s.at(2)); // find the third word
    if (sess.isUserExist(getUserName())) { //checks if user's name already exist in userMap
        error(": username is already in use");
    }
    else if ((algorithmName != "rer") && (algorithmName != "len") && (algorithmName != "gen")) {
        error(": recommendation algorithm is invalid");
    }
    else {
        User *user;
        if (getAlgorithmName() == "rer") {
            user = new RerunRecommenderUser(getUserName());
            sess.insertNewUser(getUserName(), user); // inserts to UserMap (stringname,Pointer)
        }
        if (getAlgorithmName() == "len") {
            user = new LengthRecommenderUser(getUserName());
            sess.insertNewUser(getUserName(), user);
        }
        if (getAlgorithmName() == "gen") {
            user = new GenreRecommenderUser(getUserName());
            sess.insertNewUser(getUserName(), user);
        }
        complete();
    }

}


std::string CreateUser::toString() const {
    return "CreateUser " + enumToString(getStatus()) + this->getErrorMsg();
}


BaseAction *CreateUser::copy() {
    return new CreateUser(*this);
}


std::string CreateUser::getUserName() {
    return userName;
}


std::string CreateUser::getAlgorithmName() {
    return algorithmName;
}


void CreateUser::setUserName(std::string _userName) {
    userName = std::move(_userName);
}


void CreateUser::setAlgorithmName(std::string _algoName) {
    algorithmName = std::move(_algoName);
}


CreateUser::CreateUser() : userName(), algorithmName(){}


//----------------------------------------------ChangeActiveUser-------------------------------------------------------


ChangeActiveUser::ChangeActiveUser() : userName(), algorithmName(){}

void ChangeActiveUser::act(Session &sess) {
    std::vector<std::string> s = sess.getWords();
    setUserName(s[1]);
    if (!sess.isUserExist(getUserName())) { //checks if user's name already exist in userMap
        error(": username does not exist");
    }
    else {
        sess.setActiveUser((sess.getUserMap().at(getUserName())));
        complete();
    }
}


std::string ChangeActiveUser::toString() const {
    return "ChangeActiveUser " + enumToString(getStatus()) + this->getErrorMsg();
}


BaseAction *ChangeActiveUser::copy() {
    return new ChangeActiveUser(*this);
}


std::string ChangeActiveUser::getUserName() {
    return userName;
}


void ChangeActiveUser::setUserName(std::string _userName) {
    userName = std::move(_userName);
}


//----------------------------------------------DeleteUser-------------------------------------------------------


DeleteUser::DeleteUser() : userName(){}


void DeleteUser::act(Session &sess) {
    std::vector<std::string> s = sess.getWords();
    std::string currName;
    currName = sess.getWords().at(1);
    if (!sess.isUserExist(currName)) { //checks if user's name already exist in userMap
        error(": username does not exist");
    }
    else {
        sess.eraseUserFromUserMap(currName);
        complete();
    }
}


std::string DeleteUser::toString() const {
    return "DeleteUser " + enumToString(getStatus()) + this->getErrorMsg();
}


BaseAction *DeleteUser::copy() {
    return new DeleteUser(*this);
}


std::string DeleteUser::getUserName() {
    return userName;
}


void DeleteUser::setUserName(std::string _userName) {
    userName = std::move(_userName);
}


//----------------------------------------------DuplicateUser-------------------------------------------------------


void DuplicateUser::act(Session &sess) {
    std::vector<std::string> s = sess.getWords();
    std::string originalName = s[1];
    std::string newUserName = s[2];
    if (!sess.isUserExist(originalName)) { //checks if user's name already exist in userMap
        error(" username does not exist");
    }
    if (sess.isUserExist(newUserName)) { //checks if user's name already exist in userMap
        error(" username is already in use");
    }
    else {
        User *user;
        if (sess.getUserMap().at(originalName)->getAlgoName() == "rer") {
            user = new RerunRecommenderUser(newUserName);
            sess.insertNewUser(newUserName, user); // inserts to UserMap (stringname,Pointer)
            std::unordered_map<std::string, User *> map = sess.getUserMap();
            auto search = map.find(originalName);
            User *oldUser = search->second;
            sess.getUserMap().at(originalName)->copy_history(oldUser,user);
           // sess.getActiveUser()->copy_history(oldUser, user);
            complete();

        }
        else if (sess.getUserMap().at(originalName)->getAlgoName() == "len") {
            user = new LengthRecommenderUser(newUserName);
            sess.insertNewUser(newUserName, user);
            std::unordered_map<std::string, User *> map = sess.getUserMap();
            auto search = map.find(originalName);
            User *oldUser = search->second;
            sess.getUserMap().at(originalName)->copy_history(oldUser,user);

            //sess.getActiveUser()->copy_history(oldUser, user);
            complete();

        }
        else if (sess.getUserMap().at(originalName)->getAlgoName() == "gen") {
            user = new GenreRecommenderUser(newUserName);
            sess.insertNewUser(newUserName, user);
            std::unordered_map<std::string, User *> map = sess.getUserMap();
            auto search = map.find(originalName);
            User *oldUser = search->second;
            sess.getUserMap().at(originalName)->copy_history(oldUser,user);

            // sess.getActiveUser()->copy_history(oldUser, user);
            complete();
        }
    }
}


std::string DuplicateUser::toString() const {
    return "DuplicateUser " + enumToString(getStatus()) + this->getErrorMsg();
}


BaseAction *DuplicateUser::copy() {
    return new DuplicateUser(*this);
}

//----------------------------------------------Watch-------------------------------------------------------


void Watch::act(Session &sess) {
    Watchable *askedContent = sess.getContent().at(
            std::stoi(sess.getWords()[1]) - 1); //creates pointer to current watchable*
    std::cout << "watching" << " " << sess.getContent()[(std::stoi(sess.getWords()[1])) - 1]->toString()
              << std::endl; //prints "watching <name_of_watchable>"
    if (sess.getActiveUser()->getAlgoName().compare("gen") == 0) {
        sess.getActiveUser()->intoTagsMap(askedContent);
    }

    sess.getActiveUser()->pushToHistory((long) std::stoi(sess.getWords()[1])); //pushes the content's id to user's history
    sess.insertNewAction(this);

    int loc = sess.getActiveUser()->get_history().size();
    Watchable *nextRec = (sess.getContent().at((sess.getActiveUser()->get_history().at(loc - 1)) - 1))->getNextWatchable(sess);
    complete();

    if (nextRec != nullptr) {
        std::cout << "We recommend watching " << nextRec->toString() << ", continue watching? [y/n]"
                  << std::endl;
        while (sess.isYes()) { // Takes answer, return true if user press Y
            sess.getActiveUser()->pushToHistory(nextRec->getId());
            std::cout << "watching" << " " << nextRec->toString() << std::endl; //prints "watching <name_of_watchable>"
            if (sess.getActiveUser()->getAlgoName().compare("GEN") == 0) {
                sess.getActiveUser()->intoTagsMap(nextRec);
            }
            sess.insertNewAction(this->copy());
            complete();

            nextRec = (sess.getContent().at(sess.getActiveUser()->get_history().at(sess.getActiveUser()->get_history().size() - 1) - 1))->getNextWatchable(sess); //returns "next watchable" of the last watched watchable
            if (nextRec == nullptr)
                return;

            if (nextRec != nullptr) {
                std::cout << "We recommend watching " << nextRec->toString() << ", continue watching? [y/n]"
                          << std::endl;
            }
        }
    }
}


std::string Watch::toString() const {
    return "Watch " + enumToString(getStatus()) + this->getErrorMsg();
}


BaseAction *Watch::copy() {
    return new Watch(*this);
}


//----------------------------------------------PrintContentList-------------------------------------------------------


void PrintContentList::act(Session &sess) {
    std::vector<Watchable *> content = sess.getContent(); //creates local vector of content
    for (int i = 0; i < (signed)content.size(); ++i) { //iterate through contentList
        int id = i + 1;
        std::string space = " "; // represent " " for the printing
        std::string name = content.at(i)->toString(); // takes watchable's toString (<name> + S01E01)
        int lengh = content.at(i)->getLength(); // takes watchable's length
        std::vector<std::string> tags = content.at(i)->getTags();
        std::cout << id << "." << space << name << space << lengh << " mintues "
                  << "["; //prints example: "1. Game of Thrones S01E01 58 minutes ["
        for (int j = 0; j < (signed)tags.size() - 1; ++j) {
            std::cout << tags.at(j) << ", "; //  printe example: "War, Drama, "
        }
        std::cout << tags.at(tags.size() - 1) << "]"; //prints last tag and close "]" - print example: "Fantasy]"
        std::cout << std::endl;
    }
    complete();
}


std::string PrintContentList::toString() const {
    return "PrintContentList " + enumToString(getStatus()) + getErrorMsg();
}


BaseAction *PrintContentList::copy() {
    return new PrintContentList(*this);
}


//----------------------------------------------PrintWatchHistory-------------------------------------------------------


void PrintWatchHistory::act(Session &sess) {
    User *currUserPtr = sess.getActiveUser(); //creates local pointer to activeUser
    std::cout << "Watch history for " << currUserPtr->getName() << std::endl;
    for (int i = 0; i < (signed)sess.getActiveUser()->get_history().size(); i++) {  //iterate through activeUser's watch history
        std::cout << i + 1 << ". " << sess.getContent().at(
                currUserPtr->get_history().at(i) - 1)->toString(); // print example: 1. Game of Thrones S01E01
        std::cout << std::endl; //creates new line
    }
    complete();
}

std::string PrintWatchHistory::toString() const {
    return "PrintHistoryWatch " + enumToString(getStatus()) + this->getErrorMsg();
}


BaseAction *PrintWatchHistory::copy() {
    return new PrintWatchHistory(*this);
}


//----------------------------------------------PrintActionsLog-------------------------------------------------------


void PrintActionsLog::act(Session &sess) {
    sess.getWords();
    std::vector<BaseAction *> log = sess.getActionsLog(); // creates local variable of User's actionLog
    for (int i = log.size() - 1; i >= 0; i--) { //iterate through actionLog
        std::cout << log.at(i)->toString();
             std::cout << std::endl;
    }
    std::cout << std::endl;
    complete();

}


std::string PrintActionsLog::toString() const {
    return "PrintActionLog " + enumToString(getStatus()) + this->getErrorMsg();
}


BaseAction *PrintActionsLog::copy() {
    return new PrintActionsLog(*this);
}


void Exit::act(Session &sess) {
    complete();
}


std::string Exit::toString() const {
    return "Exit " + enumToString(getStatus()) + this->getErrorMsg();
}


BaseAction *Exit::copy() {
    return new Exit(*this);
}


std::string BaseAction::enumToString(ActionStatus statusName) const {
    std::string toReturn;
    if (statusName==ERROR){
        toReturn = "ERROR";
    }
    if (statusName==PENDING){
        toReturn = "PENDING";
    }
    if (statusName==COMPLETED){
        toReturn = "COMPLETED";
    }
    return toReturn;

}

