#include "RunSession.h"
#include <sstream>
using namespace std;

RunSession::RunSession() {
    totalScore = 0;
    targetScore = 300;
    handsRemaining = 4;
    roundNumber = 1;
}

RunSession::~RunSession() {
    for (auto mod : activeModifiers) {
        delete mod;
    }
}

void RunSession::generateHand() {
    currentHand = {
        {"4", 4}, {"4", 4}, {"5", 5}, {"9", 9}, {"J", 10}, {"Q", 10}, {"2", 2}
    };
}

void RunSession::displayHand() {
    cout << "\nKartu di tangan anda:\n";
    for (const auto& c : currentHand) cout << c.display << "   "; 
    cout << "\n";
    for (size_t i = 1; i <= currentHand.size(); ++i) cout << "(" << i << ") ";
    cout << "\n";
}

void RunSession::playHand() {
    generateHand();
    while (handsRemaining > 0 && totalScore < targetScore) {
        cout << "\n==============================\n";
        cout << " Round: " << roundNumber << " | Target: " << targetScore << "\n";
        cout << " Current Score: " << totalScore << " | Hands: " << handsRemaining << "\n";
        cout << "==============================\n";

        displayHand();
        
        cout << "Pilih kartu (masukkan urutan angka, pisahkan spasi, akhiri angka 0): ";
        int choice;
        vector<Card> selectedCards;
        
        while (cin >> choice && choice != 0) {
            if (choice > 0 && choice <= currentHand.size()) {
                selectedCards.push_back(currentHand[choice - 1]);
            }
        }

        if (selectedCards.empty()) {
            cout << "Kamu harus memilih kartu!\n";
            continue;
        }

        // 1. Hitung skor dasar menggunakan Strategy Pattern
        string handName;
        int handScore = scoringSystem.evaluateHand(selectedCards, handName);
        cout << "\n>> Kombinasi: " << handName << " | Base Score: " << handScore << "\n";

        // 2. Terapkan Modifiers (Decorator-like Chain)
        for (auto mod : activeModifiers) {
            handScore = mod->applyModification(handScore);
            cout << ">> " << mod->getName() << " diterapkan! Skor menjadi: " << handScore << "\n";
        }

        totalScore += handScore;
        handsRemaining--;
    }
}

void RunSession::enterShop() {
    IModifier* newMod = shopSystem.visitShop();
    if (newMod != nullptr) {
        activeModifiers.push_back(newMod);
    }
}

void RunSession::startRun() {
    cout << "Selamat Datang di AMAZING CARD!\n";
    for (int i = 0; i < 3; i++) { // Minimal 3 rounds (seperti di dokumen pretest)
        totalScore = 0;
        handsRemaining = 4;
        
        playHand();
        
        if (totalScore >= targetScore) {
            cout << "\n*** KAMU MEMENANGKAN ROUND " << roundNumber << "! ***\n";
            enterShop();
            roundNumber++;
            targetScore += 400; // Tingkatkan kesulitan
        } else {
            cout << "\n*** GAME OVER! Target tidak tercapai. ***\n";
            return;
        }
    }
    cout << "\n*** SELAMAT! KAMU MEMENANGKAN GAME INI! ***\n";
}