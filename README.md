# Unix wc command implementation in C

This project is a C implementation of the Unix `wc` (word count) command. It provides functionality to count bytes, lines, words, and characters in a file or from standard input.

## Prerequisites

To compile and run this program, you need:

- GCC

## Compilation

```
gcc -o wc wc.c
```

## Usage

```
./wc [OPTION] [FILE]
```

If no FILE is specified, read standard input.

Options:
- -c : print the byte counts
- -l : print the newline counts
- -w : print the word counts
- -m : print the character counts

Without any options, the program prints line, word, and byte counts.

## Examples

Count lines, words, and bytes in a file:
```
./wc test.txt
```
Output:
```
7145 58164 342190 test.txt
```

Count only words in a file:
```
./wc -w test.txt
```
Output:
```
58164 test.txt
```
Count bytes from standard input:
```
cat test.txt | ./wc -c
```
Output:
```
342190
```