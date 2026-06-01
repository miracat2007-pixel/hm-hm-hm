#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Функция генерации последовательности складок
string generate_edges(const string& folds) {
    string edges = "";
    for (char fold : folds) {
        string buf = edges;
        
        // Зеркально переворачиваем и инвертируем старый кусок
        reverse(buf.begin(), buf.end());
        for (char& ch : buf) {
            ch = (ch == 'К') ? 'О' : 'К';
        }
        
        // Центральный сгиб зависит от направления
        char center = (fold == 'П') ? 'К' : 'О';
        
        edges = edges + center + buf;
    }
    return edges;
}

// Функция восстановления истории сгибаний
string recover_folds(string edges) {
    string folds = "";
    
    while (!edges.empty()) {
        // Проверка на корректность длины (всегда 2^n - 1, т.е. нечетное)
        if (edges.length() % 2 == 0) return "НЕ СУЩЕСТВУЕТ";
        
        int mid = edges.length() / 2;
        char mid_ch = edges[mid];
        
        // Определяем тип сгиба по центральному ребру
        char fold = (mid_ch == 'К') ? 'П' : 'З';
        folds.push_back(fold);
        
        string left = edges.substr(0, mid);
        string right = edges.substr(mid + 1);
        
        // Проверяем симметрию половин с инверсией
        reverse(right.begin(), right.end());
        for (char& ch : right) {
            ch = (ch == 'К') ? 'О' : 'К';
        }
        
        if (left != right) {
            return "НЕ СУЩЕСТВУЕТ";
        }
        
        // Отрезаем хвост и идем на следующий шаг
        edges = left;
    }
    
    // Переворачиваем, так как собирали с конца истории
    reverse(folds.begin(), folds.end());
    return folds;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "==================================================" << endl;
    cout << "ЛАБОРАТОРНАЯ РАБОТА: Сгибание бумажной ленты" << endl;
    cout << "==================================================" << endl;

    // Ввод и проверка для прямой задачи
    cout << "\n[Тест генерации]" << endl;
    string folds_A;
    int edge_index;
    
    cout << "Последовательность сгибаний (например, ППЗ): ";
    cin >> folds_A;
    cout << "Номер искомого ребра (с 1): ";
    cin >> edge_index;

    string generated = generate_edges(folds_A);
    
    cout << "Полученная строка ребер: " << generated << endl;
    if (edge_index >= 1 && edge_index <= (int)generated.length()) {
        cout << "Ребро №" << edge_index << " -> " << generated[edge_index - 1] << endl;
    } else {
        cout << "Ошибка: индекс вне диапазона!" << endl;
    }

    cout << "--------------------------------------------------" << endl;

    // Ввод и проверка для обратной задачи
    cout << "\n[Тест восстановления]" << endl;
    string edges_B;
    cout << "Последовательность ребер (например, ККОООКО): ";
    cin >> edges_B;

    string res = recover_folds(edges_B);
    cout << "Восстановленные сгибания: " << res << endl;

    cout << "\n==================================================" << endl;
    cout << "Программа завершила работу." << endl;
    cout << "Мамагулашвили Миранда Нодариевна, 090304-РПИа-о25" << endl;
    cout << "Для выхода нажмите Enter..." << endl;
    
    cin.ignore(32767, '\n'); 
    while(getchar() != '\n');

    return 0;
}
