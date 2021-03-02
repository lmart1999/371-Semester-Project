to run this program type the following in the command line
make
./RUSH
If no output file is selected a file named RUSH.txt will be automatically created, if the output file already exists it will be opened for editing and reading instead.
Commands can be input from text file with one of two formats.

FORMAT 1
Each command followed immediately by either an enter or their parameter(ie a file to search or create)
Createfile test.t
input text can be longer
mkdir dirname
cd dirname
createfile prog.p
4
5
quit


FORMAT 2
Createfile test.t all of this will be input text
mkdir first cd first createfile prog.p 3 4 cd .. quit

with this format you only need an enter after the input of a .t file to signify the end of input


upon recieving an invalid filenames such as ones greater than 11 characters, without a proper extension, or containing characters other than a-z, A-Z, 0-9
the program will prompt the user to reenter a proper filename, the same goes for directories.

There have been three sample inputs included in this program, to run them use the following commands, all assume empty files are being used
./RUSH <sample.txt
./RUSH <sample2.txt
./RUSH <sample3.txt

Sample 3 is the same as the test input given in the assignment

The output of sample3.txt is as follows

[ljmartin1@rucs Project1_ljmartin1]$ ./RUSH <sample3.txt
Welcome to RUSH. Enter A Command
Command:
Directory Name: root.d
        Directory: test

Command: Command: Command: Current Directory: /root.d/test
Command: Enter Text: Command:
Directory Name: test
        Filename: test.t Type: Text File

Command: A test file
Command: Command: Current Directory: /root.d
Command: quit


The file operates with 11 commands
-CreateFile - allows you to create a file of either .t or .p extension, .t accepts a further text input and .p accepts 2 integer inputs
-mkDir - allows you to create a directory, directory names do not have extensions and are at max 8 characters in length, directories are automatically ended
	**NOTE - A directory may not be named root
-cd - allows you to change direcotries to another directory in the current one, use .. to return to parent directory, accepts directory name as input
-ls - list files in current directory and tells you the directory name
-pwd - prints path to current directory
-cat - allows you to see contents of a text file in the current directory, takes text file and extension as input
-start, step, run - takes a program as input and is a place holder for future progression, takes program file and extension as input
-printinfo, prints list of all directories, files, and programs along with their contents and memory locations
-Quit - ends program

None of these are case sensitive commands, names are validated upon entering as are commands, if either is invalid you will be prompted to reenter them.

