# include "blockchain.h"
# include "datamanager.h"
# include "menu.h"
# include "index.h"

int main()
{
    BlockChain<Transfer> chain;

    DataManager::load("assets/transfers.csv", chain);

    Index index;

    index.create_hash_index(chain);


    // cout << index.EqualTo(Member::sender, "Raja") << "\n";
    // cout << index.EqualTo(Member::receiver, "Mannix") << "\n";
    // cout << index.EqualTo(Member::sender, "Mannix") << "\n";


    auto menu = Menu::init(chain, index);
    menu->display_main();

    return 0;
}