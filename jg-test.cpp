#include <random>
#include <iostream>
#include "SensorManager.h"
#include "DisplayReport.h"

int main(){
    SensorManager s;
    std::vector<WeatherReport> history;
    std::mutex history_lock;
    std::thread weather_monitoring(std::ref(s), &history, &history_lock);
    while (1){
        while ( history.size() == 0 ){

        }
        auto latest = history.back();
        if ( history.back().time != latest.time ){
            std::cout << "Measured " << latest.temperature << "degrees " << '\n';
            latest = history.back();
        }
    }

    weather_monitoring.join();
}