#include "src/Server.h"

int main() {
    Server server(6379);

    if (!server.initialize()) {
        std::cerr << "Server initialization failed\n";
        return 1;
    }

    server.waitForConnection();

    return 0;
}