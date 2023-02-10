# ifndef INDEX_H
# define INDEX_H

# include <iostream>
# include "blockchain.h"
# include "structures/chainhash.h"
# include "record.h"

using namespace std;

enum class Member { sender, receiver };

struct Index
{
    void create_hash_index(BlockChain<Transfer>& blockchain)
    {
        for (int i = 1; i < blockchain.chain.size(); ++i)
        {
            auto block = blockchain.chain[i];

            string sender = block->data.get_sender();
            string receiver = block->data.get_receiver();
            Transfer* ptr = &block->data;
            
            sender_index.insert(sender, ptr);
            receiver_index.insert(receiver, ptr);
        }
    }

    Transfer EqualTo(Member member, string key)
    {
        switch (member)
        {
        case Member::sender:
            return *sender_index.find(key);
        case Member::receiver:
            return *receiver_index.find(key);
        default:
            throw runtime_error("Block data not found");
        }
    }

    ChainHash<string, Transfer*> sender_index;
    ChainHash<string, Transfer*> receiver_index;
};


# endif // INDEX_H