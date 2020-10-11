
#include "../Include/Watchable.h"
#include "../Include/Session.h"
#include "../Include/User.h"


long Watchable::getId() const{
    return id;
}


Watchable* Episode::copy(){
    return new Episode(*this);
}


int Watchable::getLength(){
    return length;
}


std::vector<std::string> Watchable::getTags(){
    return tags;
}


Watchable::Watchable(long id, int length, const std::vector<std::string> &tags) : id(id), length(length), tags(tags) {}


Watchable::~Watchable() {
    tags.clear();
}


std::string Episode::getSeriesName() {
    return seriesName;
}


std::string Movie::toString() const{
    return name;
}


Watchable* Movie::getNextWatchable(Session& sess) const{
    return sess.getActiveUser()->getRecommendation(sess);
}


Movie::Movie(long id, const std::string &name, int length, const std::vector<std::string> &tags): Watchable(id, length, tags), name(name) {
}


std::string Movie::getSeriesName() {
    return "";
}


Watchable* Episode::getNextWatchable(Session& sess) const {
    Watchable *ans = nullptr;
    unsigned long currentId = getId();
    if( currentId < sess.getContent().size()) { //if current is not the last watchable at content
        if(sess.getContent().at(currentId )->getSeriesName().compare(seriesName)==0){ //if next content is an episode with the same series's name
            ans = sess.getContent().at(currentId); //return next episode
        }
        else {
            ans = sess.getActiveUser()->getRecommendation(sess);
        }
    }
    else {
        ans = sess.getActiveUser()->getRecommendation(sess);
    }
    return ans;
}


int Episode::getEpisode() {
    return episode;
}


Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode, const std::vector<std::string> &tags) :  Watchable(id, length, tags), seriesName(seriesName), season(season), episode(episode), nextEpisodeId(-1){}


//////destructor

Movie::~Movie() {}


Watchable *Movie::copy() {
    return new Movie(*this);
}

//////destructor

Episode::~Episode() {}


std::string Episode::toString() const {
    std::string epOutput  = "";
    std::string seOutput  = "";
    int ep = episode;
    int se = season;

    if (se < 10){
        seOutput = "S0" + std::to_string(season);
    }
    else{
        seOutput = "S" + std::to_string(season);
    }
    if (ep < 10){
        epOutput = "E0" + std::to_string(episode);
    }
    else{
        epOutput = "E" + std::to_string(episode);
    }
    return seriesName + " " + seOutput + epOutput;
}

void Episode::setNextEpisodeId(long id) {
    nextEpisodeId= id;
}
