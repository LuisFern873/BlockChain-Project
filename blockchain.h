# ifndef BLOCK_CHAIN_H
# define BLOCK_CHAIN_H

# include "block.h"
# include "record.h"
# include "structures/doublelist.h"

template <typename T, size_t N = 5>
class BlockChain
{
    public:
        BlockChain();
        void insert(T feature);
        void update(size_t id);
        void remove(size_t id);
        void display();


        int size();

        Block<T, N>* block;

    private:
        DoubleList<Block<T, N>*> chain;

        void create_genesis();

    friend class Index;
};

template <typename T, size_t N>
BlockChain<T, N>::BlockChain()
{
    create_genesis();
    block = new Block<T, N>();
}

template <typename T, size_t N>
void BlockChain<T, N>::insert(T feature)
{
    block->insert(feature);

    if (!block->data.is_full())
        return;
    
    block->id = chain.size();
    block->previous_hash = chain.back()->hash;

    if (block->mine()) {
        chain.push_back(block);
        block = new Block<T, N>();
    }
    else
        throw runtime_error("Block not mined");

    // update index
    // Index::update();
}

template <typename T, size_t N>
void BlockChain<T, N>::update(size_t id)
{
    // re hashing
    // from id to last block
    // update ledger and index
}

template <typename T, size_t N>
void BlockChain<T, N>::remove(size_t id)
{
    // Just remove from index
}

template <typename T, size_t N>
void BlockChain<T, N>::display()
{
    auto iterator = --chain.end();
    for (int i = 0; i < 10; ++i) {
        cout << **iterator << "\n";
        cout << " 🢁 🢃 \n\n";
        --iterator;
    }
}

template <typename T, size_t N>
void BlockChain<T, N>::create_genesis()
{
    auto genesis = new Block<T, N>();

    while (!genesis->data.is_full())
        genesis->insert(T());

    if (genesis->mine()) {
        chain.push_front(genesis);
    }
    else
        throw runtime_error("Block not mined");  
}

template <typename T, size_t N>
int BlockChain<T, N>::size()
{
    return chain.size();
}


# endif // BLOCK_CHAIN_H