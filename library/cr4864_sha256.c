#include <mbedtls/sha256.h>
#include <cr4864_sha256.h>

//#define SHA2_DEBUG

// Minimal hand-rolled debug print -- avoids pulling in printf_'s vararg/hex
// formatting machinery, which blows the 32KB maskrom budget (zsbl was
// already within ~176 bytes of the limit before any instrumentation).
// Forward-declared directly (matches the existing printf_ pattern in this
// file) since uart.h isn't on mbedcrypto's include path.
#ifdef SHA2_DEBUG
extern int uart_putc(unsigned char index, unsigned char c);

static void dbg_puthex64(uint64_t v) {
    static const char hexdig[] = "0123456789abcdef";
    for (int shift = 60; shift >= 0; shift -= 4) {
        uart_putc(3, hexdig[(v >> shift) & 0xF]);
    }
}
// tag: 'e'=entry, 'r'=readback. One line: "Dre<hex64>\n" (D=debug, e/r=tag).
static void dbg_print_state(char tag, uint64_t s0) {
    uart_putc(3, 'D');
    uart_putc(3, tag);
    dbg_puthex64(s0);
    uart_putc(3, '\n');
}
#else
#define dbg_print_state(a, b)
#endif


int mbedtls_internal_sha256_process( mbedtls_sha256_context *ctx, const unsigned char data[64] )
{
    int done = 0;
    uint64_t temp;
    volatile uint64_t *stateptr;

	stateptr = (volatile uint64_t *)(ctx->state);
    dbg_print_state('e', stateptr[0]);
    for (int i=0; i<4; i++)
    {
        *((volatile uint64_t*)(SHA2560_CTRL_ADDR+SHA256_ISTATE+i*8)) = stateptr[i];
    }

    //copy message
    for (int i=0; i<8; i++)
    {
        temp = *((uint32_t*)(&data[(i*8)+4]));
        temp = temp << 32;
        temp |= *((uint32_t*)(&data[i*8]));
        *((volatile uint64_t*)(SHA2560_CTRL_ADDR+SHA256_DATA+i*8)) = temp;
    }

    // Bug fix for RTL issue: JIRA :https://inspiresemi.atlassian.net/browse/THUNDER-737
    asm volatile("fence o,o" ::: "memory");   // force data writes before start

    //start hashing
    *((volatile uint64_t*)(SHA2560_CTRL_ADDR+SHA256_CONTROL)) = SHA256_FLAG_INITMIDSTATE | SHA256_FLAG_START;
    
    // Bug fix for RTL issue: JIRA :https://inspiresemi.atlassian.net/browse/THUNDER-737
    asm volatile("fence o,i" ::: "memory");   // force CONTROL store to take effect before polling STATUS
    
    //poll for done
    done = *(volatile uint64_t*)(SHA2560_CTRL_ADDR+SHA256_STATUS); 
    while (!(done & SHA256_FLAG_DONE))
    {
         done = *(volatile uint64_t*)(SHA2560_CTRL_ADDR+SHA256_STATUS);
    }
    //copy back result state
    // Results are stored in register offset 0x80 - 0x98
    for (int i=0; i<4; i++)
    {
        //le_conv = *((uint64_t*)(SHA2560_CTRL_ADDR+SHA256_OSTATE+i*8));
        //printf("reg %d : %lx\n", i, le_conv);
        stateptr[i] = *((volatile uint64_t*)(SHA2560_CTRL_ADDR+SHA256_OSTATE+i*8));
    }
    dbg_print_state('r', stateptr[0]);
    return 0;
}
