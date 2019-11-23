#include "../Include/Action.h"
#include <string>
#include <iostream>
#define ENUM_TO_STR(ENUM) std::string(#ENUM) //check that this is a valid solution

void BaseAction::complete(){
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(const std::string& errorMsg){
    status = ActionStatus::ERROR;
    std::cout<<"Error - " << &errorMsg << std::endl;//to check if to print with & or with out.
}

std::string BaseAction::getErrorMsg() const{
    return errorMsg;
};

ActionStatus BaseAction::getStatus() const{
    return status;
};


void CreateUser::act(Session& sess){
    User user => user
    if letter valid => ok
            else {
                error(invalid )
            }

};

std::string CreateUser::toString() const{
    return "CreateUser " + ENUM_TO_STR(getStatus());

};
