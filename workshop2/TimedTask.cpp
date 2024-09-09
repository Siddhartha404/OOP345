//Name: Siddhartha Thapa Chhetri
//Email: sthapa-chhetri2@myseneca.ca
//ID: 147913222
//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.

#include "TimedTask.h"

namespace seneca {

    TimedTask::TimedTask() : current_records(0) {}

    void TimedTask::startClock() {
        start_time = std::chrono::steady_clock::now();
    }

    void TimedTask::stopClock() {
        end_time = std::chrono::steady_clock::now();
    }

    void TimedTask::addTask(const char* task_name) {
        if (current_records < MAX_TASKS) {
            tasks[current_records].name = task_name;
            tasks[current_records].units = "nanoseconds";
            tasks[current_records].duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
            current_records++;
        }
    }

    std::ostream& operator<<(std::ostream& os, const TimedTask& tt) {

        os << "--------------------------\n";
        os << "Execution Times:\n";
        os << "--------------------------\n";
        for (int i = 0; i < tt.current_records; ++i) {
            os << std::left << std::setw(21) << tt.tasks[i].name << " "
                << std::right << std::setw(13) << tt.tasks[i].duration.count() << " "
                << tt.tasks[i].units << "\n";
        }
        os << "--------------------------\n";
        return os;
    }
}
