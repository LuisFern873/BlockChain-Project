# ifndef MENU_H
# define MENU_H

# include <iostream>
# include "blockchain.h"
# include "index.h"

using namespace std;

class Menu
{
    public:
        static Menu* init(BlockChain<Transfer>& chain, Index& index);
        void display_main();

    private:
        inline static Menu* menu = nullptr;
        inline static BlockChain<Transfer>* chain;
        inline static Index* index;

        Menu() = default;
        struct Capybara {
            static void display();
        };

        void display_create();
        void display_update();
        void display_delete();
        void display_query();

        void display_transfer();

        // Query menus :)
        void display_equal_to();
        void display_range_search();
        void display_starts_with();
        void display_contains();
        void display_max();
        void display_min();
        void display_ledger();
};

Menu* Menu::init(BlockChain<Transfer>& Chain, Index& Index)
{
    if (menu == nullptr) {
        menu = new Menu();
        chain = &Chain;
        index = &Index;
    }
    return menu;
}

void Menu::display_main()
{
    cout << "---------------------------------------------\n";
    cout << "∗∗∗∗∗∗∗∗∗∗∗∗ Welcome to CapyCoin ∗∗∗∗∗∗∗∗∗∗∗∗\n";
    cout << "---------------------------------------------\n";
    Capybara::display();
    cout << "1) Create transaction. 💰\n";
    cout << "2) Update transaction. 🖊️\n";
    cout << "3) Remove transaction. 🧶\n";
    cout << "4) Query data. 📊\n";
    cout << "5) Sign out. ❌\n";
    
    short option;
    do {
        cout << "Enter an option: ";
        cin >> option;
    } while ( 1 > option or option > 5);

    cout << "\n";

    switch (option) 
    {
    case 1:
        display_create();
        break;
    case 2:
        display_update();
        break;
    case 3:
        display_delete();
        break;
    case 4:
        display_query();
        break;
    case 5:
        cout << "Thank you for your preference!\n";
        break;
    }
}

void Menu::display_create()
{
    cout << "---------------------------------------\n";
    cout << "∗∗∗∗∗∗∗∗∗∗∗ Create transaction ∗∗∗∗∗∗∗∗∗∗∗\n";
    cout << "---------------------------------------\n";
    cout << "1) Make transfer. 🟢\n";
    cout << "2) Deposit. 🟡\n";
    cout << "3) Withdrawal. 🟣\n";
    cout << "4) Go back to main menu. ⬅️\n";

    short option;
    do {
        cout << "Enter an option: ";
        cin >> option;
    } while ( 1 > option or option > 4);

    switch (option)
    {
    case 1:
        display_transfer();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        display_main();
        break;
    }
}

void Menu::display_update()
{
    size_t id_block;
    size_t id_transaction;
    cout << "Id block: ";
    cin >> id_block;
    cout << "Id transaction: ";
    cin >> id_transaction;

    // cout << (*chain)[id_block];

    string sender;
    string receiver;
    double amount;
    cout << "New amount: ";
    cin >> amount;
    cout << "New sender: ";
    cin >> sender;
    cout << "New receiver: ";
    cin >> receiver;
    
    chain->update(Transfer{amount, sender, receiver}, id_block, id_transaction);
    cout << "\n";

    display_main();
}


void Menu::display_delete()
{

}

void Menu::display_transfer()
{
    string sender;
    string receiver;
    double amount;

    cout << "Amount: ";
    cin >> amount;
    cout << "Sender: ";
    cin >> sender;
    cout << "Receiver: ";
    cin >> receiver;

    // Validar datos
    chain->insert(Transfer{amount, sender, receiver});
    DataManager::simulate("assets/10000_transfers.csv", *chain);
    
    
    // cout << *chain->block << "\n";
    cout << "\n";
    display_create();
}

void Menu::display_query()
{
    cout << "--------------------------------\n";
    cout << "∗∗∗∗∗∗∗∗∗∗ Query data ∗∗∗∗∗∗∗∗∗∗\n";
    cout << "--------------------------------\n";
    cout << "1) Equal to [...]\n";
    cout << "2) Range search [...]\n";
    cout << "3) Starts with [...]\n";
    cout << "4) Contains [...]\n";
    cout << "5) Max value [...]\n";
    cout << "6) Min value [...]\n";
    cout << "7) Ledger [...]\n";
    cout << "8) Go back to main menu ⬅️\n";

    short option;
    do {
        cout << "Enter an option: ";
        cin >> option;
    } while ( 1 > option or option > 8);

    switch (option)
    {
    case 1:
        display_equal_to();
        break;
    case 2:
        display_range_search();
        break;
    case 3:
        display_starts_with();
        break;
    case 4:
        display_contains();
        break;
    case 5:
        display_max();
        break;
    case 6:
        display_min();
        break;
    case 7:
        display_ledger();
        break;
    case 8:
        display_main();
        break;
    }
}

void Menu::display_equal_to()
{
    string name;
    Member member;
    short option;

    cout << "1) Sender\n";
    cout << "2) Receiver\n";
    cout << "Member: ";
    cin >> option;
    member = option == 1 ? Member::sender : Member::receiver;

    cout << "Name: ";
    cin >> name;

    cout << index->EqualTo(member, name) << "\n";

    display_query();
}

void Menu::display_range_search()
{
    double start, end;
    cout << "Start: ";
    cin >> start;
    cout << "End: ";
    cin >> end;

    vector<Transfer*> transfers = index->RangeSearch(start, end);

    for (auto& transfer : transfers)
        cout << *transfer << "\n";

    display_query();
}


void Menu::display_starts_with()
{
    string prefix;
    Member member;
    short option;

    cout << "1) Sender\n";
    cout << "2) Receiver\n";
    cout << "Member: ";
    cin >> option;
    member = option == 1 ? Member::sender : Member::receiver;

    cout << "Prefix: ";
    cin >> prefix;

    vector<Transfer*> transfers = index->starts_with(member, prefix);

    for (auto& transfer : transfers)
        cout << *transfer << "\n";

    display_query();
}

void Menu::display_contains()
{
    display_query();
}

void Menu::display_max()
{
    cout << index->MaxValue() << "\n";

    display_query();
}

void Menu::display_min()
{
    cout << index->MinValue() << "\n";

    display_query();
}

void Menu::display_ledger(){
    cout << "\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗ 📖 Ledger 📖 ∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗∗\n";
    cout << "-----------------------------------------------------------------------\n";
    chain->display();
    cout << "\n\n";
    display_query();
}

void Menu::Capybara::display()
{
    cout << "⠀⠀⢀⣀⠤⠿⢤⢖⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
    cout << "⡔⢩⠂⠀⠒⠗⠈⠀⠉⠢⠄⣀⠠⠤⠄⠒⢖⡒⢒⠂⠤⢄⠀⠀⠀⠀\n";
    cout << "⠇⠤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠈⠀⠈⠈⡨⢀⠡⡪⠢⡀⠀\n";
    cout << "⠈⠒⠀⠤⠤⣄⡆⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠢⠀⢕⠱⠀\n";
    cout << "⠀⠀⠀⠀⠀⠈⢳⣐⡐⠐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠁⠇\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠑⢤⢁⠀⠆⠀⠀⠀⠀⠀⢀⢰⠀⠀⠀⡀⢄⡜⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠘⡦⠄⡷⠢⠤⠤⠤⠤⢬⢈⡇⢠⣈⣰⠎⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣃⢸⡇⠀⠀⠀⠀⠀⠈⢪⢀⣺⡅⢈⠆⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠶⡿⠤⠚⠁⠀⠀⠀⢀⣠⡤⢺⣥⠟⢡⠃⠀⠀⠀\n";
    cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀\n";
}



# endif // MENU_H


