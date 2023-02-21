#include <ctime>
#include <iostream>
#include <unistd.h>
# include "chainhash.h"

using namespace std;

string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

int main() {
    // srand((unsigned)time(NULL) * getpid());     
    auto chain = new ChainHash<string, int>();

    for (int i = 0; i < 100; ++i) {
        chain->insert(gen_random(10), 10);
    }
    chain->display();
    

    delete chain;     
    return 0;
}
