#include <fstream>
#include <stdio.h>
#include "Rooms.h"
#include "hash.h"
#include "path.h"
#pragma once

void MakeRoomFromBot(std::string NameOfFile, RoomInMIPT & RoomFrom, RoomInMIPT & RoomTo, const AllMIPTHash & FullHashTable); // Read info from Bot and make correct RoomInMIPT objects

std::pair<const AllMIPTHash, const HashPaths> Initial();     //need for making Hash Sets

void WriteAnswer(const std::string & NameOfFile, const AllMIPTHash & FullHashTable, const HashPaths & HashPath);  //main function, which speaks with Boris

