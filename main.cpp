# include "datamanager.h"
# include "index.h"
# include "menu.h"

int main()
{
    BlockChain<Transfer> chain;

    DataManager::load("assets/100_transfers.csv", chain);

    auto menu = Menu<Transfer>::init(chain);
    menu->display_main();

    return 0;
}