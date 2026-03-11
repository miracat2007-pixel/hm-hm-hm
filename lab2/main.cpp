#include <iostream>
#include <vector>
#include <complex>
#include <chrono>
#include <iomanip>
#include <string>

using namespace std;


typedef complex<double> dcomplex;

const int N = 1024;
const int BLOCK_SIZE = 64; 

// 1.Классическое умножение по формуле
void multiply_ijk(const dcomplex* A, const dcomplex* B, dcomplex* C) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            dcomplex sum = 0;
            for (int k = 0; k < N; ++k) {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}
// 2.Оптимизированный алгоритм / Tiling
void multiply_tiled(const dcomplex* A, const dcomplex* B, dcomplex* C) {
    for (int ih = 0; ih < N; ih += BLOCK_SIZE) {
        for (int kh = 0; kh < N; kh += BLOCK_SIZE) {
            for (int jh = 0; jh < N; jh += BLOCK_SIZE) {
                for (int i = ih; i < ih + BLOCK_SIZE; ++i) {
                    for (int k = kh; k < kh + BLOCK_SIZE; ++k) {
                        dcomplex temp = A[i * N + k];
                        for (int j = jh; j < jh + BLOCK_SIZE; ++j) {
                            C[i * N + j] += temp * B[k * N + j];
                        }
                    }
                }
            }
        }
    }
}

int main() {
 
    setlocale(LC_ALL, ".UTF-8");

    auto* A = new dcomplex[N * N];
    auto* B = new dcomplex[N * N];
    auto* C = new dcomplex[N * N];

  
    for (int i = 0; i < N * N; ++i) {
        A[i] = { (double)rand()/RAND_MAX, (double)rand()/RAND_MAX };
        B[i] = { (double)rand()/RAND_MAX, (double)rand()/RAND_MAX };
    }

    // Теоретическая сложность: c = 2 * n^3
    double complexity = 2.0 * N * N * N;

    auto run_test = [&](string name, auto func) {
        fill(C, C + N * N, dcomplex(0, 0));
        auto start = chrono::high_resolution_clock::now();
        
        func();
        
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> t = end - start;
        
        // Производительность: p = c / t * 10^-6 (MFlops)
        double mflops = (complexity / t.count()) * 1e-6;
        
        cout << left << setw(30) << name 
             << " | Время: " << fixed << setprecision(4) << t.count() << " сек"
             << " | Производительность: " << setprecision(2) << mflops << " MFlops" << endl;
    };


    run_test("1. Классический",    [&]() { multiply_ijk(A, B, C); });
    run_test("2. Блочный (Tiling)",        [&]() { multiply_tiled(A, B, C); });

    cout << "\nМамагулашвили Миранда Нодариевна" << endl;
    cout << "Группа РПИа-о25" << endl;
  
    while(getchar() != '\n');

    return 0;
}