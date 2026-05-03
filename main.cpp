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

int generate(int seed) {
        int sum = 0;

        for (int i = 0; i < name.length(); i++)
            sum += name[i];

        sum = sum + balance + winStreak * 13 + seed * 7;
        sum = (sum * 17 + 23) % 100;

        return sum;
    }

void saveHistory(string game, string result, int bet) {
        ofstream file("history.txt", ios::app);
        file << name << " | " << game << " | Bet: " << bet
             << " | " << result << endl;
        file.close();
    }
};

void numberGame() {
        int bet, guess;

        cout << "\nBalance: " << balance << endl;

        do {
            cout << "Enter bet: ";
            cin >> bet;
        } while (bet <= 0 || bet > balance);

        do {
            cout << "Guess (1-10): ";
            cin >> guess;
        } while (guess < 1 || guess > 10);
        
        int number = (generate(guess) % 10) + 1;

        cout << "Number: " << number << endl;

        if (guess == number) {
            int reward = bet * 5;

            if (winStreak >= 2)
                reward += bet * 2;

            cout << "You WON: " << reward << endl;
            updateBalance(reward);
            increaseStreak();

            saveHistory("NumberGame", "WIN", bet);
        } else {
            cout << "You LOST: " << bet << endl;
            updateBalance(-bet);
            resetStreak();

            saveHistory("NumberGame", "LOSS", bet);
        }

        save();
    }

public:
    void menu() {
        int choice;

        do {
            cout << "\n===== CASINO =====\n";
            cout << "1. Number Game\n";
            cout << "2. Dice Game\n";
            cout << "3. Deposit\n";
            cout << "4. Balance\n";
            cout << "5. Exit\n";

            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
                case 1: numberGame(); break;
                case 2: diceGame(); break;
                case 3: deposit(); break;
                case 4: cout << "Balance: " << balance << endl; break;
                case 5: cout << "Exiting...\n"; break;
                default: cout << "Invalid\n";
            }

        } while (choice != 5);
    }
};

// ================= MAIN =================
int main() {
    Game g;
    g.login();
    g.menu();
    return 0;
}
