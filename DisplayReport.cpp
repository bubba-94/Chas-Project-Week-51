#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include "DisplayReport.h"



std::mutex mtx;

void displayTime() {
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(1));       
        
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        
        std::lock_guard<std::mutex> lock(mtx);       
        std::cout << "Current Time: " << std::ctime(&now) << std::endl;
    }
}

void displayWeather(){
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(5));

        history.updateWeatherData();

        std::lock_guard<std::mutex> lock(mtx);
        history.getWeatherData();
       std::cout << "" << std::endl;
    }
}
