#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdint.h>

#define RECV_BUF_SIZE 64
#define SERVER_PORT 37260 // Gimbal Camera (Server) Port
#define SERVER_IP "192.168.144.25" // Gimbal Camera (Server) IP

int main() {
    int sockfd;
    int ret, i, recv_len;
    struct sockaddr_in send_addr, recv_addr;
    //55 66 01 02 00 00 00 07 64 64 3d cf
    unsigned char send_buf[] = {0x55, 0x66, 0x01, 0x01, 0x00, 0x00, 0x00, 0x08, 0x01, 0xd1, 0x12};
    unsigned char recv_buf[RECV_BUF_SIZE] = {0};
    /* Create a UDP socket
    AF_INET: IPv4 address
    SOCK_DGRAM: UDP protocol
    0: Automatically select the corresponding default protocol
    */

    
    printf("Sent bytes: ");
    for (int i = 0; i < sizeof(send_buf); ++i)
        printf("%02X ", send_buf[i]);
    printf("\n");

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket");
    exit(1);
    }
    printf("Socket created successfully\n");
    /* Set the IP address and port number of the gimbal camera
    sin_family: IPv4 address
    sin_addr.s_addr: Gimbal camera IP address
    sin_port: Gimbal camera port number
    */
    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    send_addr.sin_port = htons(SERVER_PORT);
        /* Send frame data
        sockfd: Socket file descriptor
        send_buf: The starting address of the data to be sent in memory
    sizeof(send_buf): Length of the data to be sent
    0: Send flag, usually 0
    (struct sockaddr *)&send_addr: Structure pointer of the data receiving end’s
    address (including IP address and port number)
    addr_len: Size of the data receiving end address structure
    */
    printf("Send HEX data\n");
    socklen_t addr_len = sizeof(struct sockaddr_in);
    if (sendto(sockfd, send_buf, sizeof(send_buf), 0, (struct sockaddr *)&send_addr, addr_len) < 0) {
    perror("sendto");
    exit(1);
    }
    printf("Data sent successfully\n");
    /* Receive the returned data from the gimbal camera
    sockfd: Socket file descriptor
    recv_buf: Memory location where the received data will be stored
    RECV_BUUF_SIZE: Size of the buffer, i.e., the expected maximumdata length
    0: Receive flag, usually 0
    (struct sockaddr *)&recv_addr: Structure that will be filled with the sending end’s
    address (including IP and port)
    &addr_len: The location to store the actual size of the sender's address after
    the call
    */
    recv_len = recvfrom(sockfd, recv_buf, RECV_BUF_SIZE, 0, (struct sockaddr*)&recv_addr, &addr_len);
    if (recv_len < 0) {
        printf("Failed to receive data: %s\n", strerror(errno));
        perror("recvfrom");
        exit(1);
    }
    // Print the received data in hexadecimal form
    printf("Received HEX data: ");
    for (int i = 0; i < recv_len; i++) {
    printf("%02x ", recv_buf[i]);
    }

    printf("\n");
    // Close the socket
    close(sockfd);
    return 0;   
}