#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include <unordered_map>
#include <istream>

#include "../Include/User.h"

class Session;

enum ActionStatus{
    PENDING, COMPLETED, ERROR
};

class BaseAction{

public:
    BaseAction();
    BaseAction(ActionStatus status);
    virtual ~BaseAction();
    ActionStatus getStatus() const;
    virtual void act(Session& sess)=0;
    virtual std::string toString() const=0;
    void setStatus(ActionStatus);
    std::string getGetErrorMsg() const;
    virtual BaseAction* copy()=0;

protected:
    void complete();
    void error(const std::string& errorMsg);
    std::string getErrorMsg() const;
    std::string enumToString(ActionStatus) const;

private:
    std::string errorMsg;
    ActionStatus status;
    std::string userName;
    std::string algorithmName;
};

class CreateUser : public BaseAction {
public:
    CreateUser();
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copy();
    void setUserName(std::string _userName);
    void setAlgorithmName(std::string _algoName);
    std::string getUserName();
    std::string getAlgorithmName();

private:
    std::string userName;
    std::string algorithmName;
};

class ChangeActiveUser : public BaseAction {
public:
    ChangeActiveUser();

    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copy();
    void setUserName(std::string _userName);
    std::string getUserName();

private:
    std::string userName;
    std::string algorithmName;
};

class DeleteUser : public BaseAction {
public:
    DeleteUser();
    virtual void act(Session & sess);
    virtual std::string toString() const;
    virtual BaseAction* copy();
    void setUserName(std::string _userName);
    std::string getUserName();

private:
    std::string userName;
};


class DuplicateUser : public BaseAction {
public:
    virtual void act(Session & sess);
    virtual std::string toString() const;
    virtual BaseAction* copy();
};

class PrintContentList : public BaseAction {
public:
    virtual void act (Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copy();
};

class PrintWatchHistory : public BaseAction {
public:
    virtual void act (Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copy();
};


class Watch : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copy();
};


class PrintActionsLog : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copy();
};

class Exit : public BaseAction {
public:
    virtual void act(Session& sess);
    virtual std::string toString() const;
    virtual BaseAction* copy();
};
#endif