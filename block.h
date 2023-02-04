# ifndef BLOCK_H
# define BLOCK_H

# include <iostream>
# include "sha256.h"

using namespace std;

template <typename T>
class Block
{
    public:
    T data;
    size_t nonce;
    string hash;
    bool is_valid;

    Block(T data) : data(data), nonce(0){
        update_hash(); 
    }

    void set_nonce(size_t new_nonce){
        nonce = new_nonce;
        update_hash();
    }

    friend ostream& operator<<(ostream& os, const Block& block){
        os << "Data: " << block.data << "\n";
        os << "Nonce: " << block.nonce << "\n";
        os << "Hash: " << block.hash << "\n";
        os << "Valid: " << boolalpha << block.is_valid << "\n";
        return os;
    }

    private:
    void update_hash(){
        hash = Sha256<T>{}(data, nonce);
        is_valid = hash.starts_with("00");
    }
};

# endif // BLOCK_H