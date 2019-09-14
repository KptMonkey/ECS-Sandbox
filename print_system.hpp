#pragma once

#include "system.hpp"
#include "manager_manager.hpp"
#include "Components/print.hpp"
#include <random>
#include <iostream>

extern ManagerManager manager;

std::string reverse(std::string const &s)
{
    std::string rev(s.rbegin(), s.rend());
    return rev;
}

class PrintSystem : public System {
public:
    void update() {
        static std::random_device dev;
        static std::mt19937 rng(dev());
        static std::uniform_int_distribution<std::mt19937::result_type> dist(1,6);
        for(auto e : mEntities) {
            auto &print = manager.getComponent<Print>(e);
            std::cout << print.output << std::endl;
            if(dist(rng) == 3) {
                auto output = reverse(print.output);
                output.push_back(' ');
                print.output = reverse(output);
                print.output;
            }
        }
    }
};
