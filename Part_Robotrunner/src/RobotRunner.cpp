#include "RobotRunner.hpp"
#include <iostream>
#include <vector>

bool RobotRunner::IsInstantiated = false;
RobotRunner* RobotRunner::instance = nullptr;

void RobotRunner::Add_Module(BaseModule* _function)
{
    Module_table[_function->m_type].push_back(_function);
}

void RobotRunner::Add_RobotPart(Robot_part* _part)
{
    Robot_part_hashmap[_part->m_name] = _part;
}

void RobotRunner::Add_Controller(RobotController* _controller)
{
    Robot_controller_hashmap[_controller->m_name] = _controller;
}

void RobotRunner::Print_RobotPart()
{
    for(auto it = Robot_part_hashmap.begin(); it != Robot_part_hashmap.end(); ++it)
    {
        std::cout << it->first << std::endl;
    }
}

void RobotRunner::Print_Controller()
{
    for(auto it = Robot_controller_hashmap.begin(); it != Robot_controller_hashmap.end(); ++it)
    {
        std::cout << it->first << std::endl;
    }
}
void RobotRunner::Print_Module()
{
    for(int i = 0; i < MT_LENGTH; ++i)
    {
        if(i == 0)
        {
            std::cout << "共注册了" << Module_table[i].size() << "个传感器函数,分别为：" << std::endl;           
        }
        else if(i == 1)
        {
            std::cout << "共注册了" << Module_table[i].size() << "个控制器函数,分别为：" << std::endl;      
        }
        else if(i == 2)
        {
            std::cout << "共注册了" << Module_table[i].size() << "个执行器函数,分别为：" << std::endl;      
        }

        for(int j = 0; j < Module_table[i].size(); ++j)
        {
            std::cout << Module_table[i][j]->m_name << "  ";
        }
        std::cout << std::endl;   
    }
}

BaseModule* RobotRunner::Get_Module(std::string _name)
{
    for(int i = 0; i < MT_LENGTH; ++i)
    {
        for(int j = 0; j < Module_table[i].size(); ++j)
        {
            if(Module_table[i][j]->m_name == _name)
            {
                return Module_table[i][j];
            }
        }
    }
    std::cout << stderr << "no moodule named "<< _name << std::endl;
    Print_Module();
    return nullptr;
}

RobotController* RobotRunner::Get_Controller(std::string _name)
{
    return Robot_controller_hashmap[_name];
}

Robot_part* RobotRunner::Get_RobotPart(std::string _name)
{
    return Robot_part_hashmap[_name];
}

void RobotRunner::run()
{
    //按顺序执行
    for(int i = 0; i < MT_LENGTH; ++i)
    {
        for(int j = 0; j < Module_table[i].size(); ++j)
        {
            BaseModule* _moudule = Module_table[i][j];
            _moudule->run();
        }
    }
}
void RobotRunner::init()
{
    //遍历Robot_controller_hashmap
    for(auto it = Robot_controller_hashmap.begin(); it != Robot_controller_hashmap.end(); ++it)
    {
        it->second->init();
    }
}

void RobotRunner::cleanup()
{}