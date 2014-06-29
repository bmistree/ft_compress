#ifndef __ACTION_HPP__
#define __ACTION_HPP__

#include <vector>

class Action
{};

typedef std::vector<Action*> ActionList;
typedef ActionList::iterator ActionListIter;
typedef ActionList::const_iterator ActionListCIter;

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
