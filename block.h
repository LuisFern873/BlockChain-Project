# ifndef BLOCK_H
# define BLOCK_H

# include <iostream>
# include "sha256.h"

using namespace std;

template <typename T>
class Block
{
    public:
        size_t id;
        size_t nonce;
        T data; // Transaction data
        string hash;
        string previous_hash;
        bool is_valid;

        Block(T data) : data(data), nonce(0){
            update_hash(); 
        }

        void set_nonce(size_t new_nonce){
            nonce = new_nonce;
            update_hash();
        }

        template <typename T1>
        friend ostream& operator<<(ostream& os, const Block<T1>& block);

    private:
        void update_hash();
};

template <typename T>
ostream& operator<<(ostream& os, const Block<T>& block){
    os << "id: " << block.id << "\n";
    os << "Nonce: " << block.nonce << "\n";
    os << "Transaction data:\n" << block.data;
    os << "Hash: " << block.hash << "\n";
    os << "Previous hash: " << block.previous_hash << "\n";
    os << "Valid: " << boolalpha << block.is_valid << "\n";
    return os;
}


template <typename T>
void Block<T>::update_hash()
{
    static Sha256<T,size_t> hasher{};
    hash = hasher(data, nonce);
    is_valid = hash.starts_with("00");
}

# endif // BLOCK_H