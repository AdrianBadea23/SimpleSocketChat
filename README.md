# Sockets in C

- socket = low level endpoint used for processing information across a network
- common network protocols like HTTP and FTP rely on sockets underneath to make connections

## Client Socket Workflow

- socket() => connect() => recv()
- client socket is created with a socket()
- connected to an address with connect() call
- retrive data with recv() call

## Server Socket Workflow

- create socket with a socket() call
- bind socket to an IP and port
- listen for connections
- accept a connection and call send() or recv() function
