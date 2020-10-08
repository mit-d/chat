#include "msg.h"

int msgd(char* socket_file, char* out)
{
    if (fork() == 0) {
        printf("starting daemon...");
        fflush(stdout);

        struct sockaddr_un name;
        int down_flag = 0;
        int ret;
        int connection_socket;
        int data_socket;
        char buffer[BUFFER_SIZE];

        /* Remove the unix socket if it exists */
        unlink(socket_file);

        /* Create local socket. */
        connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
        if (connection_socket == -1) {
            perror("socket");
            exit(EXIT_FAILURE);
        }

        /*
         * For portability clear the whole structure, since some
         * implementations have additional (nonstandard) fields
         */
        memset(&name, 0, sizeof(struct sockaddr_un));

        /* Bind socket to socket name. */
        name.sun_family = AF_UNIX;
        strncpy(name.sun_path, socket_file, sizeof(name.sun_path) - 1);

        ret = bind(connection_socket, (const struct sockaddr*)&name, sizeof(struct sockaddr_un));
        if (ret == -1) {
            perror("bind");
            exit(EXIT_FAILURE);
        }

        /*
         * Prepare for accepting connections. The backlog size is set
         * to 20. So while one request is being processed other requests
         * can be waiting.
         */

        ret = listen(connection_socket, 20);
        if (ret == -1) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        // MAIN SERVER LOOP //
        for (;;) {
            /* Wait for incoming connection. */
            data_socket = accept(connection_socket, NULL, NULL);
            if (data_socket == -1) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            for (;;) {
                /* Wait for next data packet. */

                ret = read(data_socket, buffer, BUFFER_SIZE);
                if (ret == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
                }

                /* Ensure buffer is 0-terminated. */
                buffer[BUFFER_SIZE - 1] = 0;

                /* Handle commands. */
                // Exit on a 'DOWN' command
                if (!strncmp(buffer, "DOWN", BUFFER_SIZE)) {
                    down_flag = 1;
                    break;
                }

                if (!strncmp(buffer, "END", BUFFER_SIZE)) {
                    break;
                }

                printf("%s\n", buffer);
            }

            /* Send result here.. */
            ret = write(data_socket, buffer, BUFFER_SIZE);

            if (ret == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }

            /* Close socket. */
            close(data_socket);

            /* Quit on DOWN command. */
            if (down_flag) {
                break;
            }
        }
    }
    return 0;
}
