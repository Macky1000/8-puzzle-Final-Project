# 8-puzzle-Final-Project
## How to run

To run the program, navagate to the file and input these commands to the terminal:
```
g++ .\8puzzle.cpp
.\a.exe
```

## Change input

To change the input for the program, go to input.txt and input the desired puzzle in this format:

```
<tile> <tile> <tile>
<tile> <tile> <tile>
<tile> <tile> <tile>
```

Each `tile` is a digit from 0 to 8. Do note the program is not guaranteed to give the correct solution for a puzzle that is incorrect or unsolvable such as:

```
0 0 0      1 3 2
0 0 0  or  8 0 4
0 0 0      7 6 5
```
