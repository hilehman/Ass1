
#include "../Include/Session.h"
#include "../Include/User.h"
#include "../Include/Watchable.h"

class Watchable;

class Session;

User::User(const std::string &name) : history(), name(name), algoName("len"){
    std::vector<long> hist;
    history = hist;
}


User::~User() {
    history.clear();
}


std::string User::getAlgoName() {
    return algoName;
}


void User::pushToHistory(long watched) {
    history.push_back(watched);
}


void User::setAlgoName(std::string input) {
    algoName = input;
}

std::string User::getName() const {
    return name;
}

std::vector<long> User::get_history() const {
    return history;
}

void User::set_history(std::vector<long> input) {
    history = input;
}


void User::copy_history(User * originalUser, User * newUser) {
    for (unsigned int i = 0; i < originalUser->history.size(); i++) {
        newUser->pushToHistory(originalUser->history.at(i));
    }
}


LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) {
    setAlgoName("len");

}


Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    Watchable *ans = nullptr;
    int sum = 0;
    double average = 0;
    for (unsigned int i = 0; i < history.size(); i++) {
        sum = sum + s.getContent().at(history.at(i) - 1)->getLength();
    }
    average = (double) sum / history.size();
    double max = INT_MAX;
    for (unsigned int i=0; i<s.getContent().size(); i++) {
        double distance = abs(double((s.getContent().at(i)->getLength()) - average));
        if ((distance < max) && (notExistInHistory(s, s.getContent().at(i)->getId()))) {
            max = distance;
            ans = s.getContent().at(i);
        }
    }
    return ans;
}


bool User::notExistInHistory(Session &s, int id) {
    bool notExist = true;
    for (unsigned int j = 0; j < history.size() && notExist; j++) {
        if (history.at(j) == id) {
            notExist = false;
        }
    }
    return notExist;
}


std::map<std::string, int> GenreRecommenderUser::getTagsMap() {
    return tagsMap;
}


void GenreRecommenderUser::intoTagsMap(Watchable *watched) {
    std::vector<std::string> tags;
    tags = watched->getTags();
    for (unsigned int i = 0; i < tags.size(); i++) {
        std::string inputTag = tags.at(i);
        if (tagsMap.count(inputTag)) {
            tagsMap.find(inputTag)->second++;
        } else {
            tagsMap.insert({inputTag, 1});
        }
    }
}


RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name), rerIteration(0) {
    setAlgoName("rer");
}


Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    if (history.empty())
        return nullptr;
    else{

        Watchable *ans =s.getContent().at((history.at(rerIteration))-1);
        rerIteration++;
        return ans;
    }
}


GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name), tagsMap() {
    setAlgoName("gen");
    std::map<std::string, int> var;
    tagsMap = var;
}


Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    Watchable *ans = nullptr;
    std::string tagName;
    int max = 0;
    while (ans == nullptr) {
        for (std::map<std::string, int>::iterator it = tagsMap.begin();
             it != tagsMap.end(); it++) {
            int curr = it->second;
            if (curr > max) { //if current tag's value is bigger than max
                tagName = it->first; //change tagName to that tag's name
                max = curr; // set max to current tag's value
            }
        }
        ans = s.giveContentByTag(tagName); //takes Watchable* or null value from function
        if (ans == nullptr) {
            tagsMap.erase(tagName); //erase the most popular tag as was found
            max = 0;
        }
        if (tagsMap.empty())
            return ans;
    }

    return ans;
}


////destructor


LengthRecommenderUser::~LengthRecommenderUser() {}


User *LengthRecommenderUser::copy() {
    return new LengthRecommenderUser(*this);
}


void LengthRecommenderUser::intoTagsMap(Watchable *watched) {
    return;
}


User *RerunRecommenderUser::copy() {
    return new RerunRecommenderUser(*this);
}


User *GenreRecommenderUser::copy() {
    return new GenreRecommenderUser(*this);
}


RerunRecommenderUser::~RerunRecommenderUser() {}


void RerunRecommenderUser::intoTagsMap(Watchable *watched) {
    return;
}


GenreRecommenderUser::~GenreRecommenderUser() {
    tagsMap.clear();
}
