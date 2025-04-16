# Build Your Own Redis

![Project Status](https://img.shields.io/badge/status-in%20progress-yellow)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue)
![License](https://img.shields.io/badge/license-MIT-green)

## Overview

This project is a from-scratch implementation of Redis. The goal is to understand Redis's core functionality by implementing it's key features in C++.

**Note:** All code in this repository is written by hand, with no copy-pasting from existing implementations or AI-generated code. This project represents my learning journey to understand Redis at a fundamental level.

## Learning Objectives

This project aims to deepen my understanding of systems programming through hands-on implementation. Key learning objectives include:

- **Networking fundamentals**: Understanding TCP/IP, socket programming, and client-server architecture
- **Protocol design**: Implementing the RESP (Redis Serialization Protocol) from specifications
- **Concurrent programming**: Managing multiple client connections and handling requests simultaneously
- **In-memory database concepts**: Designing efficient data structures for key-value storage
- **System design**: Creating a modular, maintainable architecture
- **Performance optimization**: Building efficient data handling and processing systems

## Development Approach

I'm taking an incremental, test-driven approach to this project:

1. **Research**: Understanding Redis concepts before implementation
2. **Incremental development**: Building one feature at a time, starting with core functionality
3. **Testing**: Creating tests for each component to verify correctness
4. **Refactoring**: Continuously improving code quality and architecture
5. **Documentation**: Documenting design decisions and implementation details

## Project Roadmap

- [ ] Stage 1: TCP server that responds to PING
- [ ] Stage 2: RESP protocol parser and serializer
- [ ] Stage 3: Handling multiple clients concurrently
- [ ] Stage 4: Basic Redis commands (GET, SET, ECHO)
- [ ] Stage 5: Key expiration functionality
- [ ] Stage 6: Additional commands (DEL, EXISTS)
- [ ] Stage 7: Replication functionality

## Building and Running

### Prerequisites

- C++ compiler with C++20 support
- Make

### Build

```bash
make
```

### Run

```bash
./redis-server
```

### Run with port

```bash
./redis-server --port 6379
```

### Test with redis-cli

```bash
redis-cli ping
```

## Core Concepts to Explore

### TCP Networking

Redis operates as a TCP server, requiring an understanding of:
- Socket programming in C++
- Client-server communication patterns
- Connection management

### RESP Protocol

The Redis Serialization Protocol (RESP) is a simple text-based protocol that:
- Serializes different data types (strings, errors, integers, arrays)
- Uses a prefix notation to distinguish types
- Supports both request and response formatting

### In-Memory Data Storage

Redis is fundamentally an in-memory database, which involves:
- Efficient data structures for fast access
- Memory management considerations
- Expiration mechanisms for time-based key removal

### Concurrency

A production-ready Redis implementation handles:
- Multiple simultaneous client connections
- Thread safety considerations
- Event-driven I/O

## Learning Resources

Throughout this project, I'll be consulting:
- [Redis Protocol Specification](https://redis.io/topics/protocol)
- [Redis Command Reference](https://redis.io/commands)
- [Redis Internals](https://redis.io/topics/internals)
- Systems programming references and best practices
- Networking and concurrency patterns in C++

## Learning Resources

- [Redis Protocol Specification](https://redis.io/topics/protocol)
- [Redis Command Reference](https://redis.io/commands)
- [Redis Internals](https://redis.io/topics/internals)

## License

This project is licensed under the MIT License.
