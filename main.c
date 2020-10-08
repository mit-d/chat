#include "msg.h"

int main(int argc, char** argv)
{
    char out[4096];

    // Handle command line arguments with gnu getopt
    int option;
    while ((option = getopt(argc, argv, "rdhs:")) != -1) {
        switch (option) {
        case 'r': // Receive Message and print to stdout
            //get_msg(SOCKET_NAME, out);
            break;
        case 'h': // Print help page
            printf("Usage: msg [options] \"message\"\n");
            printf("Options:\n");
            printf("  -r           receive a single message\n");
            printf("  -d           Start process as daemon. Receive messages until receiving a DOWN\n");
            printf("  -s [message] Send a single message, non-interactive\n");
            break;
        case 'd': // Start Daemon
            msgd(SOCKET_NAME, out);
            break;
        case 's': // Send message
            put_msg(SOCKET_NAME, optarg);
            break;
        default:
            break;
        }
        return EXIT_SUCCESS;
    }

    if (argc == 1) {
        printf("Send messages from stdin\n");
    }

    printf("UID/PID is %i/%i\n", getuid(), getpid());

    return EXIT_FAILURE;
}

