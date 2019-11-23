

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include "../Include/User.h"

class Watchable;
class Session;

/*class User {
public:
    User(const std::string &name) { // פה מאתחלים עם ערכים

    }

    User() { // פה מאתחלים בנאי ריק דיפולטיבי - זה אני הוספתי
        LengthRecommenderUser(const std::string& "default");
    }

    virtual Watchable *getRecommendation(Session &s) = 0;

    std::string getName() const;

    std::vector<Watchable *> get_history() const;

protected:
    std::vector<Watchable *> history;
   // void setName (const std::string inputName){
     //   name first()
   // }

private:
    const std::string name;


};*/

std::string User::getName() const {
    return name;
}

std::vector<Watchable*> User::get_history() const {
    return history;
}

LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) {}
Watchable* LengthRecommenderUser::getRecommendation(Session &s) {

}

RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name) {}
Watchable* RerunRecommenderUser::getRecommendation(Session &s) {

}

GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name) {}
Watchable* GenreRecommenderUser::getRecommendation(Session &s) {

}

//destructors
LengthRecommenderUser::~LengthRecommenderUser() {

}

RerunRecommenderUser::~RerunRecommenderUser() {

}

GenreRecommenderUser::~GenreRecommenderUser() {

}