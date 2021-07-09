#include <iostream>
#include "tcp_server.h"

int main() {
    tcp_server server(1234);
    server.loop();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
