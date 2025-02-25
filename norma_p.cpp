/**
 * DANIEL ETEBAN MARQUEZ UPEGUI
 * 25 de Febrero de 2025
 * Ejemplo con thread
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>

using namespace std;
using namespace std::chrono;

const int SIZE = 100000000;

vector<long> v(SIZE);

void fill(int start, int end) {
    for (int i = start; i < end; i++) {
        v[i] = 10LL;
    }
}

void norma_p(int start, int end, int p, long long &sum) {
    for (int i = start; i < end; i++) {
        v[i] = pow(v[i], 1/p);
        sum += v[i];
    }
}

void norma_pPro(int start, int end, int p, long long &sum) {
    for (int i = start; i < end; i++) {
        sum += pow(v[i], 1/p);
    }
}

int main() {
    fill(0, SIZE);
    //Un hilo para norma_p (secuencial)
    auto start = chrono::system_clock::now();
    long long partSecuencial = 0;
    thread t1(norma_p, 0, SIZE, 5, ref(partSecuencial));
    t1.join();
    auto stop = chrono::system_clock::now();
    //Duración en milisegundos
    auto duration = duration_cast<milliseconds>(stop - start);
    printf("Tiempo de ejecución: %ldms\n", duration.count());
    printf("Suma: %lld\n", partSecuencial);
    

    //Dos hilos para sumaPro
    start = chrono::system_clock::now();
    long long part1 = 0, part2 = 0;
    thread t7(norma_pPro, 0, SIZE/2, 5, ref(part1));
    thread t8(norma_pPro, SIZE/2, SIZE, 5, ref(part2));
    t7.join();
    t8.join();
    stop = chrono::system_clock::now();
    //Duración en milisegundos
    duration = duration_cast<milliseconds>(stop - start);
    printf("Tiempo de ejecución 2 hilos: %ldms\n", duration.count());
    printf("Unión: %lld\n", part1 + part2);

}