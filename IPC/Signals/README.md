# 🔹 5. Signals

## Basics
- Signals are **asynchronous notifications** sent to a process to notify it of events.
- Types:
  - **Standard signals**: e.g., `SIGINT`, `SIGTERM`, `SIGKILL`, `SIGUSR1`, `SIGUSR2`
  - **Realtime signals**: `SIGRTMIN` to `SIGRTMAX` (queued, priority-aware)
- Signals can be **sent by the kernel**, other processes, or self (`raise()`).

## Signal Handling
- **Default actions**: terminate, ignore, stop, continue
- **Custom handlers**: using `signal()` or `sigaction()`

### System Calls / Functions
- `signal(int signum, void (*handler)(int))` → simple handler setup
- `sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)` → advanced handler
- `sigprocmask(int how, const sigset_t *set, sigset_t *oldset)` → block/unblock signals
- `sigpending(sigset_t *set)` → check pending signals
- `kill(pid_t pid, int sig)` → send signal to another process
- `raise(int sig)` → send signal to self
- `pause()` → wait for a signal
- `alarm(unsigned seconds)` → send `SIGALRM` after delay
- `setitimer()` → interval timers
- `sigqueue()` → send signal with accompanying data (realtime signals)

## Structures
- `struct sigaction {  
    void (*sa_handler)(int);  // or sa_sigaction for extended info  
    sigset_t sa_mask;          // signals to block during handler  
    int sa_flags;              // SA_RESTART, SA_SIGINFO, etc.  
    void (*sa_restorer)(void);
  };`
- `sigset_t` → used for blocking/unblocking signals

## Intermediate Concepts
- **Signal blocking** → prevent signal delivery temporarily
- **Signal masking** → using `sigprocmask()` or `pthread_sigmask()`
- **Reentrant handlers** → handler must be async-signal-safe
- **SA_RESTART flag** → restart interrupted syscalls automatically
- **Pending signals** → signals sent while blocked are queued (except standard signals)

## Advanced Topics
- **Realtime signals** → queued, ordered by priority
- **siginfo_t** → additional info in handler (sender PID, signal code, value)
- **Signals & multithreading** → `pthread_sigmask()` per thread
- **Signal-driven I/O** → `SIGIO` for asynchronous I/O
- **Timers & signals** → `timer_create()` + `SIGEV_SIGNAL`
- **Reliable vs unreliable signals** → POSIX vs older UNIX behavior

## Practical Projects
1. Implement a **custom Ctrl+C handler** (SIGINT)
2. **Parent-child signal communication** using `kill()`
3. Use `alarm()` or `setitimer()` for periodic tasks
4. Implement a **signal-based notification system** between processes
5. Queue messages via **realtime signals** (`sigqueue()`)
6. Handle asynchronous **SIGIO** events from sockets or pipes
7. Demonstrate multithreaded signal masking and delivery

## References
- `man 7 signal`
- `man 2 sigaction`, `man 2 sigprocmask`, `man 2 kill`, `man 2 sigqueue`
- Michael Kerrisk — *The Linux Programming Interface*
