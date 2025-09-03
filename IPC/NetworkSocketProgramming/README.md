# Network Socket Programming Mastery Roadmap

This guide covers the complete set of topics, system calls, and projects you need to master **Network Socket Programming (TCP/UDP)** in Linux.

---

## 🔹 1. Basics of Network Sockets
- Communication between processes over a network (different hosts or same host).
- **Domains**:
  - `AF_INET`  → IPv4
  - `AF_INET6` → IPv6
- **Types**:
  - `SOCK_STREAM` → TCP (reliable, connection-oriented)
  - `SOCK_DGRAM` → UDP (unreliable, connectionless)
  - `SOCK_RAW` → Raw sockets (custom protocols, requires root)
- Key difference vs UNIX Domain Sockets: Uses IP + Port instead of filesystem path.

---

## 🔹 2. Essential System Calls

### Socket Creation & Setup
- `socket(int domain, int type, int protocol)`
- `bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`
- `listen(int sockfd, int backlog)`
- `accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)`
- `connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`

### Data Transfer
- `send(int sockfd, const void *buf, size_t len, int flags)`
- `recv(int sockfd, void *buf, size_t len, int flags)`
- `sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)`
- `recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)`
- `write()`, `read()` (also valid for sockets)

### Socket Options
- `getsockopt(int sockfd, int level, int optname, ...)`
- `setsockopt(int sockfd, int level, int optname, ...)`
  - Common options:
    - `SO_REUSEADDR`, `SO_REUSEPORT`
    - `SO_SNDBUF`, `SO_RCVBUF`
    - `TCP_NODELAY` (disable Nagle’s algorithm)
    - `SO_KEEPALIVE`

### Closing
- `shutdown(int sockfd, int how)`
- `close(int fd)`

---

## 🔹 3. Structures to Study
- `struct sockaddr_in {  
    sa_family_t    sin_family;   // AF_INET  
    in_port_t      sin_port;     // Port number  
    struct in_addr sin_addr;     // IPv4 address  
  };`

- `struct sockaddr_in6` (for IPv6)
- `struct addrinfo` (for `getaddrinfo()`)

---

## 🔹 4. Intermediate Concepts
- **Client-Server Model** (TCP handshake).
- **Endianess** conversions:
  - `htons()`, `htonl()`, `ntohs()`, `ntohl()`
- **DNS resolution**:
  - `getaddrinfo()`, `getnameinfo()`
- **Blocking vs Non-blocking sockets**:
  - `fcntl(fd, F_SETFL, O_NONBLOCK)`
- **Multiplexing**:
  - `select()`, `poll()`, `epoll()`

---

## 🔹 5. Advanced Topics
- **IPv6 programming** (`AF_INET6`, dual-stack sockets).
- **Raw sockets** (custom protocols, packet crafting).
- **Broadcast & Multicast sockets**:
  - `setsockopt(..., IP_MULTICAST_TTL, ...)`
- **Asynchronous I/O** (`epoll`, `io_uring`).
- **TLS/SSL sockets** (using OpenSSL).
- **Performance tuning** with socket options (`TCP_FASTOPEN`, `SO_SNDBUF`, `SO_RCVBUF`).
- **Security considerations**:
  - Firewalls, SELinux, socket permissions.

---

## 📚 References
- `man 7 socket`
- `man 2 socket`, `man 2 bind`, `man 2 listen`, `man 2 accept`, `man 2 connect`
- W. Richard Stevens, *UNIX Network Programming (Volume 1)*
- Michael Kerrisk, *The Linux Programming Interface*

---
