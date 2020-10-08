#include "msg.h"

int main(int argc, char** argv)
{
    char out[4096];

    // Handle command line arguments with gnu getopt
    int option;
    while ((option = getopt(argc, argv, "rdh")) != -1) {
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
            break;
        default:
            break;
        }
        return 1;
    }

    if (argc == 2) {
        sendMessage(FILENAME, argv[1]);
        return 0;
    }

    // printf() displays the string inside quotation
    // Only will happen if presented the wrong arguments
    printf("Hello, World!\n");
    return -1;
}

