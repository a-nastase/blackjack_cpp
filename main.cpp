#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

int coins = 500;

int bal() {
    return coins;
}

vector<int> d;
vector<int> p;


int sumCards(char o) {
    int sum = 0;
    if(o == 0) {
        int rez = 0;
        for(int i = 0; i < d.size(); i++) {
            if(d[i] == 11) {
                rez+=1;
            } else {
                sum+=d[i];
            }
        }
        while(rez) {
            if(11+sum>21) {
                sum+=1;
            } else {
                sum+=11;
            }
            rez--;
        }
    } else {
        int rez = 0;
        for(int i = 0; i < p.size(); i++) {
            if(p[i] == 11) {
                rez+=1;
            } else {
                sum+=p[i];
            }
        }
        while(rez) {
            if(11+sum>21) {
                sum+=1;
            } else {
                sum+=11;
            }
            rez--;
        }
    }
    return sum;
}

void dispCards() {
    cout << "Your cards: ";
    for(int x : p) {
        cout << x << " ";
    }
    cout << "- sum: " << sumCards(1);
    cout << "\nDealer cards: ";
    for(int x : d) {
        cout << x << " ";
    }
    cout << "- sum: " << sumCards(0);
    cout << "\n";
}

vector<int> c;

int main() {
    for(int i = 2; i < 10; i++) {
        c.push_back(i);
        c.push_back(i);
        c.push_back(i);
        c.push_back(i);
    }
    for(int i = 0; i < 4; i++) {
        c.push_back(10);
        c.push_back(10);
        c.push_back(10);
        c.push_back(10);
        c.push_back(11);
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(c.begin(), c.end(), g);
    int it = 0;
    char x;
    cout << "Hello! These are the commands: p to play, b to check balance and q to quit\n";
    cin >> x;
    while(x!='q') {
        switch (x) {
            case 'b': cout << bal() << "\n"; break;
            case 'p':
                p.clear(); d.clear();
                p.push_back(c[it]); it++; d.push_back(c[it]); it++;
                p.push_back(c[it]); it++; d.push_back(c[it]); it++;
                dispCards();

                cout << "Hit with h and stand with s\n";

                cin >> x;
                if(x == 'h') {
                    while(x == 'h' && sumCards(1) < 21) {
                        p.push_back(c[it++]);
                        dispCards();
                        if(sumCards(1) >= 21) {
                            break;
                        }
                        cin >> x;
                    }
                }

                if(sumCards(1) > 21) {
                    cout << "You lost\n"; coins-=10; break;
                }

                while(sumCards(0) <= 21) {
                    if(sumCards(0) < 15) {
                        d.push_back(c[it]); it++;
                    } else {
                        break;
                    }
                }
                dispCards();

                int q = sumCards(0), w = sumCards(1);
                if(q > 21) {
                    cout << "You won\n";
                    coins+=10;
                } else if(w > q) {
                    cout << "You won\n";
                    coins+=10;
                } else if(w < q) {
                    cout << "Dealer won\n";
                    coins-=10;
                } else {
                    cout << "Equality\n";
                }
                break;
        }
        cin >> x;
    }
}
