#include "RobotRunner.hpp"
#include <iostream>
#include <vector>
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
        std::cout << i << std::endl;
        for(int j = 0; j < Module_table[i].size(); ++j)
        {
            std::cout << Module_table[i][j]->m_name << std::endl;
        }
    }
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