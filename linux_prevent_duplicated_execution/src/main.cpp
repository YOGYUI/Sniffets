#include <cstdio>
#include <vector>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>

extern char *__progname;

void get_process_id_list(const char *proc_name, std::vector<pid_t> &list) {
    char command[256]{0, };
    char result[256]{0, };

    sprintf(command, "pidof %s", proc_name);
    // get "pidof" result as string
    FILE *fp = popen(command, "r");
    list.clear();
    if (fp) {
        size_t ret = fread(result, 1, 256, fp);
        pclose(fp);
        if (ret <= 0) {
            printf("failed to get pidof command result\n");
            return;
        }
        // convert as std::string and remove new line character(\n)
        std::string szres(result);
        szres.replace(szres.find('\n'), 1, "");
        // split string and push pid values in vector (delimeter = ' ')
        std::string szpid;
        std::istringstream stream(szres);
        while (getline(stream, szpid, ' ')) {
            pid_t pid = strtol(szpid.c_str(), nullptr, 10);
            list.push_back(pid);
        }
    }
}

bool check_executable(const char *proc_name) {
    std::vector<pid_t> pid_list;
    // get pid list of specific process
    get_process_id_list(proc_name, pid_list);
    // get pid of current process and remove it from vector 
    pid_t my_pid = getpid();
    pid_list.erase(std::remove(pid_list.begin(), pid_list.end(), my_pid), pid_list.end());
    // check size of vector (if not empty, process is duplicated)
    if (!pid_list.empty()) {
        printf("Found other process which is running (count: %zu)\n", pid_list.size());
        for (auto &pid : pid_list) {
            printf("%d\n", pid);
        }
        return false;
    }

    return true;
}

int main(int argc, char *argv[]) {
    pid_t my_pid = getpid();
    if (!check_executable(__progname)) {
        return 1;
    } else {
        while (1) {
            printf("process <%s (PID %d)> is running\n", __progname, my_pid);
            sleep(5);
        }
    }

    return 0;
}
