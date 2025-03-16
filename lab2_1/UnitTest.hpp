#ifndef UNITTESTS_H
#define UNITTESTS_H

#include <iostream>
#include <string>
#include "Fraction.hpp"

class UnitTests {
private:
    int passed;
    int failed;
    // Вывод результата одного теста
    void printTestResult(const std::string& testName, const std::string& initialData,
                         const std::string& expected, const std::string& actual, bool pass);
    // Преобразование дроби в строку формата "[+/-] numerator/denom"
    std::string fractionToString(const Fraction& f);
public:
    UnitTests();
    void runTests();

    // Объявление тестовых функций (по принципу arrange -> act -> assert)
    void testAdditionPositive();
    void testAdditionNegative();
    void testSubtractionPositive();
    void testSubtractionNegative();
    void testMultiplicationPositive();
    void testMultiplicationNegative();
    void testDivisionPositive();
    void testDivisionNegative();
    void testToCommonDenom();
    void testCompareEqual();
    void testCompareGreater();
    void testCompareLess();
};

#endif // UNITTESTS_H
