from pymavlink import mavutil

# Create a connection to UDP port 60002, listening for messages
master = mavutil.mavlink_connection('udp:103.92.24.110:60002')

print("Listening for MAVLink messages on UDP port 14445...")

while True:
    msg = master.recv_match(blocking=True)
    if msg:
        print(msg)
