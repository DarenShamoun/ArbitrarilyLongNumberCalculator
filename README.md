# Project #3: Postfix Integer Calculator
The goal of this project is to create a simple calculator that can perform
arithmetic operations on integers of (practically) unlimited size.

In this project, the calculator must use *postfix* notation.
Rather than the functional programming style used in the first two projects,
this project should use object oriented programming techniques.
It should use the *Chain of Responsibility* pattern 
to abstract away the actual operations performed from the calculator class.
The calculator class is merely a simple driver with no knowledge about
the actual calculations performed.

## Turn in checklist
All projects will be graded according to the project rubric in Canvas.

Before uploading your project,
make sure it meets all of the rubric criteria in order to get full credit.

1. Ensure all project requirements are met and all results are correct.
2. Ensure the intent behind every program element is "crystal clear".
   Add documentation where it makes sense to do so.
3. Ensure the top of each source file includes your name and student ID.
4. Your finished project must compile on buffy.
5. Project rubric requirements for correctness, clarity, design,
   and coding are met or exceeded.

## Reflection
When you are **finished**, take a moment to 
[rate this project](https://forms.gle/uNtvPp78dJhSPMND6).

## Project Requirements
In order to receive full credit, your project must satisfy **all**
of the following requirements:

1. Process command line arguments:   
   `-h` to display `h`elp text and exit.  
   `-v` to produce `v`erbose output.
2. Process input strings containing equations in postfix notation.
   Each equation should reside in a single line of input
3. Process equations using a mix of symbols 
   (addition, multiplication, exponentiation)
   containing numbers of arbitrary length.

   Assume that most values will exceed the maximum length for any
   builtin type in C++.
4. Process input interactively in a terminal window.

   When running interactively, entering 'quit' exits the program.
5. Process input directed into the program from standard input,
   for example:

   ```
   # echo "16 16 16 * *" | ./calc -v
   16 16 16 * * = 4096
   ```

   or   
   ```
   # echo "13 55 ^" | ./calc
   18487763498758903017821863604872883745551547783010632046513957
   ```
6. Process input redirected from a file.
   For example, given a file `input.txt`, containing:    
   ```
   # simple addition
   2 3 +

   16 16 16 * *
   ```

   Then using it should produce:  
   ```
   # ./calc -v < input.txt
   2 3 + = 5
   16 16 16 * * = 4096

   ```

   The file src/input.txt shows some examples, your program
   should be able to process.
7. When processing input, the program should silently ignore blank lines
   and lines the begin with a `#` character.

   The program **should** be tolerant of leading and trailing whitespace
   on lines as well as leading zeroes on values.
8. Use the class Handler to abstract computation logic.   

   Each operation (`+`, `*`, and `^`) must encapsulate each operation
   in a class that inherits from Handler.

   Also encapsulate the code to convert strings to numbers
   in the same way - by extending Handler.

9. Use a `std::stack` to manage calculator BigInt operands.  
   Do **not** store operators on this stack.

## Chain of Responsibility Pattern
The *Chain of Responsibility design pattern* allows an object to handle 
a request without knowing what object will receive and handle it.
Each member in the chain is a link in a sequential data structure.
Objects in the chain are followed until one that can handle the request,
but for this lab, all of the objects that implement the `Handler` interface
can simply be stored in a `std::vector` and iterated over.

All clients of Handler objects treat each object as a 'black box'
by simply invoking the base object virtual `handle()` function.

Since the calculator has no idea which Handler will operate on a token,
each must be tried.
For example, given the input `"2 2 +"`,
each part of this string is first split into individual tokens:
"2", "2", and "+".
These are stored in a `std::vector`, which then must be evaluated.

So now we have two `vector`'s: 

1. A vector of `Handler*` objects:

   - Add
   - Multiply
   - Power
   - OperandPusher

2. A vector of `std::string`

Each `string` will be processed by exactly one `Handler` object.
- Create an outer loop to loop on each `string`.
- Create an inner loop to loop on each `Handler` object.
- Call the `handle()` function of each `Handler` object 
  and pass in the current `string` token as a parameter.
- If the current `Handler` object knows how to handle the token provided,
  then perform it's action.

  - If the token is an operand,
    then it is pushed onto the stack provided as a parameter.
  - If the token is an operator,
    then two operands are popped off the stack, 
    the appropriate operation is performed, 
    and the result is pushed back onto the stack.

Once any `Handler` returns `true`, 
processing should continue to the next token.

### References
- [OO design](http://www.oodesign.com/chain-of-responsibility-pattern.html)
- [Source making](https://sourcemaking.com/design_patterns/chain_of_responsibility)


## Example output
This section provides expected outputs from your finished program.
The character `#` represents the command prompt.
It may look different on your computer.

You are under no compulsion to attempt to replicate these examples exactly.
They do, however, provide reasonable goals, and you are free to emulate
these examples.

Your output should make sense for your application.

### Show help
Provide an **accurate description** of how to run the program, then exit.

```
Usage: ./calc [-h] [-v] 
to run the program interactively. To run using standard input:
echo 'equation' | ./calc
where 'equation' is a postfix notation equation, i.e. '2 2 +'
or:
  ./calc < input_file.txt
where 'input_file.txt' contains postfix notation equations, one per line

Options:
  -h   Show this text
  -v   Set a verbose output flag.  Default = false.

Running with no input from standard in enters 'interactive mode'.
Equations can be entered one per line.
The program runs until 'quit' is the first word on a line or EOF is reached.
#
```

### Using an input file
With the verbose output option set:

```
# ./calc -v < input.txt 
000000056669777     99999911111 + 352324012 + 03 ^      555557778 * = 562400792227677956625810678708149922000000
99999999 990001 * 01119111 55565    33333 + * +  88888888              + = 99099674628565
123456789 1111111111 * 111119 2111111 9111111 * + *  1 ^ = 2638486500477638652325851269760
9 1 +     5 *     00000000 + = 50
999999999  0 * = 0
9 0 ^ = 1
#
```

### Interactive mode
Continue to accept input and display results until `quit`
is the only string on a line.

Display results when a newline (enter) is entered.

```
# ./calc
000000056669777     99999911111 + 352324012 + 03 ^      555557778 *
562400792227677956625810678708149922000000
1 2 + 3 * 4 ^
6561
quit
#
```

### Output when bad inputs received
Under no circumstances should your program throw an unhandled exception,
abort, or crash.
A new situation you now need to handle is having 
too few operators or operands.

The following examples show what handling bad inputs
might look like when running interactively.

```
./calc
2 +
Invalid argument: Not enough operands to execute add operation.
2

1 2 + + + 
Invalid argument: Not enough operands to execute add operation.
Invalid argument: Not enough operands to execute add operation.
3

1 2 3 * * * 
Invalid argument: Not enough operands to execute multiply operation.
6

1 2 3 4 * ^
Error: could not produce a result.
  Too few operators in problem.
  Operands still on problem stack:
  1: 4096
  2: 1
#
```


## This is too hard, I need help!
If you are having difficulty getting started,
there is a set of unit tests you can use.

Compile and run the tests exactly the same we use lab tests.

These tests do not test everything,
but do validate the BigInt class and the classes used in
the Chain of Responsibility pattern.

**These steps are not required to get full credit for this project.**

They exist purely for those having trouble getting started.

There are several functional tests of the basic arithmetic, however,
which any working calculator should be able to pass.

