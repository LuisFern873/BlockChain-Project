# ifndef MENU_H
# define MENU_H

# include <iostream>
# include "blockchain.h"

using namespace std;

class Menu
{
    private:
        inline static Menu* menu = nullptr;
        inline static BlockChain<Transfer>* chain;

        Menu() = default;
        struct Capybara
        {
            static void display();
        };

    public:
        static Menu* init(BlockChain<Transfer>* chain);
        void display_main();

    private:
        void display_create();
        void display_query();
};

Menu* Menu::init(BlockChain<Transfer>* cha)
{
    if (menu == nullptr) {
        menu = new Menu();
        chain = cha;
    }
    return menu;
}

void Menu::display_main()
{
    cout << "-----------------------------------------\n";
    cout << "********** Welcome to CapyCoin **********\n";
    cout << "-----------------------------------------\n";
    Capybara::display();
    cout << "1) Create transaction 💰\n";
    cout << "2) Query data 📊\n";
    cout << "3) Sign out ❌\n";
    cout << "Enter option: ";
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
    cout << "1) Make transfer 🟢\n";
    cout << "2) Deposit 🟡\n";
    cout << "3) Withdrawal 🟣\n";
    cout << "4) Go back to main menu ⬅️\n";
    cout << "Enter option: ";
    short option;
    cin >> option;
    switch (option)
    {
    case 1:
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
    cout << "Enter option: ";
    short option;
    cin >> option;

    switch (option)
    {
    case 7:
        chain->display();
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


