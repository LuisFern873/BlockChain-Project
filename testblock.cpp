# include <iostream>
# include "block.h"
# include "record.h"

int main()
{
    auto block = new Block<Transfer, 3>();

    block->insert(Transfer(100, "Luis", "Pierina"));
    block->insert(Transfer(150, "Jose", "Pierina"));
    block->insert(Transfer(200, "Marcos", "Pierina"));

    cout << *block << "\n";

    delete block;

    return 0;
}