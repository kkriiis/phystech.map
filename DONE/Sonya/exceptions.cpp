#include <iostream>
#include <string>
#include <ctime>
#include "exceptions.h"


//EXCEPTIONS

std::string Exception::what(){
    return _msg;
};

std::string Exception::call() const{
    return _msg;
}

std::string WrongReadFromFileException::what()
{
    _msg += " wrong read from file\n";
    return _msg;
};

std::string NonvaluableBuildingException::what()
{
    _msg += " no such building\n";
    return _msg;
};

std::string NonvaluableSectionException::what()
{
    _msg += " no such section\n";
    return _msg;
};

std::string NonvaluableRoomException::what()
{
    _msg += " no such room\n";
    return _msg;
};

std::string NotFoundInDataBaseException::what()
{
    _msg += " not found in DataBase\n";
    return _msg;
};

std::string CollisiousInHashException::what()
{
    _msg += " Collisious In Hash\n";
    return _msg;
};


Exception::Exception(std::string msg): _msg{msg} {};

NotFoundInDataBaseException::NotFoundInDataBaseException(std::string msg): Exception{msg} {};

WrongReadFromFileException::WrongReadFromFileException(std::string msg):  Exception{msg} {};

NonvaluableBuildingException::NonvaluableBuildingException(std::string msg):  Exception{msg} {};

NonvaluableSectionException::NonvaluableSectionException(std::string msg): Exception{msg} {};

NonvaluableRoomException::NonvaluableRoomException(std::string msg): Exception{msg} {};

CollisiousInHashException::CollisiousInHashException(std::string msg): Exception{msg} {};
