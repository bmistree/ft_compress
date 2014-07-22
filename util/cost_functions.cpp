#include <algorithm>

#include "cost_functions.hpp"
#include "../lib/table.hpp"

/** TableSizeCostFunction */

float TableSizeCostFunction::cost (const TablePtrSet& table_set) const
{
    int total_num_entries = 0;
    for (TablePtrSet::const_iterator citer = table_set.begin();
         citer != table_set.end(); ++citer)
    {
        total_num_entries += (*citer)->num_entries();
    }
    return (float) total_num_entries;
};


/** TableSizeCandidateProducer */

TableSizeCandidateProducer::TableSizeCandidateProducer(
    const TablePtrSet& table_ptr_set,
    const TableSizeCostFunction& cost_function)
 
 : CandidateProducer<TablePtrSet>(cost_function),
   _table_ptr_set(table_ptr_set),
   _cost_current(cost_function.cost(table_ptr_set))
{}

TableSizeCandidateProducer::~TableSizeCandidateProducer()
{}


float TableSizeCandidateProducer::generate_candidate_get_cost()
{
    // choose a random table to stage a change to, reset candidate_cost, and
    // return it.
    int rand_set_index = rand() % _table_ptr_set.size();

    _candidate = _table_ptr_set.begin();
    std::advance(_candidate,rand_set_index);
    (*_candidate)->perturb();
    _candidate_cost = _cost_function.cost(_table_ptr_set);
    return _candidate_cost;
}

float TableSizeCandidateProducer::cost_current() const
{
    return _cost_current;
}

void TableSizeCandidateProducer::reject_candidate()
{
    (*_candidate)->undo_last_perturbation();
}

void TableSizeCandidateProducer::accept_candidate()
{
    _cost_current = _candidate_cost;
    (*_candidate)->filter_eclipsed();
}

