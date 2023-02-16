# ifndef MENU_H
# define MENU_H

# include <iostream>
# include "blockchain.h"

using namespace std;

class Menu
{
    public:
        static Menu* init(BlockChain<Transfer>& chain);
        void display_main();

    private:
        inline static Menu* menu = nullptr;
        inline static BlockChain<Transfer>* chain;

        Menu() = default;
        struct Capybara {
            static void display();
        };

        void display_create();
        void display_query();

        void display_transfer();
};

Menu* Menu::init(BlockChain<Transfer>& chaim)
{
    if (menu == nullptr) {
        menu = new Menu();
        chain = &chaim;
    }
    return menu;
}

void Menu::display_main()
{
    cout << "-----------------------------------------\n";
    cout << "********** Welcome to CapyCoin **********\n";
    cout << "-----------------------------------------\n";
    Capybara::display();
    cout << "1) Create transaction. 💰\n";
    // cout << "2) Update transaction. 🖊️\n";
    // cout << "3) Remove transaction. 🧶\n";
    cout << "2) Query data. 📊\n";
    cout << "3) Sign out. ❌\n";
    cout << "Enter an option: ";
    short option;
    cin >> option;
    cout << "\n";
    
    switch (option) 
    {
    case 1:
        display_create();
        break;
    case 2:
        display_query();
        break;
    case 3:
        cout << "Thank you for your preference!\n";
        break;
    default:
        cout << "Enter a valid option.\n";
        display_main();
        break;
    }
}

void Menu::display_create()
{
    cout << "----------------------------------------\n";
    cout << "********** Create transaction ********** \n";
    cout << "----------------------------------------\n";
    cout << "1) Make transfer. 🟢\n";
    cout << "2) Deposit. 🟡\n";
    cout << "3) Withdrawal. 🟣\n";
    cout << "4) Go back to main menu. ⬅️\n";
    cout << "Enter an option: ";
    short option;
    cin >> option;
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
    default:
        break;
    }
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
    chain->insert(Transfer(amount, sender, receiver));

    cout << "The transfer was completed successfully. ✅\n";
    cout << "Waiting to complete block...\n";
    cout << *chain->block << "\n";
    cout << "\n";
    display_create();
}

void Menu::display_query()
{
    cout << "--------------------------------\n";
    cout << "********** Query data **********\n";
    cout << "--------------------------------\n";
    cout << "1) Equal to ...\n";
    cout << "2) Range search ...\n";
    cout << "3) Start with ...\n";
    cout << "4) Contains ...\n";
    cout << "5) Max value ...\n";
    cout << "6) Min value ...\n";
    cout << "7) Ledger ...\n";
    cout << "8) Go back to main menu ⬅️\n";
    cout << "Enter an option: ";
    short option;
    cin >> option;

    switch (option)
    {
    case 7:
        chain->display();
        display_query();
        break;
    case 8:
        display_main();
        break;
    default:
        break;
    }
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


