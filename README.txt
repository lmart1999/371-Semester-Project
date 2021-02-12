to run this program type the following in the command line
make
./RUFS
If no output file is selected a file named RUFS.txt will be automatically created, if the output file already exists it will be cleared before starting
to avoid overwrite errors.
Commands can be input from text file with one of two formats.

FORMAT 1
Each command followed immediately by an enter
Createfile
test.t
input text can be longer
createdir
dirname
createfile
prog.p
4
5
quit

If a directory is not ended upon quit it is automatically ended at the end of the program

FORMAT 2
Createfile test.t all of this will be input text
createdir first createfile prog.p 3 4 enddir quit

with this format you only need an enter after the input of a .t file to signify the end of input


upon recieving an invalid filenames such as ones greater than 11 characters, without a proper extension, or containing characters other than a-z, A-Z, 0-9
the program will prompt the user to reenter a proper filename, the same goes for directories.

There have been three sample inputs included in this program, to run them use the following commands
./RUFS <sample.txt
./RUFS <sample2.txt
./RUFS <sample3.txt

Sample 3 is the same as the test input given in the assignment

The output of sample3.txt is as follows

[ljmartin1@rucs Project1_ljmartin1]$ ./RUFS <sample3.txt
Welcome to RUFS. Enter one of the following commands:
CreateDir or CreateFile or EndDir or quit
Command: Enter File Name: Enter CPU requirements: Enter Memory Requirements: Command: Enter Directory Name: Command: Enter File Name: Enter Text: Command: Command:
0: Directory:root.d
11: Directory root.d contains 2 file/directory
15:     Filename:prog1.p
        Type: Program
26:  Contents: CPU Requirement:  2, Memory Requirement 3
34: Directory:first.d
45: Directory first.d contains 1 file/directory
49:     test.t
        Type:   Text
60: Size of Text File:  1 byte
64: Contents of text file:      A
65: End of Directory first.d
79: End of Directory root.d

The file operates with 4 commands
-CreateFile - allows you to create a file of either .t or .p extension, .t accepts a further text input and .p accepts 2 integer inputs
-CreateDir - allows you to create a directory, directory names do not have extensions and are at max 8 characters in lenght
-EndDir - closes the open directory and records the number of items that were in it
-Quit - closes all open directories and reads all information from the binary file

None of these are case sensitive commands, names are validated upon entering as are commands, if either is invalid you will be prompted to reenter them.


Future Improvements:
Make a disk manager class to handle reading and writing
Make another class for User interacton