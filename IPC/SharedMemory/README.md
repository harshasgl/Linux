# Shared Memory Mastery Roadmap

This guide covers the complete set of topics, system calls, and projects you need to master **Shared Memory IPC** in Linux.

---

## 🔹 1. Basics
- Shared memory = region of memory accessible by multiple processes.
- Fastest IPC (direct memory access, no kernel copying).
- Types:
  - **System V Shared Memory** (classic, older).
  - **POSIX Shared Memory** (modern, portable).
- Limitation: No built-in synchronization → must use semaphores/mutex.

---

## 🔹 2. Essential System Calls

### System V Shared Memory
- `shmget(key, size, shmflg)` → create/get shared memory segment
- `shmat(shmid, shmaddr, shmflg)` → attach to process space
- `shmdt(shmaddr)` → detach from process space
- `shmctl(shmid, cmd, buf)` → control ops (remove, inspect, set)

### POSIX Shared Memory
- `shm_open(name, oflag, mode)` → create/open shared memory object
- `ftruncate(fd, length)` → set size of shared memory
- `mmap(addr, length, prot, flags, fd, offset)` → map memory into process
- `munmap(addr, length)` → unmap shared memory
- `close(fd)` → close descriptor
- `shm_unlink(name)` → remove shared memory object

---

## 🔹 3. Data Structures
- **System V**: 
  - `struct shmid_ds`
  - `struct ipc_perm`
- **POSIX**: controlled via file descriptors (no special structure).

---

## 🔹 4. Synchronization
Shared memory does not provide synchronization. Combine it with:
- **System V Semaphores**: `semget`, `semop`, `semctl`
- **POSIX Semaphores**: `sem_open`, `sem_wait`, `sem_post`, `sem_close`, `sem_unlink`
- **POSIX Mutex/Cond Var**: `pthread_mutexattr_setpshared`

---

## 🔹 5. Intermediate Concepts
- Shared memory lifecycle: **create → attach → use → detach → remove**
- Permissions and ownership
- Persistence differences:
  - System V: persists until `IPC_RMID`
  - POSIX: persists until `shm_unlink`
- Anonymous shared memory: `mmap(MAP_SHARED | MAP_ANONYMOUS, …)`
- File-backed shared memory: `mmap` on files

---

## 🔹 6. Advanced Topics
- **Huge pages** with `MAP_HUGETLB`
- **Zero-copy** data sharing
- Passing shared memory descriptors over **UNIX domain sockets**
- Shared memory in containers (`/dev/shm`)
- NUMA-aware allocation
- Security (permissions, SELinux, namespaces)

---

## 📚 References
- `man 2 shmget`, `man 2 shmat`, `man 2 shmctl`
- `man 3 shm_open`, `man 2 mmap`
- *Advanced Programming in the UNIX Environment* — W. Richard Stevens
- *The Linux Programming Interface* — Michael Kerrisk

---
