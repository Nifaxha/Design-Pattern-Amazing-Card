#ifndef RUNSESSION_H
#define RUNSESSION_H

#include <iostream>
#include <vector>
#include <string>

class RunSession {
private:
    int currentScore;
    int targetScore;
    int handsRemaining;
    int discardsRemaining;
    int currentRound;

public:
    RunSession();
    
    // Fungsi utama untuk menjalankan loop permainan
    void startRound();
    bool isRoundOver();
    bool isGameOver();
    
    // Getters & Setters sederhana
    void addScore(int points);
    void useHand();
    void useDiscard();
    
    // Display status ke terminal VS Code
    void displayStatus();
};

#endif