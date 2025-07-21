class Receiver:
    def __init__(self, src_addr: str, dst_addr: str):
        self.src_addr = src_addr
        self.dst_addr = dst_addr

    def start(self):
        print(f"Starting receiver from {self.src_addr} to {self.dst_addr}")

    def stop(self):
        print("Stopping receiver")

    def receive_data(self):
        print("Receiving data...")