#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

struct Horse {
    std::string name;
    double odds;
    double support_rate; // 計算された支持率（%）
    double expected_value;
};

double calculateExpectedValue(double odds, double win_prob) {
    return odds * win_prob - (1 - win_prob);
}

void printCombination(const std::vector<Horse>& horses, const std::vector<int>& combination) {
    for (int i : combination) {
        std::cout << horses[i].name << " ";
    }
}

double calculateCombinationEV(const std::vector<Horse>& horses, const std::vector<int>& combination) {
    double ev = 1.0;
    for (int i : combination) {
        ev *= horses[i].expected_value;
    }
    return ev;
}

int main() {
    int num_horses;
    std::cout << "Enter the number of horses: ";
    std::cin >> num_horses;

    std::vector<Horse> horses(num_horses);
    double total_inverse_odds = 0.0;

    // オッズの入力
    for (int i = 0; i < num_horses; i++) {
        std::cout << "Enter horse " << i + 1 << " name: ";
        std::cin >> horses[i].name;
        std::cout << "Enter " << horses[i].name << "'s odds: ";
        std::cin >> horses[i].odds;

        total_inverse_odds += 1.0 / horses[i].odds; // 逆数の合計
    }

    // 支持率・期待値の計算
    for (int i = 0; i < num_horses; i++) {
        horses[i].support_rate = (1.0 / horses[i].odds) / total_inverse_odds * 100.0;
        double win_prob = horses[i].support_rate / 100.0;
        horses[i].expected_value = calculateExpectedValue(horses[i].odds, win_prob);
    }

    // 馬券の種類
    std::cout << "\nBet type (1: Win, 2: Place, 3: Quinella, 4: Exacta, 5: Wide, 6: Trifecta, 7: Tricast): ";
    int bet_type;
    std::cin >> bet_type;

    // 結果表示
    std::cout << "\nExpected Values:\n";
    if (bet_type == 1) { // 単勝
        for (const auto& horse : horses) {
            std::cout << horse.name << " | Odds: " << horse.odds
                      << " | Support Rate: " << horse.support_rate << "%"
                      << " | EV: " << horse.expected_value;
            if (horse.expected_value > 0) {
                std::cout << " (Profitable Bet!)";
            }
            std::cout << std::endl;
        }
    } else if (bet_type == 2) { // 複勝
        for (const auto& horse : horses) {
            std::cout << horse.name << " | Odds: " << horse.odds
                      << " | Support Rate: " << horse.support_rate << "%"
                      << " | EV: " << horse.expected_value;
            if (horse.expected_value > 0) {
                std::cout << " (Profitable Bet!)";
            }
            std::cout << std::endl;
        }
    } else if (bet_type == 3) { // 馬連
        for (int i = 0; i < num_horses; i++) {
            for (int j = i + 1; j < num_horses; j++) {
                std::vector<int> combination = {i, j};
                double ev = calculateCombinationEV(horses, combination);
                std::cout << "Combination: ";
                printCombination(horses, combination);
                std::cout << "| EV: " << ev << std::endl;
            }
        }
    } else if (bet_type == 4) { // 馬単
        for (int i = 0; i < num_horses; i++) {
            for (int j = 0; j < num_horses; j++) {
                if (i != j) {
                    std::vector<int> combination = {i, j};
                    double ev = calculateCombinationEV(horses, combination);
                    std::cout << "Combination: ";
                    printCombination(horses, combination);
                    std::cout << "| EV: " << ev << std::endl;
                }
            }
        }
    } else if (bet_type == 5) { // ワイド
        for (int i = 0; i < num_horses; i++) {
            for (int j = i + 1; j < num_horses; j++) {
                std::vector<int> combination = {i, j};
                double ev = calculateCombinationEV(horses, combination);
                std::cout << "Combination: ";
                printCombination(horses, combination);
                std::cout << "| EV: " << ev << std::endl;
            }
        }
    } else if (bet_type == 6) { // 3連複
        for (int i = 0; i < num_horses; i++) {
            for (int j = i + 1; j < num_horses; j++) {
                for (int k = j + 1; k < num_horses; k++) {
                    std::vector<int> combination = {i, j, k};
                    double ev = calculateCombinationEV(horses, combination);
                    std::cout << "Combination: ";
                    printCombination(horses, combination);
                    std::cout << "| EV: " << ev << std::endl;
                }
            }
        }
    } else if (bet_type == 7) { // 3連単
        for (int i = 0; i < num_horses; i++) {
            for (int j = 0; j < num_horses; j++) {
                for (int k = 0; k < num_horses; k++) {
                    if (i != j && j != k && i != k) {
                        std::vector<int> combination = {i, j, k};
                        double ev = calculateCombinationEV(horses, combination);
                        std::cout << "Combination: ";
                        printCombination(horses, combination);
                        std::cout << "| EV: " << ev << std::endl;
                    }
                }
            }
        }
    }

    return 0;
}