#include <iostream>
#include <stack> // для варианта В
#include <windows.h>

using namespace std;

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

    //Вариант А (Массив)
    StackArray stackA;
    // идем с конца массива в начало
    for (int i = n - 1; i >= 0; i--) {
        // выкидываем все элементы, которые меньше текущего
        while (!stackA.isEmpty() && stackA.top() <= A[i]) {
            stackA.pop();
        }
        // если стек опустел, значит большего числа справа нет
        if (stackA.isEmpty()) {
            result[i] = 0;
        } else {
            result[i] = stackA.top(); // нашли ближайшее большее
        }
        stackA.push(A[i]); // незабываем добавить текущее число в стек
    }

    cout << "Вариант А (через массив).    Ответ: ";
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;


    // Вариант Б (Список)
    StackList stackB;
    // логика точно такая же, только стек другой
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

    cout << "Вариант Б (через список).    Ответ: ";
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    // чистим список, если там что-то осталось в конце
    while (!stackB.isEmpty()) {
        stackB.pop();
    }


    //Вариант В (STL)
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

    cout << "Вариант В (STL std::stack).  Ответ: ";
    for (int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    cout << "\nГруппа: 090304-РПИа-о25" << endl;
    cout << "Фамилия: Мамагулашвили Миранда Нодариевна" << endl;

    return 0;
}
