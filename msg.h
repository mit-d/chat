#ifndef _MSG_H__
#define _MSG_H__

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/817f599099859209eac6c2b45f7f302c.socket"
#define BUFFER_SIZE 12
#define BUF_SIZE 4096

int put_msg(char* socket_file, char* message);
int get_msg(char* socket_file, char* message);
int msgd(char* socket_file, char* out);

#endif
