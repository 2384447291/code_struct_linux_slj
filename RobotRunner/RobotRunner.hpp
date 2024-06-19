#ifndef ROBOTRUNNER_HPP
#define ROBOTRUNNER_CPP

#include <string>
#include "PeriodicTask.h"
#define MAX_FunctionNum 8
#define MAX_RobotPart 32

enum ModuleType
{
    MT_INPUT = 0,
    MT_OPERATOR,
    MT_OUTPUT,
    MT_LENGTH,
};

class RobotRunner;

class Robot_part;

class Module
{
    public:
        Module(ModuleType _type, Robot_part* _pOwner, void (Robot_part::*_function)(),std::string _name);
        void (Robot_part::*m_function)();
        Robot_part* m_pOwner;
        ModuleType m_type;
        std::string m_name;

        void run() { (m_pOwner->*m_function)(); }
};

class Robot_part
{
    public:
        Robot_part(RobotRunner* _pOwner,std::string _name);

        RobotRunner* m_pOwner;
        std::string m_name;

        void Add_Moudule(Module* _function);


        int Function_num = 0;
        Module* m_FunctionList[MAX_FunctionNum];

};

class RobotRunner : public PeriodicTask{
    public:    
        RobotRunner(PeriodicTaskManager* _taskManager, float _period, std::string _name):
        PeriodicTask( _taskManager, _period, _name),m_RobotPart{nullptr},m_FunctionList{nullptr}{}

        void init() override;
        void run() override;
        void cleanup() override;

        void Add_RobotPart(Robot_part* _part);

        int Function_num[MT_LENGTH] = {0};
        int Part_num = 0;
        Module* m_FunctionList[MT_LENGTH][MAX_FunctionNum];
        Robot_part* m_RobotPart[MAX_RobotPart];
};

#endif
