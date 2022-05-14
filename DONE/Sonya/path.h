#include <vector>
#include <stdio.h>
#include <unordered_map>
#include "Rooms.h"
#include "hash.h"
#pragma once


typedef std::unordered_map< std::string, std::string> HashPaths;
void make_hash_for_paths (HashPaths & HashPath);

class Path{
private:
    std::vector<RoomInMIPT> _beginnings;
    std::vector<RoomInMIPT> _endings;
    std::vector<std::string> _result;
public:
    Path() = default;
    Path(std::vector<RoomInMIPT> beginnings, std::vector<RoomInMIPT> endings, std::vector<std::string> result);
    Path(RoomInMIPT & begin, RoomInMIPT & end);
    Path(const Path & from);
    ~Path() = default;
    
    friend std::ostream & operator<< (std::ostream & stream, const Path & string); //used for print to output file
    void print(); //print all structure of Path

    int get_sizes() const;
    
    void make_Path(const AllMIPTHash & FullHashTable, const HashPaths & HashPath);
    
    void buildings_path(const AllMIPTHash & FullHashTable); //will be called only once for one Path
    int sections_path(const AllMIPTHash & FullHashTable, int iterator, const HashPaths & HashPath); //return number of added elements.The same meaning for the following
    int rooms_path(const AllMIPTHash & FullHashTable, int iterator);
    
    void change_buildings_path(const AllMIPTHash & HashTable, std::string NameOfFile);
    int change_sections_path(const AllMIPTHash & HashTable, std::string NameOfFile, int iterator, std::string building, const HashPaths & HashPath);
    int change_rooms_path(const AllMIPTHash & HashTable, std::string NameOfFile, int iterator, std::string building, int section);
    
};
