all: compile link

compile:
	g++ -Wall -std=gnu++14 -fexceptions -DGLFW_DLL -DSTB_IMAGE_IMPLEMENTATION -g -std=gnu++14 -IC:\MinGW\include -c main.cpp

link: 
	g++ main.o -o main -LC:\MinGW\lib  -lglfw3 -lopengl32 -lgdi32  C:\MinGW\lib\libglfw3.a C:\MinGW\lib\libglfw3dll.a C:\MinGW\lib\libopengl32.a
