#include "msg.h"

int main(int argc, char** argv)
{
    char out[BUF_SIZE];

    // Handle command line arguments with gnu getopt
    int option;
    while ((option = getopt(argc, argv, "irdhs:")) != -1) {
        switch (option) {
        case 'i':
            printf("Entering interactive mode...");
            for (;;) {
                printf("%s>>", "User");
                fgets(out, BUF_SIZE, stdin);
            }
            break;
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
        case 'd':
            /* The daemon will work as a server, redirecting all received
             * messages to standard output 
             * */
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

    return EXIT_FAILURE;
}

