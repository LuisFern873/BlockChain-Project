# ifndef INDEXING_H
# define INDEXING_H

# include <iostream>
# include "blockchain.h"
# include "structures/chainhash.h"
# include "record.h"

using namespace std;


class Indexing
{
    public:

    template <typename T>
    static void sender_hash_index(BlockChain<T>& blockchain)
    {
        ChainHash<string, T*> index;

        for(int i = 1; i < blockchain.chain.size(); ++i){
            auto& block = blockchain.chain[i];

            string Sender = block->data.get_sender();
            T* ptr = &block->data;

            cout << Sender << ": " << ptr << "\n";
            index.insert(Sender, ptr);
        }

        cout << *index.find("Pedro");
    }
};

# endif // INDEXING_H