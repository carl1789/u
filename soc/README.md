# Windows Socket Programming Examples

This repository contains C++ socket programming examples adapted for Windows. The programs demonstrate basic TCP and UDP communication, including a simple echo server/client and a file transfer server/client, as well as a trigonometry calculator using UDP.

## Programs

- **win_client.cpp / win_server.cpp**: Basic TCP echo client and server.
- **win_fileclient.cpp / win_fileserver.cpp**: TCP file transfer client and server.
- **win_uclient.cpp / win_ufclient.cpp / win_userver.cpp / win_ufserver.cpp**: UDP trigonometry calculator client and server (uclient and ufclient are identical, userver and ufserver are identical).

## Compilation

To compile these programs on Windows, use a C++ compiler like g++ (from MinGW) or Visual Studio's cl.exe. You need to link with the Winsock library.

### Using g++ (MinGW):

```bash
g++ win_client.cpp -o win_client.exe -lws2_32
g++ win_server.cpp -o win_server.exe -lws2_32
g++ win_fileclient.cpp -o win_fileclient.exe -lws2_32
g++ win_fileserver.cpp -o win_fileserver.exe -lws2_32
g++ win_uclient.cpp -o win_uclient.exe -lws2_32
g++ win_ufclient.cpp -o win_ufclient.exe -lws2_32
g++ win_userver.cpp -o win_userver.exe -lws2_32
g++ win_ufserver.cpp -o win_ufserver.exe -lws2_32
```

### Using Visual Studio (cl.exe):

```bash
cl win_client.cpp /link ws2_32.lib
cl win_server.cpp /link ws2_32.lib
# And so on for each file
```

## Running the Programs

### TCP Echo Example:
1. Run the server: `win_server.exe`
2. In another terminal, run the client: `win_client.exe`

The client sends "Hello from Client!" and receives "Hello from Server!" back.

### File Transfer Example:
1. Ensure `sample.txt` exists in the directory.
2. Run the server: `win_fileserver.exe`
3. In another terminal, run the client: `win_fileclient.exe`

The client requests `sample.txt` and saves it as `received_sample.txt`.

### UDP Trigonometry Calculator:
1. Run the server: `win_userver.exe` (or `win_ufserver.exe`)
2. In another terminal, run the client: `win_uclient.exe` (or `win_ufclient.exe`)

Enter commands like "sin 30" to get the sine of 30 degrees. Type "exit" to quit.

## Notes

- These programs use localhost (127.0.0.1) for communication.
- Ports: TCP echo uses 8080, file transfer uses 9090, UDP calculator uses 65433.
- Ensure no firewall blocks the ports.
- For production use, add proper error handling and security measures.