#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

// helper function for debug messages
void msg(const char* message) {
    std::cerr << message << std::endl;
}

// Function to handle client connection
static void do_something(int connfd) {
    char buffer[1024];    
    ssize_t n = read(connfd, buffer, sizeof(buffer) - 1);
    if (n < 0) {
        msg("read(error)");
        return;
    }

    // null terminating C buffer
    buffer[n] = '\n';
    // converting C buffer into C++ string
    std::string rbuf(buffer);

    printf("client says: %s\n", buffer);

    std::string wbuf = "world";
    write(connfd, wbuf.c_str(), wbuf.length());
}

int main() {
    std::cout << "This is test commit for Jenkins integration #5";
    // create Socket and initialize it
    int ServerHandleFd = socket(AF_INET, SOCK_STREAM, 0);
    if (ServerHandleFd < 0) {
        perror("socket()");
        return 1;
    }

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
        
        do_something(connfd);

        close(connfd);
    }

    return 0;
}
