#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// --- Функция для Части А ---
// Генерирует последовательность ребер по строке сгибаний
string generate_edges(const string& folds) {
    string edges = "";
    for (char fold : folds) {
        string next_edges = edges;
        
        // Инвертируем и разворачиваем предыдущие ребра
        reverse(next_edges.begin(), next_edges.end());
        for (char& ch : next_edges) {
            ch = (ch == 'К') ? 'О' : 'К';
        }
        
        // Центральное ребро зависит от типа сгибания
        char center = (fold == 'П') ? 'К' : 'О';
        
        edges = edges + center + next_edges;
    }
    return edges;
}

// --- Функция для Части Б ---
// Пытается восстановить сгибания по последовательности ребер
string recover_folds(string edges) {
    string folds = "";
    
    while (!edges.empty()) {
        // Длина строки ребер для n сгибаний всегда равна 2^n - 1 (нечетное число)
        if (edges.length() % 2 == 0) return "НЕ СУЩЕСТВУЕТ";
        
        int mid = edges.length() / 2;
        char center_edge = edges[mid];
        
        // Определяем, какое сгибание дало такое центральное ребро
        char fold = (center_edge == 'К') ? 'П' : 'З';
        folds.push_back(fold);
        
        // Проверяем, корректна ли правая часть относительно левой
        string left = edges.substr(0, mid);
        string right = edges.substr(mid + 1);
        
        // Правая часть должна быть зеркальной инверсией левой
        reverse(right.begin(), right.end());
        for (char& ch : right) {
            ch = (ch == 'К') ? 'О' : 'К';
        }
        
        if (left != right) {
            return "НЕ СУЩЕСТВУЕТ";
        }
        
        // Переходим к предыдущему шагу (левая половина — это ребра до последнего сгиба)
        edges = left;
    }
    
    // Так как мы шли с конца (от полной ленты к начальной), разворачиваем результат
    reverse(folds.begin(), folds.end());
    return folds;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "==================================================" << endl;
    cout << "ЛАБОРАТОРНАЯ РАБОТА: Сгибание бумажной ленты" << endl;
    cout << "==================================================" << endl;

    // --- ЧАСТЬ А ---
    cout << "\n[Часть А]" << endl;
    string folds_A;
    int edge_index;
    
    cout << "Введите последовательность сгибаний (например, ППЗ): ";
    cin >> folds_A;
    cout << "Введите номер ребра (от 1): ";
    cin >> edge_index;

    string generated = generate_edges(folds_A);
    
    cout << "Полная строка ребер: " << generated << endl;
    if (edge_index >= 1 && edge_index <= (int)generated.length()) {
        cout << "Тип ребра под номером " << edge_index << ": " << generated[edge_index - 1] << endl;
    } else {
        cout << "Ошибка: неверный номер ребра!" << endl;
    }

    cout << "--------------------------------------------------" << endl;

    // --- ЧАСТЬ Б ---
    cout << "\n[Часть Б]" << endl;
    string edges_B;
    cout << "Введите последовательность ребер (например, ККОООКО): ";
    cin >> edges_B;

    string recovered = recover_folds(edges_B);
    cout << "Результат восстановления сгибаний: " << recovered << endl;

    // Красивый финал, как ты просила :)
    cout << "\n==================================================" << endl;
    cout << "Работа завершена успешно." << endl;
    cout << "Мамагулашвили Миранда Нодариевна, 090304-РПИа-о25" << endl;
    cout << "Нажмите Enter для выхода..." << endl;
    
    cin.ignore(32767, '\n'); // Очистка буфера
    while(getchar() != '\n');

    return 0;
}