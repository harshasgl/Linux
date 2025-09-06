#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/unix_socket_multiplex"
#define BUFFER_SIZE 128

int main() {
    int client_fd;
    struct sockaddr_un addr;
    char buffer[BUFFER_SIZE];

    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (connect(client_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("connect");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Enter two numbers (0 0 to exit):\n");

    while (1) {
        int num1, num2;
        printf("Enter numbers: ");
        if (scanf("%d %d", &num1, &num2) != 2) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n'); // clear stdin
            continue;
        }

        snprintf(buffer, sizeof(buffer), "%d %d", num1, num2);
        send(client_fd, buffer, strlen(buffer), 0);

        if (num1 == 0 && num2 == 0) {
            printf("Exiting...\n");
            break;
        }

        // Receive sum from server
        int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) {
            printf("Server disconnected\n");
            break;
        }
        buffer[bytes] = '\0';
        printf("%s", buffer);
    }

    close(client_fd);
    return 0;
}
