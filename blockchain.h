# ifndef BLOCK_CHAIN_H
# define BLOCK_CHAIN_H

# include "block.h"
# include "transaction.h"
# include "circularlist.h"

template <typename T>
class BlockChain
{
    public:
    BlockChain();
    void insert(T data);
    void display(ostream& os = cout);

    private:
    CircularList<Block<T>*> chain;
    void create_genesis();

};

template <typename T>
BlockChain<T>::BlockChain()
{

}


template <typename T>
void BlockChain<T>::insert(T data)
{
    auto block = new Block<T>(data);
    block->id = chain.size();
    chain.push_back(block);
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
    
}


# endif // BLOCK_CHAIN_H