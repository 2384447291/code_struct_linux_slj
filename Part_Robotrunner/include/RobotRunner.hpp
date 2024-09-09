#ifndef ROBOTRUNNER_HPP
#define ROBOTRUNNER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "PeriodicTask.hpp"
#include "Timer.h"
#include <chrono>

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

        BaseModule* Get_Module(std::string _name);
        RobotController* Get_Controller(std::string _name);
        Robot_part* Get_RobotPart(std::string _name);

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

    virtual uint32_t getCallCount() const = 0;
    virtual double getAverageTime() const = 0;
    virtual double getAverageTimeInMs() const = 0;
    virtual double getAverageTimeInus() const = 0;
    virtual long getAverageTimeInns() const = 0;

    ModuleType m_type;
    std::string m_name;

    double m_totalTime = 0;

    int64_t m_calltime = 0;
    uint32_t m_callCountS = 0;
    uint32_t m_callCount = 0;
    uint64_t all_callCount = 0;
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
    void run() override { 
        if (Gloabl_Timer::hasElapsedMs(1000, m_calltime))
        {
            m_callCountS = m_callCount;
            m_callCount = 0;
            // std::cout << std::dec << m_name << " " << m_totalTime * 1000000000/all_callCount << std::endl;
        }
        auto start = std::chrono::high_resolution_clock::now();
        (m_pOwner->*m_function)(); 
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        m_totalTime += elapsed.count();
        m_callCount++;
        all_callCount++;
        }

    uint32_t getCallCount() const {
        return m_callCountS;
    }

    double getAverageTime() const {
        return all_callCount > 0 ? m_totalTime / all_callCount : 0;
    }

    double getAverageTimeInMs() const {
        return m_callCount > 0 ? (m_totalTime * 1000) / all_callCount : 0;
    }

    double getAverageTimeInus() const {
        return m_callCount > 0 ? (m_totalTime * 1000000) / all_callCount : 0;
    }
    long getAverageTimeInns() const {
        return m_callCount > 0 ? static_cast<long>((m_totalTime * 1000000000)/all_callCount) : 0;
    }
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
