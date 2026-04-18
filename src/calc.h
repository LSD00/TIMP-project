#ifndef CALC_H
#define CALC_H

#include <vector>

#if defined(_WIN32)
#  if defined(CALC_LIBRARY)
#    define CALC_EXPORT __declspec(dllexport)
#  else
#    define CALC_EXPORT __declspec(dllimport)
#  endif
#else
#  define CALC_EXPORT __attribute__((visibility("default")))
#endif

struct CalcResult {
    double x;
    double y;
};

CALC_EXPORT std::vector<CalcResult> MainCalcSafe(int a, int b, int c);

#endif