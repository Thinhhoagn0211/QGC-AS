from pymavlink import mavutil
import random

# Kết nối tới QGroundControl hoặc thiết bị đang lắng nghe trên port 14551
master = mavutil.mavlink_connection('udpout:172.16.11.14:14551')

print("✅ Heartbeat received!")
print("Target system:", master.target_system)
print("Target component:", master.target_component)

# Các tham số bạn cần
auto_focus = 1
touch_x = random.randint(0, 1920)
touch_y = random.randint(0, 1080)

# Gửi lệnh COMMAND_LONG với command = 10001
master.mav.command_long_send(
    master.target_system,        # Phải là giá trị thực nhận từ heartbeat (thường là 1)
    master.target_component,     # Thường là 1
    10001,                       # Lệnh custom
    1,                           # Confirmation
    auto_focus,                  # param1
    touch_x,                     # param2
    touch_y,                     # param3
    0, 0, 0, 0                   # param4–7
)
print("✅ COMMAND_LONG sent with command 10001.")

# from pymavlink import mavutil
# import random

# # Client binds locally to receive messages (bidirectional)
# master = mavutil.mavlink_connection('udp:0.0.0.0:14551', source_system=1)


# # Listen for any responses
# while True:
#     msg = master.recv_match(blocking=True, timeout=5)
#     if msg:
#         print(f"Received message: {msg}")
#     else:
#         print("⏰ No message received in 5 seconds.")
#         break


