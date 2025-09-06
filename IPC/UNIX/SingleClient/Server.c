#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/unix_socket_add"
#define BUFFER_SIZE 128

int main() {
    int server_fd, client_fd;
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE];

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

    printf("Server running 24/7 at %s\n", SOCKET_PATH);

    while (1) {
        // 5. Accept client
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        printf("Client connected\n");

        while (1) {
            int num1, num2, sum;
            // Receive numbers from client
            int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
            if (bytes <= 0) break; // client disconnected
            buffer[bytes] = '\0';

            // Parse numbers
            if (sscanf(buffer, "%d %d", &num1, &num2) != 2) {
                const char *msg = "Invalid input. Send two integers.\n";
                send(client_fd, msg, strlen(msg), 0);
                continue;
            }

            // Check for client exit signal
            if (num1 == 0 && num2 == 0) {
                printf("Client requested disconnect\n");
                break;
            }

            sum = num1 + num2;
            snprintf(buffer, sizeof(buffer), "Sum: %d\n", sum);

            // Send sum back to client
            send(client_fd, buffer, strlen(buffer), 0);
        }

        close(client_fd);
        printf("Client disconnected\n");
    }

    // Cleanup (never reached)
    close(server_fd);
    unlink(SOCKET_PATH);

    return 0;
}
