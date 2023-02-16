# ifndef BLOCK_CHAIN_H
# define BLOCK_CHAIN_H

# include "block.h"
# include "record.h"
# include "structures/doublelist.h"

template <typename T>
class BlockChain
{
    public:
        BlockChain();
        void insert(T feature);
        void update(size_t id);
        void remove(size_t id);
        void display();

    private:
        DoubleList<Block<T, 4>*> chain;

        void create_genesis();

    friend class Index;
};

template <typename T>
BlockChain<T>::BlockChain()
{
    create_genesis();
}

template <typename T>
void BlockChain<T>::insert(T feature)
{
    auto block = new Block<T>();

    block->insert(feature);

    if (!block.data.is_full())
        return;

    block->id = chain.size();
    block->previous_hash = chain.back()->hash;

    if (block->mine())
        chain.push_back(block);
    else
        throw runtime_error("Block not mined");
        
    // update index
    // Index::update();
}

template <typename T>
void BlockChain<T>::update(size_t id)
{
    // re hashing
    // from id to last block
    // update ledger and index
}

template <typename T>
void BlockChain<T>::remove(size_t id)
{
    // Just remove from index
}

template <typename T>
void BlockChain<T>::display()
{
    auto iterator = chain.begin();
    while(iterator != chain.end()){
        cout << **iterator << "\n";
        ++iterator;
    }
}

template <typename T>
void BlockChain<T>::create_genesis()
{
    auto genesis = new Block<T>();
    genesis->id = 0;
    genesis->previous_hash = string(64, '0');

    if (genesis->mine())
        chain.push_front(genesis);
    else
        throw runtime_error("Block not mined");
}


# endif // BLOCK_CHAIN_H