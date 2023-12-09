Trimble Ag Programming Challenge - Flatland


Functionality:

    Read an input file, decode the data and create particles and areas in different shapes.
    Generate notifications on the standard output when a particle has entered or has left an area.
    Also write the result into an output file.
    The output is formatted:
        ENTER <time> <particle name> <area name>
        EXIT <time> <particle name> <area name>


Methods:
    
    Used a Flatland class to represent a flat land with areas and particles.
    Used a Particle class to represent a particle with a particle name and a trajectory.
    Used a Shape class as an interface, derived by Rectanle, Triangle, Circle and Polygon class.

    To evaluate the particle inside or outside of the CIRCLE area:
        Calculate distance between particle and circle center. 
        Evaluate the particle as inside of the area if the distance equal to or less than radius.

    To evaluate the particle inside or outside of the TRIANGLE, RECTANGLE, POLYGON areas:
        Cast a horizontal ray from a particle, calculate the number of intersections between the ray and every size of the area.
        Evaluate the particle as inside of the area if the number of intersections is odd, or if the particle is on the side of area.


Program Files:

    This program is written in C++, consists of:

    Code files:
        main.cpp
        Flatland.h
        Flatland.cpp
        Shape.h
        Shape.cpp
        Particle.h
        Particle.cpp
    Notes:
        readme.txt
    Executable files:
        main_win.exe (for Windows)
        main_linux (for Ubuntu)


Usage:
    
    This program has been tested both on Windows10 and Ubuntu22.04.

    On Windows
        Use command: 
                    .\main_win.exe path_to_input_file
        to run the program, for example: 
                    .\main_win.exe examples\input\test1.txt
        
        Use command: 
                    g++ -o main_win main.cpp Flatland.cpp Shape.cpp Particle.cpp
        to build the program.
    
    On Linux(Ubuntu)
        Use command: 
                    ./main_linux path_to_input_file
        to run the program, for example: 
                    ./main_linux examples/input/test1.txt

        Use command: 
                    g++ -o main_linux main.cpp Flatland.cpp Shape.cpp Particle.cpp
        to build the program.