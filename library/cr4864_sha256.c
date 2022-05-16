#include <mbedtls/sha256.h>
#include <cr4864_sha256.h>

#define printf printf_
extern int printf_(const char* format, ...);


int mbedtls_internal_sha256_process( mbedtls_sha256_context *ctx, const unsigned char data[64] ) 
{
    int done = 0;
    //uint64_t le_conv;
    for (int i=0; i<4; i++)
    {
        *((uint64_t*)(SHA2560_CTRL_ADDR+SHA256_ISTATE+i*8)) = *((uint64_t*)(&ctx->state[i*2]));
    }

    //copy message    
    for (int i=0; i<8; i++)
    { 
        *((uint64_t*)(SHA2560_CTRL_ADDR+SHA256_DATA+i*8)) = *((uint64_t*)(&data[i*8]));
    }
    //start hashing   
    *((uint64_t*)(SHA2560_CTRL_ADDR+SHA256_CONTROL)) = SHA256_FLAG_INITMIDSTATE | SHA256_FLAG_START;
    //poll for done 
    done = *(uint64_t*)(SHA2560_CTRL_ADDR+SHA256_STATUS);
    while (!(done & SHA256_FLAG_DONE))
    {
         done = *(uint64_t*)(SHA2560_CTRL_ADDR+SHA256_STATUS);
    }
    //copy back result state
    // Results are stored in register offset 0x80 - 0x98
    // 0x80 = MSBs of Sha2
    // 0x98 = LSBs of Sha2
    // registers are being stored in BE format
    // So we have to convert them to LE before we store them in the state.
    
    for (int i=0; i<4; i++) 
    {
        //le_conv = *((uint64_t*)(SHA2560_CTRL_ADDR+SHA256_OSTATE+i*8));
        //printf("reg %d : %lx\n", i, le_conv);
        *((uint64_t*)(&ctx->state[i*2])) = *((uint64_t*)(SHA2560_CTRL_ADDR+SHA256_OSTATE+i*8)); 
    }
    return 0;
}
