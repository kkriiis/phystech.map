#include <fstream>
#include "Rooms.h"
#include "exceptions.h"

RoomInMIPT::RoomInMIPT(std::string building, int section, std::string number):
_number{number},
_building{building},
_section{section}
{};

RoomInMIPT::RoomInMIPT(const RoomInMIPT & from):
_number{from._number},
_building{from._building},
_section{from._section}
{};

void RoomInMIPT::PrintInfo()
{
    std :: cout << '\n' << this -> _building << '\n' << (this -> _section)/10 << " floor, " << this ->_number << "room\n";
}

std::ostream & operator<< (std::ostream & stream, const RoomInMIPT & room)
{
    stream << '\n' << room._building << '\n' << room._section << " " << room._number <<'\n';
    return stream;
}

bool operator== (const RoomInMIPT & lhs, const RoomInMIPT & rhs)
{
    if (lhs._building != rhs._building)
    {
        return false;
    }
    if (lhs._number != rhs._number)
        return false;
    return true;
}

std::string RoomInMIPT::compare(const RoomInMIPT & compared) const
{
    if (_building != compared._building)     
    {
        return "building";
    } //BAD!! MAYBE EXCEPTIONS LATER
    if (_section != compared._section)
        return "section";
    if (_number != compared._number)
        return "room";
    return "equal";
}

RoomInMIPT & RoomInMIPT::operator= (const RoomInMIPT & other)
{
    if (this == &other)
        return *this;
    _number = other._number;
    _building = other._building;
    _section = other._section;
    return *this;
}

void RoomInMIPT::check_is_valuable_room()
{
    std::string section = std::to_string(_section);
    std::string string;
    string  = "buildings";
    this -> find_in_DataBase(string ,_building);
    string = _building;
    this -> find_in_DataBase(string ,section);
    string = _building  + "/" +  section;
    this -> find_in_DataBase(string, _number);
}

void RoomInMIPT::find_in_DataBase(std::string & NameOfFile, std::string & ObjectToFind)
{
    std::ifstream CheckFile;
    CheckFile.open("../DataBase/LISTS/" + NameOfFile + ".txt");
    
    std::string Compared;
    int flag = 0;
    while (!CheckFile.eof() && !flag){
        getline(CheckFile, Compared, '\n');
        if (ObjectToFind == Compared)
            flag = 1;
    }
    CheckFile.close();
    if(flag == 0)
        throw NotFoundInDataBaseException(ObjectToFind);
}


std::string RoomInMIPT::get_number() const
{
    return _number;
}

int RoomInMIPT::get_section() const
{
    return _section;
}

std::string RoomInMIPT::get_building() const
{
    return _building;
}







