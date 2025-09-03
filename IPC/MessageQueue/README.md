# Linux IPC Mastery Roadmap

This README provides a structured roadmap to master **Inter-Process Communication (IPC)** in Linux.  
It covers **UNIX Domain Sockets, Shared Memory, Message Queues, and Network Sockets**, with system calls, structures, and project ideas.

---

# 🔹 1. UNIX Domain Sockets

## Basics
- IPC mechanism using the filesystem namespace (not network).
- Types:
  - `SOCK_STREAM` → reliable, connection-oriented (like TCP).
  - `SOCK_DGRAM` → datagram, connectionless (like UDP).
  - `SOCK_SEQPACKET` → sequenced, reliable datagrams.
- Difference: `AF_INET` (network sockets) vs `AF_UNIX` (local IPC).

## System Calls
- **Socket creation & setup**  
  `socket()`, `bind()`, `listen()`, `accept()`, `connect()`
- **Data transfer**  
  `send()`, `recv()`, `sendto()`, `recvfrom()`, `read()`, `write()`
- **File descriptor passing**  
  `sendmsg()`, `recvmsg()`
- **Socket options**  
  `getsockopt()`, `setsockopt()` (SO_PASSCRED, SO_PEERCRED, SO_RCVBUF, SO_SNDBUF)
- **Closing**  
  `shutdown()`, `close()`

## Structures
- `struct sockaddr_un`  
- `struct msghdr`, `struct cmsghdr` (for ancillary data & FD passing).

## Intermediate Concepts
- Abstract namespace sockets (`sun_path[0] = '\0'`).
- Permissions (filesystem-based).
- Peer credentials (`SO_PEERCRED`).
- Socket pairs → `socketpair()`.

## Advanced Topics
- File descriptor passing.
- SCM_CREDENTIALS (sending process credentials).
- Zero-copy communication.
- Non-blocking I/O: `select()`, `poll()`, `epoll()`.
- Error handling & security.

---

# 🔹 2. Shared Memory

## Basics
- Fastest IPC (direct memory access).
- Types:
  - **System V**: `shmget`, `shmat`, `shmdt`, `shmctl`.
  - **POSIX**: `shm_open`, `mmap`, `munmap`, `shm_unlink`.
- Requires synchronization (semaphores/mutexes).

## System V System Calls
- `shmget()`, `shmat()`, `shmdt()`, `shmctl()`

## POSIX System Calls
- `shm_open()`, `ftruncate()`, `mmap()`, `munmap()`, `close()`, `shm_unlink()`

## Data Structures
- **System V**: `struct shmid_ds`, `struct ipc_perm`
- **POSIX**: File descriptors (no special struct)

## Synchronization
- System V: `semget`, `semop`, `semctl`
- POSIX: `sem_open`, `sem_wait`, `sem_post`
- POSIX pthread mutexes with `PTHREAD_PROCESS_SHARED`

## Intermediate Concepts
- Shared memory lifecycle.
- Permissions & persistence.
- Anonymous shared memory → `mmap(MAP_SHARED | MAP_ANONYMOUS)`
- File-backed shared memory.

## Advanced Topics
- Huge pages (`MAP_HUGETLB`)
- Zero-copy techniques.
- Passing shared memory descriptors via UNIX sockets.
- `/dev/shm` in containers.
- NUMA-aware allocation.
- Security (permissions, namespaces).

## Projects
- Writer/Reader echo app.
- Producer-consumer with semaphores.
- Shared memory ring buffer.
- Multi-process matrix multiplication.
- Mini key-value store (like Redis).
- UDS + shared memory hybrid system.

---

# 🔹 3. Message Queues

## Basics
- IPC via **discrete messages** (not streams).
- Two APIs:
  - **System V** → `msgget`, `msgsnd`, `msgrcv`, `msgctl`
  - **POSIX** → `mq_open`, `mq_send`, `mq_receive`, `mq_close`, `mq_unlink`
- POSIX supports message priorities.

## System V System Calls
- `msgget()`, `msgsnd()`, `msgrcv()`, `msgctl()`

## POSIX Functions
- `mq_open()`, `mq_send()`, `mq_receive()`
- `mq_getattr()`, `mq_setattr()`
- `mq_close()`, `mq_unlink()`

## Structures
- **System V**:  
  ```c
  struct msgbuf {
      long mtype;
      char mtext[1];
  };
