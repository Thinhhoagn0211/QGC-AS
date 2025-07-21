from pymavlink import mavutil
import time

# Open UDP output connection to the remote server
target_ip = "103.92.24.110"
target_port = 60002
master = mavutil.mavlink_connection(f'udpout:{target_ip}:{target_port}')

# Create a dummy system and component ID
sysid = 1
compid = 1

# Wait a moment for the connection to settle
time.sleep(1)

# Send a heartbeat message
master.mav.heartbeat_send(
    mavutil.mavlink.MAV_TYPE_GCS,      # Type
    mavutil.mavlink.MAV_AUTOPILOT_INVALID,  # Autopilot
    0, 0, 0                             # base_mode, custom_mode, system_status
)
print("Heartbeat sent to", target_ip, ":", target_port)

# Optionally: send more MAVLink messages, e.g., command_long
master.mav.command_long_send(
    sysid,     # target system
    compid,    # target component
    31000,     # command ID (custom)
    0,         # confirmation
    1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7   # parameters
)
print("Custom command 31000 sent.")
