
# Project Title: **Encrypted Chat Server**

## Description
This project implements an ARC4 encryption library and a simple chat server using socket communication. The ARC4 library is used for encrypting and decrypting messages exchanged between the client and server.
## Project Structure

```bash
c_project/
│
├── arc4/
│   ├── arcfour.h          # Header file for ARC4 encryption
│   ├── arcfour.c          # Implementation of ARC4 encryption
│   ├── example.c          # Example usage of ARC4 library
│   └── Makefile           # Makefile to build the ARC4 library
│
├── chat_server/
│   ├── client.c           # Client code for the chat application
│   ├── server.c           # Server code for the chat application
│   └── Makefile           # Makefile to build the chat client and server
│
└── README.md              # This file
```

## Features
- **ARC4 Encryption**: An implementation of the ARC4 encryption algorithm.
- **Socket Communication**: A simple TCP client-server model for sending and receiving messages.
- **Timeout Mechanism**: The server automatically terminates the connection if no message is received within 30 seconds.

## Prerequisites
- **Compiler**: GCC (GNU Compiler Collection)
- **Operating System**: Linux or macOS (Windows support may require modifications)

## Installation and Setup

### 1. Clone the Repository
```bash
git clone https://github.com/gopiyadav989/c_project.git
cd c_project
```

### 2. Build the ARC4 Library
```bash
cd arc4/
make
```
This will generate the `libarcfour.a` static library.

### 3. Build the Chat Server and Client
```bash
cd ../chat_server/
make
```
This will generate the `Client` and `Server` binaries.

## Usage

### 1. Run the Server
```bash
./Server
```
The server will start listening on port `8080`.

### 2. Run the Client
```bash
./Client <server_ip_address>
```
Replace `<server_ip_address>` with the actual IP address of the server. The client will connect to the server on port `8080`.

### 3. Communication
- The client sends encrypted messages to the server.
- The server responds with an encrypted message.
- Both client and server decrypt the received messages before displaying them.
- Type `bye` to terminate the communication.

## Configuration Options

- **Port**: Default is set to `8080` in `server.c` and `client.c`.
- **Timeout**: The server has a timeout of 10 seconds (set in `server.c` and zclient.c`).


### Changing Port Number
To use a different port, update the `PORT` definition in both `server.c` and `client.c`:
```c
#define PORT 8080  // Change 8080 to your desired port number
```

## Makefile Overview
- **arc4/Makefile**: Builds the ARC4 encryption library (`libarcfour.a`).
- **chat_server/Makefile**: Builds the Client and Server binaries, linking against `libarcfour.a`.


## Future Enhancements
- **User Authentication**: Implement user authentication for secure message exchanges.
- **Multiple Clients Support**: Modify the server to handle multiple client connections simultaneously.
- **GUI Interface**: Develop a graphical user interface for the client application.

## Acknowledgments
- **ARC4 Algorithm**: Thanks to the creators and maintainers of the ARC4 encryption algorithm.
- **Socket Programming Resources**: Gratitude to various online resources and communities that provide support for socket programming in C.

---
