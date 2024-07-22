import socket
import sys

# Create an SCTP socket object
s = socket.socket(socket.AF_INET,
                  socket.SOCK_STREAM,
                  socket.IPPROTO_SCTP)

# Get local Host machine name
host = socket.gethostname()
port = 22222

# Bind to port
try:
    s.bind((host, port))
except socket.error as msg:
    print("Bind failed. Error Code : " + str(msg[0]) + " Message " + msg[1])
    sys.exit()
print("Socket bind complete")

# Listen for a single transmission
s.listen(1)
print("Socket now listening")

while(True):
    client = s.accept()
    print("Connection Accepted")
    
    data = client.recv(1024)
    print("Data received: ", data)

    client.close()
