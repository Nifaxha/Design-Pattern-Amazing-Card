#include "RunSession.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

RunSession::RunSession() {
    totalScore = 0;
    targetScore = 300;
    handsRemaining = 4;
    discardsRemaining = 3;
    roundNumber = 1;
    std::srand(static_cast<unsigned int>(std::time(0))); 
}

RunSession::~RunSession() {
    for (auto mod : activeModifiers) delete mod;
}

// Fungsi ini hanya mengisi slot kosong di tangan sampai jumlahnya 7
void RunSession::fillHand() {
    std::vector<std::string> suits = {"Heart", "Spade", "Club", "Diamond"};
    std::vector<Card> deckPool;
    
    // Bikin referensi deck
    for (const auto& suit : suits) {
        for (int i = 2; i <= 10; i++) deckPool.push_back({std::to_string(i), i, suit});
        deckPool.push_back({"J", 10, suit});
        deckPool.push_back({"Q", 10, suit});
        deckPool.push_back({"K", 10, suit});
        deckPool.push_back({"A", 11, suit});
    }

    // Isi kartu sampai penuh (7 kartu)
    while (currentHand.size() < 7) {
        int randomIndex = std::rand() % deckPool.size();
        currentHand.push_back(deckPool[randomIndex]);
    }
}

void RunSession::displayHand() {
    std::cout << "\nKartu di tangan anda:\n";
    // Tampilkan format: Nilai-Suit (Contoh: 10-Heart)
    for (const auto& c : currentHand) std::cout << c.display << "-" << c.suit[0] << "   "; 
    std::cout << "\n";
    for (size_t i = 1; i <= currentHand.size(); ++i) std::cout << " (" << i << ")   ";
    std::cout << "\n";
}

void RunSession::playHand() {
    currentHand.clear();
    fillHand(); 
    
    while (handsRemaining > 0 && totalScore < targetScore) {
        std::cout << "\n==================================================\n";
        std::cout << " Round: " << roundNumber << " | Target Score: " << targetScore << "\n";
        std::cout << " Current: " << totalScore << " | Hands: " << handsRemaining << " | Discards: " << discardsRemaining << "\n";
        std::cout << "==================================================\n";

        displayHand();
        
        std::cout << "\nPilih kartu (masukkan urutan angka, pisahkan spasi, akhiri angka 0): ";
        int choice;
        std::vector<int> selectedIndices;
        std::vector<Card> selectedCards;
        
        while (std::cin >> choice && choice != 0) {
            // Pastikan input valid dan tidak ada duplikat index
            if (choice > 0 && choice <= currentHand.size()) {
                if (std::find(selectedIndices.begin(), selectedIndices.end(), choice) == selectedIndices.end()) {
                    selectedIndices.push_back(choice);
                    selectedCards.push_back(currentHand[choice - 1]);
                }
            }
        }

        if (selectedCards.empty()) {
            std::cout << "Kamu belum memilih kartu apa pun!\n";
            continue;
        }

        std::cout << "\nApakah kamu ingin:\n";
        std::cout << "[1] Mainkan Kartu Ini\n";
        std::cout << "[2] Buang (Discard) Kartu Ini\n";
        std::cout << "Pilih (1/2): ";
        int action;
        std::cin >> action;

        if (action == 2) {
            if (discardsRemaining > 0) {
                discardsRemaining--;
                std::cout << "\n>> Membuang " << selectedIndices.size() << " kartu...\n";
            } else {
                std::cout << "\n>> GAGAL: Kesempatan Discard kamu sudah habis!\n";
                continue; 
            }
        } 
        else if (action == 1) {
            std::string handName;
            int handScore = scoringSystem.evaluateHand(selectedCards, handName);
            std::cout << "\n>> KOMBUNASI: " << handName << " | Base Score: " << handScore << "\n";

            for (auto mod : activeModifiers) {
                handScore = mod->applyModification(handScore);
                std::cout << ">> " << mod->getName() << " diterapkan! Skor menjadi: " << handScore << "\n";
            }

            totalScore += handScore;
            handsRemaining--;
        }

        // Hapus kartu yang dipilih dari tangan (harus dihapus dari index terbesar dulu agar urutan tidak bergeser)
        std::sort(selectedIndices.rbegin(), selectedIndices.rend());
        for (int idx : selectedIndices) {
            currentHand.erase(currentHand.begin() + idx - 1);
        }

        // Isi kembali kartu yang kosong
        fillHand();
    }
}

void RunSession::enterShop() {
    IModifier* newMod = shopSystem.visitShop();
    if (newMod != nullptr) activeModifiers.push_back(newMod);
}

void RunSession::startRun() {
    std::cout << "Selamat Datang di AMAZING CARD!\n";
    for (int i = 0; i < 3; i++) { 
        totalScore = 0;
        handsRemaining = 4;
        discardsRemaining = 3; // Reset discard setiap ronde
        
        playHand();
        
        if (totalScore >= targetScore) {
            std::cout << "\n*** KAMU MEMENANGKAN ROUND " << roundNumber << "! ***\n";
            enterShop();
            roundNumber++;
            targetScore += 400; 
        } else {
            std::cout << "\n*** GAME OVER! Target tidak tercapai. ***\n";
            return;
        }
    }
    std::cout << "\n*** SELAMAT! KAMU MEMENANGKAN GAME INI! ***\n";
}