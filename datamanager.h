# include "blockchain.h"
# include <fstream>
# include <sstream>
# include "structures/circulararray.h"
 
using namespace std;

struct DataManager
{
    static void load(string filename, BlockChain<Transfer>& chain);
    static void simulate(string filename, BlockChain<Transfer>& chain);
};

void DataManager::load(string filename, BlockChain<Transfer>& chain)
{
    cout << "Loading data...\n";
    string line;
    ifstream file(filename);

    while (getline(file, line))
    {
        istringstream iss(line);

        CircularArray<string, 3> fields;
        string field;

        while (getline(iss, field, ','))
        {
            fields.push_back(field);
        }

        double amount = stod(fields[0]);
        string sender = fields[1];
        string receiver = fields[2];

        chain.insert(Transfer(amount, sender, receiver));
    }

    file.close();
    cout << "Data have been loaded successfully. ✅\n";
}

void DataManager::simulate(string filename, BlockChain<Transfer>& chain)
{
    cout << "Waiting other transfers to mine block...\n";
    string line;
    ifstream file(filename);

    int counter = 0;
    while (getline(file, line) and counter < 4)
    {
        istringstream iss(line);

        CircularArray<string, 3> fields;
        string field;

        while (getline(iss, field, ','))
        {
            fields.push_back(field);
        }

        double amount = stod(fields[0]);
        string sender = fields[1];
        string receiver = fields[2];

        chain.insert(Transfer(amount, sender, receiver));

        ++counter;
    }

    file.close();
    cout << "The transfer was completed successfully. ✅\n";
}
