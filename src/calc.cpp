#include "calc.h"
#include <cmath>

std::vector<CalcResult> MainCalcSafe(int a, int b, int c) {
    std::vector<CalcResult> results;
    results.reserve(41);
    
    double x = -10.0;
    for (int i = 0; i <= 40; ++i, x += 0.5) {
        double y = 0.0;
        if (x < 0) {
            y = (std::abs(x * x - 1) > 1e-9) ? (a / (x * x - 1)) : 0.0;
        } else if (x > 0 && x < 1) {
            y = (1.0 / x) + b;
        } else if (x > 1) {
            y = (c * x) / (x * x + 1);
        }
        results.push_back({x, y});
    }
    return results;
}