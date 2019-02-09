#ifndef _XIL_ETHERLITE_H_
#define _XIL_ETHERLITE_H_


#define ETHL_MDIOADDR (ETHERLITE_BASE+0x7e4)
#define ETHL_MDIOWR (ETHERLITE_BASE+0x7e8)
#define ETHL_MDIORD (ETHERLITE_BASE+0x7ec)
#define ETHL_MDIOCTRL (ETHERLITE_BASE+0x7F0)

#define ETHL_OFFSET_CTRL 0x7fc

#define ETHL_RX_PING_BUFF (void*)(ETHERLITE_BASE+0x1000)
#define ETHL_RX_PONG_BUFF (void*)(ETHERLITE_BASE+0x1800)
#define ETHL_RX_PING_CTRL (void*)(ETHL_RX_PING_BUFF+ETHL_OFFSET_CTRL)
#define ETHL_RX_PONG_CTRL (void*)(ETHL_RX_PONG_BUFF+ETHL_OFFSET_CTRL)

#define ETHL_TX_PING_BUFF (void*)(ETHERLITE_BASE)
#define ETHL_TX_PING_CTRL (void*)(ETHERLITE_BASE+0x7fc)
#define ETHL_TX_PING_LEN  (void*)(ETHERLITE_BASE+0x7f4)
#define ETHL_GIE          (void*)(ETHERLITE_BASE+0x7f8)


void platform_eth_init();

uint32_t platform_eth_get_packet_nb( void* buf, uint32_t maxlen );
void platform_eth_send_packet( const void* src, uint32_t size );




#endif
