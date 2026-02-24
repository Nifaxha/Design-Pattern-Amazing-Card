#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Card {
    string display;
    int value;
};

void displayHand(const std::vector<Card>& hand) {
    cout << "\nKartu di tangan anda:\n";
    // Menampilkan visual kartu (angka saja seperti permintaanmu)
    for (const auto& c : hand) cout << c.display << "  "; 
    cout << "\n";
    
    // Menampilkan urutan angka untuk dipilih pemain
    for (int i = 1; i <= hand.size(); ++i) cout << "(" << i << ") ";
    cout << "\n";
}

int main() {
    // Contoh kartu di tangan
    vector<Card> hand = {{"4", 4}, {"4", 4}, {"5", 5}, {"9", 9}, {"J", 10}, {"Q", 10}, {"2", 2}};

    displayHand(hand);

    cout << "\nPilih kartu untuk dimainkan (masukkan nomor urut, pisahkan dengan spasi, akhiri dengan 0): ";
    int choice;
    while (cin >> choice && choice != 0) {
        if (choice > 0 && choice <= hand.size()) {
            cout << "Anda memilih kartu: " << hand[choice - 1].display << "\n";
        }
    }

    return 0;
}