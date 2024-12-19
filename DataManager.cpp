#include <chrono>
#include <thread>


struct WeatherReport{
    std::chrono::time_point logged_time;
    float temp;
    float humidity;
    float pressure;
};

struct SensorList{
    
};

class DataManager{
    public:
    static void make_report( std::vector<WeatherReport>*out, std::mutex& );
};

class TempSensor{
    private:
    std::mutex temp_mutex;
    float last_temp;
    void measure_temp();
    std::thread measure_thread(measure_temp, data_source);

    public:
    float poll();
};

void DataManager::make_report( std::vector<WeatherReport> *history, std::mutex &history_mutex ){
    history_mutex.lock();
    WeatherReport report;
    report.logged_time = std::chrono::now();
    report.temp = tempsensor.poll();
    report.humidity = humiditysensor.poll();
    report.pressure = pressuresensor.poll();
    history->push_back(report);
    history_mutex.unlock();
}

class Sensor{
    static void measure_temp(WeatherReport*, std::mutex&);
};

void Sensor::measure_temp(WeatherReport* destination, std::mutex &current_mutex){
    while(current_mutex.try_lock()){
            destination->temp += 0.5;
            current_mutex.lock();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void runprogram(){
    WeatherReport current;
    std::mutex a;
    std::thread temp_sensing(Sensor::measure_temp, &current, a);
    std::vector<WeatherReport> history;
    std::mutex history_mutex;
    std::thread report_making(DataManager::make_report, &history, history_mutex);
}