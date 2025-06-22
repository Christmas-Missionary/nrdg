# What is this?  

This is a very rough program where given a base, it generates all numbers with no repeating digits.
Though this program allows bases from 1 to 16, it can quickly generate all non-digit-repeating decimal numbers in around 16 seconds, as well as all non-digit-repeating base-11 numbers in around 3 minutes. Bases 12 to 16 take too long for my standards.  

If anyone is able to improve the performance of this, or check to see if this program is correct in the numbers it generates, you have my blessing to do `git clone`, experiment, and do a pull request if you are confident in your code.  
I recommend looking at `next_nrd_number` and `increment_repeating_digit`.

# How to build

**Linux + Macos (Unix)**

`nrd $ cc -Wall -Wextra -Wpedantic -O3 src/main.c src/nrd.c -o nrd`  


# Todo

Make program go faster yet still be right  
Generate only a section of numbers for paste-bin  
- Input starting point, then go for how many times  
- Example: `$ nrd 10 --start 1260345 --for 900`  

`--help, -h` and `--version, -v`

Fix internal timing of program  
Command and args for windows MSVC


# Benchmark Table 

CPU: Apple M2

|Base|Amount|POSIX `time` command|
|----|------|------|
|1|1        |0.00s user 0.00s system 75% cpu 0.005 total
|2|2        |0.00s user 0.00s system 74% cpu 0.005 total
|3|10       |0.00s user 0.00s system 74% cpu 0.005 total
|4|48       |0.00s user 0.00s system 74% cpu 0.005 total
|5|260      |0.00s user 0.00s system 76% cpu 0.006 total
|6|1630     |0.00s user 0.00s system 79% cpu 0.008 total
|7|11742    |0.01s user 0.01s system 65% cpu 0.029 total
|8|95900    |0.04s user 0.06s system 61% cpu 0.170 total
|9|876808   |0.43s user 0.59s system 63% cpu 1.617 total
|10|8877690 |4.75s user 6.19s system 66% cpu 16.538 total
|11|98641010|47.56s user 55.24s system 55% cpu 3:04.08 total  
|12|???|???
|13|???|???
|14|???|???
|15|???|???
|16|???|???