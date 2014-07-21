#ifndef __COST_FUNCTIONS_HPP__
#define __COST_FUNCTIONS_HPP__

#include <memory>
#include <set>
#include "../lib/table.hpp"

class CostFunction
{
public:
    virtual float cost () const = 0;
};

typedef std::unique_ptr<CostFunction> UniqueCostFuncPtr;


class TableSize
{
public:
    TableSize(const TablePtrSet& table_set);
    virtual float cost () const;
private:
    const TablePtrSet& _table_set;
};

#endif
