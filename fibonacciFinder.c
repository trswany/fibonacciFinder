#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define INPUT_BUF_LEN           (10)
#define ERR_INVALID_ENTRY       (-1)
#define FIRST_FIBONACCI_NUM     (0)
#define SECOND_FIBONACCI_NUM    (1)
#define TEST_PATTERN_LENGTH     (39)
#define ENABLE_PRINTING         (1)
#define DISABLE_PRINTING        (0)

int calculateFibonacciNumbers(int n, int enablePrinting);
void printFibonacciNumber(unsigned long int number);
int isPrime(unsigned long int number);
void testFibonacciCalculator(void);
void printUsage(void);

int main(int argc, char *argv[])
{
    char inputChars[INPUT_BUF_LEN];
    int n;

    // Verify the user gave us enough command-line arguments
    if (argc != 2) {
        printUsage();
        return 0;
    }

    // If we see --test, run the test
    else if (!strcmp(argv[1], "--test")) {
        testFibonacciCalculator();
        return 0;
    }

    // Otherwise, the user is asking us to print Fibonacci numbers
    else {
        // Convert the user's entry to an integer
        n = strtol(argv[1], NULL, 10);
        if (n <= 0) {
            printf("Error, invalid entry.\r\n");
            return ERR_INVALID_ENTRY;
        }

        // Calculate and print fibonacci numbers
        calculateFibonacciNumbers(n, ENABLE_PRINTING);
    }
}

// Calculates and prints n numbers of the Fibonacci sequence. Set enablePrinting
// to 1 to enable printing, 0 to disable.
//
// Note: recursion is typically avoided on embedded systems due to
// stack size limitations. This implementation does not use recursion.
//
// Returns: the n-th Fibonacci number (for testing)
int calculateFibonacciNumbers(int n, int enablePrinting)
{
    unsigned long int newNum, prevNum, prevPrevNum;
    int i;

    // Protect against invalid input
    if (n == 0) {
        return 0;
    }

    // The first two numbers of the sequence are special cases
    else if (n == 1) {
        if (enablePrinting) {
            printFibonacciNumber(FIRST_FIBONACCI_NUM);
        }
        return FIRST_FIBONACCI_NUM;
    }
    else if (n == 2) {
        if (enablePrinting) {
            printFibonacciNumber(FIRST_FIBONACCI_NUM);
            printFibonacciNumber(SECOND_FIBONACCI_NUM);
        }
        return SECOND_FIBONACCI_NUM;
    }

    // All other numbers use this algorithm
    else {
        if (enablePrinting) {
            printFibonacciNumber(FIRST_FIBONACCI_NUM);
            printFibonacciNumber(SECOND_FIBONACCI_NUM);
        }
        prevPrevNum = 0;
        prevNum = 1;
        for (i=3; i <= n; i++) {
            newNum = prevNum + prevPrevNum;
            if (enablePrinting) {
                printFibonacciNumber(newNum);
            }
            prevPrevNum = prevNum;
            prevNum = newNum;
        }
    }

    return newNum;
}

// Print the specified number.
//
// Note: I assume here that we should print both "Buzz" and "Fizz" when
// a number is divisible by both 3 and 5.
void printFibonacciNumber(unsigned long int number)
{
    if (number == 0) {
        printf("%lu\r\n", number);
    }
    else if ((number % 3 == 0) && (number % 5 == 0)) {
        printf("Buzz Fizz\r\n");
    }
    else if (number % 3 == 0) {
        printf("Buzz\r\n");
    }
    else if (number % 5 == 0) {
        printf("Fizz\r\n");
    }
    else if (isPrime(number)) {
        printf("BuzzFizz\r\n");
    } else {
        printf("%lu\r\n", number);
    }
}

// Check to see if a number is prime
//
// Note: There are many primality-test algorithms. Many of these are
// probabilistic and have a chance of being wrong. Some are heuristic and have
// not been proven to be accurate. To avoid being wrong, I use here the simple,
// time-consuming brute-force primality test.
//
// Returns 1 if a number is prime, 0 otherwise
int isPrime(unsigned long int number)
{
    unsigned long int upperBound;
    unsigned long int i;

    // 0 and 1 are not prime
    if (number <= 1) {
        return 0;
    }

    // Don't bother testing above sqrt(number)
    upperBound = sqrt(number);
    for(i = 2; i <= upperBound; i++) {
        if (number % i == 0) {
            return 0;
        }
    }

    // If we get here, our number must be prime
    return 1;
}

// Tests the Fibonacci calculator. Prints test results.
// Test pattern is the Fibonacci sequence pulled from the Online Encyclopedia
// of Integer Sequences (OEIS). https://oeis.org/A000045
void testFibonacciCalculator(void)
{
    int i;
    unsigned long int number;
    unsigned long int testPattern[TEST_PATTERN_LENGTH] =   {0, 1, 1, 2, 3, 5,
                            8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987,
                            1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368,
                            75025, 121393, 196418, 317811, 514229, 832040,
                            1346269, 2178309, 3524578, 5702887, 9227465,
                            14930352, 24157817, 39088169};

    for (i=1; i < TEST_PATTERN_LENGTH; i++) {
        number = calculateFibonacciNumbers(i, DISABLE_PRINTING);
        printf("Verifying %d-th Fibonacci number %lu == %lu... ", i,
            number, testPattern[i-1]);
        if (number != testPattern[i-1]) {
            printf("FAILED.\r\n");
            return;
        } else {
            printf("PASSED.\r\n");
        }
    }
    printf("Test complete. PASSED.\r\n");
}

// Prints usage information
void printUsage(void)
{
    printf("Fibonacci Finder v1.0\r\n");
    printf("Calculates and prints the first n numbers of the ");
    printf("Fibonacci sequence\r\n");
    printf("Usage: fibonacciFinder [--test] [n]\r\n");
    printf("Example: fibonacciFinder 9\r\n");
    return;
}
