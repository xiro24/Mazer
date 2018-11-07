#README
BY: Simon Lay           

-- Mazer v2 --

To compile the program simply
type in: make
In the src directory and that should give you the compiled executable.

To run the program type in: './mazer'
Into the command prompt, then append it with any of the following commands

Note that the command to generate the maze is now based on two different
algorithms.
The following are:
    --gp      Generates a maze based on Prims's algorithm (random cell picked)
    --gr      Generates a maze based on Recursive backtrack (newest cell picked)

You can only generate or load the maze at a time, not both.

Note: width cannot be greater than height.

The following possible commands are (gr can be replaced with gp for prims):
    ./mazer --gr --sv example.svg
                --sb example.maze
    ./mazer --gr seed --sv example.svg
                     --sb example.maze
    ./mazer --gr seed width height --sv example.svg
                                   --sb example.maze
    ./mazer --gr width height --sv example.svg --sb example.maze
                              --sb example.maze --sv example.svg
    ./mazer --lb example.maze
    ./mazer --lb example.maze --sv example.svg
    ./mazer --lb example.maze --sv example.svg --sb example.maze
                              --sb example.maze --sv example.svg

    In summary most combinations involving generating the seed can be done
    by either including a seed and dimensions1 and dimensions2 or leaving it out.
    This will then generate a random seed to construct the maze and the seed can
    be used to obtain the maze again if wish to do so.

    The new implementation which allows a solution to the maze (--pm) should not
    be inserted in between the width and height.
     For example:
        ./mazer --gr width height --pm --sv example.svg --sb example.maze

        ./mazer --gr width height --sv example.svg --pm --sb example.maze

        ./mazer --gr width height --sv example.svg --pm --sb example.maze --pm

    Development:
    This is a major overhaul compared to A1, I've separated the classes to make
    them more modular and included polymorphism to reduce duplicate code for
    maze generation.

    I used a while loop for recursive as the assignment spec only specified that
    we only needed it to select the newest cell that was added as the head cell.

    I've decided to use a recursive version of the Maze Routing algorithm in the
    wikipedia page which is much more efficient when contrasted to the
    generation algorithms

    Polymorphism:
    Both Prim and Recursive inherit functions from the Growing Tree super class,
    this helps reduce the code both of these algorithms use to generate
    their maze.

    Custom Sets / template Sets
    I believe they follow the assignment spec.

    Bugs, Errors:
    I don't think there are any bugs. If there are then i may not of encountered
    the when i was using the application.

    Thank you for reading.
