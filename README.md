# LC-3-Emulator:
understanding computer architecture ? Let's emulate one

## Resources:
- https://www.cs.utexas.edu/users/fussell/courses/cs310h/lectures/Lecture_10-310h.pdf
- https://www.jmeiners.com/lc3-vm/#-lc3.c-block-99
- https://www.youtube.com/watch?v=CDO28Esqmcg&list=PLhwVAYxlh5dvB1MkZrcRZy6x_a2yORNAu
- https://jupyter.brynmawr.edu/services/public/dblank/CS240%20Computer%20Organization/2015-Fall/Notes/LC-3%20I-O.ipynb
- https://www.cs.unca.edu/~brock/classes/Spring2009/ece109/Lectures/Examples
- https://wchargin.com/lc3web/
## Usage:
### Build:
- Simply have any C compiler (makefile has gcc), and use
```
    make
```
- Running in default Mode:
```
    ./lc3Vm examples/Image
```

- Running in Debug Mode:
```
    ./lc3Vm -d examples/Image ;; you can step by pressing any key
```
### Running Programs ? How ?:
- In the example folder you'll find rogue and 2048 games I downloaded from:
>> [LC3Vm-HowTo](https://www.jmeiners.com/lc3-vm/#-lc3.c-block-99)
- Also, you can find the 'Image' that I wrote and compiled inside:
>> [lc3Emulator](https://wchargin.com/lc3web/)
- I would encourage you to write your own programs and test maybe you can find some bugs ...
### Looks cool How can I make one ?:
- The pdf inside the repo has all the specific details you need to know to make this, test with the emulator and if you get stuck you can go for the tutorial (I don't advise you to go full into tutorials without testing your limits).
## Progress:
**Implemented => X**  
**Unused => //**  
[X] op_BR  
[X] op_ADD  
[X] op_LD  
[X] op_ST  
[X] op_JSR  
[X] op_AND  
[X] op_LDR  
[X] op_STR  
[//] op_RTI  
[X] op_NOT  
[X] op_LDI  
[X] op_STI  
[X] op_JMP  
[//] op_RES  
[X] op_LEA  
[X] op_TRAP  
