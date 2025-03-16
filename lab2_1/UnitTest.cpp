#include "UnitTest.hpp"

UnitTests::UnitTests() : passed(0), failed(0) {}

void UnitTests::printTestResult(const std::string& testName, const std::string& initialData,
                                const std::string& expected, const std::string& actual, bool pass) {
    std::cout << "Название теста: " << testName << std::endl;
    std::cout << "Исходные данные: " << initialData << std::endl;
    std::cout << "Ожидаемый результат: " << expected << std::endl;
    std::cout << "Фактический результат: " << actual << std::endl;
    std::cout << (pass ? "Тест пройден" : "Тест провален") << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

std::string UnitTests::fractionToString(const Fraction& f) {
    std::string result;
    result += (f.getSign() == 1) ? "[+]" : "[-]";
    result += " " + std::to_string(f.getNumerator()) + "/" + std::to_string(f.getDenominator());
    return result;
}

void UnitTests::runTests() {
    testAdditionPositive();
    testAdditionNegative();
    testSubtractionPositive();
    testSubtractionNegative();
    testMultiplicationPositive();
    testMultiplicationNegative();
    testDivisionPositive();
    testDivisionNegative();
    testToCommonDenom();
    testCompareEqual();
    testCompareGreater();
    testCompareLess();
    std::cout << "Всего пройдено тестов: " << passed << std::endl;
    std::cout << "Всего провалено тестов: " << failed << std::endl;
}

// Тесты для оператора сложения
void UnitTests::testAdditionPositive() {
    // Arrange: [+] 1/2 + [+] 1/2
    std::string testName = "Addition Positive";
    Fraction f1(1, 2, 1);
    Fraction f2(1, 2, 1);
    std::string initialData = fractionToString(f1) + " + " + fractionToString(f2);
    Fraction expected(1, 1, 1); // [+] 1/1
    // Act
    Fraction result = f1 + f2;
    // Assert
    bool pass = (result.getNumerator() == expected.getNumerator() &&
                 result.getDenominator() == expected.getDenominator() &&
                 result.getSign() == expected.getSign());
    printTestResult(testName, initialData, fractionToString(expected), fractionToString(result), pass);
    (pass ? passed++ : failed++);
}

void UnitTests::testAdditionNegative() {
    // Arrange: [-] 1/3 + [-] 2/3 = [-] 1/1
    std::string testName = "Addition Negative";
    Fraction f1(1, 3, -1);
    Fraction f2(2, 3, -1);
    std::string initialData = fractionToString(f1) + " + " + fractionToString(f2);
    Fraction expected(1, 1, -1); // [-] 1/1
    // Act
    Fraction result = f1 + f2;
    // Assert
    bool pass = (result.getNumerator() == expected.getNumerator() &&
                 result.getDenominator() == expected.getDenominator() &&
                 result.getSign() == expected.getSign());
    printTestResult(testName, initialData, fractionToString(expected), fractionToString(result), pass);
    (pass ? passed++ : failed++);
}

// Тесты для оператора вычитания
void UnitTests::testSubtractionPositive() {
    // Arrange: [+] 3/4 - [+] 1/4 = [+] 1/2
    std::string testName = "Subtraction Positive";
    Fraction f1(3, 4, 1);
    Fraction f2(1, 4, 1);
    std::string initialData = fractionToString(f1) + " - " + fractionToString(f2);
    Fraction expected(1, 2, 1); // [+] 1/2
    // Act
    Fraction result = f1 - f2;
    // Assert
    bool pass = (result.getNumerator() == expected.getNumerator() &&
                 result.getDenominator() == expected.getDenominator() &&
                 result.getSign() == expected.getSign());
    printTestResult(testName, initialData, fractionToString(expected), fractionToString(result), pass);
    (pass ? passed++ : failed++);
}

void UnitTests::testSubtractionNegative() {
    // Arrange: [+] 1/2 - [+] 3/2 = [-] 1/1
    std::string testName = "Subtraction Negative";
    Fraction f1(1, 2, 1);
    Fraction f2(3, 2, 1);
    std::string initialData = fractionToString(f1) + " - " + fractionToString(f2);
    Fraction expected(1, 1, -1); // [-] 1/1
    // Act
    Fraction result = f1 - f2;
    // Assert
    bool pass = (result.getNumerator() == expected.getNumerator() &&
                 result.getDenominator() == expected.getDenominator() &&
                 result.getSign() == expected.getSign());
    printTestResult(testName, initialData, fractionToString(expected), fractionToString(result), pass);
    (pass ? passed++ : failed++);
}

// Тесты для оператора умножения
void UnitTests::testMultiplicationPositive() {
    // Arrange: [+] 2/3 * [+] 3/4 = [+] 1/2
    std::string testName = "Multiplication Positive";
    Fraction f1(2, 3, 1);
    Fraction f2(3, 4, 1);
    std::string initialData = fractionToString(f1) + " * " + fractionToString(f2);
    Fraction expected(1, 2, 1); // [+] 1/2
    // Act
    Fraction result = f1 * f2;
    // Assert
    bool pass = (result.getNumerator() == expected.getNumerator() &&
                 result.getDenominator() == expected.getDenominator() &&
                 result.getSign() == expected.getSign());
    printTestResult(testName, initialData, fractionToString(expected), fractionToString(result), pass);
    (pass ? passed++ : failed++);
}

void UnitTests::testMultiplicationNegative() {
    // Arrange: [-] 2/3 * [+] 3/4 = [-] 1/2
    std::string testName = "Multiplication Negative";
    Fraction f1(2, 3, -1);
    Fraction f2(3, 4, 1);
    std::string initialData = fractionToString(f1) + " * " + fractionToString(f2);
    Fraction expected(1, 2, -1); // [-] 1/2
    // Act
    Fraction result = f1 * f2;
    // Assert
    bool pass = (result.getNumerator() == expected.getNumerator() &&
                 result.getDenominator() == expected.getDenominator() &&
                 result.getSign() == expected.getSign());
    printTestResult(testName, initialData, fractionToString(expected), fractionToString(result), pass);
    (pass ? passed++ : failed++);
}

// Тесты для оператора деления
void UnitTests::testDivisionPositive() {
    // Arrange: [+] 3/4 / [+] 1/2 = [+] 3/2
    std::string testName = "Division Positive";
    Fraction f1(3, 4, 1);
    Fraction f2(1, 2, 1);
    std::string initialData = fractionToString(f1) + " / " + fractionToString(f2);
    Fraction expected(3, 2, 1); // [+] 3/2
    // Act
    Fraction result = f1 / f2;
    // Assert
    bool pass = (result.getNumerator() == expected.getNumerator() &&
                 result.getDenominator() == expected.getDenominator() &&
                 result.getSign() == expected.getSign());
    printTestResult(testName, initialData, fractionToString(expected), fractionToString(result), pass);
    (pass ? passed++ : failed++);
}

void UnitTests::testDivisionNegative() {
    // Arrange: [-] 3/4 / [+] 1/2 = [-] 3/2
    std::string testName = "Division Negative";
    Fraction f1(3, 4, -1);
    Fraction f2(1, 2, 1);
    std::string initialData = fractionToString(f1) + " / " + fractionToString(f2);
    Fraction expected(3, 2, -1); // [-] 3/2
    // Act
    Fraction result = f1 / f2;
    // Assert
    bool pass = (result.getNumerator() == expected.getNumerator() &&
                 result.getDenominator() == expected.getDenominator() &&
                 result.getSign() == expected.getSign());
    printTestResult(testName, initialData, fractionToString(expected), fractionToString(result), pass);
    (pass ? passed++ : failed++);
}

// Тест для приведения дробей к общему знаменателю
void UnitTests::testToCommonDenom() {
    // Arrange: [+] 1/2 и [+] 1/3 должны стать [+] 3/6 и [+] 2/6 соответственно
    std::string testName = "To Common Denom";
    Fraction f1(1, 2, 1);
    Fraction f2(1, 3, 1);
    std::string initialData = fractionToString(f1) + " и " + fractionToString(f2);
    // Act
    f1.toCommonDenominator(f2);
    // Assert
    bool pass = (f1.getNumerator() == 3 && f1.getDenominator() == 6 &&
                 f2.getNumerator() == 2 && f2.getDenominator() == 6);
    std::string expectedStr = "[+] 3/6 и [+] 2/6";
    std::string resultStr = fractionToString(f1) + " и " + fractionToString(f2);
    printTestResult(testName, initialData, expectedStr, resultStr, pass);
    (pass ? passed++ : failed++);
}

// Тесты для метода compare
void UnitTests::testCompareEqual() {
    // Arrange: [+] 1/2 compare [+] 2/4 → равны (0)
    std::string testName = "Compare Equal";
    Fraction f1(1, 2, 1);
    Fraction f2(2, 4, 1);
    std::string initialData = fractionToString(f1) + " compare " + fractionToString(f2);
    short expected = 0;
    // Act
    short result = f1.compare(f2);
    // Assert
    bool pass = (result == expected);
    printTestResult(testName, initialData, "0", std::to_string(result), pass);
    (pass ? passed++ : failed++);
}

void UnitTests::testCompareGreater() {
    // Arrange: [+] 3/4 compare [+] 1/2 → первая больше (1)
    std::string testName = "Compare Greater";
    Fraction f1(3, 4, 1);
    Fraction f2(1, 2, 1);
    std::string initialData = fractionToString(f1) + " compare " + fractionToString(f2);
    short expected = 1;
    // Act
    short result = f1.compare(f2);
    // Assert
    bool pass = (result == expected);
    printTestResult(testName, initialData, "1", std::to_string(result), pass);
    (pass ? passed++ : failed++);
}

void UnitTests::testCompareLess() {
    // Arrange: [+] 1/2 compare [+] 3/4 → первая меньше (-1)
    std::string testName = "Compare Less";
    Fraction f1(1, 2, 1);
    Fraction f2(3, 4, 1);
    std::string initialData = fractionToString(f1) + " compare " + fractionToString(f2);
    short expected = -1;
    // Act
    short result = f1.compare(f2);
    // Assert
    bool pass = (result == expected);
    printTestResult(testName, initialData, "-1", std::to_string(result), pass);
    (pass ? passed++ : failed++);
}