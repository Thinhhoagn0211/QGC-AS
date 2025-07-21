import argparse
from pymavlink import mavutil
from config.load import ConfigurationLoader

def main(config: dict):
    print(f"Source Address: {config['src_addr']}")
    # Create a UDP input server (bind to IP 192.168.144.100, port 14550)
    master = mavutil.mavlink_connection(
        'udp:localhost:14550',
        source_system=255  # Use 255 if you're not an actual MAV system
    )

    print("Listening for MAVLink packets on udp:192.168.144.100:14550")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Load configuration and run main function.')
    parser.add_argument('--config', type=str, default='config.yml', help='Path to the configuration file')
    args = parser.parse_args()

    config_loader = ConfigurationLoader(args.config)
    config = config_loader.load()
    print(f"Loaded configuration: {config}")
    main(config)