#include <sys/stat.h>
#include <string>
#include <iostream>

bool check_dir_exist(const char *path) {
    bool exist = false;
    struct stat st;
    if(stat(path, &st) == 0) {
        if( ((st.st_mode) & S_IFMT) == S_IFDIR ) {
            exist = true;
        }
    }

    return exist;
}

int main(int argc, char *argv[]) {
    std::string path1("./test_dir_1");
    std::string path2("./test_dir_2");

    if (check_dir_exist(path1.c_str())) {
        std::cout << "Path1 (" << path1 << ") Exist\n";
    } else {
        std::cout << "Path1 (" << path1 << ") Not Exist\n";
    }

    if (check_dir_exist(path2.c_str())) {
        std::cout << "Path2 (" << path2 << ") Exist\n";
    } else {
        std::cout << "Path2 (" << path2 << ") Not Exist\n";
    }

    return 0;
}