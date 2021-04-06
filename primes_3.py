#version 3, goes through a database of prime numbers
#6.7s to get all primes under 100.000

DATAFILENAME = "primes"
DATAFILEEXTENSION = ".csv"

import time #to calculate how long this took
import os #so it doesn't immediately close
import csv #to write and read from csv files
import math

def _init():
    new_primes = 0

    _start = 0
    tempArr = getDataFile()
    _start = tempArr[-1]

    _end = int(input("what number do you want to end at?\nIt has to be at least {}\n".format(_start)))
    print()

    if _start >= _end:
        print("number too low")
        return 0

    startTime = time.time()

    prime_numbers, new_primes = process(_start, _end) #values are range user put in

    elapsedTime = time.time() - startTime
    writeToDataFile(prime_numbers)
    print("Time elapsed: {}".format(elapsedTime))
    print("new prime numbers found: {}".format(new_primes))
    print("range searched: {} to {}".format(_start, _end))

#checks if number is prime for everything and if true adds it to array
def process(nstart, nend): 
    newprime = 0
    primes = getDataFile()
    for i in range(nstart, nend + 1):
        if isPrime(i, primes):
            primes.append(i)
            newprime += 1
    return primes, newprime

def isPrime(n, primes): #checks if number is a prime by dividing and checking remainder
    for i in primes:#range(2, round(n / 2) + 1)
        if i >= 2 and i < round(math.sqrt(n)) + 1:
            if n % i == 0:
                return False
        elif not n % i == 0:
            break
    return True

def getDataFile():
    primes = []
    filename = DATAFILENAME + DATAFILEEXTENSION
    with open(filename, 'w+') as datafile:
        dataread = csv.reader(datafile, delimiter = ' ')
        for row in dataread:
            for i in row:
                o = ""
                for j in i:
                    if j == ',':
                        primes.append(int(o))
                        o = ""
                    else: o += j
    if primes == []: primes = [2]
    return primes

def writeToDataFile(prime_values):
    filename = DATAFILENAME + DATAFILEEXTENSION
    primes = getDataFile()
    primes += prime_values
    primes = cleanup(primes)
    with open(filename, 'w') as datafile:
        datawrite = csv.writer(datafile)
        datawrite.writerow(primes)
        pass

def cleanup(duplicate): #geeksforgeeks function to remove duplicates from list 
    final_list = [] 
    for num in duplicate: 
        if num not in final_list: 
            final_list.append(num) 
    return final_list 

_init()
os.system("pause")