#ifndef __COST_FUNCTIONS_HPP__
#define __COST_FUNCTIONS_HPP__

#include <memory>
#include <set>
#include "../lib/table.hpp"

class CostFunction
{
public:
    virtual float cost (const TablePtrSet& table_set) const = 0;
};

typedef std::unique_ptr<CostFunction> UniqueCostFuncPtr;


class TableSize
{
public:
    virtual float cost (const TablePtrSet& table_set) const;
};

#endif
