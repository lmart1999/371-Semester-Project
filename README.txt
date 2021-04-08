to run this program type the following in the command line
make
./RATCH
If no output file is selected a file named RATCH.txt will be automatically created, if the output file already exists it will be opened for editing and reading instead.
Commands can be input from text file with one of two formats.

FORMAT 1
Each command followed immediately by either an enter or their parameter(ie a file to search or create)
Createfile test.t
input text can be longer
mkdir dirname
cd dirname
Addprogram prog.p 4 5 1 2
quit


FORMAT 2
Createfile test.t all of this will be input text
mkdir first cd first addprogram prog.p 3 4 
cd .. quit

with this format you only need an enter after the input of a .t file to signify the end of input or at the end of a Addprogram command


upon recieving an invalid filenames such as ones greater than 11 characters, without a proper extension, or containing characters other than a-z, A-Z, 0-9
the program will prompt the user to reenter a proper filename, the same goes for directories and programs.

There have been four sample inputs included in this program along with a sample File system, to run them use the following commands
./RATCH test.txt <test1.txt
./RATCH test.txt <testWrite.txt
./RATCH test.txt <testRound.txt
./RATCH test.txt <testStep.txt

test1.txt is the same as the test input given in the assignment

The output of test1.txt is as follows:

[ljmartin1@rucs project3_ljmartin1]$ ./RATCH test.txt <test1.txt
Welcome to RUSH. Enter A Command
Command: Command: Command: Command: Command: Command: Advancing the System until all jobs are finished

Current Time <0>
Running job first.p has 4 time left and is using 1 memory resources.
The queue is:
        Position 1: job second.p has 4 units left and is using 1 memory resources.
        Position 2: job third.p has 2 units left and is using 1 memory resources.

Current Time <1>
Running job second.p has 4 time left and is using 1 memory resources.
The queue is:
        Position 1: job third.p has 2 units left and is using 1 memory resources.
        The process first.p is obtaining IO and will be back in 1 units

Current Time <5>
Running job third.p has 2 time left and is using 1 memory resources.
The queue is:
        Position 1: job first.p has 3 units left and is using 1 memory resources.
Finished Jobs are:
        second.p 4 5

Current Time <7>
Running job first.p has 3 time left and is using 1 memory resources.
The queue is: empty
Finished Jobs are:
        second.p 4 5
        third.p 2 7

Current Time <10>
Running Job is empty
The queue is: empty
Finished Jobs are:
        second.p 4 5
        third.p 2 7
        first.p 4 10



The file operates with these commands
-CreateFile - allows you to create a file of either .t extension, .t accepts a further text input 
-addprogram - allows you to create a program using either 2 or 4 integers of form "Addprogram cpuReq Memreq IOStartTime IOExecTime", if 3 are included the third will be discarded and any more than 4 will also be discarded, cpu and memory  requirement are required
-mkDir - allows you to create a directory, directory names do not have extensions and are at max 8 characters in length, directories are automatically ended
-cd - allows you to change direcotries to another directory in the current one, use .. to return to parent directory, accepts directory name as input
-ls - list files in current directory and tells you the directory name
-pwd - prints path to current directory
-cat - allows you to see contents of a text file in the current directory, takes text file and extension as input
-start - takes a program as input and adds it to the queue of runnning jobs if there is memory available
-setburst - sets the burst size for the round robin style queue of running jobs
-setmemory - sets avaible memory for jobs to use while running
-getmemory - retrieves the current system memory
-Step - advances the system x number of units - if the number of units to advance is larger than the set burst time it uses the set burst time if it is less it treats this lower number as the burst time. EX - if the burst time = 4 and you step 2, for that step the BT will be 2 but if you step 1- it will be 4 with the final burst being only 2
-run- advances the system until all jobs are finished
-printinfo, prints list of all directories, files, and programs along with their contents and memory locations
-Quit - ends program

None of these are case sensitive commands, names are validated upon entering as are commands, if either is invalid you will be prompted to reenter them.

