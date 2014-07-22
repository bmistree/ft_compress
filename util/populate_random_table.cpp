#include <memory>
#include <string>
#include <stdlib.h>
#include <unordered_map>
#include <vector>

#include "../lib/entry.hpp"
#include "../lib/header.hpp"
#include "../lib/table.hpp"
#include "../lib/action.hpp"

#include "populate_random_table.hpp"

// FIXME: should actually use real max priority
#define NUM_PRIORITIES 32000
static int random_priority()
{
    return rand() % MAX_PRIORITY;
}


static UniqueEntryPtr generate_random_entry(
    const GeneralActionConstructionParameters& params,
    int num_header_bits)
{
    UniqueEntryPtr to_return (
        new Entry(
            random_priority(),
            Header(num_header_bits)));
    UniqueActionPtr action_ptr = Action::generate_random_action(params);
    to_return->add_action(action_ptr);
    return std::move(to_return);
}

void PopulateRandomTable::populate_random_table(
    Table& table,int num_entries,
    const GeneralActionConstructionParameters& params,
    int num_header_bits)
{
    std::unordered_map<int,std::vector<UniqueEntryPtr>> entries_to_add;

    // can only insert entry if the entry does not conflict with an existing
    // entry with identical priority.  For instance, should not have two
    // entries with priority 10 that match the same packet and one forwards
    // and one drops.  Similarly, should not have two identical entries.
    // The way we enforce this requirement is to filter entries that have
    // identical priorities and whose headers match.
    int num_added = 0;
    // FIXME: for certain parameter combinations, can get infinite loops (eg.,
    // if request so many entries with so few header bits that *must* get
    // conflict).  Should assert out in those cases.
    while (num_added < num_entries)
    {
        UniqueEntryPtr to_add = generate_random_entry(params,num_header_bits);
        const Header& to_add_header = to_add->match();
        
        std::vector<UniqueEntryPtr>& same_priorities_vec =
            entries_to_add[to_add->priority()];

        for (auto vec_iter = same_priorities_vec.begin();
             vec_iter != same_priorities_vec.end(); ++vec_iter)
        {
            UniqueEntryPtr& entry_ptr = *vec_iter;
            const Header& vec_header = entry_ptr->match();
            if (vec_header.is_subset_of(to_add_header) ||
                to_add_header.is_subset_of(vec_header))
            {
                continue;
            }
        }

        same_priorities_vec.push_back(std::move(to_add));
        ++ num_added;
    }

    // actually add entries to map.
    for (auto map_iter = entries_to_add.begin();
         map_iter != entries_to_add.end(); ++map_iter)
    {
        for (auto vec_iter = map_iter->second.begin();
             vec_iter != map_iter->second.end(); ++vec_iter)
        {
            table.add_entry(*vec_iter);
        }
    }
}
