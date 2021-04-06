#version 2, goes through prime numbers only
#6.7s to get all primes under 100.000

import time #to calculate how long this took
import os #so it doesn't immediately close
import math

def _init():
    _end = int(input("what number do you want to end at?\n"))
    print()

    startTime = time.time()

    prime_numbers, primes_found = process(_end) #values are range user put in

    elapsedTime = time.time() - startTime
    print("\nTime elapsed: {}".format(elapsedTime))
    print("prime numbers found: {}".format(primes_found))
    print("range searched: {} to {}".format(0, _end))

#checks if number is prime for everything and if true adds it to array
def process(nend):
    primes_found = 0
    primes = []
    for i in range(1, nend + 1):
        if isPrime(i, primes):
            primes.append(i)
            primes_found += 1
    return primes, primes_found

def isPrime(n, primes): #checks if number is a prime by dividing and checking remainder
    for i in primes:#range(2, round(n / 2) + 1)
        if i >= 2 and i < round(math.sqrt(n)) + 2:
            if n % i == 0:
                return False
        elif not n % i == 0:
            break
    return True

_init()
os.system("pause")