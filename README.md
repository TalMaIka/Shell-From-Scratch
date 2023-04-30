# Compare

This program is a command-line tool that checks if two files are equal. It takes two file names as command-line arguments and outputs "equal" if the files have the same content or "distinct" if they have different content.

## How to run a sample:

* Create two sample files in the current directory with different content. For example, create a file named "file1.txt" with the content "Hello, world!" and another file named "file2.txt" with * * the content "Hello, world?".
* Open a terminal and navigate to the directory where the files were created.
* Compile the program by typing "gcc -o filecompare filecompare.c" and press enter.
* Run the program by typing "./filecompare file1.txt file2.txt" and press enter.
* The output should be "distinct".

## The program also accepts two optional flags:

* "-v" prints verbose output. If the files are equal, it will print "equal". If they are different, it will print "distinct".
* "-i" makes the comparison case-insensitive.

# Copy

The program is a file copying utility, that allows the user to copy the contents of one file to another. It checks whether the destination file exists, and if so, it prompts the user to confirm whether they want to overwrite it or not. It also has an option to enable verbose output that gives feedback on the progress of the file copy.


## How to run a sample:
* ./copy file1.txt file2.txt

## The program also accepts two optional flags:
* -v : enable verbose output
* -f : force overwrite of destination file

## Example with flags:
*./copy file1.txt file2.txt -v -f

This will copy the contents of file1.txt to file2.txt, enable verbose output, and force overwrite of file2.txt if it already exists.

# Decode

This program demonstrates the dynamic loading of shared libraries and decoding messages using different codecs.

The program takes two arguments: the name of the codec (either "codecA" or "codecB") and the message to decode. The program then loads the corresponding shared library using dlopen() and obtains a function pointer for the decode() function using dlsym(). The decode() function is then called on the input message, which modifies the message in place. Finally, the decoded message is printed to stdout.

To run the program, compile it with the following command:
* make decode

Then, execute it with the following command:
* ./decode <codec> <message>
  
For example, to decode the message "khoor" using codecA, run:
* ./codec codecA khoor

# Encode
  
This project contains two dynamic libraries, libcodecA.so and libcodecB.so, which encode and decode messages using different algorithms. The main program loads the specified codec library at runtime and uses it to encode or decode the given message.

To run the program, use the following command:
* make encode
* ./encode codecB <message>

# stShell
  
This program is a simple shell that allows users to run basic command-line operations. The shell reads user input, executes the command, and then displays the results. It also allows for output to be redirected to a file using the ">" or ">>" operators, piping abilities and child process terminate when Ctrl+C promted.
  
To run the program, compile it with the following command:
* make stshell
* ./stshell

And you are ready to play with the shell abilities.
  
## Inorder to compile all of the programs
* make all


