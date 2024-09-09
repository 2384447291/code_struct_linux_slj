// #include "PeriodicTask.hpp"
// class Test1 :public PeriodicTask{
//     public:
//     Test1(PeriodicTaskManager*tm, float period)
//     :PeriodicTask(tm,period,"Test1",0){}
//     void run()
//     {
//         // std::this_thread::sleep_for(std::chrono::nanoseconds(10));
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//     }

//     void init(){void();}

//     void cleanup(){void();}

// };

// class Test2 :public PeriodicTask{
//     public:
//     Test2(PeriodicTaskManager*tm, float period)
//     :PeriodicTask(tm,period,"Test2",1){}
//     void run()
//     {
//         std::this_thread::sleep_for(std::chrono::nanoseconds(10));
//     }

//     void init(){void();}

//     void cleanup(){void();}
// ;
// };


// class Test3 :public PeriodicTask{
//     public:
//     Test3(PeriodicTaskManager*tm, float period)
//     :PeriodicTask(tm,period,"Test3",2){}
//     void run()
//     {
//         std::this_thread::sleep_for(std::chrono::nanoseconds(10));
//     }

//     void init(){}

//     void cleanup(){}

// };

// class Test4 :public PeriodicTask{
//     public:
//     Test4(PeriodicTaskManager*tm, float period)
//     :PeriodicTask(tm,period,"Test4",3){}
//     void run()
//     {
//         std::this_thread::sleep_for(std::chrono::nanoseconds(10));
//     }

//     void init(){}

//     void cleanup(){}
// };

int main()
{

    // cpu_set_t mask;
    // CPU_ZERO(&mask);
    // CPU_SET(5, &mask);

    // if (sched_setaffinity(0, sizeof(mask), &mask) < 0) 
    // {
    //     perror("sched_setaffinity");
    // }
    // PeriodicTaskManager testmanager;
    // Test1 test1(&testmanager, 0.001f);
    // test1.start();
    // Test2 test2(&testmanager, 0.001f);
    // test2.start();
    // Test3 test3(&testmanager, 0.001f);
    // test3.start();
    // Test4 test4(&testmanager, 0.001f);
    // test4.start();
    // while(1)
    // {
    //     testmanager.printStatus();
    // }
}