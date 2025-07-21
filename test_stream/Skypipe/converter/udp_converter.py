class Converter:
    def __init__(self, src_addr: str, dst_addr: str):
        self.src_addr = src_addr
        self.dst_addr = dst_addr

    def convert(self, data: bytes) -> bytes:
        # Placeholder for conversion logic
        return data

    def run(self):
        import socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.bind((self.src_addr.split(':')[0], int(self.src_addr.split(':')[1])))
        
        while True:
            data, addr = sock.recvfrom(1024)
            converted_data = self.convert(data)
            sock.sendto(converted_data, (self.dst_addr.split(':')[0], int(self.dst_addr.split(':')[1])))