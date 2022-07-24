#include <chrono>
#include <string>
#include <iostream>

static std::string get_time_stamp() {
    const auto now = std::chrono::system_clock::now();
    time_t tm_now = std::chrono::system_clock::to_time_t(now);
    struct tm tstruct = *localtime(&tm_now);

    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;
    
    char temp[128];
    snprintf(temp, sizeof(temp), "%04d%02d%02d-%02d:%02d:%02d.%03ld",
        tstruct.tm_year + 1900, tstruct.tm_mon + 1, tstruct.tm_mday, 
        tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec, millis.count());

    return std::string(temp);
}

int main(int argc, char *argv[]) {
    std::cout << "current time: " << get_time_stamp() << "\n";

    std::cout << "press any key to exit" << "\n";
    std::cin.get();

    return 0;
}