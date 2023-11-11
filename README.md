# One Tough Puzzle

## "Over *300,000* wrong ways to assemble the pieces, but only *One* right way! This is truly... One Tough Puzzle!"

### Background:

I found this puzzle in my mom's house a couple of weeks ago with a rather 
daunting title: One Tough Puzzle. The box says it was developed by the Great
American Puzzle Factory and after looking it up, I found that its production 
has been discontinued. However, the schtick of the thing is that the puzzle has 
only nine red, nearly identical, four-sided pieces, and every piece has some 
combination of some or all of the four types of faces: a spade, club, diamond, 
or a heart. Last, every piece is constructed such that two of its faces point 
out and two of its faces point in.

The rules are also simple. Connect every piece into a three by three grid. If it's 
been made correctly, the box says that grid's sides should have exactly six faces 
pointing out and six faces pointing in. No other instruction is provided. 

The tag line, quoted at the top of that ReadMe, says it all. The problem is deceptively
simple, but is definitely in NP, not that I've proved it. If you don't know what that
means, that's fine. Basically, it's mathematically hard.

So I built an algorithm to solve it, optimizing things all over the place in order to
try and build a solution as quickly as possible. To make it more interesting (though 
its a natural place to go), the algorithm I built actually extends any n by n puzzle, 
so feel free to make a larger one.

From what I can figure, anything over five by five would be pretty impossible for any human
to do. I haven't done the total calculations, but we're talking int the quadrillions of 
possibilites. This, of course, is where this algorithm *shines*. 


![Alt text](https://camo.githubusercontent.com/39b05d8cdf9c3548d5866610e36c5b1b16e2175578f38acec873c78a689eabbe/68747470733a2f2f7261772e6769746875622e636f6d2f646f756764726f7065722f70757a7a6c652f617474656d70745f322f70757a7a6c652e706e67)

### How to use:

1. You can download the whole project into any empty folder. 
2. From there, you can compile it by typing "make" into your command line from the folder in use.
3. Then, create a file called pieces.txt and put it in the folder as well. 
    a. Starting on the first line, write the faces on each piece into each new line, with a single
       space between each face.  
    b. We do this by first converting each face type into a number: spade = 0, club = 1; diamond = 2,
       and hearts = 3. We will write these numbers down onto the .txt file.
    c. Ordering also matters. Orient each piece such that one of its outward facing sides points up
       and the other one points to the right. In other words, look at the photo linked above, rotate
       any of those pieces clockwise by 90 degrees. Make your pieces look like that. Now, consider the
       top-facing side as the first face (index 0) and index clockwise.
    d. This should leave you with a pieces.txt file that looks something like this:  
        0 0 3 1  
        2 1 1 2  
        3 2 1 1  
        3 2 2 3  
        1 3 0 3  
        1 3 2 1  
        0 2 0 3  
        3 0 0 1  
        0 2 3 2  
5. Last, run the algorithm by typing ./otp_solver in the command line. This will output a solution.txt
   file into your folder that contains the answer. It should look something like this:  
    Note: Parenthesized numbers describe the right-pointing face index.  
    This is the solution:  
    8(1) 5(0) 2(0)  
    7(1) 4(0) 1(0)  
    6(1) 3(0) 0(0)  
6. And that's it! To clear the compiled code and .o files, type "make clean". 
