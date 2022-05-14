#pragma once

class Exception{
protected:
    std::string _msg;
public:
    Exception(std::string msg);
    virtual ~Exception() = default;
    virtual std::string what();
    std::string call() const;
};


class WrongReadFromFileException : public Exception{
private:
    std::string _msg;
public:
    WrongReadFromFileException(std::string msg = "Wrong Read From File");
    virtual std::string what() override;
};

class NotFoundInDataBaseException : public Exception{
private:
    std::string _msg;
public:
    NotFoundInDataBaseException(std::string msg = "Not Found In DataBase");
    virtual std::string what() override;
};

class CollisiousInHashException : public Exception{
private:
    std::string _msg;
public:
    CollisiousInHashException(std::string msg = "Collisious In Hash");
    virtual std::string what() override;
};


class NonvaluableBuildingException : public Exception{
private:
    std::string _msg;
public:
    NonvaluableBuildingException (std::string msg = "Nonvaluable Building");
    virtual std::string what() override;
};

class NonvaluableSectionException : public Exception{
private:
    std::string _msg;
public:
    NonvaluableSectionException(std::string msg = "Nonvaluable Section");
    virtual std::string what() override;
};

class NonvaluableRoomException : public Exception{
private:
    std::string _msg;
public:
    NonvaluableRoomException(std::string msg = "Nonvaluable Room");
    virtual std::string what() override;
};
