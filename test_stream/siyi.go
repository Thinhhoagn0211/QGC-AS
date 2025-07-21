package main

import (
	"fmt"
	"net"
	"os"
	"time"
)

func main() {
	// Define the target UDP address and port
	addr := "172.16.11.17:14445"

	// Define the UDP message to send
	data := []byte{0x55, 0x66, 0x01, 0x00, 0x00, 0x00, 0x02, 0x07, 0xf4}
	fmt.Printf("Sending data: % X\n", data)

	// Resolve UDP address
	udpAddr, err := net.ResolveUDPAddr("udp", addr)
	if err != nil {
		fmt.Println("Error resolving address:", err)
		os.Exit(1)
	}

	// Create UDP connection
	conn, err := net.DialUDP("udp", nil, udpAddr)
	if err != nil {
		fmt.Println("Error creating UDP connection:", err)
		os.Exit(1)
	}
	defer conn.Close()

	// Send the data
	_, err = conn.Write(data)
	if err != nil {
		fmt.Println("Error sending data:", err)
		os.Exit(1)
	}
	fmt.Println("Data sent successfully")

	// Set read timeout (optional, if expecting response)
	conn.SetReadDeadline(time.Now().Add(2 * time.Second))

	// Read response
	buf := make([]byte, 1024)
	n, addrResp, err := conn.ReadFromUDP(buf)
	if err != nil {
		fmt.Println("Error reading response:", err)
		return
	}

	fmt.Printf("Received %d bytes from %s: % X\n", n, addrResp, buf[:n])
}
