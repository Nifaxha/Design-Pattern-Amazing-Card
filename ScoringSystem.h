#ifndef SCORINGSYSTEM_H
#define SCORINGSYSTEM_H
using namespace std;

#include <vector>
#include <string>
#include "Card.h"

// Interface Strategy
class IScoringStrategy {
public:
    virtual ~IScoringStrategy() = default;
    virtual int calculateScore(const vector<Card>& cards) = 0;
    virtual string getHandName() = 0;
};

// Concrete Strategy: Pair (Jika ada 2 kartu dengan nilai sama)
class PairStrategy : public IScoringStrategy {
public:
    int calculateScore(const vector<Card>& cards) override {
        if (cards.size() == 2 && cards[0].value == cards[1].value) {
            return (cards[0].value * 2) + 50; // Base score Pair
        }
        return 0;
    }
    string getHandName() override { return "Pair"; }
};

// Concrete Strategy: High Card (Jumlah nilai biasa)
class HighCardStrategy : public IScoringStrategy {
public:
    int calculateScore(const vector<Card>& cards) override {
        int total = 0;
        for (const auto& c : cards) total += c.value;
        return total + 10; // Base score High Card
    }
    string getHandName() override { return "High Card"; }
};

// Context class
class ScoringSystem {
public:
    int evaluateHand(const vector<Card>& cards, string& outHandName) {
        // Cek strategi Pair terlebih dahulu
        PairStrategy pairStrat;
        int score = pairStrat.calculateScore(cards);
        if (score > 0) {
            outHandName = pairStrat.getHandName();
            return score;
        }

        // Default ke High Card
        HighCardStrategy highCardStrat;
        outHandName = highCardStrat.getHandName();
        return highCardStrat.calculateScore(cards);
    }
};

#endif