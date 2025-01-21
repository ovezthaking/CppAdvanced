#include <functional>
#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>
#include <future>
#include <numeric>

class thread_pool {
public:
    using Task = std::function<double()>;

    explicit thread_pool(std::size_t numThreads) {
        start(numThreads);
    }

    ~thread_pool() {
        stop();
    }

    void add_task(Task task) {
        {
            std::unique_lock<std::mutex> lock{mEventMutex};
            mTasks.emplace(std::move(task));
        }
        mEventVar.notify_one();
    }

    double average() {
        std::unique_lock<std::mutex> lock{mResultMutex};
        if (mResults.empty()) return 0.0;
        double sum = std::accumulate(mResults.begin(), mResults.end(), 0.0);
        return sum / mResults.size();
    }

    void stop() noexcept {
        {
            std::unique_lock<std::mutex> lock{mEventMutex};
            mStopping = true;
        }
        mEventVar.notify_all();
        for (auto &thread : mThreads) {
            thread.join();
        }
    }

private:
    std::vector<std::thread> mThreads;
    std::condition_variable mEventVar;
    std::mutex mEventMutex;
    std::mutex mResultMutex;
    bool mStopping = false;
    std::queue<Task> mTasks;
    std::vector<double> mResults;

    void start(std::size_t numThreads) {
        for (auto i = 0u; i < numThreads; i++) {
            mThreads.emplace_back([=] {
                while (true) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock{mEventMutex};
                        mEventVar.wait(lock, [=] { return mStopping || !mTasks.empty(); });
                        if (mStopping && mTasks.empty())
                            break;
                        task = std::move(mTasks.front());
                        mTasks.pop();
                    }
                    double result = task();
                    {
                        std::unique_lock<std::mutex> lock{mResultMutex};
                        mResults.push_back(result);
                    }
                }
            });
        }
    }
};

int main() {
    {
        thread_pool pool{4};

        pool.add_task([] {
            return 1.0;
        });
        
        //std::cout << "Task 1 added" << std::endl;
        //std::cin.get();

        pool.add_task([] {
            return 2.0;
        });

        //std::cout << "Task 2 added" << std::endl;
        //std::cin.get();

        pool.add_task([] {
            return 3.0;
        });

        //std::cout << "Task 3 added" << std::endl;
        //std::cin.get();

        pool.add_task([] {
            return 4.0;
        });

        //std::cout << "Task 4 added" << std::endl;
        //std::cin.get();

        std::cout << "Average: " << pool.average() << std::endl;
    }
    return 0;
}
