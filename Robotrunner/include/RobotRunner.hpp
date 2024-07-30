#ifndef ROBOTRUNNER_HPP
#define ROBOTRUNNER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "PeriodicTask.hpp"

class Robot_part;
class BaseModule;
class RobotController;
class RobotRunner : public PeriodicTask{
    public:    
        static RobotRunner* Instance(){ return instance; }
        RobotRunner(RobotRunner* _instance):
        PeriodicTask(0.001,"robotrunner",100,sched_get_priority_max(SCHED_FIFO),SCHED_FIFO)
        {
            if(!IsInstantiated)
            {
                instance =_instance;
            }
            IsInstantiated = true;
        }

        //后接override表明为虚函数覆盖了父类的某个函数否则编译报错
        void init() override;
        void run() override;
        void cleanup() override;

        void Add_RobotPart(Robot_part* _part);
        void Add_Module(BaseModule* _function);
        void Add_Controller(RobotController* _controller);

        void Print_RobotPart();
        void Print_Module();
        void Print_Controller();
    private:
        static bool IsInstantiated;
        static RobotRunner* instance;
        std::vector<BaseModule*> Module_table[3];
        std::unordered_map<std::string, Robot_part*> Robot_part_hashmap;
        std::unordered_map<std::string, RobotController*> Robot_controller_hashmap;
};

bool RobotRunner::IsInstantiated = false;
RobotRunner* RobotRunner::instance = nullptr;

//函数分为三种，传感器，控制器，执行器
enum ModuleType
{
    MT_SENSOR = 0,
    MT_CONTROLLER,
    MT_ACTUATOR,
    MT_LENGTH,
};

// 基类接口
class BaseModule {
public:
    BaseModule(ModuleType _type, std::string _name):m_type{_type},m_name{_name}{}
    virtual void run() = 0;
    ModuleType m_type;
    std::string m_name;
};

//传感类+执行类的函数为robotpart自己的函数，不需要进行外部的robotpart之间的交互,T一般为robotpart的子类
//控制器的函数为robotRunner的函数，需要进行robotpart之间的交互,T为robotRunner的子类
template<typename T>
class Module : public BaseModule {
public:
    Module(ModuleType _type, T* _pOwner, void (T::*_function)(), std::string _name)
    :BaseModule(_type,_name),
    m_function(_function),
    m_pOwner(_pOwner)
    {
        RobotRunner::Instance()->Add_Module(this);
    }
    void run() override { (m_pOwner->*m_function)(); }
    // 其他成员和方法
private:
    T* m_pOwner;
    void (T::*m_function)();
};

class Robot_part
{
    public:
        Robot_part(std::string _name):m_name{_name}
        {
            RobotRunner::Instance()->Add_RobotPart(this);
        }
        std::string m_name;
};

class RobotController
{
    public:
        RobotController(std::string _name):m_name(_name)
        {
            RobotRunner::Instance()->Add_Controller(this);
        }

        std::string m_name;

        virtual void init() = 0;
};
#endif
