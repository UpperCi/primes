#version 1, goes through all numbers, not just an assorted list of them
#8.8s to get all primes under 100.000

import time #to calculate how long this took
import os #so it doesn't immediately close

def _init():
    _start = int(input("what number do you want to start at?\n"))
    _end = int(input("what number do you want to end at?\n"))
    print()

    startTime = time.time()

    prime_numbers, primes_found = process(_start, _end) #values are range user put in

    elapsedTime = time.time() - startTime
    print(prime_numbers)
    print("\nTime elapsed: {}".format(elapsedTime))
    print("prime numbers found: {}".format(primes_found))
    print("range searched: {} to {}".format(_start, _end))

#checks if number is prime for everything and if true adds it to array
def process(nstart, nend): 
    primes = []
    primes_found = 0
    for i in range(nstart, nend + 1):
        if isPrime(i):
            primes.append(i)
            primes_found += 1
    return primes, primes_found

def isPrime(n): #checks if number is a prime by dividing and checking remainder
    for i in range(2, round(n / 2) + 1):
        if n % i == 0:
            return False
    if n > 1:
        return True

_init()
os.system("pause")