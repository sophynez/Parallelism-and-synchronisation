# Parallelism-and-synchronisation
Script to simulate the the two concepts of parallelism and synchronisation between processes (programs) in an operating system in a single program with a given task. 

## Task of the script
In this program, we aim to synchronize a set of parallel processes using signal manipulation under
UNIX using the C language. To illustrate this, we take the task of finding prime numbers between 2 and a given n.

Only 2 parallel processes will be used to realize this task. To do this, we use a parent process P which registers the
numbers in a file f then create 2 processes P1 and P2 cooperating to calculate the prime numbers, then
prints the contents of file f and exits. The process P coordinates the other processes created. f will be updated to contain only prime numbers at the end. 
