#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    std::cout << "This is a test commit for Jenkins integration";
    // create Socket and initialize it
    int ServerHandleFd = socket(AF_INET, SOCK_STREAM, 0);
    
    // setting socket options before binding
    int val = 1;
    setsockopt(ServerHandleFd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    
    // setting struct's options
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);        // port
    addr.sin_addr.s_addr = htonl(0);    // wildcard IP 0.0.0.0

    // binding and starting to listen == making socket available for connections
    int rv = bind(ServerHandleFd, (const struct sockaddr *)&addr, sizeof(addr));
    if (rv) { 
        perror("bind()"); 
        return 1; 
    }
    rv = listen(ServerHandleFd, SOMAXCONN);
    if (rv) { 
        perror("listen()"); 
        return 1; 
    }

    // infinite loop that accepts connections
    while (true) {
        struct sockaddr_in client_addr {};
        socklen_t addrlen = sizeof(client_addr);
        int connfd = accept(ServerHandleFd, (struct sockaddr *)&client_addr, &addrlen);
        if (connfd < 0) {
            continue;
        }
        // Placeholder for future implementation
        // do_something();
        close(connfd);
    }

    return 0;
}
