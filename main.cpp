
# include "blockchain.h"
# include "tester.h"

using namespace std;

int main()
{
    BlockChain<Transaction> chain;

    chain.insert(Transfer(100, "Luis", "Pierina"));
    chain.insert(Transfer(20, "Stuart", "Mario"));
    chain.insert(Transfer(50, "Luciana", "Pablo"));

    chain.display();

    return 0;
}

// https://stackoverflow.com/questions/13091302/stdvector-for-parent-and-child-class
// Problema: upcasting (a child class is transform into a parent class) when pushing into container
// missing information because child class keeps more attributes (sender and receiver)

// Useful links! :)
// https://andersbrownworth.com/blockchain/
// https://www.freecodecamp.org/news/how-does-blockchain-really-work-i-built-an-app-to-show-you-6b70cd4caf7d/