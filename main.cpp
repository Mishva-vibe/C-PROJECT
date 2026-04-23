#include<iostream>
#include<fstream>
#include<string>

using namespace std;
class player{
protected:
string name;
int balance;
int winStreak;
public:
Player(){
        balance = 0;
        winStreak = 0;
    }

    void login() {
        int choice;

        while (true) {
            cout << "1. Login\n2. Register\nChoice: ";
            cin >> choice;

            if (choice == 1) {
                string filePass;
                cout << "Enter username: ";
                cin >> name;

                ifstream file(name + ".txt");

                if (!file) {
                    cout << "User not found\n";
                    continue;
                }

                cout << "Enter password: ";
                cin >> password;

                file >> filePass >> balance >> winStreak;
                file.close();

                if (filePass == password) {
                    cout << "Login successful\n";
                    break;
                } else {
                    cout << "Wrong password\n";
                }

            } else if (choice == 2) {
                cout << "Enter new username: ";
                cin >> name;

                cout << "Set password: ";
                cin >> password;

                cout << "Enter deposit: ";
                cin >> balance;

                winStreak = 0;
                save();

                cout << "Account created\n";
                break;

            } else {
                cout << "Invalid choice\n";
            }
        }
    }

    void save() {
        ofstream file(name + ".txt");
        file << password << " " << balance << " " << winStreak;
        file.close();
    }

    void deposit() {
        int amt;
        cout << "Enter amount: ";
        cin >> amt;

        if (amt > 0) {
            balance += amt;
            cout << "Deposited\n";
        } else {
            cout << "Invalid amount\n";
        }
    }

    void updateBalance(int amt) { balance += amt; }
    void increaseStreak() { winStreak++; }
    void resetStreak() { winStreak = 0; }
};

class Game : public Player {
private:

};
int main(){
    
}
