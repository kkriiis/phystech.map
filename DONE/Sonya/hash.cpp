#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <unordered_set>
#include "exceptions.h"
#include "hash.h"

void AllMIPTHash::HashAppend(std::string BuildingToAppend, HashSet & HashToAppend){
    Hashes.push_back(HashToAppend);
    buildings.push_back(BuildingToAppend);
}

bool  AllMIPTHash::HashRemove(std::string BuildingToRemove, HashSet & HashToRemove){
    int flag = 0;
    
    std::vector<std::string>::iterator BuildIt = find(buildings.begin(), buildings.end(), BuildingToRemove);
    if(BuildIt != buildings.end())
    {
        buildings.erase(BuildIt);
        flag ++;
        
        std::vector<HashSet>::iterator HashIt = find(Hashes.begin(), Hashes.end(), HashToRemove);
        if ((HashIt != Hashes.end()) && (flag == 1))
        {
            Hashes.erase(HashIt);
            flag ++;
        }
    }
    return (flag == 2)?true:false;
}

RoomInMIPT AllMIPTHash::FindInBuildingHash(const RoomInMIPT & RoomToFind) const
{
    
    std::string building = RoomToFind.get_building();
    
    auto CurrenBuildingHashTableIt = find(buildings.begin(), buildings.end(), building);
    
    if (CurrenBuildingHashTableIt == buildings.end())
        throw NonvaluableBuildingException (building);
    
    std::size_t CurrentHashTableIt = CurrenBuildingHashTableIt - buildings.begin();
    
    HashSet HashTable = *(Hashes.begin() + CurrentHashTableIt);
    
    auto NumberOfFoundedRoom = HashTable.count(RoomToFind);
    
    if (NumberOfFoundedRoom == 0)
        throw NonvaluableRoomException (building + ", " + RoomToFind.get_number());
    if (NumberOfFoundedRoom > 1)
        throw CollisiousInHashException (building + ", " + RoomToFind.get_number());

    auto FoundedRoomIt = HashTable.find(RoomToFind);

    return *(FoundedRoomIt);
}

void AllMIPTHash::print_Hash(int iterator)
{
    for(auto i = 0; i <  Hashes[iterator].bucket_count(); ++i)
    {
        std::cout<< "bucket #"<< i << "contains:";
            for(auto local_it = Hashes[iterator].begin(i); local_it != Hashes[iterator].end(i) ; ++local_it)
                std::cout << "\n" << *local_it;
        std::cout<< std::endl;
    }
}

void InitialMakeHash(AllMIPTHash & HashTable){
    std::ifstream BuildingList;
    BuildingList.open("../DataBase/LISTS/buildings.txt");
    
    std::string building;
    while(!BuildingList.eof())
    {
        getline(BuildingList, building, '\n');
        MakeHashForBuilding(building, HashTable);
    }
};

void MakeHashForBuilding(const std::string & building, AllMIPTHash & HashTable){
    
    std::ofstream FileHash;
    FileHash.open( "../DataBase/HASH/" + building + "_hash.txt", std::ios::out);
    
    //find init_hash_building file
    
    std::ifstream FileFrom;
    FileFrom.open("../DataBase/HASH/hash_init_" + building + ".txt");
    if(!FileFrom.is_open())
      throw NotFoundInDataBaseException (building);
       
    HashSet HashArray;
    
    while (!FileFrom.eof())
    {
        int section, counter = 0;
        FileFrom >> section >> counter;
        if (counter == 0)
            throw NonvaluableSectionException(std::to_string(section));
        MakeHashForSection(section, counter, building, FileFrom, HashArray);
    }
    
    FileFrom.close();
    
    FileHash << HashArray.size() << '\n';
    for (auto i: HashArray){
        FileHash << i << '\n';
    }
    FileHash.close();
    
    HashTable.HashAppend(building, HashArray);
};

void MakeHashForSection(int &section, int &counter, const  std::string & building,  std::ifstream & FileFrom, HashSet & HashArray){
    
    std::string CurrentRoom;
    int key;
    for (auto i = 0; i < counter; ++i){
        
        FileFrom >> CurrentRoom;
        
        RoomInMIPT Hashed(building, section, CurrentRoom);
        HashArray.insert(Hashed);
        
    }
};




