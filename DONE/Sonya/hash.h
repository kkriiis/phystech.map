#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_set>
#include "Rooms.h"
#pragma once

template <typename T>
class Hash {
public:
    size_t operator()(const T &s) const
    {
        size_t h1 = std::hash<std::string>{}(s.get_number());
        size_t h2 = std::hash<std::string>{}(s.get_building());
        return h1 ^ ( h2 << 1 );
    }
};

typedef std::unordered_set<RoomInMIPT, Hash<RoomInMIPT> > HashSet;

class AllMIPTHash {
private:
    std::vector<HashSet> Hashes;
    std::vector<std::string> buildings;
public:
    AllMIPTHash() = default;
    ~AllMIPTHash() = default;
    void HashAppend(std::string BuildingToAppend, HashSet & HashToAppend);
    bool HashRemove(std::string BuildingToRemove, HashSet & HashToRemove);
    RoomInMIPT FindInBuildingHash(const RoomInMIPT & RoomToFind) const;
    
    void print_Hash(int iterator); //print HashSet for element of AllMIPTHash[iterator]
};

void InitialMakeHash(AllMIPTHash & HashTable);

void MakeHashForBuilding(const std::string & building, AllMIPTHash & HashTable);

void MakeHashForSection(int &section, int &counter,const std::string & building,  std::ifstream & FileFrom, HashSet & HashArray);




