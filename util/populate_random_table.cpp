#include <memory>
#include <string>
#include <stdlib.h>

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


static UniqueEntryPtr generate_random_entry(int num_header_bits)
{
    UniqueEntryPtr to_return (
        new Entry(
            random_priority(),
            Header(num_header_bits)));
    UniqueActionPtr action_ptr = Action::generate_random_action();
    to_return->add_action(action_ptr);
    return std::move(to_return);
}

void PopulateRandomTable::populate_random_table(
    Table& table,int num_entries,int num_header_bits)
{
    for (int i = 0; i < num_entries; ++i)
    {
        UniqueEntryPtr to_add = generate_random_entry(num_header_bits);
        table.add_entry(to_add);
    }
}
