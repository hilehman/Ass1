
#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <climits>
#include <cmath>        // std::abs
#include <iostream>
#include <utility>
#include <algorithm>

class Watchable;
class Session;


class User{

public:
    User(const std::string& name);
    virtual ~User();
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::string getAlgoName();
    std::vector<long> get_history() const;
    void setAlgoName(std::string input);
    void copy_history(User * activeUser, User * newUser);
    void set_history(std::vector<long> input);
    bool notExistInHistory(Session &s, int i);
    virtual void intoTagsMap (Watchable* watched)=0;
    virtual User* copy()=0;
    void pushToHistory(long watched);

protected:
    std::vector<long> history;

private:
    std::string name;
    std::string algoName;
};


class LengthRecommenderUser : public User {

public:
    LengthRecommenderUser(const std::string &name);
    virtual Watchable *getRecommendation(Session &s);
    virtual void intoTagsMap (Watchable* watched);
    virtual ~LengthRecommenderUser();
    virtual User* copy();

private:
};


class RerunRecommenderUser : public User {

public:
    RerunRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
    virtual void intoTagsMap (Watchable* watched);
    virtual ~RerunRecommenderUser();
    virtual User* copy();

private:
    int rerIteration; //holds number of iteration at rerRecommendation
};

class GenreRecommenderUser : public User {

public:
    GenreRecommenderUser(const std::string& name);
    virtual Watchable* getRecommendation(Session& s);
    virtual ~GenreRecommenderUser();
    std::map<std::string, int> getTagsMap();
    virtual void intoTagsMap (Watchable* watched);
    virtual User* copy();

private:
    std::map<std::string,int> tagsMap;
};

#endif
