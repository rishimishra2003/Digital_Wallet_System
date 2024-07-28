#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <ctime>
#include <iomanip>
using namespace std;
// Base class
class Account
{
protected:
    float amt;

public:
    Account();

    virtual void viewWallet(string no) = 0;
    virtual void transactHistory(string no) = 0;
};

Account::Account()
{
    amt = 0.0;
}

class Wallet : public Account
{
protected:
    bool transact(string no, int n);

public:
    Wallet();
    void transfer(string no);
    void recharge(string no);
    void withdraw(string no);
    void viewWallet(string no) override;
    void billPayment(string no);
    void gift(string no);
    void message(string no);
    void transactHistory(string no) override;

    Wallet operator+(const Wallet &other) const
    {
        Wallet result;
        result.amt = this->amt + other.amt;
        return result;
    }

    Wallet operator-(const Wallet &other) const
    {
        Wallet result;
        result.amt = this->amt - other.amt;
        return result;
    }
};

Wallet::Wallet()
{
    amt = 0.0;
}

bool Wallet ::transact(string no, int n)
{
    stringstream ss;
    stringstream ss1;
    fstream f;

    string line;

    ss << no << ".txt";

    f.open(ss.str());

    vector<string> v;
    while (getline(f, line))
    {
        if (line.find("BALANCE : Rs. ") != string::npos)
        {
            string bal;
            float balance;

            bal = line.substr(14, line.length());

            balance = stof(bal);

            if (amt < 0)
            {
                cout << endl
                     << "INVALID ENTRY !!!" << endl;
                return false;
            }

            if (n == 1) // Amount is being added
            {
                Wallet transaction;
                transaction.amt = static_cast<float>(0);
                Wallet result = *this + transaction;
                balance += result.amt;

                ss1 << "T " << no << ".txt";

                ofstream f1;

                f1.open(ss1.str(), ios::app);

                time_t now = time(0);
                char *dateTime = ctime(&now);

                f1 << "Rs.   " << setw(10) << amt << " - " << dateTime << endl;

                f1.close();
            }
            else if (n == 0) // Amount is being withdew
            {
                if (amt <= balance)
                {
                    Wallet transaction;
                    transaction.amt = static_cast<float>(0);
                    Wallet result = *this - transaction;
                    balance = balance - result.amt;

                    ss1 << "T " << no << ".txt";

                    ofstream f1;

                    f1.open(ss1.str(), ios::app);

                    time_t now = time(0);
                    char *dateTime = ctime(&now);

                    f1 << "Rs. - " << setw(10) << amt << " - " << dateTime << endl;

                    f1.close();
                }
                else
                {
                    return false;
                }
            }

            f.close();
            ofstream out(ss.str());

            for (auto e : v)
            {
                out << e << endl;
            }

            out << "BALANCE : Rs. " << balance << endl
                << endl;

            return true;
        }
        else
        {
            v.push_back(line);
        }
    }

    f.close();

    return false;
}

void Wallet ::transfer(string no)
{
    string no1;
    ifstream f;
    string line;

    bool chk;
    int i = 0;

    fflush(stdin);
    cout << "ENTER ACCOUNT NUMBER TO TRANSFER : ";
    getline(cin, no1);

    f.open("USER.txt", ios::in);

    if (!f)
    {
        cout << endl
             << "ACCOUNT NOT FOUND" << endl;
    }
    else
    {
        while (getline(f, line))
        {
            if (line == no1)
            {
                f.close();

                cout << "ENTER AMOUNT TO TRANSFER : Rs. ";
                cin >> amt;

                chk = transact(no, 0);
                if (chk)
                {
                    transact(no1, 1);
                    cout << endl
                         << "TRANSFER SUCCESSFUL" << endl;
                }
                else
                {
                    cout << endl
                         << "INSUFFICIENT BALANCE TO TRANSFER !!!" << endl;
                    cout << "TRANSFER FAILED" << endl;
                }

                i = 1;

                break;
            }
        }
    }

    if (i == 0)
        cout << endl
             << "TRANSFER FAILED" << endl;
}

void Wallet ::recharge(string no)
{
    string no1;
    ifstream f;
    string line;

    bool chk;
    int i = 0;
    cout << "Select operator" << endl;
    cout << "1. Jio" << endl;
    cout << "2. Airtel" << endl;
    cout << "3. BSNL" << endl;
    cout << "4. MTNL" << endl;
    cout << "5. VI" << endl;
    int n;
    cin >> n;
    if (n >= 1 && n <= 5)
        system("cls");
    else
    {
        cout << "invalid choice" << endl;
        return;
    }
    fflush(stdin);
    cout << "ENTER THE NUMBER : ";
    string phnnum;
    fflush(stdin);
    cin >> phnnum;
    if (phnnum.length() != 10)
    {
        cout << "INVALID NUMBER" << endl;
        return;
    }
    cout << endl;
    cout << "ENTER AMOUNT TO RECHARGE : Rs. ";
    cin >> amt;

    chk = transact(no, 0);
    if (chk)
    {
        // transact(no1,1);
        cout << endl
             << "RECHARGE SUCCESSFUL" << endl;
    }
    else
    {
        cout << endl
             << "INSUFFICIENT BALANCE TO RECHARGE !!!" << endl;
        cout << "RECHARGE FAILED" << endl;
    }

    i = 1;

    if (i == 0)
        cout << endl
             << "RECHARGE FAILED" << endl;
}

void Wallet ::withdraw(string no)
{
    bool chk;

    cout << "ENTER AMOUNT TO WITHDRAW : Rs. ";
    cin >> amt;

    chk = transact(no, 0);
    if (chk)
    {
        // transact(no1,1);
        cout << endl
             << "WITHDRAWL SUCCESSFUL" << endl;
    }
    else
    {
        cout << endl
             << "INSUFFICIENT BALANCE FOR WITHDRAWL !!!" << endl;
        cout << "WITHDRAWL FAILED" << endl;
    }
}

void Wallet ::billPayment(string no)
{
    string no1;
    ifstream f;
    string line;

    bool chk;
    int i = 0;

    fflush(stdin);
    cout << "ENTER MERCHANT ACCOUNT NUMBER TO TRANSFER : ";
    getline(cin, no1);

    f.open("MERCHANT.txt", ios::in);

    if (!f)
    {
        cout << endl
             << "INVALID MERCHANT ACCOUNT" << endl;
    }
    else
    {
        while (getline(f, line))
        {
            if (line == no1)
            {
                f.close();

                cout << "ENTER AMOUNT FOR PAYMENT : Rs. ";
                cin >> amt;

                chk = transact(no, 0);
                if (chk)
                {
                    // transact(no1,1);
                    cout << endl
                         << "PAYMENT SUCCESSFUL" << endl;
                }
                else
                {
                    cout << endl
                         << "INSUFFICIENT BALANCE FOR PAYMENT !!!" << endl;
                    cout << "PAYMENT FAILED" << endl;
                }

                i = 1;

                break;
            }
        }
    }

    if (i == 0)
        cout << endl
             << "PAYMENT FAILED" << endl;
}

void Wallet ::gift(string no)
{
    string no1;
    ifstream f;
    string line;
    ofstream f2;

    bool chk;
    int i = 0;

    fflush(stdin);
    cout << "ENTER ACCOUNT NUMBER TO TRANSFER : ";
    getline(cin, no1);

    f.open("USER.txt", ios::in);

    string s;

    if (!f)
    {
        cout << endl
             << "ACCOUNT NOT FOUND" << endl;
    }
    else
    {
        while (getline(f, line))
        {
            if (line == no1)
            {
                f.close();
                f2.open("MESSAGE " + no1 + ".txt", ios::app);
                if (!f2)
                {
                    f2.close();
                    f2.open("MESSAGE " + no1 + ".txt", ios::out);
                }

                cout << "ENTER AMOUNT TO TRANSFER : Rs. ";
                cin >> amt;
                f2 << endl;
                fflush(stdin);
                cout << "WRITE YOUR MESSAGE : ";
                f2 << "MESSAGE:" << endl;
                getline(cin, s);
                f2 << s << endl
                   << endl;
                time_t now = time(0);
                char *dateTime = ctime(&now);
                f2 << dateTime << endl
                   << endl;

                f2.close();

                chk = transact(no, 0);
                if (chk)
                {
                    transact(no1, 1);
                    cout << endl
                         << "MESSAGE SENT!!" << endl;
                    cout << endl
                         << "TRANSFER SUCCESSFUL" << endl;
                }
                else
                {
                    cout << endl
                         << "INSUFFICIENT BALANCE TO TRANSFER !!!" << endl;
                    cout << "TRANSFER & MESSAGE SENT FAILED" << endl;
                }

                i = 1;

                break;
            }
        }
    }

    if (i == 0)
        cout << endl
             << "TRANSFER & MESSAGE SENT FAILED" << endl;
}

void Wallet ::viewWallet(string no)
{
    stringstream ss;
    ifstream f;

    string line;

    ss << no << ".txt";

    f.open(ss.str());

    while (getline(f, line))
    {
        if (line.find("BALANCE : Rs. ") != string::npos)
        {
            cout << "AVAILABLE " << line << endl;

            break;
        }
    }

    f.close();
}

void Wallet ::message(string no)
{
    stringstream ss;
    ifstream f;

    string line;

    ss << "MESSAGE " << no << ".txt";

    f.open(ss.str());
    // cout<<endl;
    while (getline(f, line))
    {
        cout << line << endl;
    }
    cout << endl;

    f.close();
}

void Wallet ::transactHistory(string no)
{
    stringstream ss;
    ifstream f;

    string line;

    ss << "T " << no << ".txt";

    f.open(ss.str());

    while (getline(f, line))
    {
        cout << line << endl;
    }

    f.close();
}

//******************************************************************

class User : public Wallet
{

public:
    //  Wallet w;

    string name;
    string mobile;
    float balance;
    int pin;

    User();
    void signup();
    bool check();
    static bool login(string no);
    void display(string no);

protected:
private:
};

User::User()
{
    name = "";
    mobile = "";
    balance = 0.0;
    pin = 0;
}

void User ::signup()
{
    bool chk;

    stringstream ss;

    fflush(stdin);
    cout << "ENTER YOUR NAME          : ";
    getline(cin, name);
    fflush(stdin);
    cout << "ENTER YOUR MOBILE NUMBER : ";
    getline(cin, mobile);
    cout << "ENTER INITIAL BALANCE    : Rs. ";
    cin >> balance;
    cout << "ENTER A 4 DIGIT PIN      : ";
    cin >> pin;

    chk = check();

    if (chk)
    {
        ofstream f;

        ss << mobile << ".txt";

        f.open(ss.str(), ios::out);

        f << pin << endl;
        f << "NAME    : " << name << endl;
        f << "MOBILE  : " << mobile << endl;
        f << "BALANCE : Rs. " << balance << endl
          << endl;

        f.close();

        stringstream ss1;
        ss1 << "T " << mobile << ".txt";

        ofstream f1;

        f1.open(ss1.str(), ios::app);

        time_t now = time(0);
        char *dateTime = ctime(&now);

        f1 << "Rs.   " << setw(10) << balance << " - " << dateTime << endl;

        f1.close();

        cout << endl
             << "ACCOUNT CREATED SUCCESSFULLY" << endl;
        cout << "NOTE : ACCOUNT NUMBER IS SAME AS MOBILE NUMBER" << endl;
    }
    else
    {
        cout << endl
             << "ACCOUNT NOT CREATED" << endl;
        cout << "INVALID ENTRY FOUND OR ACCOUNT ALREADY EXISTS !!!" << endl;
    }
}

bool User ::check()
{
    string line;
    fstream f;

    f.open("USER.txt", ios::in);

    if (mobile.length() != 10)
        return false;

    if (!f)
    {
        f.close();

        f.open("USER.txt", ios::out);
    }
    else
    {
        while (getline(f, line))
        {
            if (line == mobile)
            {
                f.close();
                return false;
            }
        }
    }

    if (balance <= 0)
        return false;

    if (pin < 1000 || pin >= 10000)
        return false;

    f.close();

    f.open("USER.txt", ios::app);
    f << mobile << endl;
    f.close();

    return true;
}

bool User ::login(string no)
{
    string line;
    fstream f;
    stringstream ss;

    int cpin;

    f.open("USER.txt", ios::in);

    if (!f)
    {
        return false;
    }
    else
    {
        while (getline(f, line))
        {
            if (line == no)
            {
                ss << no << ".txt";
                f.close();

                f.open(ss.str(), ios::in);

                getline(f, line);

                cout << "ENTER YOUR PIN            : ";
                cin >> cpin;

                if (cpin == stoi(line))
                {
                    f.close();
                    return true;
                }
            }
        }
    }

    f.close();

    return false;
}

void User ::display(string no)
{
    int choice;
    bool chk;

    while (1)
    {
        system("cls");
        cout << "1.  DEPOSIT " << endl;
        cout << "2.  TRANSFER " << endl;
        cout << "3.  VIEW WALLET " << endl;
        cout << "4.  TRANSACTION HISTORY " << endl;
        cout << "5.  MOBILE RECHARGE " << endl;
        cout << "6.  WITHDRAW " << endl;
        cout << "7.  BILL PAYMENT " << endl;
        cout << "8.  GIFT " << endl;
        cout << "9.  VIEW MESSAGE " << endl;
        cout << "10. LOGOUT " << endl
             << endl;

        cout << "ENTER YOUR CHOICE : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            cout << "ENTER AMOUNT TO DEPOSIT : Rs. ";
            cin >> amt;
            chk = transact(no, 1);
            if (chk)
                cout << endl
                     << "DEPOSIT SUCCESSFUL" << endl;
            else
                cout << "DEPOSIT FAILED" << endl;
            break;
        }
        case 2:
        {
            system("cls");
            transfer(no);
            break;
        }
        case 3:
        {
            system("cls");
            viewWallet(no);
            break;
        }
        case 4:
        {
            system("cls");
            transactHistory(no);
            break;
        }
        case 5:
        {
            system("cls");
            recharge(no);
            break;
        }
        case 6:
        {
            system("cls");
            withdraw(no);
            break;
        }
        case 7:
        {
            system("cls");
            billPayment(no);
            break;
        }
        case 8:
        {
            system("cls");
            gift(no);
            break;
        }
        case 9:
        {
            system("cls");
            message(no);
            break;
        }
        case 10:
            system("cls");
            cout << "LOGOUT SUCCESSFUL" << endl;
            return;
        default:
            cout << "INVALID CHOICE !!!" << endl;
        }

        cout << endl;
        system("pause");
    }
}

class Menu : public User
{
public:
    int choice;
    void menuProg()
    {
        while (1)
        {
            system("cls");

            cout << "1. SIGN UP" << endl;
            cout << "2. LOGIN" << endl;
            cout << "3. DELETE ACCOUNT" << endl;
            cout << "4. EXIT" << endl
                 << endl;

            cout << "ENTER YOUR CHOICE : ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                system("cls");
                cout << "SIGNUP" << endl
                     << endl;
                // User obj;
                signup();
                break;
            }
            case 2:
            {
                system("cls");
                //  User obj;
                string no;
                bool chk;
                cout << "LOGIN" << endl
                     << endl;
                fflush(stdin);
                cout << "ENTER YOUR ACCOUNT NUMBER : ";
                getline(cin, no);
                chk = login(no);
                if (chk)
                {
                    display(no);
                }
                else
                {
                    cout << endl
                         << "ACCOUNT NOT FOUND OR INVALID PIN!!!" << endl
                         << endl;
                }
                break;
            }

            case 3:
            {
                system("cls");
                // User obj;
                string no;
                bool chk;
                cout << "DELETE ACCOUNT" << endl
                     << endl;
                fflush(stdin);
                cout << "ENTER YOUR ACCOUNT NUMBER : ";
                getline(cin, no);

                chk = login(no);
                if (!chk)
                {
                    cout << "ACCOUNT NOT FOUND!" << endl;
                }
                else
                {
                    string sp = no + ".txt";
                    remove(sp.c_str());
                    sp = "T " + no + ".txt";
                    remove(sp.c_str());
                    sp = "MESSAGE " + no + ".txt";
                    remove(sp.c_str());

                    ifstream f;
                    f.open("USER.txt");
                    int k;
                    vector<string> v;
                    vector<int> vint;
                    int count = 1;
                    while (f >> sp)
                    {
                        if (no != sp)
                        {
                            v.push_back(sp);
                        }
                    }

                    ofstream f2;
                    f2.open("NEWUSER.txt");
                    for (int i = 0; i < v.size(); i++)
                    {
                        f2 << v[i] << endl;
                    }
                    f.close();
                    f2.close();
                    if (remove("USER.txt") == 0)
                        cout << "ACCOUNT DELETE SUCCESSFULL" << endl;
                    rename("NEWUSER.txt", "USER.txt");
                }
                break;
            }

            case 4:
                exit(0);
            default:
                cout << endl
                     << "INVALID CHOICE !!!" << endl;
            }

            cout << endl;
            system("pause");
        }
    }
};

int main()
{
    Menu p1;
    p1.menuProg();
    return 0;
}
