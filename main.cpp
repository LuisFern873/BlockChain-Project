# include "client.h"

using namespace std;

int main()
{
    string data = "hello, world!";
    string hash = Sha256<string,int>{}(data,10);
    cout << hash << "\n";
    cout << hash.length() << "\n";

    // Block<string> GenesisBlock(data);

    // cout << "Before mining\n" << GenesisBlock << endl;

    // Client::mine<string>(GenesisBlock);

    // cout << "After mining\n" << GenesisBlock << endl;

    return 0;
}