#ifndef __COST_FUNCTIONS_HPP__
#define __COST_FUNCTIONS_HPP__

#include <memory>
#include <set>
#include "../lib/table.hpp"

template <class T>
class CostFunction
{
public:
    virtual float cost(const T& to_find_cost_of) const = 0;
};

template <class T>
class CandidateProducer
{
public:
    CandidateProducer(const CostFunction<T>& cf)
     : _cost_function(cf)
    {}
    virtual ~CandidateProducer()
    {}
    
    virtual float generate_candidate_get_cost() = 0;
    virtual float cost_current() const = 0;
    virtual void reject_candidate() = 0;
    virtual void accept_candidate() = 0;
    
protected:
    const CostFunction<T>& _cost_function;
};



class TableSizeCostFunction : public CostFunction<TablePtrSet>
{
public:
    virtual float cost (const TablePtrSet& to_find_cost_of) const;
};

class TableSizeCandidateProducer : public CandidateProducer<TablePtrSet>
{
public:
    TableSizeCandidateProducer(
        const TablePtrSet& table_ptr_set,
        const TableSizeCostFunction& cost_function);
    ~TableSizeCandidateProducer();

    virtual float generate_candidate_get_cost();
    virtual float cost_current() const;
    virtual void reject_candidate();
    virtual void accept_candidate();
    
private:
    const TablePtrSet& _table_ptr_set;
    float _cost_current;

    TablePtrSetCIter _candidate;
    float _candidate_cost;
};

#endif
