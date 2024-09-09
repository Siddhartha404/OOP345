//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.

#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>

namespace seneca {

    struct Task {
        std::string name;
        std::string units;
        std::chrono::nanoseconds duration;
    };

    class TimedTask {
    public:
        TimedTask();
        void startClock();
        void stopClock();
        void addTask(const char* task_name);
        friend std::ostream& operator<<(std::ostream& os, const TimedTask& tt);

    private:
        static const int MAX_TASKS = 10;
        int current_records;
        std::chrono::steady_clock::time_point start_time;
        std::chrono::steady_clock::time_point end_time;
        Task tasks[MAX_TASKS];
    };
}

#endif // TIMEDTASK_H
