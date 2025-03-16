#include "Fraction.hpp"

// Функция для нахождения НОД двух чисел
int Fraction::gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return std::abs(a);
}

// Приведение дроби к несократимому виду
void Fraction::simplify() {
    int d = gcd(numerator, denominator);
    if (d != 0) {
        numerator /= d;
        denominator /= d;
    }
}

Fraction::Fraction(int num, int denom, short sgn) {
    if (denom <= 0) {
        throw std::invalid_argument("Знаменатель должен быть положительным");
    }
    numerator = std::abs(num);
    denominator = std::abs(denom);
    sign = sgn;
    simplify();
}

int Fraction::getNumerator() const {
    return numerator;
}

int Fraction::getDenominator() const {
    return denominator;
}

short Fraction::getSign() const {
    return sign;
}

void Fraction::setNumerator(int num) {
    numerator = std::abs(num);
    simplify();
}

void Fraction::setDenominator(int denom) {
    if (denom <= 0) {
        throw std::invalid_argument("Знаменатель должен быть положительным");
    }
    denominator = std::abs(denom);
    simplify();
}

void Fraction::setSign(short sgn) {
    sign = sgn;
}

void Fraction::print() const {
    char signChar = (sign == 1) ? '+' : '-';
    std::cout << "[" << signChar << "] " << numerator << " / " << denominator;
}

Fraction Fraction::operator+(const Fraction& other) const {
    int newNumerator = sign * numerator * other.denominator + other.sign * other.numerator * denominator;
    int newDenom = denominator * other.denominator;
    short newSign = (newNumerator >= 0) ? 1 : -1;
    return Fraction(std::abs(newNumerator), newDenom, newSign);
}

Fraction Fraction::operator-(const Fraction& other) const {
    int newNumerator = sign * numerator * other.denominator - other.sign * other.numerator * denominator;
    int newDenom = denominator * other.denominator;
    short newSign = (newNumerator >= 0) ? 1 : -1;
    return Fraction(std::abs(newNumerator), newDenom, newSign);
}

Fraction Fraction::operator*(const Fraction& other) const {
    int newNumerator = sign * numerator * other.sign * other.numerator;
    int newDenom = denominator * other.denominator;
    short newSign = (newNumerator >= 0) ? 1 : -1;
    return Fraction(std::abs(newNumerator), newDenom, newSign);
}

Fraction Fraction::operator/(const Fraction& other) const {
    // Для деления знаменатель второй дроби (числитель другой дроби) не должен быть равен 0
    if (other.numerator == 0) {
        throw std::invalid_argument("Деление на ноль");
    }
    int newNumerator = sign * numerator * other.sign * other.denominator;
    int newDenom = denominator * other.numerator;
    short newSign = (newNumerator >= 0) ? 1 : -1;
    return Fraction(std::abs(newNumerator), newDenom, newSign);
}

void Fraction::toCommonDenominator(Fraction& other) {
    int lcd = denominator * other.denominator / gcd(denominator, other.denominator);
    numerator *= lcd / denominator;
    other.numerator *= lcd / other.denominator;
    denominator = lcd;
    other.denominator = lcd;
}

short Fraction::compare(const Fraction& other) const {
    Fraction result = *this - other;
    return (result.numerator == 0) ? 0 : result.sign;
}
