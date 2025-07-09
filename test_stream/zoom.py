from pymavlink import mavutil

# Connect to the camera's MAVLink port
master = mavutil.mavlink_connection('/dev/ttyACM1', baud=115200)
master.wait_heartbeat()
print("✅ Connected to system %d component %d" % (master.target_system, master.target_component))

MAV_CMD_REQUEST_MESSAGE = 512
CAMERA_SETTINGS = 267

master.mav.command_long_send(
    master.target_system,
    master.target_component,
    512,  # MAV_CMD_REQUEST_MESSAGE
    0,
    260,  # CAMERA_SETTINGS
    0, 0, 0, 0, 0, 0
)

msg = master.recv_match(type='CAMERA_SETTINGS', blocking=True, timeout=5)
if msg:
    print(f"Zoom Level: {msg.zoomLevel}")