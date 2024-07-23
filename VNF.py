import socket
import sys
import ctypes
import array
from ctypes import *

# Create an SCTP socket object
s = socket.socket(socket.AF_INET,
                  socket.SOCK_STREAM,
                  socket.IPPROTO_SCTP)

# Get local Host machine name
host = '127.0.0.1'
port = 22222

# C structure mapping
class PNF_READY(Structure):
    _fields_ = [("segment_length",      c_int, 16),
                ("more",                c_int, 1),
                ("segment_number",      c_int, 7),
                ("sequence_number",     c_int, 8),
                ("transit_timestamp",   c_int, 32),

                ("termination_type",    c_int, 8),
                ("phy_id",              c_int, 8),
                ("message_id",          c_int, 16),
                ("length",              c_int, 32),

                ("version_info",        c_uint32)]

# Bind to port
try:
    s.bind((host, port))
except socket.error as msg:
    print("Bind failed. Error Code : " + str(msg[0]) + " Message " + msg[1])
    sys.exit()
print("Socket bind complete, IP: " + str(host) + ", port:" + str(port))

# Listen for a single transmission
s.listen(1)
print("Socket now listening")

while(True):
    client, addr = s.accept()
    print("Connection Accepted")
    
    raw = client.recv(32)
    data = PNF_READY.from_buffer_copy(raw)

    print("Data received.\nSegment length =", data.segment_length)
    print("More flag =", data.more)
    print("Segment number =", data.segment_number)
    print("Sequence number =", data.sequence_number)
    print("Timestamp =", data.transit_timestamp)

    print("Termination type =", data.termination_type)
    print("Termination type =", data.phy_id)
    print("Termination type =", data.message_id)
    print("Termination type =", data.length)

    print("Version info =", data.version_info)

    client.close()
    sys.exit()
