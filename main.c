#include <HDL51001_ccf.h>
#include <spi.h>
#include <wdt.h>
#include <uart.h>

#include "lcd.h"
#include "util.h"

//16 bit word (12 bits data + 4 control bits)

int cmd_pos = 0;
char cmd_buf[32];

static void process_cmd(char *cmd)
{
    int iv;

    if (!*cmd) {
        return;
//    } else if (!strncmp(cmd, "lcd-print ", 10)) {
    } else if (!strcmp(cmd, "lcd-print")) {
        uart_send_str("\r\n*** Not implemented *** ", UART3);
//        uart_send_str(cmd+11, UART3);
	LCD_DrawCircle(100, 100, 50, 0x7e0);
    }
}

void cmd_update(void (*cmd_cb)(char *))
{
    char in;
    in = UART_GET_BYTE(UART3);

    switch (in)
    {
	case '\r':
		if (cmd_pos > 0) {
			memset(cmd_buf+cmd_pos, 0, sizeof(cmd_buf)-cmd_pos);
			cmd_cb(cmd_buf);
		}
		cmd_pos = 0;
		uart_send_str("\r\n# ", UART3);
		break;
	case 8:
	case 0x7f:
		if (cmd_pos > 0) {
			cmd_pos--;
			uart_send_str("\x8 \x8", UART3);
		}
		break;
	default:
//		if (!isprint(in))
//			break;
		uart_send_int(in, UART3);
		while(UART_FIFO_TX_EMPTY(UART3) == 0);
		cmd_buf[cmd_pos++] = in;
		if (cmd_pos == sizeof(cmd_buf)-1) {
			uart_send_str("\r\n*** cmd overflow ***\r\n# ", UART3);
			cmd_pos = 0;
		}
		break;
    }
}

void main()
{
    UART_InitTypeDef UART_InitStructure;

    GPIOD->DIR = ((uint32_t)0x00007000);
    GPIOD->OUT = ((uint32_t)0x00001000);

    UART_InitStructure.BaudRate = 38400; //set baudrate
    UART_InitStructure.TypeParity = 0x00000000; //parity control type
    UART_InitStructure.Parity = 0x00000000; //enable parity control
    UART_InitStructure.FlowControl = 0x00000000; //enable cts/rts
    UART_InitStructure.Mode = 0x00000003; //rx enable - 1 bit, tx enable - 2 bit (rx + tx en)  
        
    uart_init(UART3, &UART_InitStructure);
    GPIOD->OUT = ((uint32_t)0x00002000);
    
    WDT_OFF;
    
    GPIOD->BPS = 0xF00; //uart alternative port
    GPIOB->BPS = 0x07F; //SPI0 alternative port

    uart_send_str("System is booting...\r\nSPI0CFG=", UART3);

    GPIOB->DIR |= 0x100; // GPIOB[8] is OUTPUT
    GPIOB->OUT &= ~0x100; // GPIOB[8] is OUTPUT
    GPIOD->OUT = ((uint32_t)0x00004000);

    uart_send_str(itoa(SPI0->CFG, 16), UART3);
    uart_send_str(" SPI0CR=", UART3);
    uart_send_str(itoa(SPI0->CR, 16), UART3);

    SPI_SSEN(SPI0, 1); //разрешаем сигналы СS для SPI0
    SPI_TWEN(SPI0, 0); //запрещаем трёхпроводный режим для SPI0
    SPI0->SS = 0x07; //выставляем сигнал CS в логическую единицу
    SPI0->CR = 0x377F0000; //конфигурируем SPI0

    GPIOD->OUT = ((uint32_t)0x00003000);
    uart_send_str("\r\nConfiguring LCD...\r\n", UART3);

    if (!LCD_init())
        uart_send_str("*** LCD not found ***\r\n", UART3);

    memset(cmd_buf, 0, sizeof(cmd_buf));

    uart_send_str("# ", UART3);

    while(1){
        if (UART_NEW_DATA(UART3))
            cmd_update(process_cmd);
    }
}
