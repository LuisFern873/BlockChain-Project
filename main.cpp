# include "blockchain.h"
# include "datamanager.h"
# include "menu.h"
# include "index.h"

int main()
{
    BlockChain<Transfer> chain;

    DataManager::load("assets/100_transfers.csv", chain);

    Index index(chain);

    index.create_hash_index();
    index.create_tree_index();
    index.create_trie_index();

    auto menu = Menu::init(chain, index);
    menu->display_main();

    return 0;
}