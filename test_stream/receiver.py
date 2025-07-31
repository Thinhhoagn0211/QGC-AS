from pymavlink import mavutil
from generated.include.mavlink.gimbal import MAVLink  # adjust path as needed
# Connect to MAVLink stream
master = mavutil.mavlink_connection('udp:0.0.0.0:14550')
master.WIRE_PROTOCOL_VERSION = '2.0'

master.mav = MAVLink(master)
master.mav.srcSystem = 1
master.mav.srcComponent = 200  # your gimbal system/component ID
# Listen for custom message
while True:
    msg = master.recv_match(blocking=True)
    if msg:
        print(f"Received: {msg.get_type()}")
        if msg.get_type() == 'GIMBAL_RAW_GPS_DATA':
            print("✅ Custom GIMBAL_RAW_GPS_DATA received!")
            print(msg.to_dict())
