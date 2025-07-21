from pymavlink import mavutil

# Connect via UDP send-only
master = mavutil.mavlink_connection('udpout:192.168.1.29:14445')
# master.wait_heartbeat()
# Send command without waiting for heartbeat
master.mav.command_long_send(
    master.target_system,  # Target system ID
    master.target_component,  # Target component ID
    10126,  # MAV_CMD_SET_CAMERA_SOURCE
    0,      # Confirmation
    0,      # main_source
    0,      # sub_source
    16, 0, 0, 0, 0
)

print("✅ MAV_CMD_SET_CAMERA_SOURCE sent (no heartbeat check)")


