#include "RunSession.h"
using namespace std;

RunSession::RunSession() {
    currentScore = 0;
    targetScore = 300; // Target awal ronde 1
    handsRemaining = 4;
    discardsRemaining = 3;
    currentRound = 1;
}

void RunSession::displayStatus() {
    cout << "\n==============================\n";
    cout << "        AMAZING CARD CONSOLE       \n";
    cout << "==============================\n";
    cout << " Round: " << currentRound << "\n";
    cout << " Score: " << currentScore << " / " << targetScore << "\n";
    cout << " Hands: " << handsRemaining << " | Discards: " << discardsRemaining << "\n";
    cout << "==============================\n";
}

void RunSession::addScore(int points) {
    currentScore += points;
    cout << ">> Kamu mendapatkan " << points << " Aset!\n";
}

void RunSession::useHand() {
    if (handsRemaining > 0) handsRemaining--;
}

void RunSession::useDiscard() {
    if (discardsRemaining > 0) discardsRemaining--;
}

bool RunSession::isRoundOver() {
    return (currentScore >= targetScore);
}

bool RunSession::isGameOver() {
    return (handsRemaining <= 0 && currentScore < targetScore);
}
