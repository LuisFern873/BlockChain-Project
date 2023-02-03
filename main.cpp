# include <iostream>
# include "sha256.h"

using namespace std;

int main()
{
    string message = "Hello, world!";

    cout << Sha256<string>{}(message) << "\n";

    // 315f5bdb76d078c43b8ac0064e4a0164612b1fce77c869345bfc94c75894edd3

    return 0;
}