#include <iostream>
#include <algorithm>

using namespace std;

/*
 * Функция для вычисления минимального n такого, что B^n делится на A.
 * Используем разложение числа A на простые множители.
 */
long long solve(long long a, long long b) {
    long long max_n = 1;
    long long temp_a = a;

    // Перебираем потенциальные простые делители числа A
    for (long long i = 2; i * i <= temp_a; ++i) {
        if (temp_a % i == 0) {
            // Считаем степень вхождения i в число A
            long long count_a = 0;
            while (temp_a % i == 0) {
                count_a++;
                temp_a /= i;
            }

            // Считаем степень вхождения i в число B
            long long count_b = 0;
            long long temp_b = b;
            while (temp_b % i == 0) {
                count_b++;
                temp_b /= i;
            }

            // Если простого делителя i нет в B, то решение невозможно
            if (count_b == 0) return -1;

            // Вычисляем локальное n для данного делителя
            // (count_a + count_b - 1) / count_b - деление с округлением вверх
            long long current_n = (count_a + count_b - 1) / count_b;
            max_n = max(max_n, current_n);
        }
    }

    // Если после цикла temp_a > 1, значит осталось последнее простое число
    if (temp_a > 1) {
        long long count_a = 1;
        long long count_b = 0;
        long long temp_b = b;
        
        while (temp_b % temp_a == 0) {
            count_b++;
            temp_b /= temp_a;
        }

        if (count_b == 0) return -1;
        
        long long current_n = (count_a + count_b - 1) / count_b;
        max_n = max(max_n, current_n);
    }

    return max_n;
}

int main() {
    setlocale(LC_ALL, ".UTF-8");

    long long a, b;

    if (!(cin >> a >> b)) return -1;

    cout << solve(a, b) << endl;
    cout << "Мамагулашвили Миранда Нодариевна, 090304-РПИа-о25" << endl;

    getchar();
    while(getchar() != '\n');

    return 0;
}
