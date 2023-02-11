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
        void insert(T data);
        void display(ostream& os = cout);

    private:
        DoubleList<Block<T>*> chain;
        void create_genesis();

    friend class Index;
};

template <typename T>
BlockChain<T>::BlockChain()
{
    create_genesis();
}

template <typename T>
void BlockChain<T>::insert(T data)
{
    auto block = new Block<T>(data);
    block->id = chain.size();
    block->previous_hash = chain.back()->hash;

    if (block->mine())
        chain.push_back(block);
    else
        throw runtime_error("Block not mined");
}

template <typename T>
void BlockChain<T>::display(ostream& os)
{
    auto iterator = chain.begin();
    while(iterator != chain.end()){
        os << **iterator << "\n";
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