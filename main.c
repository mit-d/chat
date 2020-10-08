#include "msg.h"

int main(int argc, char** argv)
{
    char out[4096];

    // Handle command line arguments with gnu getopt
    int option;
    while ((option = getopt(argc, argv, "rdhs:")) != -1) {
        switch (option) {
        case 'r': // Receive Message
            // Open File for reading
            /* receiveMessage(FILENAME, out); */
            /* printf("Message: %s\n", out); */
            break;
        case 'h':
            /* printf("Usage: msg [options] \"message\"\n"); */
            /* printf("Options:\n"); */
            /* printf("  -r  receive message\n"); */
            /* printf("  -d  Start process as daemon\n"); */
            break;
        case 'd': // Start Daemon
            msgd(SOCKET_NAME, out);
            break;
        case 's': // Start Daemon
            put_msg(SOCKET_NAME, optarg);
            break;
        default:
            break;
        }
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

