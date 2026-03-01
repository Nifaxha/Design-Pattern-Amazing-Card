#ifndef SHOPSYSTEM_H
#define SHOPSYSTEM_H

#include <iostream>
#include "ModifierFactory.h"

class ShopSystem {
public:
    IModifier* visitShop() {
        std::cout << "\n--- AMAZING CARD SHOP ---\n";
        std::cout << "Pilih Enhancer untuk dibeli:\n";
        std::cout << "1. Flat Bonus Enhancer (+30 Score)\n";
        std::cout << "2. Multiplier Enhancer (x2 Score)\n";
        std::cout << "0. Lewati Shop\n";
        std::cout << "Pilihan: ";
        
        int choice;
        std::cin >> choice;
        
        if (choice == 1 || choice == 2) {
            std::cout << ">> Enhancer berhasil dibeli!\n";
            return ModifierFactory::createModifier(choice);
        }
        std::cout << ">> Anda meninggalkan shop.\n";
        return nullptr;
    }
};

#endif