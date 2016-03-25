# Fibonacci Finder
Find and print Fibonacci numbers. Prints "Buzz" and "Fizz" for style.

## Installation

1. Download the project
2. gcc -o fibonacciFinder fibonacciFinder.c

## Usage

Calculate and print the first n numbers of the Fibonacci Sequence with:
./fibonacciFinder n
Example: ./fibonacciFinder 10

To test the Fibonacci algorithm, use:
./fibonacciFInder --test

## Example Output

$ ./fibonacciFinder 20
0
1
1
BuzzFizz
Buzz
Fizz
8
BuzzFizz
Buzz
34
Fizz
BuzzFizz
Buzz
BuzzFizz
377
Fizz
Buzz
BuzzFizz
2584
4181

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request

## Notes

1. I use the version of the Fibonacci sequence that starts with 0, 1, ...
2. I don't use recursion because recursion is dangerous on embedded systems (stack space is limited)
3. I use the simple, brute-force prime-finding algorithm because it's guaranteed to give the right answer
4. I use a test pattern of Fibonacci numbers pulled from the Online Encyclopedia of Integer Sequences (OEIS). https://oeis.org/A000045
5. I assume that numbers that are divisible by both 3 and 5 should print both "Buzz" and "Fizz". Therefore, a number like 15 would print "Buzz Fizz".
