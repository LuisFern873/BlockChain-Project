# include <iostream>
# include "block.h"
# include "record.h"

int main()
{
    auto block = new Block<Transfer, 5>();

    block->insert(Transfer(100, "Luis", "Pierina"));
    block->insert(Transfer(150, "Jose", "Pierina"));
    block->insert(Transfer(200, "Marcos", "Pierina"));
    block->insert(Transfer(40, "Rodrigo", "Pierina"));
    block->insert(Transfer(80, "Stuart", "Pierina"));

    block->mine();

    cout << *block << "\n";

    delete block;

    return 0;
}