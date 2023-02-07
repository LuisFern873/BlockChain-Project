# include "blockchain.h"
# include "tester.h"

using namespace std;

int main()
{
    BlockChain<Transfer> chain;

    chain.insert(Transfer(100, "Luis", "Pierina"));
    chain.insert(Transfer(20, "Stuart", "Mario"));
    chain.insert(Transfer(50, "Luciana", "Pablo"));
    chain.insert(Transfer(80, "Pedro", "Andy"));

    chain.display();

    return 0;
}