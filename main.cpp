# include "datamanager.h"
# include "index.h"
# include "menu.h"

int main()
{
    BlockChain<Transfer> chain;

    DataManager::load("assets/10000_transfers.csv", chain);

    auto menu = Menu<Transfer>::init(chain);
    menu->display_main();

    return 0;
}