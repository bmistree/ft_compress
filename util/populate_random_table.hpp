#ifndef __POPULATE_RANDOM_TABLE_HPP__
#define __POPULATE_RANDOM_TABLE_HPP__

#include "../lib/table.hpp"
#include "../lib/action.hpp"

#define DEFAULT_NUM_HEADER_BITS 5

class PopulateRandomTable
{
public:
    /** For now, each entry just has a single random action. */
    static void populate_random_table(
        Table& table,int num_entries,
        const GeneralActionConstructionParameters& params,
        int num_header_bits = DEFAULT_NUM_HEADER_BITS);
};

#endif
