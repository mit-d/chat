# Design Documentation
This is a simple messaging server that takes advantage of UNIX sockets.

## Usage
If there is no server running, you must start one with `msg -d`.
This will start a server that forks into the background. Then, messages can be
sent and received.

### Sending Messages
To send a single message, non-interactively, you can use the `-s` flag. This
will send the optarg as a message.

### Receiving Messages
To receive a single message, you can use the `-r` flag. This will retrieve the
message from the server and write it to stdout. 

### Daemon
The messages will be stored in the daemon's memory. There will be a maximum
message size and a maximum backlog.

Once started, the daemon will open a socket and bind to the socket file
specified on the command line, or make a new one in `/temp`. 

Once a client connects, it will send a string. Depending on what it is, the
server will process that string and send a response. 

In the case of the client
sending a message, that message is pushed into the message queue. The server
responds with an empty message in the case of a successful message or an error
code. 

For a client to receive a message, will send a string with the command "REQ", 
a space, and then the client's unique identity. The server will return the first
message that isn't tagged with the same identity. This is to allow two users to
communicate with the server at the same time without retrieving their own
messages.

### Interactive Mode
You will be able to connect to the server in interactive mode, allowing you to
chat with other users. Messages sent in interactive mode will be tagged with a
unique identity. If not specified, this will be in the form of the PID of the interactive process. 

## Options:
-i [Identity],              Interactive mode
-s [Message],               Send Message
-r,                         Receive message and print to stdout.
-d [socket file],           Start the daemon and bind to the specified socket file
