/**
 * @file iperf_client.c
 * @author Product application department
 * @brief  iperf_client 文件
 * @version V1.0
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */

// 头文件包含
#include "iperf_client.h"
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/api.h"
#include <lwip/sockets.h>

// 全局变量定义
#define IPERF_BUFSZ 256 //(4 * 1024)

// 函数定义

/**
 * @brief iperf_client 初始化函数
 *
 * @param thread_param
 */
static void iperf_client(void *thread_param)
{
    int sock = -1, i;
    struct sockaddr_in client_addr;
    uint8_t *send_buf;
    u32_t tick1, tick2;
    uint64_t sentlen;
    ip4_addr_t ipaddr;
    printf("client mode\r\n");
    printf("目地IP地址:%d.%d.%d.%d \t 端口号:%d\n\n",
           DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3, DEST_PORT);

    printf("请将电脑上位机设置为TCP Server.在User/arch/sys_arch.h文件中将目标IP地址修改为您电脑上的IP地址\n\n");

    printf("修改对应的宏定义:DEST_IP_ADDR0,DEST_IP_ADDR1,DEST_IP_ADDR2,DEST_IP_ADDR3,DEST_PORT\n\n");

    send_buf = (uint8_t *)pvPortMalloc(IPERF_BUFSZ);

    // printf("pvPortMalloc oK send_buf = %08x\n\n",send_buf);

    IP4_ADDR(&ipaddr, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3);

    if (!send_buf)
        return;

    for (i = 0; i < IPERF_BUFSZ; i++)
        send_buf[i] = i & 0xff;

    while (1)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            printf("Socket error\n");
            vTaskDelay(10);
            continue;
        }

        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(DEST_PORT);
        client_addr.sin_addr.s_addr = ipaddr.addr;
        memset(&(client_addr.sin_zero), 0, sizeof(client_addr.sin_zero));

        if (connect(sock,
                    (struct sockaddr *)&client_addr,
                    sizeof(struct sockaddr)) == -1)
        {
            printf("Connect failed!\n");
            closesocket(sock);
            vTaskDelay(10);
            continue;
        }

        printf("Connect to iperf server successful!\n");
        tick1 = sys_now();
        while (1)
        {
            tick2 = sys_now();
            if (tick2 - tick1 >= configTICK_RATE_HZ * 5)
            {
                float f;
                f = (float)(sentlen * configTICK_RATE_HZ / 125 / (tick2 - tick1));
                f /= 1000.0f;
                printf("send speed = %.4f Mbps!\n", f);

                tick1 = tick2;
                sentlen = 0;
            }

            if (write(sock, send_buf, IPERF_BUFSZ) < 0)
                break;
            else
            {
                sentlen += IPERF_BUFSZ;
            }
        }
        closesocket(sock);
    }
}

/**
 * @brief iperf_server 初始化函数
 *
 * @param thread_param
 */
static void iperf_server(void *thread_param)
{
    uint8_t *recv_data;
    socklen_t sin_size;
    u32_t tick1, tick2;
    int sock = -1, connected, bytes_received;
    uint64_t recvlen;
    struct sockaddr_in server_addr, client_addr;
    char speed[32] = {0};
    fd_set readset;
    struct timeval timeout;
    printf("server mode\r\n");
    recv_data = (uint8_t *)pvPortMalloc(IPERF_BUFSZ);
    if (recv_data == NULL)
    {
        printf("No memory\n");
        goto __exit;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("Socket error\n");
        goto __exit;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DEST_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), 0x0, sizeof(server_addr.sin_zero));

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        printf("Unable to bind\n");
        goto __exit;
    }

    if (listen(sock, 5) == -1)
    {
        printf("Listen error\n");
        goto __exit;
    }

    timeout.tv_sec = 30;
    timeout.tv_usec = 0;

    while (1)
    {
        FD_ZERO(&readset);
        FD_SET(sock, &readset);

        if (select(sock + 1, &readset, NULL, NULL, &timeout) == 0)
            continue;

        sin_size = sizeof(struct sockaddr_in);

        connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);

        printf("new client connected from (%s, %d)\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        {
            int flag = 1;

            setsockopt(connected,
                       IPPROTO_TCP,   /* set option at TCP level */
                       TCP_NODELAY,   /* name of option */
                       (void *)&flag, /* the cast is historical cruft */
                       sizeof(int));  /* length of option value */
        }

        recvlen = 0;
        tick1 = sys_now();
        while (1)
        {
            bytes_received = recv(connected, recv_data, IPERF_BUFSZ, 0);
            if (bytes_received <= 0)
                break;
            //            if(write(connected,recv_data,bytes_received) < 0) break;

            recvlen += bytes_received;

            tick2 = sys_now();
            if (tick2 - tick1 >= configTICK_RATE_HZ * 5)
            {
                float f;

                f = (float)(recvlen * configTICK_RATE_HZ / 125 / (tick2 - tick1));
                f /= 1000.0f;
                snprintf(speed, sizeof(speed), "%.4f Mbps!\n", f);
                printf("%s", speed);
                tick1 = tick2;
                recvlen = 0;
            }
        }
        printf("client disconnected (%s, %d)\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        if (connected >= 0)
            closesocket(connected);
        connected = -1;
    }

__exit:
    if (sock >= 0)
        closesocket(sock);
    if (recv_data)
        free(recv_data);
}

/**
 * @brief iperf 初始化函数
 *
 */
void iperf_client_init(void)
{
    //    sys_thread_new("iperf_server", iperf_server, NULL, 2048, 8);//开发板做server端
    sys_thread_new("iperf_client", iperf_client, NULL, 2048, 8); // 开发板做client端
}
