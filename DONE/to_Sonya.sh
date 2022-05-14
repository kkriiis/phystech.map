#!/bin/bash
cd Sonya
g++ main.cpp hash.cpp Rooms.cpp path.cpp exceptions.cpp -o test -std=c++17
./test

