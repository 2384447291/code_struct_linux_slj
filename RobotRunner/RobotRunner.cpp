#include "RobotRunner.hpp"
Module::Module(ModuleType _type, Robot_part* _pOwner, void (Robot_part::*_function)(),std::string _name)
    : m_function(_function),
    m_pOwner(_pOwner), 
    m_type(_type),
    m_name(_name)
    {
        _pOwner->Add_Moudule(this);
    }

Robot_part::Robot_part(RobotRunner* _pOwner,std::string _name)
    :m_pOwner(_pOwner), 
    m_name(_name),
    m_FunctionList{nullptr}
    {
        _pOwner->Add_RobotPart(this);
    }

void Robot_part::Add_Moudule(Module* _function)
{
    //加入到robot_part
    m_FunctionList[Function_num] = _function;
    Function_num++;
    //加入到RobotRunner
    int _id = m_pOwner->Function_num[_function->m_type];
    m_pOwner->m_FunctionList[_function->m_type][_id] = _function;
    m_pOwner->Function_num[_function->m_type]++;
}

void RobotRunner::Add_RobotPart(Robot_part* _part)
{
    m_RobotPart[Part_num] = _part;
    Part_num++;
}

void RobotRunner::run()
{
    //传感器函数优先执行
    for(int i = 0; i < Function_num[MT_INPUT]; ++i)
    {
        Module* _moudule = m_FunctionList[MT_INPUT][i];
        _moudule->run();
    }

}

void RobotRunner::init()
{
    
}

void RobotRunner::cleanup()
{
    
}