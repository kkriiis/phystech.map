#include <stdio.h>
#include <vector>
#include <filesystem>
#include <stdlib.h>
#include "path.h"
#include "Rooms.h"
#include "main.h"

void make_hash_for_paths(HashPaths & HashPath)
{
    std::pair<std::string, std::string> hashed;

    std::ifstream HashFile;
    HashFile.open("../DataBase/HASH/paths.txt");
    
    while(! HashFile.eof())
    {
        getline(HashFile, hashed.first);
        getline(HashFile, hashed.second);
        //HashPath.insert(HashPaths::value_type(hashed.first, hashed.second));
        HashPath[hashed.first] = hashed.second;
    }
    
    HashFile.close();
}

Path::Path(std::vector<RoomInMIPT> beginnings, std::vector<RoomInMIPT> endings, std::vector<std::string> result):
_beginnings{beginnings}, _endings{endings}, _result{result}
{};

Path::Path(RoomInMIPT & begin, RoomInMIPT & end)
{
    _beginnings.push_back(begin);
    _endings.push_back(end);
};

Path::Path(const Path & from)
{
    Path(from._beginnings, from._endings, from._result);
};

std::ostream & operator<< (std::ostream & stream, const Path & string)
{
    stream << "Go to ";
    for(auto it = 0; it <  string.get_sizes() - 1; ++it)
    {
        if (it != string.get_sizes() - 2)
        {
            if ((string._endings[it].compare(string._beginnings[it + 1]) == "section") || (string._endings[it].compare(string._beginnings[it + 1]) == "building"))
                stream << " -> ";
            else
            stream <<  " -> " << string._endings[it].get_number() << ' ';
        }
        else
            stream << " -> ";
        stream << string._result[it];
    }
    stream << " -> ";
    stream << string._endings[string._endings.size() - 1].get_number();
    
    return stream;
}

void Path::print()
{
    for(auto i: _result)
            std::cout<< i << '\n';
    
    for(auto i = 0; i < this -> get_sizes(); i++)
    {
        std::cout << _beginnings[i] << "->\n" << _endings[i] << '\n';
    }
}

int Path::get_sizes() const
{
    return (_beginnings.size() == _endings.size()) ? _endings.size() : 0;
}

void Path::make_Path(const AllMIPTHash & FullHashTable, const HashPaths & HashPath)
{
    
    //make paths between different buildings
    std::vector<RoomInMIPT> temp_begin = _beginnings;
    std::vector<RoomInMIPT> temp_end = _endings;
    int counter = 0;
    
    for (auto i = 0; i < temp_begin.size(); ++i)
    {
        if(temp_begin[i].compare(temp_end[i]) == "building")
            this -> buildings_path(FullHashTable);
    }
    
    //make paths between different sections
    temp_begin = _beginnings;
    temp_end = _endings;
    for (auto i = 0; i < temp_begin.size(); ++i)
    {
        if(temp_begin[i].compare(temp_end[i]) == "section")
            counter = this -> sections_path(FullHashTable, i + counter, HashPath);
    }
    
    //make paths between different rooms in same sections. This step ias need only for beginning and ending of all path.
    temp_begin = _beginnings;
    temp_end = _endings;
    counter = 0;
    
    for (auto i = 0; i < temp_begin.size(); ++i)
    {
        if(temp_begin[i].compare(temp_end[i]) == "room")
            counter = this -> rooms_path(FullHashTable, i + counter);
    }
    
};

void Path::buildings_path(const AllMIPTHash & FullHashTable)
{
    //make file for Chris
    
    RoomInMIPT from = _beginnings[0];
    RoomInMIPT to = _endings[0];
    
    std::fstream Sended;
    Sended.open("../input.txt", std::ios::out);
    
    std::ifstream MapFile;
    MapFile.open("../DataBase/PATHS/buildings.txt");
    
    std::string s;
    
    while (!MapFile.eof())
    {
        getline(MapFile, s, '\n');
        Sended << s << '\n';
    }
    Sended << from.get_building() << " " << to.get_building();
    
    Sended.close();
    MapFile.close();
    
    //speak with Chris
    
    system(".././to_Kris.sh");
    
    // get file with name like std::string NameOfFile
    
    std::string NameOfFile = "../output_from_Kris.txt";
    
    this -> change_buildings_path(FullHashTable, NameOfFile);
};

void Path::change_buildings_path(const AllMIPTHash & FullHashTable, std::string NameOfFile)
{
    std::ifstream InputFile;
    InputFile.open(NameOfFile);
    
    std::string from, to;
    std::string buff_name;
    RoomInMIPT buff;
    
    InputFile >> from;
    
    while(!InputFile.eof())
    {
        InputFile >> to;
        buff_name = "buf_" + from + "_" + to;
        
        //Make new end tail
        buff = RoomInMIPT(from, 0, buff_name);
        
        //Find in Hash
        buff = FullHashTable.FindInBuildingHash(buff);
        
        //write buffer as new end
        _endings.insert(_endings.end() - 1, buff);
        
        //Make new Begin Tail
        buff = RoomInMIPT(to, 0, buff_name);
        buff = FullHashTable.FindInBuildingHash(buff);
        _beginnings.insert( _beginnings.end(), buff);
        
        //write info about moving to result <- think about it
        _result.push_back("change building");
        
        //move pair (from, to)
        from = to;
    };
    
    InputFile.close();
}

int Path::sections_path(const AllMIPTHash & FullHashTable, int iterator, const HashPaths & HashPath)
{
    RoomInMIPT from = _beginnings[iterator];
    RoomInMIPT to = _endings[iterator];
    
    std::fstream Sended;
    Sended.open("../input.txt", std::ios::out);
    
    std::ifstream MapFile;
    MapFile.open("../DataBase/PATHS/" + from.get_building() + ".txt");
    
    std::string s;
    
    while (!MapFile.eof())
    {
        getline(MapFile, s, '\n');
        Sended << s << '\n';
    }
    Sended << from.get_section() << " " << to.get_section();
    
    Sended.close();
    MapFile.close();

    //speak with Chris
    
    system(".././to_Kris.sh");
    
    //read info from Chris
    
    std::string NameOfFile = "../output_from_Kris.txt";
    
    int counter = this -> change_sections_path(FullHashTable, NameOfFile, iterator, from.get_building(), HashPath);
    return counter;
    
}


int Path::change_sections_path(const AllMIPTHash & FullHashTable, std::string NameOfFile, int iterator, std::string building, const HashPaths & HashPath)
{
    std::ifstream InputFile;
    InputFile.open(NameOfFile);
    
    //read string1, string2
    int from, to;
    int temp_it = iterator;
    
    std::string buff_name;
    RoomInMIPT buff;
    
    InputFile >> from;
    
    while(!InputFile.eof())
    {
        InputFile >> to;
        buff_name = "buf_" + std::to_string(from) + "_" + std::to_string(to);
        
        //Make new end tail
        buff = RoomInMIPT(building, from, buff_name);
        
        //write buffer as new end
        _endings.insert(temp_it + _endings.begin(), buff);
        
        //Make new Begin Tail
        buff = RoomInMIPT(building, to, buff_name);
        
        //buff = FindInHash(FullHashTable, buff);
        _beginnings.insert( temp_it + 1 + _beginnings.begin(), buff);
        
        _result.insert(temp_it + _result.begin(), HashPath.at(buff_name));
        //_result.insert(temp_it + _result.begin(), "change section");
        temp_it ++;
        
        //move pair (from, to)
        from = to;
    };
    
    InputFile.close();
    return (temp_it - iterator);
}

int Path::rooms_path(const AllMIPTHash & FullHashTable, int iterator)
{
    RoomInMIPT from = _beginnings[iterator];
    RoomInMIPT to = _endings[iterator];
    
    std::fstream Sended;
    Sended.open("../input.txt", std::ios::out);
    
    std::ifstream MapFile;
    std::string name = "../DataBase/PATHS/" + from.get_building() + "/" + std::to_string(from.get_section()) +  ".txt";
    MapFile.open(name);
    
    std::string s;
    
    while (!MapFile.eof())
    {
        getline(MapFile, s, '\n');
        Sended << s << '\n';
    }
    Sended << from.get_number() << " " << to.get_number();
    
    Sended.close();
    MapFile.close();

    //speak with Chris
    
    system(".././to_Kris.sh");
    
    //read info from Chris
    std::string NameOfFile = "../output_from_Kris.txt";
    
    int counter = this -> change_rooms_path(FullHashTable, NameOfFile, iterator, from.get_building(), from.get_section());
    return counter;
}

int Path::change_rooms_path(const AllMIPTHash & FullHashTable, std::string NameOfFile, int iterator, std::string building, int section)
{
    std::ifstream InputFile;
    InputFile.open(NameOfFile);
    int temp_it = iterator;
    
    std::string from;
    RoomInMIPT next_room;
    
    InputFile >> from; // skip first room
    InputFile >> from;
    
    while(!InputFile.eof())
    {
        //Make new tails pair
        next_room = RoomInMIPT(building, section, from);

        //Find in Hash
        next_room = FullHashTable.FindInBuildingHash(next_room);
        
        //write buffer as new end
        _endings.insert(temp_it + _endings.begin(), next_room);
        //and as beginning
        _beginnings.insert( temp_it + 1 + _beginnings.begin(), next_room);
        
        _result.insert(temp_it + _result.begin(), "");
        
        temp_it ++;
        InputFile >> from;
    };
    
    //this -> print();
    
    InputFile.close();
    return temp_it - iterator;
}
