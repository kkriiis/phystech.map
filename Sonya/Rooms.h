#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_set>
#pragma once

class RoomInMIPT
{
private:
    std::string _number;
    std::string _building;
    int _section;
public:
    RoomInMIPT(std::string building = "", int section = 0, std::string number = "");
    RoomInMIPT(const RoomInMIPT & from);
    ~RoomInMIPT() = default;
    
    void PrintInfo();
    
    friend std::ostream & operator<< (std::ostream & stream, const RoomInMIPT & string);
    
    RoomInMIPT & operator= (const RoomInMIPT & other);

    // == operator is used ONLY FOR HASH. If you need compare Rooms, use compare()
    friend bool operator== (const RoomInMIPT & lhs, const RoomInMIPT & rhs);
    std::string compare(const RoomInMIPT & other) const;
    
    void check_is_valuable_room();
    void find_in_DataBase(std::string & NameOfFile, std::string & ObjectToFind);
    
    std::string get_number() const;
    int get_section() const;
    std::string get_building() const;
    
};

