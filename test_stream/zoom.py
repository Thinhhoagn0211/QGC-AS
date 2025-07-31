import time
from pymavlink import mavutil
import generated.include.mavlink.gimbal as gimbal
sender = mavutil.mavlink_connection("udpout:172.16.11.17:14445", source_system=1)
sender.mav = gimbal.MAVLink(sender)
sender.WIRE_PROTOCOL_VERSION = '2.0'


# Send message
# msg = gimbal.MAVLink_request_video_stitching_mode_message(dummy=0)
# msg = gimbal.MAVLink_auto_focus_message(auto_focus=1, touch_x=30, touch_y=40)
# msg = gimbal.MAVLink_request_system_info_message(
#     dummy=0
# )

# Enable laser
# sender.mav.send(gimbal.MAVLink_set_laser_state_message(laser_state=1))
# time.sleep(0.5)

# # Send GPS and attitude with real timestamps
# start_time = time.monotonic()
# time_boot_ms = int((time.monotonic() - start_time) * 1000)
# sender.mav.send(gimbal.MAVLink_send_raw_gps_to_gimbal_message(
#     time_boot_ms=time_boot_ms,
#     lat=2227683,
#     lon=11417612,
#     alt=1700,
#     alt_ellipsoid=0,
#     vn=0,
#     ve=0,
#     vd=0,
# ))

# sender.mav.send(gimbal.MAVLink_send_aircraft_attitude_data_to_gimbal_message(
#     time_boot_ms=time_boot_ms,
#     roll=0,
#     pitch=6000,
#     yaw=15000,
#     roll_speed=0,
#     pitch_speed=0,
#     yaw_speed=0,
# ))

# # Wait and ensure gimbal has distance
# sender.mav.send(gimbal.MAVLink_request_laser_distance_target_longitude_latitude_message(dummy=0))
# time.sleep(0.3)


# msg = gimbal.MAVLink_request_laser_distance_measurement_message(
#     dummy=0,
# )

# msg = gimbal.MAVLink_request_current_gimbal_mode_message(
#     dummy=0,
# )

# msg = gimbal.MAVLink_request_gimbal_to_send_data_stream_message(
#     data_type=2,data_freq=1
# )

msg = gimbal.MAVLink_set_gimbal_attitude_angles_message(
    yaw= 1500,
    pitch= 60,
)

# msg = gimbal.MAVLink_request_gimbal_to_send_data_stream_message(
#     data_freq=1,
#     data_type=2,
# )

# msg = gimbal.MAVLink_request_system_info_message(
#     dummy=0
# )

# msg = gimbal.MAVLink_set_laser_state_message(
#     laser_state=1,  # 0: off, 1: on
# )

# msg = gimbal.MAVLink_request_video_stitching_mode_message(
#     dummy=0
# )

# msg = gimbal.MAVLink_set_video_stitching_mode_message(
#     vdisp_mode=4
# )

# msg = gimbal.MAVLink_request_gimbal_to_send_data_stream_message(
#     data_freq=0,
#     data_type=2,
# )
# sender.mav.send(msg)
# print(f"[SEND] Sent message with center_pos = {msg}")

# Receive the message (even if it's our own)
while True:
    received = sender.recv_match(blocking=True, timeout=3)
    if received:
        print(f"[SENDER] Got ACK: command={received}")
    else:
        print("[SENDER] No ACK received")

