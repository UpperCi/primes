//version 1, goes through all numbers not just an assorted list of them
//0.81s to get all primes under 100.000

#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>

bool isPrime(unsigned int n) 
{//checks if number is a prime by dividing and checking remainder
    unsigned int h = std::round(n / 2) + 1;
    for (unsigned int i = 2; i < h; i++)
    {
        if (n % i == 0) return false;
    }
    if (n > 1) return true;
    return false;
}
//checks if number is a prime for everything and if true, adds it to vector
std::vector<unsigned int> process(unsigned int nstart, unsigned int nend){
    std::vector<unsigned int> primes;
    for (unsigned int i = nstart; i < nend + 1; i++)
    {
        if (isPrime(i)) primes.push_back(i);
    }
    return primes;
}

float _init()
{
    unsigned int _start, _end;
    std::cout << "What number do you want to start at?" << std::endl;
    std::cin >> _start;
    std::cout << "What number do you want to end at?" << std::endl;
    std::cin >> _end;
    std::cout << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<unsigned int> prime_numbers;
    prime_numbers = process(_start, _end); //values are range user put in

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    for (int i = 0; i < prime_numbers.size(); i++)
        std::cout << prime_numbers.at(i) << ' ';
    return elapsed.count();
}

int main()
{
    std::cout << std::endl << "time elapsed: " << _init();
    std::cout << std::endl << "Press any key to continue . . .";
    std::cin.get();
    std::cin.get();
}