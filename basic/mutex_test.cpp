#include <iostream>
#include <thread>
#include <mutex>

volatile int counter(0);
std::mutex mtx;

void attempt_10k_increase(){
    for(int i=0;i<10000;i++){
        if(mtx.try_lock()){
            ++counter;
            mtx.unlock();
        }
    }
}

int main(){
    std::thread threads[10];
    for(int i=0;i<10;i++)
        threads[i] = std::thread(attempt_10k_increase);
    
    for(auto& th : threads) th.join();
    std::cout << counter << "success increases of the counter.\n";

    return 0;
}