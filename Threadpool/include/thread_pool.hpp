/**
 * @file thread_pool.hpp
 * @brief This file contains the definition of the thread_pool class and its related classes.
 * 
 * @author Razirp (RenPengyu2001@outlook.com)
 * @version v1.0.0
 * @date 2024-04-13
 * @license MIT License
 * @copyright (c) 2024 Razirp
 */

#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <list>
#include <cstdint>
#include <semaphore>
#include <shared_mutex>
#include <future>

//所有变量都在thread_utils命名空间下，防止冲突
namespace thread_utils
{
class thread_pool 
{
private:
    class worker_thread;        // 工作线程类
    enum class status_t : std::int8_t 
    { 
        TERMINATED = -1, 
        TERMINATING = 0, 
        RUNNING = 1, 
        PAUSED = 2, 
        SHUTDOWN = 3
    };  // 线程池的状态，-1: 线程池已终止；0: 线程池将终止；1: 线程池正在运行；2: 线程池被暂停；3: 线程池在等待任务完成，但不再接受新任务
    //使用atomic声明的变量能够不使用锁来实现多线程访问，支持bool、int、char等数据数据，不支持浮点和自定义类等
    std::atomic<status_t> status;//使用原子变量能不用加锁        
    std::atomic<std::size_t> max_task_count;  // 任务队列中任务的最大数量，0表示没有限制    // 当任务队列中的任务数量将或已经超过此值时，新提交的任务将被拒绝
    //shared_mutex相对于mutex的单独线程享有锁的情况有三种情况读模式加锁状态；写模式加锁状态；不加锁状态；
    //当读写锁处于写加锁状态时，在其解锁之前，所有尝试对其加锁的线程都会被阻塞
    //当读写锁处于读加锁状态时，所有试图以读模式对其加锁的线程都可以得到访问权，但是如果想以写模式对其加锁，线程将阻塞。
    //但是如果有线程尝试以写模式加锁，那么后续的读线程将会被阻塞，这样可以避免锁长期被读者占有。
    std::shared_mutex status_mutex;             // 状态变量的互斥锁(虽然使用了原子表示status，还是加锁稳妥一点)       
    std::shared_mutex task_queue_mutex;         // 任务队列的互斥锁
    std::shared_mutex worker_list_mutex;        // 线程列表的互斥锁

    std::condition_variable_any task_queue_cv; // 任务队列的条件变量
    std::condition_variable_any task_queue_empty_cv; // 任务队列为空的条件变量

    std::queue<std::function<void()>> task_queue;      // 任务队列，其中存储着待执行的任务
    std::list<worker_thread> worker_list;              // 线程列表，其中存储着工作线程
    // 禁用拷贝/移动构造函数及赋值运算符
    //通过将拷贝构造函数和移动构造函数声明为delete，可以阻止该类对象被拷贝或移动构造。这意味着在使用该类时，不能进行拷贝构造或移动构造操作。
    thread_pool(const thread_pool&) = delete;
    thread_pool(thread_pool&&) = delete;
    thread_pool& operator=(const thread_pool&) = delete;
    thread_pool& operator=(thread_pool&&) = delete;
    // 在取得对状态变量的独占访问后，调用以下函数，以确保线程池的状态变更是原子的
    void pause_with_status_lock();
    void resume_with_status_lock();
    void terminate_with_status_lock();
    void wait_with_status_lock();
    void shutdown_with_status_lock();
    void shutdown_now_with_status_lock();
public:
    thread_pool(std::size_t initial_thread_count, std::size_t max_task_count = 0);
    ~thread_pool();
    
    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))>;
    void pause();
    void resume();
    void shutdown();    // 等待所有任务执行完毕后再终止线程池
    void shutdown_now();    // 立即终止线程池       // 会丢弃任务队列中的任务
    void terminate();   // 终止线程池
    void wait();    // 等待所有任务执行完毕
    void add_thread(std::size_t count_to_add);
    void remove_thread(std::size_t count_to_remove);
    void set_max_task_count(std::size_t count_to_set);
    std::size_t get_thread_count();
    std::size_t get_task_count();
};

class thread_pool::worker_thread
{
private:
    enum class status_t : std::int8_t { 
        TERMINATED = -1, 
        TERMINATING = 0, 
        RUNNING = 1, 
        PAUSED = 2, 
        BLOCKED = 3
    };  // 状态变量类型，-1:线程已终止；0: 线程将终止；1: 线程正在运行; 2: 线程被暂停；3: 线程在阻塞等待新任务
    std::atomic<status_t> status;       
    std::binary_semaphore pause_sem;       // 信号量，用于线程暂停时的阻塞
    std::shared_mutex status_mutex;         // 状态变量的互斥锁
    thread_pool *pool;      // 线程池
    std::thread thread;     // 工作线程
    // 禁用拷贝/移动构造函数及赋值运算符
    worker_thread(const worker_thread&) = delete;
    worker_thread(worker_thread&&) = delete;
    worker_thread& operator=(const worker_thread&) = delete;
    worker_thread& operator=(worker_thread&&) = delete;
    // 在取得对状态变量的独占访问后，调用以下函数，以确保线程的状态变更是原子的
    status_t terminate_with_status_lock();
    void pause_with_status_lock();
    void resume_with_status_lock();
public:
    worker_thread(thread_pool* pool);
    ~worker_thread();
    status_t terminate();
    void pause();
    void resume();

};

//decltype辅助auto推理函数结果
//decltype(f(args...))用来提取变量类型，这里表示future返回的变量类型为f(args...)的类型
template<typename F, typename... Args>
auto thread_pool::submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))>//当对象离开作用域时，它会自动解锁共享互斥量
{   // 提交任务
    std::shared_lock<std::shared_mutex> status_lock(status_mutex);  // 为状态变量读加锁
    //原子变量status的读取使用status.load()
    switch (status.load())
    {
    case status_t::TERMINATED: // 线程池已终止
        throw std::runtime_error("[thread_pool::submit][error]: thread pool is terminated");
    case status_t::TERMINATING: // 线程池将终止
        throw std::runtime_error("[thread_pool::submit][error]: thread pool is terminating");
    case status_t::PAUSED: // 线程池被暂停
        throw std::runtime_error("[thread_pool::submit][error]: thread pool is paused");
    case status_t::SHUTDOWN: // 线程池在等待任务完成，但不再接受新任务
        throw std::runtime_error("[thread_pool::submit][error]: thread pool is waiting for tasks to complete, but not accepting new tasks");
    case status_t::RUNNING: // 线程池正在运行，允许加入新的任务
        break;
    default:
        throw std::runtime_error("[thread_pool::submit][error]: unknown status");
    }
    
    if (max_task_count > 0 && get_task_count() >= max_task_count)
    {   // 如果任务队列已满，则拒绝提交任务
        throw std::runtime_error("[thread_pool::submit][error]: task queue is full");
    }
    //等价替换语法
    using return_type = decltype(f(args...));
    //make_shared智能指针
    // auto bar = std::make_shared<指针指向变量的类型> (变量的构造函数所需要传入的参数);

    //std::packaged_task类似于std::function，但是会自动将其结果传递给std::future对象
    //std::packaged_task对象内部包含两个元素：(1).存储的任务(stored task)是一些可调用的对象(例如函数指针、成员或函数对象的指针)
    //(2).共享状态，它可以存储调用存储的任务(stored task)的结果，并可以通过std::future进行异步访问
    //标准的声明样式如下std::packaged_task<函数类型> task(std::bind(函数本体);
    //该变量可以调用get_future()来绑定一个future变量获取该函数的返回值

    //std::bind可以看作一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对象来适应原对象的参数列表。
    //auto newCallable = bind(callable, arg_list);
    //该形式表达的意思是：当调用newCallable时，会调用callable，并传给它arg_list中的参数。
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
    //如果不使用forward，f，args会因为传入的问题发生左右值转换
    //声明一个名字为task的智能指针（std::make_shared）指向一个 std::packaged_task 对象（用来和future连用返回该函数的结果）
    std::future<return_type> res = task->get_future();
    std::unique_lock<std::shared_mutex> lock(task_queue_mutex);//为任务队列增加写加锁
    //lambda表达式(lambda表达式本身代表一个匿名函数(即没有函数名的函数))  [capture list] (parameter list) -> return type { function body }

    //capture list 是捕获列表，用于指定 Lambda表达式可以访问的外部变量，以及是按值还是按引用的方式访问。
    //捕获列表可以为空，表示不访问任何外部变量，s
    //也可以使用默认捕获模式 & 或 = 来表示按引用或按值捕获所有外部变量，
    //还可以混合使用具体的变量名和默认捕获模式来指定不同的捕获方式。

    //parameter list 是参数列表，用于表示 Lambda表达式的参数，可以为空，表示没有参数，也可以和普通函数一样指定参数的类型和名称，还可以在 c++14 中使用 auto 关键字来实现泛型参数。

    //return type 是返回值类型，用于指定 Lambda表达式的返回值类型，可以省略，表示由编译器根据函数体推导，也可以使用 -> 符号显式指定，还可以在 c++14 中使用 auto 关键字来实现泛型返回值。

    //function body为函数本体


    //下面的式子表示捕获上面的指针task，不需要参数传入，返回的是指针内的内容。
    task_queue.emplace([task](){ (*task)(); }); // 将任务封装为一个lambda表达式并放入任务队列   // 该lambda表达式会调用std::packaged_task对象的operator()方法，从而执行任务
    lock.unlock();
    task_queue_cv.notify_one();//有新的任务传入，唤醒所有线程
    return res;
}

inline void thread_pool::set_max_task_count(std::size_t count_to_set)
{   // 设置任务队列中任务的最大数量；如果设置后的最大数量小于当前任务数量，则会拒绝新提交的任务，直到任务数量小于等于最大数量
    max_task_count.store(count_to_set);
}

} // namespace thread_utils

#endif 