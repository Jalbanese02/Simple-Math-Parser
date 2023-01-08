My own attempt at making a math parser. It uses a recursive approach in dissecting a given string into elementary values and operations, and then
evaluates the expression recursively. It is currently very simple, and has some issues, but I will improve it once I have the time to do so.
In the future it will have functions, and many more special operators. The program is supposed to be wrapped to other programs, so it will not have
a user interface by itself. (Other programs pass math expressions as strings into it and receive the result as a number)

It currently has a very simple interface for testing purposes. Compile the file and use it as

./name-of-the-executeable "2+2"

to evaluate the expression "2+2".
