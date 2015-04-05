## C implementation of Common Data Structures and Algorithms

This is a project in which I have implemented a few algorithms and data structures in C.
The implementation is based on the book "Introduction to Algorithms" by Thomas Cormen, Rivest and Leiserson

This project is a learning exercise, with focus on getting comfortable with common data structures and algorithm techniques like dynamic programming.
Feel free to fork this repository and improve upon my code.


### Compiling and Executing the C programs:

I have created a Makefile. For compiling them, use the command:
`make programName`. 

Do not use any extension like .c or .o with the make command.
If the directory contains a program with name like progName.c and you issue the command: `make progName`, make will compile the program and generate an output file named progName.
You can then execute the program by issuing the command `./progName`
To modify the compilation flags, just edit the file named __Makefile__.
Change the section named __CFLAGS__.

All the programs were compiled on a Linux machine(x86_64) with gcc 4.8


### Testing the programs

The minunit directory contains a simple unit testing library for C.
I have used it in a few programs for testing with different sets of input.
