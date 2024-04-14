#include <thread>
#include <iostream>
#include <mutex>

std::mutex g_lock;

void seq(long long* temp, int left, int right) {
    while (left <= right) {
        std::lock_guard<std::mutex> lock(g_lock);
        *temp *= left;
        left += 1;
    }
}

int main() {
    int number = 0;
    long long a = 1;

    std::cout << "Enter a number: " << std::endl;
    std::cin >> number;

    int n1 = number / 3;
    int n2 = 2 * (number / 3);

    std::thread th1(seq, &a, 1, n1);
    std::thread th2(seq, &a, n1 + 1, n2);
    std::thread th3(seq, &a, n2 + 1, number);

    th1.join();
    th2.join();
    th3.join();

    std::cout << "Result: " << a << std::endl;
}