
# include "blockchain.h"

# include "tester.h"

using namespace std;

int main()
{
    BlockChain<Transaction> chain;

    Transaction t1("Luis", "Pierina", 100);
    Transaction t2("Stuart", "Mario", 20);
    Transaction t3("Luciana", "Pablo", 50);

    chain.insert(t1);
    chain.insert(t2);
    chain.insert(t3);

    chain.display();




    return 0;
}