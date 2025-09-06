#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/unix_socket_multiplex"
#define BUFFER_SIZE 128
#define MAX_CLIENTS 10

int main() {
    int server_fd, client_fd, max_fd, activity, i;
    int client_fds[MAX_CLIENTS];
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE];

    fd_set read_fds;

    // Initialize all client_fds to -1
    for (i = 0; i < MAX_CLIENTS; i++) client_fds[i] = -1;

    // 1. Create socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 2. Remove old socket file
    unlink(SOCKET_PATH);

    // 3. Bind
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        unlink(SOCKET_PATH);
        exit(EXIT_FAILURE);
    }

    printf("Multiplexed server running at %s\n", SOCKET_PATH);

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(server_fd, &read_fds);
        max_fd = server_fd;

        // Add client sockets to fd set
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (client_fds[i] > 0)
                FD_SET(client_fds[i], &read_fds);
            if (client_fds[i] > max_fd)
                max_fd = client_fds[i];
        }

        // Wait for activity
        activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (activity < 0 && errno != EINTR) {
            perror("select");
            break;
        }

        // Incoming connection
        if (FD_ISSET(server_fd, &read_fds)) {
            client_fd = accept(server_fd, NULL, NULL);
            if (client_fd < 0) {
                perror("accept");
                continue;
            }

            printf("New client connected: fd=%d\n", client_fd);

            // Add new client to array
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_fds[i] == -1) {
                    client_fds[i] = client_fd;
                    break;
                }
            }
            if (i == MAX_CLIENTS) {
                printf("Max clients reached. Connection rejected.\n");
                close(client_fd);
            }
        }

        // Check all clients for incoming data
        for (i = 0; i < MAX_CLIENTS; i++) {
            int fd = client_fds[i];
            if (fd != -1 && FD_ISSET(fd, &read_fds)) {
                int bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);
                if (bytes <= 0) {
                    // Client disconnected
                    printf("Client fd=%d disconnected\n", fd);
                    close(fd);
                    client_fds[i] = -1;
                } else {
                    buffer[bytes] = '\0';
                    int num1, num2, sum;
                    if (sscanf(buffer, "%d %d", &num1, &num2) != 2) {
                        const char *msg = "Invalid input. Send two integers.\n";
                        send(fd, msg, strlen(msg), 0);
                        continue;
                    }
                    if (num1 == 0 && num2 == 0) {
                        printf("Client fd=%d requested disconnect\n", fd);
                        close(fd);
                        client_fds[i] = -1;
                        continue;
                    }
                    sum = num1 + num2;
                    snprintf(buffer, sizeof(buffer), "Sum: %d\n", sum);
                    send(fd, buffer, strlen(buffer), 0);
                }
            }
        }
    }

    // Cleanup
    close(server_fd);
    unlink(SOCKET_PATH);
    return 0;
}
