#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket()");
        return 1;
    }
    
    // setting server address
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(1234);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK); // 127.0.0.1
    
    // connecting to server
    int rv = connect(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (rv) {
        perror("connect()");
        return 1;
    }
    
    // writing message
    std::string msg = "Hello from client";
    ssize_t bytes_written = write(fd, msg.c_str(), msg.length());
    if (bytes_written < 0) {
        perror("write()");
        return 1;
    }

    // receiving messages from server
    char buffer[1024] = {};
    ssize_t msg_length = read(fd, buffer, sizeof(buffer));
    if (msg_length < 0) {
        perror("read()");
        return 1;
    }
    buffer[msg_length] = '\0'; // ensure null-termination
    std::string response(buffer); // converting C buffer to C++ string
    std::cout << "Server says:" << response << std::endl;

}
