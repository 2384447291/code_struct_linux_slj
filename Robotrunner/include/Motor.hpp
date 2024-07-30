#ifndef MOTOR_HPP
#define MOTOR_HPP
#include "RobotRunner.hpp"

class Motor : public Robot_part
{
public:
    Motor(std::string _name):
        Robot_part(_name),
        motor_fdb_update(MT_SENSOR, this, &Motor::fdb_update, _name + "get_fdb"),
        motor_control_set(MT_ACTUATOR, this, &Motor::control, _name + "control_set")
    {};

    //电机反馈更新和电机控制的核心组件函数
    Module<Motor> motor_fdb_update;
    Module<Motor> motor_control_set;

    virtual void fdb_update() = 0;
    virtual void control() = 0;
};

#endif
