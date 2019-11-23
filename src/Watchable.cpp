
#include <string>
#include <vector>
#include "../Include/Watchable.h"

std::string Movie::toString() const {}
Watchable* Movie::getNextWatchable(Session &) const {}


std::string Episode::toString() const {}
Watchable* Episode::getNextWatchable(Session &) const {}

//destructors
Movie::~Movie() {}
Episode::~Episode() {}

//class Watchable{
//public:
//    Watchable(long id, int length, const std::vector<std::string>& tags);
//    virtual ~Watchable();
//    virtual std::string toString() const = 0;
//    virtual Watchable* getNextWatchable(Session&) const = 0;
//private:
//    const long id;
//    int length;
//    std::vector<std::string> tags;
//};
//
//
//
//class Movie : public Watchable{
//public:
//    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
//    virtual std::string toString() const;
//    virtual Watchable* getNextWatchable(Session&) const;
//private:
//    std::string name;
//};
//
//
//class Episode: public Watchable{
//public:
//    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
//    virtual std::string toString() const;
//    virtual Watchable* getNextWatchable(Session&) const;
//private:
//    std::string seriesName;
//    int season;
//    int episode;
//    long nextEpisodeId;
//};
