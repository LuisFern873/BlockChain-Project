# include "blockchain.h"
# include "datamanager.h"
# include "menu.h"

int main()
{
    BlockChain<Transfer> chain;

    DataManager::load("assets/transfers.csv", chain);

    auto menu = Menu::init(chain);
    menu->display_main();

    return 0;
}