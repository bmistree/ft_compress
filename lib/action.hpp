#ifndef __ACTION_HPP__
#define __ACTION_HPP__

#include <vector>

class Action
{};

typedef std::vector<Action> ActionList;


class DropAction : public Action
{
public:
    DropAction();
    ~DropAction();
};

class ForwardAction : public Action
{
public:
    ForwardAction();
    ~ForwardAction();
};

#endif __ACTION_HPP__
