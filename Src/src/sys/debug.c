/**
 * @file debug.c
 * @author Product application department
 * @brief  DEBUG 打印配置文件
 * @version V1.0
 * @date 2025-02-28
 *
 * @copyright Copyright (c) 2025 China Core Co. Ltd. All Rights Reserved
 *
 */
// 头文件包含
#include "debug.h"

// 全局变量定义
static uart_typedef_t *UART;

// 函数定义

/**
 * @brief DEBUG 串口初始化函数
 *
 * @param UARTx 串口号
 * @param pclk IPS 时钟
 * @param bound 波特率
 */
void uart_debug_init(uart_typedef_t *UARTx, uint32_t pclk, uint32_t bound)
{
    uint32_t band_rate = 0;

    UART = UARTx;

    UART->BRDF = (((pclk * 8 / bound) + 1) / 2) & 0x003f;
    band_rate = (pclk * 4 / bound) >> 6;
    UART->BDH = (uint8_t)((band_rate >> 8) & 0x00ff);
    UART->BDL = (uint8_t)(band_rate & 0x00ff);

    UART->CR2 = 0x00;
    UART->CR1 = 0x10;

    UART->CR2 |= (UART_RE | UART_CR2_TE_MASK);
}

/**
 * @brief DEBUG 字符获取函数
 * @param
 * @return
 */
uint8_t Getchar(void)
{
    uint8_t tmp;
    while ((UART->FSR) & UART_FIFO_FLAG_R_EMPTY)
        ;
    tmp = UART->DRL;
    return tmp;
}

/**
 * @brief DEBUG 字符输出函数
 *
 * @param ch 输出字符
 */
void Putchar(int ch)
{
    UART->CR2 |= UART_CR2_TE_MASK;

    while ((UART->SR1 & UART_SR1_TDRE_MASK) == 0x00)
    {
        ;
    }
    UART->DRL = (uint8_t)ch;
    while ((UART->SR1 & UART_SR1_TC_MASK) == 0x00)
    {
        ;
    }
    UART->CR2 &= ~UART_CR2_TE_MASK;
}

void assert_failed(uint8_t *file, uint32_t line)
{
    printf("Wrong parameters value: file %s on line %d\r\n", file, line);
    while (1)
        ;
}

int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

// 加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if PRINTF_DSP
/*
 * Arm Compiler 4/5
 */
#if defined(__CC_ARM)
#pragma import(__use_no_semihosting)
// 解决HAL库使用时,某些情况可能报错的bug
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}
// 标准库需要的支持函数
struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

/*
 * Arm Compiler 6.6 LTM (armclang)
 */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) && (__ARMCC_VERSION < 6100100)

#error "This case not support \r\n"
/*
 * Arm Compiler above 6.10.1 (armclang)
 */
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100)

__asm(".global __use_no_semihosting\n\t");
// 标准库需要的支持函数
struct FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* FILE is typedef’ d in stdio.h. */
FILE __stdout;
// 定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
    x = x;
}

// 重定义fputc函数
int fputc(int ch, FILE *f)
{
    //    UART->CR2 |= UART_CR2_TE_MASK;

    while ((UART->SR1 & UART_SR1_TDRE_MASK) == 0x00)
    {
        ;
    }
    UART->DRL = (uint8_t)ch;
    while ((UART->SR1 & UART_SR1_TC_MASK) == 0x00)
    {
        ;
    }
    //    UART->CR2&= ~UART_CR2_TE_MASK;

    return ch;
}
// end
//////////////////////////////////////////////////////////////////

#else
void xputc(char c)
{
    if (_CR_CRLF && c == '\n')
        xputc('\r'); /* CR -> CRLF */

    while ((UART->SR1 & UART_SR1_TDRE_MASK) == 0x00)
    {
        ;
    }
    UART->DRL = (uint8_t)c;
    while ((UART->SR1 & UART_SR1_TC_MASK) == 0x00)
    {
        ;
    }
}

/*----------------------------------------------*/
/* Put a null-terminated string                 */
/*----------------------------------------------*/

void xputs(                /* Put a string to the default device */
           const char *str /* Pointer to the string */
)
{
    while (*str)
    {
        xputc(*str++);
    }
}

/*----------------------------------------------*/
/* Formatted string output                      */
/*----------------------------------------------*/
/*  xprintf("%d", 1234);            "1234"
    xprintf("%6d,%3d%%", -200, 5);    "  -200,  5%"
    xprintf("%-6u", 100);            "100   "
    xprintf("%ld", 12345678);        "12345678"
    xprintf("%llu", 0x100000000);    "4294967296"    <_USE_LONGLONG>
    xprintf("%04x", 0xA3);            "00a3"
    xprintf("%08lX", 0x123ABC);        "00123ABC"
    xprintf("%016b", 0x550F);        "0101010100001111"
    xprintf("%*d", 6, 100);            "   100"
    xprintf("%s", "String");        "String"
    xprintf("%-5s", "abc");            "abc  "
    xprintf("%5s", "abc");            "  abc"
    xprintf("%c", 'a');                "a"
    xprintf("%f", 10.0);            <xprintf lacks floating point support. Use regular printf.>
*/

static void xprintf(
    const char *fmt, /* Pointer to the format string */
    va_list arp      /* Pointer to arguments */
)
{
    uint32_t r, i, j, w, f;
    int n;
    char s[32], c, d, *p;
#if _USE_LONGLONG
    _LONGLONG_t v;
    unsigned _LONGLONG_t vs;
#else
    long v;
    unsigned long vs;
#endif

    for (;;)
    {
        c = *fmt++; /* Get a format character */
        if (!c)
            break; /* End of format? */
        if (c != '%')
        { /* Pass it through if not a % sequense */
            xputc(c);
            continue;
        }
        f = w = 0;  /* Clear parms */
        c = *fmt++; /* Get first char of the sequense */
        if (c == '0')
        { /* Flag: left '0' padded */
            f = 1;
            c = *fmt++;
        }
        else
        {
            if (c == '-')
            { /* Flag: left justified */
                f = 2;
                c = *fmt++;
            }
        }
        if (c == '*')
        { /* Minimum width from an argument */
            n = va_arg(arp, int);
            if (n < 0)
            { /* Flag: left justified */
                n = 0 - n;
                f = 2;
            }
            w = n;
            c = *fmt++;
        }
        else
        {
            while (c >= '0' && c <= '9')
            { /* Minimum width */
                w = w * 10 + c - '0';
                c = *fmt++;
            }
        }
        if (c == 'l' || c == 'L')
        { /* Prefix: Size is long */
            f |= 4;
            c = *fmt++;
#if _USE_LONGLONG
            if (c == 'l' || c == 'L')
            { /* Prefix: Size is long long */
                f |= 8;
                c = *fmt++;
            }
#endif
        }
        if (!c)
            break; /* End of format? */
        d = c;
        if (d >= 'a')
            d -= 0x20;
        switch (d)
        {         /* Type is... */
        case 'S': /* String */
            p = va_arg(arp, char *);
            for (j = 0; p[j]; j++)
                ;
            while (!(f & 2) && j++ < w)
                xputc(' ');
            xputs(p);
            while (j++ < w)
                xputc(' ');
            continue;
        case 'C': /* Character */
            xputc((char)va_arg(arp, int));
            continue;
        case 'B': /* Binary */
            r = 2;
            break;
        case 'O': /* Octal */
            r = 8;
            break;
        case 'D': /* Signed decimal */
        case 'U': /* Unsigned decimal */
            r = 10;
            break;
        case 'X': /* Hexdecimal */
            r = 16;
            break;
        default: /* Unknown type (passthrough) */
            xputc(c);
            continue;
        }

        /* Get an argument and put it in numeral */
#if _USE_LONGLONG
        if (f & 8)
        { /* long long argument? */
            v = va_arg(arp, _LONGLONG_t);
        }
        else
        {
            if (f & 4)
            { /* long argument? */
                v = (d == 'D') ? (long)va_arg(arp, long) : (long)va_arg(arp, unsigned long);
            }
            else
            { /* int/short/char argument */
                v = (d == 'D') ? (long)va_arg(arp, int) : (long)va_arg(arp, uint32_t);
            }
        }
#else
        if (f & 4)
        { /* long argument? */
            v = va_arg(arp, long);
        }
        else
        { /* int/short/char argument */
            v = (d == 'D') ? (long)va_arg(arp, int) : (long)va_arg(arp, uint32_t);
        }
#endif
        if (d == 'D' && v < 0)
        { /* Negative value? */
            v = 0 - v;
            f |= 16;
        }
        i = 0;
        vs = v;
        do
        {
            d = (char)(vs % r);
            vs /= r;
            if (d > 9)
                d += (c == 'x') ? 0x27 : 0x07;
            s[i++] = d + '0';
        } while (vs != 0 && i < sizeof s);
        if (f & 16)
            s[i++] = '-';
        j = i;
        d = (f & 1) ? '0' : ' ';
        while (!(f & 2) && j++ < w)
            xputc(d);
        do
            xputc(s[--i]);
        while (i != 0);
        while (j++ < w)
            xputc(' ');
    }
}

void xprintf(                 /* Put a formatted string to the default device */
             const char *fmt, /* Pointer to the format string */
             ...              /* Optional arguments */
)
{
    va_list arp;

    va_start(arp, fmt);
    xprintf(fmt, arp);
    va_end(arp);
}

#endif
