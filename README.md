# Hash-table
This program analyzes multiple input files containing sequences of integers in the range [0-28].
The numbers may appear multiple times in each file.
Numbers in each file are separated by one or more characters.

The program reads the numbers from all input files and prints a summary for each unique number that appears in one or more files.
The summary includes the filenames where the number appears and the frequency of its occurrences in each file

#For example:

dat1.in 11 2 4 21 23 21 

dat2.in 21 7 4 23 21 13 13 

dat3.in 5 23 5 23 6 23 23


When running the program: 

./hash dat1.in dat2.in dat3.in

 The expected output is: 
 
2 appears in file dat1.in - 1 time

4 appears in file dat1.in - 1 time, file dat2.in - 1 time

5 appears in file dat3.in - 2 times

6 appears in file dat3.in - 1 time

7 appears in file dat2.in - 1 time

11 appears in file dat1.in - 1 time

13 appears in file dat2.in - 2 times

21 appears in file dat1.in - 2 times, file dat2.in - 2 times

23 appears in file dat1.in - 1 time, file dat2.in - 1 time, file dat3.in - 4 times

