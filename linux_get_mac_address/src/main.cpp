#include <string>
#include <regex>
#include <fstream>
#include <streambuf>
#include <iostream>

#define MAC_ADDR_SIZE   6
#define MAC_ADDR_STRING_SIZE   (MAC_ADDR_SIZE * 3 - 1)

std::string get_mac_address(const std::string& if_name)
{
    std::string mac_addr;
    std::ifstream iface("/sys/class/net/" + if_name + "/address");
    std::string str((std::istreambuf_iterator<char>(iface)), std::istreambuf_iterator<char>());
    if (str.length() > 0) {
        uint8_t buf[MAC_ADDR_SIZE] = {0, };
        std::string hex = regex_replace(str, std::regex(":"), "");
        uint64_t result = stoull(hex, 0, 16);
        for (int i = 0; i < MAC_ADDR_SIZE; i++) {
            buf[MAC_ADDR_SIZE - 1 - i] = (uint8_t) ((result & ((uint64_t) 0xFF << (i * 8))) >> (i * 8));
        }
        char temp[MAC_ADDR_STRING_SIZE + 1] = {0,};
        snprintf(temp, MAC_ADDR_STRING_SIZE, "%02X:%02X:%02X:%02X:%02X:%02X", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
        temp[MAC_ADDR_STRING_SIZE] = '\0';
        mac_addr = std::string(temp);
    }

    return mac_addr;
}

int main(int argc, char *argv[]) {
    if (argv[1]) {
        std::cout << "interface name: " << argv[1] << "\n";
        std::cout << get_mac_address(std::string(argv[1])) << "\n";
    }

    return 0;
}