#include "main.h"
#include "exceptions.h"
#include "Rooms.h"
#include "hash.h"
#include "path.h"


void MakeRoomFromBot(std::string NameOfFile, RoomInMIPT & RoomFrom, RoomInMIPT & RoomTo, const AllMIPTHash & FullHashTable)
{
    std::ifstream FileInputFromBot;
    NameOfFile = NameOfFile + ".txt";
    FileInputFromBot.open(NameOfFile);
    
    std::string ClassFrom, ClassTo;
    std::string BuildingFrom, BuildingTo;
    std::string buff;
    
    //reading and checking is file correct
    FileInputFromBot >> BuildingFrom >> ClassFrom >> BuildingTo >> ClassTo;
    
    FileInputFromBot >> buff;
    if (buff != "")
        throw WrongReadFromFileException();
    if (ClassFrom == "")
        throw WrongReadFromFileException();
    if (ClassTo == "")
        throw WrongReadFromFileException();
    FileInputFromBot.close();
    
    //making correct RoomInMIPT Objects
    
    RoomInMIPT temporaryFrom(BuildingFrom, 0, ClassFrom), temporaryTo(BuildingTo, 0, ClassTo);
        
    temporaryFrom = FullHashTable.FindInBuildingHash(temporaryFrom);
    temporaryTo = FullHashTable.FindInBuildingHash(temporaryTo);

    RoomFrom = temporaryFrom;
    RoomTo = temporaryTo;
    
    RoomFrom.check_is_valuable_room();
    RoomTo.check_is_valuable_room();
};

void WriteAnswer(const std::string & NameOfFile, const AllMIPTHash & FullHashTable, const HashPaths & HashPath)
{
    std::fstream OutputFile;
    OutputFile.open("../output_from_Sonya.txt", std::ios::out);
    
    try{
        //making Room from and Room to
        RoomInMIPT RoomFrom, RoomTo;
        MakeRoomFromBot(NameOfFile, RoomFrom, RoomTo, FullHashTable);
      
        //make path
        Path MyPath(RoomFrom, RoomTo);
        MyPath.make_Path(FullHashTable, HashPath);
        
        //write path to file
        OutputFile << MyPath;
    }
    catch(WrongReadFromFileException &s)
    {
        OutputFile << s.what() << '\n';
    }
    catch(NotFoundInDataBaseException &s)
    {
        OutputFile << s.what() << '\n';
    }
    catch(NonvaluableBuildingException &s)
    {
        OutputFile << s.what() << " is non valuable building\n";
    }
    catch(CollisiousInHashException &s)
    {
        OutputFile << s.what() << '\n';
    }
    catch(NonvaluableRoomException &s)
    {
        OutputFile << s.what() << '\n';
    }
    catch(...)
    {
        OutputFile << "smth wrong\n";
    };
    OutputFile.close();
    
};

std::pair<const AllMIPTHash, const HashPaths> Initial()
{
    AllMIPTHash FullHashTable;
    InitialMakeHash(FullHashTable);
    
    HashPaths HashPath;
    make_hash_for_paths(HashPath);
    
    std::pair<const AllMIPTHash, const HashPaths> result(FullHashTable, HashPath);
    
    return result;
};

int main(){
    
    std::pair<const AllMIPTHash, const HashPaths> Hashes = Initial(); //this is need to be done only once, at the beginning of all script
    WriteAnswer("../file", Hashes.first, Hashes.second); //this is need to be done for every Path
    return 0;
}

