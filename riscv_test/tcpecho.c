
#include <stdio.h>
#include <stdint.h>
#include "pico_stack.h"
#include "pico_socket.h"
#include "pico_ipv4.h"



#define BSIZE 1460
/* callback for TCP echo socket events */
void cb_tcpecho(uint16_t ev, struct pico_socket *s)
{
    char recvbuf[BSIZE];
    int read = 0, written = 0;
    int pos = 0, len = 0;
    struct pico_socket *sock_a;
    struct pico_ip4 orig;
    uint16_t port;
    char peer[30];
    /* process read event, data available */
    if (ev & PICO_SOCK_EV_RD)
    {
        do
        {
            
            read = pico_socket_read(s, recvbuf + len, BSIZE - len);
            dbg("Socket read %d bytes\n",read);
            if (read > 0)
                len += read;
        } while (read > 0);
    }
    /* process connect event, syn received */
    if (ev & PICO_SOCK_EV_CONN)
    {
        /* accept new connection request */
        sock_a = pico_socket_accept(s, &orig, &port);
        /* convert peer IP to string */

        pico_ipv4_to_string(peer, orig.addr);
        /* print info */
        printf("Connection established with %s:%d.\n", peer, short_be(port));
    }
    /* process fin event, receiving socket closed */
    if (ev & PICO_SOCK_EV_FIN)
    {
        printf("Socket closed. Exit normally. \n");
    }
    /* process error event, socket error occured */
    if (ev & PICO_SOCK_EV_ERR)
    {
        printf("Socket Error received: %s. Bailing out.\n", strerror(pico_err));
        exit(1);
    }
    /* process close event, receiving socket received close from peer */
    if (ev & PICO_SOCK_EV_CLOSE)
    {
        printf("Socket received close from peer.\n");
        /* shutdown write side of socket */
        pico_socket_shutdown(s, PICO_SHUT_WR);
    }
    /* if data read, echo back */
    if (len > pos)
    {
        do
        {
            /* echo data back to peer */
            written = pico_socket_write(s, recvbuf + pos, len - pos);
            printf("Socket write %d bytes\n",written);
            if (written > 0)
            {
                pos += written;
                if (pos >= len)
                {
                    pos = 0;
                    len = 0;
                    written = 0;
                }
            }
            else
            {
                printf("SOCKET> ECHO write failed, dropped %d bytes\n", (len - pos));
            }
        } while (written > 0);
    }
}
/* initialize the TCP echo socket */
void app_tcpecho(uint16_t source_port)
{
    struct pico_socket *s;
    uint16_t port_be = 0;
    int backlog = 40; /* max number of accepting connections */
    struct pico_ip4 inaddr_any;

    int ret;
    /* set the source port for the socket */
    if (source_port == 0)
        port_be = short_be(5555);
    else
        port_be = short_be(source_port);
    /* open a TCP socket with the appropriate callback */
    s = pico_socket_open(PICO_PROTO_IPV4, PICO_PROTO_TCP, &cb_tcpecho);
    if (!s)
        return;
    /* bind the socket to port_be */
    inaddr_any.addr=0;
    ret = pico_socket_bind(s, &inaddr_any, &port_be);
    if (ret != 0) return;
        
    /* start listening on socket */
    ret = pico_socket_listen(s, backlog);
   
       
}