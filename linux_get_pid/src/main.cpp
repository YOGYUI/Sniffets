#include <cstdio>
#include <vector>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sstream>

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

int main(int argc, char *argv[]) {
    std::vector<pid_t> pid_list;
    if (argv[1]) {
        get_process_id_list(argv[1], pid_list);
        printf("Process <%s> Count: %zu\n", argv[1], pid_list.size());
        for (auto & pid : pid_list) {
            printf("%d\n", pid);
        }
    }

    return 0;
}
