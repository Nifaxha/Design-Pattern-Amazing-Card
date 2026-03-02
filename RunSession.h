#ifndef RUNSESSION_H
#define RUNSESSION_H

#include <iostream>
#include <vector>
#include "Card.h"
#include "ScoringSystem.h"
#include "modifiers/IModifier.h"
#include "ShopSystem.h"

class RunSession {
private:
    int totalScore;
    int targetScore;
    int handsRemaining;
    int discardsRemaining;
    int roundNumber;
    std::vector<Card> currentHand;
    std::vector<IModifier*> activeModifiers;
    ScoringSystem scoringSystem;
    ShopSystem shopSystem;

    void fillHand(); // Fungsi baru untuk mengisi kartu kosong
    void displayHand();

public:
    RunSession();
    ~RunSession();
    void startRun();
    void playHand();
    void enterShop();
};

#endif