# ifndef CLIENT_H
# define CLIENT_H

# include <iostream>
# include "block.h"

using namespace std;

struct Client
{
    template <typename T>
    static bool mine(Block<T>& block){
        cout << "Mining..." << "\n";
        const size_t MAX = 1'000'000;
        for(size_t nonce = 1; nonce < MAX; ++nonce){
            block.set_nonce(nonce);
            if(block.is_valid){
                return true;
            }
        }
        return false;
    }
};


# endif // CLIENT_H