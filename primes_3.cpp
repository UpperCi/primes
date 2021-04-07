#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <algorithm>

using std::string;
using std::vector;

const string DATAFILENAME = "primes";
const string DATAFILEEXTENSION = ".csv";

int printVec(vector<unsigned int> v)
{
    for (int i = 0; i < v.size(); i++)
        std::cout << v.at(i) << ' ';
    return 0;
}

vector<unsigned int> strToVec(string val)
{
    vector<unsigned int> returnVec;
    string tempVal = "";

    for (char &c : val) {
        if (c == ',')
        {
            unsigned int tempNum = std::stoi(tempVal);
            returnVec.push_back(tempNum);
            tempVal = "";
        }
        else
        {
            tempVal += c;
        }
    }
    
    if (tempVal.empty() == false)
    {
        unsigned int tempNum = std::stoi(tempVal);
        returnVec.push_back(tempNum);
    }
    std::cout << std::endl;
    return returnVec;
}
//cleans up vector to remove any duplicates
vector<unsigned int> cleanVec(vector<unsigned int> v)
{
    vector<unsigned int> cleanVec;
    cleanVec = v;

    auto end = cleanVec.end();
	for (auto it = cleanVec.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}
	cleanVec.erase(end, cleanVec.end());

    return cleanVec;
}

vector<unsigned int> getDataFile()
{
    vector<unsigned int> data;

    string filename = DATAFILENAME + DATAFILEEXTENSION;
    std::fstream dataFile;
    dataFile.open(filename, std::ios::in);

    string line;
    getline(dataFile, line);
    //std::cout << "stuff: " << line << std::endl;
    dataFile.close();

    data = strToVec(line);
    return data;
}

int writeDataFile(vector<unsigned int> vals)
{
    string filename = DATAFILENAME + DATAFILEEXTENSION;
    std::fstream dataFile;
    dataFile.open(filename, std::ios::out | std::ios::app);
    for (int i = 0; i < vals.size(); i++)
    {
        dataFile << vals.at(i)
        << ',';
    }
    dataFile.close();
}

bool isPrime(unsigned int n, vector<unsigned int> primes) 
{//checks if number is a prime by dividing and checking remainder
    unsigned int h = std::round(sqrt(n)) + 2;
    for (unsigned int i = 0; i < primes.size(); i++)
    {
        unsigned int d = primes.at(i);
        if (d >= 2 && d < h)
        {
            if (n % d == 0) return false;
        }
        else if (n % d != 0) break;
    }
    if (n > 1) return true;
    return false;
}
//checks if number is a prime for everything and if true, adds it to vector
vector<unsigned int> process(
    unsigned int nstart,
    unsigned int nend,
    vector<unsigned int> prime_numbers)
{
    vector<unsigned int> primes;
    vector<unsigned int> checkPrimes = prime_numbers;
    for (unsigned int i = nstart; i < nend + 1; i++)
    {
        if (isPrime(i, checkPrimes)) 
        {
            primes.push_back(i);
            checkPrimes.push_back(i);
        }
    }
    return primes;
}
//basically the function
float _init()
{
    vector<unsigned int> prime_numbers;
    unsigned int _start = 0;

    auto start = std::chrono::high_resolution_clock::now();

    prime_numbers = getDataFile();

    if (prime_numbers.size() > 0)
    _start = prime_numbers[prime_numbers.size() - 1] + 1;

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Data initialisation complete" << std::endl << "Time elapsed: "
    << elapsed.count() << std::endl;
    
    unsigned int _end;
    std::cout << "What number do you want to end at? (at least " 
    << _start + 1 << ')' << std::endl;
    std::cin >> _end;
    
    if (_end <= _start){
        std::cout << "number out of range";
        return 0;
    }

    start = std::chrono::high_resolution_clock::now();

    vector<unsigned int> write_primes = process(_start, _end, prime_numbers); //values are range user put in
    
    //printVec(cleanVec(prime_numbers));
    writeDataFile(write_primes);

    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;

    std::cout << std::endl<<"Primes found: "<<write_primes.size()<<std::endl;
    std::cout << "Range Searched: " << _start << '-' << _end << std::endl;

    //printVec(prime_numbers);
    return elapsed.count();
}

int main()
{
    std::cout <<"time elapsed: " << _init() << std::endl;
    std::cout <<"Press enter to continue . . .";
    std::cin.get();
    std::cin.get();
}