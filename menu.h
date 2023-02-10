# ifndef MENU_H
# define MENU_H

# include <iostream>

using namespace std;

class Menu
{
    private:
    inline static Menu* instance = nullptr;

    Menu() = default;

    public:
    inline static Menu* init()
    {
        if(instance == nullptr) 
            instance = new Menu();
        return instance;
    }
    void display()
    {
        short option;
        cout << "********** Welcome to CapyCoin **********\n";
        cout << "1) Create Transaction 💰\n";
        cout << "2) Query data 📊\n";
        cout << "3) Sign out ❌\n";

        cin >> option;
        
        switch (option) 
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            cout << "Thank you for your preference.\n";
            break;
        default:
            cout << "Enter a valid option.\n";
            break;
        }
    }
};

/*
000000000000000000000000000000000000
⠀⠀⢀⣀⠤⠿⢤⢖⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⡔⢩⠂⠀⠒⠗⠈⠀⠉⠢⠄⣀⠠⠤⠄⠒⢖⡒⢒⠂⠤⢄⠀⠀⠀⠀
⠇⠤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠈⠀⠈⠈⡨⢀⠡⡪⠢⡀⠀
⠈⠒⠀⠤⠤⣄⡆⡂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠢⠀⢕⠱⠀
⠀⠀⠀⠀⠀⠈⢳⣐⡐⠐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠁⠇
⠀⠀⠀⠀⠀⠀⠀⠑⢤⢁⠀⠆⠀⠀⠀⠀⠀⢀⢰⠀⠀⠀⡀⢄⡜⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠘⡦⠄⡷⠢⠤⠤⠤⠤⢬⢈⡇⢠⣈⣰⠎⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣃⢸⡇⠀⠀⠀⠀⠀⠈⢪⢀⣺⡅⢈⠆⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠶⡿⠤⠚⠁⠀⠀⠀⢀⣠⡤⢺⣥⠟⢡⠃⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀

*/

# endif // MENU_H


