# CubeMania 3D OpenGL Game
A 3D minecraft-like game in C++,using openGL and glut library.

The game was developed by me and Ioannis Schoinochoritis,both undergraduate students at the computer science and engineering department of University of Ioannina.

# Synopsis
Goal of the game is to gather points and increase the score building,destroying,climbing,collapsing and kicking cubes inside the grid.The player starts at the center of the grid whose size is defined by the player at the start of the game.The player starts with 3 HP and 50 score.The game supports first person and third person view.

![Alt text](https://github.com/koukouzasg/CubeMania/blob/master/firstPersonView.png "FirstPerson Preview")

Unlike mincecraft there are some rules.The player controls our beloved cubeBOT which is able to draw power from the cube that is standing on and changes the color of the cube while increasing the player stock.
**BEWARE**
You can lose HP if you fall of the grid and if playerScore is 0.PlayerScore is decreased everytime cubeBOT descends a level or building a cube.


# Installation
To run and play the game, OpenGL is necessary. In Ubuntu 16.04LTS you will need to follow the next steps in order to install the OpenGL and play the game.

    sudo apt-get install build-essential
    sudo apt-get install freeglut3 freeglut3-dev
Download the library from http://www.rpmseek.com/rpm-pl/libglui2c2.html?hl=com&cs=libgcc1:RE:0:0:0:0:2420 according to your system. Then use sudo dpkg -i to install it. IF you are against errors about depedencies, please run sudo apt-get -f install. Then run sudo dpkg -i again and it should be just fine.

# Compiling
compiling using the make file
Open a terminal and type :  make cubeMania
Or you can type : g++ -o cubeMania cubeMania.cpp -lglut -lGLU -lGL               

Type : ./cubeMania

Now you should be able to play the game! Happy cubing people!Take care of cubeBOT. :)

![Alt text](https://github.com/koukouzasg/CubeMania/blob/master/thirdPersonView.png "ThirdPerson Preview")

# How to Play
-   W,w : Move forward and climb cubes
-   D,d : Turn Right.
-   A,a : Turn left.
-   S,s : Turn 180 degrees.
-   Q,q : Destroy cube.
-   Spacebar : Increase playerStock,lose 5 points,change color.If color is blue you cant draw  any more.
-   E,e : Delete the column in front of you,including the ground cube creating a hole in the grid.Lose 20 points
-   R,r : Collapse all the cubes that float in the air.While the cubes are falling cubeBOT cant move.Gain 10 points.
-   Left-click : Build a cube.Gain 5 points lose one stock.
-   Right-click : Kick a cube and all the other cubes in the same line until they reach the edge of the grid.
-   V,v : Switch to thirdPerson view.
-   C,c : Switch to firstPerson view.
-   Escape : Exit the game.

# Contact
Please feel free to contact me for any details-specifications you want in koukouzasg@hotmail.gr .
