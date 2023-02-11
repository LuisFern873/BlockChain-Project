# include "blockchain.h"
# include "index.h"
# include "tester.h"
# include "menu.h"

using namespace std;

int main()
{
    // // Load data
    // BlockChain<Transfer> chain;

    // chain.insert(Transfer(100, "Luis", "Pierina"));
    // chain.insert(Transfer(20, "Stuart", "Mario"));
    // chain.insert(Transfer(50, "Luciana", "Pablo"));
    // chain.insert(Transfer(80, "Pedro", "Andy"));
    // chain.insert(Transfer(60, "Carlos", "Carlota"));

    // chain.display();

    // // Sender and Receiver Hash Index
    // Index index;
    // index.create_hash_index(chain);

    // cout << index.EqualTo(Member::sender, "Pedro");
    // cout << index.EqualTo(Member::receiver, "Mario");

    // Display menu
    auto Menu = Menu::init();
    Menu->display_main();

    return 0;
}