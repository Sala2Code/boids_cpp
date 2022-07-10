# boids_cpp
Simple Boids using SFML (C++)


## TLDR;

main.cpp is the whole code.
serf.hpp is where there are variables. So to change the behaviour of boids you must to do here.
In main.cpp change the path of serf.hpp. For me, it's the same as SFML.

![2022-07-10 17-33-46](https://user-images.githubusercontent.com/109032171/178151668-36afaa0a-cbec-44af-bbbb-87f600e6bd55.gif)


## YouTube

This is a video where I wrote the code.
Thanks if you come !
Channel : https://www.youtube.com/channel/UCcEkxe69YprtYS2dDW7w5-Q ;

### More info

There are 2 versions : the V1 (main_1.cpp) and the V2 (main.cpp)

The V1 is with border, no generation (only those from start, stay) and the starting is that all boids are in a "grid" with an random angle viewing.
To use the V1, just rename to "main.cpp"

The V2 is a horizontal moving, without border and generation. You can choose the max of boids.

To use the project, install all .dll and makefile. Then in Vscode you can run writting "make" and to launch th .exe whether you click on the .exe or you write ./main.exe
In serf.hpp you can modify the behaviour of boids.
Boids are named "serf". 

My SFML is in "C:/librairies" so if you want use the makefile to run easily you must change the path.
