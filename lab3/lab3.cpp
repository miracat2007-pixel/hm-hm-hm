#include <iostream>
#include <stack> // для варианта В
#include <windows.h>
#include <chrono>

using namespace std;
using namespace chrono;

// Вариант А: стек через обычный массив
struct StackArray {
    int data[100]; // тут храним числа
    int topIndex = -1; // -1 значит стек пока пустой

    void push(int value) {
        topIndex++;
        data[topIndex] = value;
    }

    void pop() {
        if (topIndex >= 0) {
            topIndex--;
        }
    }

    int top() {
        return data[topIndex];
    }

    bool isEmpty() {
        return topIndex == -1;
    }
};

// Вариант Б: стек через список на указателях
struct Node {
    int value;
    Node* next;
};

struct StackList {
    Node* head = nullptr; // верхушка стека

    void push(int val) {
        Node* newNode = new Node;
        newNode->value = val;
        newNode->next = head;
        head = newNode;
    }

    void pop() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp; // чтобы память не текла
        }
    }

    int top() {
        return head->value;
    }

    bool isEmpty() {
        return head == nullptr;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n = 6;
    int A[6] = {1, 3, 2, 5, 3, 4};
    int result[6]; // массив для ответов

    cout << "Исходный массив А: ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n\n";

    // Вариант А (Массив) - измерение времени
    auto startA = high_resolution_clock::now();
    StackArray stackA;
    for (int i = n - 1; i >= 0; i--) {
        while (!stackA.isEmpty() && stackA.top() <= A[i]) {
            stackA.pop();
        }
        if (stackA.isEmpty()) {
            result[i] = 0;
        } else {
            result[i] = stackA.top();
        }
        stackA.push(A[i]);
    }
    auto endA = high_resolution_clock::now();
    auto durationA = duration_cast<microseconds>(endA - startA);

    cout << "Вариант А (через массив).    Ответ: ";
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << " | Время: " << durationA.count() << " мкс" << endl;

    // Вариант Б (Список) - измерение времени
    auto startB = high_resolution_clock::now();
    StackList stackB;
    for (int i = n - 1; i >= 0; i--) {
        while (!stackB.isEmpty() && stackB.top() <= A[i]) {
            stackB.pop();
        }
        if (stackB.isEmpty()) {
            result[i] = 0;
        } else {
            result[i] = stackB.top();
        }
        stackB.push(A[i]);
    }
    auto endB = high_resolution_clock::now();
    auto durationB = duration_cast<microseconds>(endB - startB);

    cout << "Вариант Б (через список).    Ответ: ";
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << " | Время: " << durationB.count() << " мкс" << endl;

    // чистим список, если там что-то осталось в конце
    while (!stackB.isEmpty()) {
        stackB.pop();
    }

    // Вариант В (STL) - измерение времени
    auto startC = high_resolution_clock::now();
    stack<int> stackC;
    for (int i = n - 1; i >= 0; i--) {
        while (!stackC.empty() && stackC.top() <= A[i]) {
            stackC.pop();
        }
        if (stackC.empty()) {
            result[i] = 0;
        } else {
            result[i] = stackC.top();
        }
        stackC.push(A[i]);
    }
    auto endC = high_resolution_clock::now();
    auto durationC = duration_cast<microseconds>(endC - startC);

    cout << "Вариант В (STL std::stack).  Ответ: ";
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << " | Время: " << durationC.count() << " мкс" << endl;

    // Вывод времени работы в консоль отдельно
    cout << "\n========================================" << endl;
    cout << "ВРЕМЯ РАБОТЫ АЛГОРИТМОВ:" << endl;
    cout << "========================================" << endl;
    cout << "Вариант А (массив)    : " << durationA.count() << " микросекунд" << endl;
    cout << "Вариант Б (список)    : " << durationB.count() << " микросекунд" << endl;
    cout << "Вариант В (STL)       : " << durationC.count() << " микросекунд" << endl;
    cout << "========================================" << endl;

    cout << "\nГруппа: 090304-РПИа-о25" << endl;
    cout << "Фамилия: Мамагулашвили Миранда Нодариевна" << endl;
    return 0;
}
