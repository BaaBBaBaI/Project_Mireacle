#include <gtest/gtest.h>
#include "ThreadPool.h"
#include <atomic>
#include <chrono>
#include <future>

TEST(ThreadPoolTest, InitAndWorkersCount) {
    ThreadPool pool(4);
    EXPECT_EQ(pool.getWorkerCount(), 4);
}

TEST(ThreadPoolTest, ExecuteSingleTask) {
    ThreadPool pool(2);
    std::promise<int> p;
    auto f = p.get_future();
    
    pool.enqueue([&p]() {
        p.set_value(42);
    });
    
    EXPECT_EQ(f.get(), 42);
}

TEST(ThreadPoolTest, ExecuteMultipleTasks) {
    ThreadPool pool(4);
    std::atomic<int> counter{0};
    
    const int task_count = 20;
    for (int i = 0; i < task_count; ++i) {
        pool.enqueue([&counter]() {
            counter++;
        });
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_EQ(counter.load(), task_count);
}

TEST(ThreadPoolTest, QueueSizeTracking) {
    ThreadPool pool(1);
    
    std::promise<void> block;
    auto block_future = block.get_future();
    
    pool.enqueue([&block_future]() {
        block_future.wait();
    });
    
   
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    pool.enqueue([]() {});
    pool.enqueue([]() {});
    
    EXPECT_EQ(pool.getQueueSize(), 2);
    
    block.set_value();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_EQ(pool.getQueueSize(), 0);
}

TEST(ThreadPoolTest, GracefulShutdown) {
    std::atomic<int> counter{0};
    {
        ThreadPool pool(2);
        for (int i = 0; i < 10; ++i) {
            pool.enqueue([&counter]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                counter++;
            });
        }
    }
    EXPECT_EQ(counter.load(), 10);
}

TEST(ThreadPoolTest, ReentrantEnqueues) {
    ThreadPool pool(4);
    std::atomic<int> counter{0};
    
    pool.enqueue([&pool, &counter]() {
        counter++;
        pool.enqueue([&counter]() {
            counter++;
        });
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_EQ(counter.load(), 2);
}

TEST(ThreadPoolTest, StressEnqueue) {
    ThreadPool pool(8);
    std::atomic<int> counter{0};
    
    const int count = 200;
    for (int i = 0; i < count; ++i) {
        pool.enqueue([&counter]() {
            counter++;
        });
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_EQ(counter.load(), count);
}
