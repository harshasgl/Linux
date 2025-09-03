# UNIX Domain Sockets Mastery Roadmap

This guide covers the complete set of topics, system calls, and concepts you need to master **UNIX Domain Sockets (UDS)** in Linux.

---

## 🔹 1. Basics of UNIX Domain Sockets
- IPC mechanism using the filesystem namespace (not network).
- Types:
  - `SOCK_STREAM` → reliable, connection-oriented (like TCP).
  - `SOCK_DGRAM` → datagram, connectionless (like UDP).
  - `SOCK_SEQPACKET` → sequenced, reliable datagrams.
- Learn the difference between:
  - `AF_INET` → TCP/UDP sockets (network).
  - `AF_UNIX` → local IPC sockets.

---

## 🔹 2. System Calls

### Socket Creation & Setup
- `socket(int domain, int type, int protocol)`
- `bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`
- `listen(int sockfd, int backlog)`
- `accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)`
- `connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)`

### Data Transfer
- `send(int sockfd, const void *buf, size_t len, int flags)`
- `recv(int sockfd, void *buf, size_t len, int flags)`
- `sendto(int sockfd, ...)`, `recvfrom(int sockfd, ...)` (for datagrams)
- `write()`, `read()` (also valid for sockets)

### File Descriptor Passing
- `sendmsg(int sockfd, const struct msghdr *msg, int flags)`
- `recvmsg(int sockfd, struct msghdr *msg, int flags)`

### Socket Options
- `getsockopt(int sockfd, int level, int optname, ...)`
- `setsockopt(int sockfd, int level, int optname, ...)`
  - Common options: `SO_PASSCRED`, `SO_PEERCRED`, `SO_RCVBUF`, `SO_SNDBUF`

### Closing
- `shutdown(int sockfd, int how)`
- `close(int fd)`

---

## 🔹 3. Structures to Study
- `struct sockaddr_un {  
    sa_family_t sun_family;   // AF_UNIX  
    char sun_path[108];       // pathname of socket file  
  };`
- `struct msghdr`, `struct cmsghdr` (for ancillary data & file descriptor passing)

---

## 🔹 4. Intermediate Concepts
- **Abstract namespace sockets**: `sun_path[0] = '\0'` → not in filesystem.
- **Permission handling**: UDS access control via filesystem permissions.
- **Peer credential passing**: use `SO_PEERCRED`.
- **Socket pairs**: `socketpair(AF_UNIX, SOCK_STREAM, 0, sv[])`.

---

## 🔹 5. Advanced Topics
- **File descriptor passing**: e.g., send a pipe/socket between processes.
- **SCM_CREDENTIALS**: send process credentials over a socket.
- **Zero-copy communication** for high-performance IPC.
- **Non-blocking & multiplexing**: `select()`, `poll()`, `epoll()`.
- **Error handling & recovery**: peer crash, stale socket files.
- **Security**: access control with filesystem permissions & SELinux.

---

## 📚 References
- `man 7 unix` → Official Linux manpage for UNIX sockets.
- W. Richard Stevens, *UNIX Network Programming* (Volume 1).
- Michael Kerrisk, *The Linux Programming Interface*.

---
