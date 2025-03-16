#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;
    short sign; // 1 для положительного, -1 для отрицательного

    // Вспомогательная функция для нахождения НОД
    static int gcd(int a, int b);
    // Приведение дроби к несократимому виду
    void simplify();

public:
    // Конструктор с параметрами: числитель, знаменатель, знак
    Fraction(int num, int denom, short sgn);

    // Геттеры
    int getNumerator() const;
    int getDenominator() const;
    short getSign() const;

    // Сеттеры
    void setNumerator(int num);
    void setDenominator(int denom);
    void setSign(short sgn);

    // Метод для вывода дроби в консоль
    void print() const;

    // Перегрузка арифметических операторов
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    // Приведение двух дробей к общему знаменателю
    void toCommonDenominator(Fraction& other);

    // Сравнение дробей: возвращает 0 (равны), 1 (первая больше) или -1 (первая меньше)
    short compare(const Fraction& other) const;
};

#endif // FRACTION_H
