This repository is meant to document my progress on a rubiks cube emulator. The code is my code, written from scratch, using the C++ std library. I compile using g++. So far the goals of this project are as follows:

1.  Get more comfortable with C++
2.  Get comfortable with graphics in C++
3.  Build an intuition for finite group theory
4.  Build an intuition for God's algorithm (https://en.wikipedia.org/wiki/Optimal_solutions_for_the_Rubik%27s_Cube)

Right now, the code successfully emulates a rubiks cube through the *RuboidCuboid* object, supporting CCW and CW rotation of faces. However, it is not very intuitive, as the only way to see the cube state is through ascii printouts as below:

*
RuboidCuboid rubecube = RuboidCuboid();
rubecube.printCube();

    000
    000
    000
111 222 333 444 
111 222 333 444 
111 222 333 444 
    555
    555
    555

rubecube.rotate(W,true);
rubecube.rotate(G,true);
rubecube.rotate(R,true);
rubecube.rotate(Y,true);
rubecube.printCube();

    003
    004
    234
440 220 555 133 
110 220 332 544 
223 332 544 110 
    554
    551
    111
*

Future steps on this project are as follows:

1. Implement a GUI complete with intuitive 3d spatial rotations of the cube, and maube face rotation animations even a simple shader.
2. Implement an algorithm for solving the rubik's cube using a meet in the middle approach.