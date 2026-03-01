#ifndef IMODIFIER_H
#define IMODIFIER_H
#include <string>

class IModifier {
public:
    virtual ~IModifier() = default;
    // Fungsi untuk memodifikasi skor (berantai)
    virtual int applyModification(int currentScore) = 0;
    virtual std::string getName() = 0;
};

// Concrete Modifier A: Tambahan Flat Bonus
class FlatBonusModifier : public IModifier {
private:
    int bonus;
public:
    FlatBonusModifier(int b) : bonus(b) {}
    int applyModification(int currentScore) override {
        return currentScore + bonus;
    }
    std::string getName() override { return "Flat Bonus Enhancer (+" + std::to_string(bonus) + ")"; }
};

// Concrete Modifier B: Pengali (Multiplier)
class MultiplierModifier : public IModifier {
private:
    int multiplier;
public:
    MultiplierModifier(int m) : multiplier(m) {}
    int applyModification(int currentScore) override {
        return currentScore * multiplier;
    }
    std::string getName() override { return "Multiplier Enhancer (x" + std::to_string(multiplier) + ")"; }
};

#endif