/* InspireSemi hardware SHA256 driver */

/* Changes Copyright (c) 2020 InspireSemi LLC. */

#include <stdint.h>

#ifdef __ASSEMBLER__
#define _AC(X,Y)        X
#else
#define _AC(X,Y)        (X##Y)
#endif /* !__ASSEMBLER__*/

#define SHA256_FLAG_INITMIDSTATE 0b00000001
#define SHA256_FLAG_INIT         0b00000010
#define SHA256_FLAG_START        0b00000100
#define SHA256_FLAG_SAVEMIDSTATE 0b00001000

#define SHA256_ISTATE 0
#define SHA256_DATA 32
#define SHA256_CONTROL 96
#define SHA256_OSTATE 128
#define SHA256_STATUS 160

#define SHA256_FLAG_RUNNING      0b00000001
#define SHA256_FLAG_DONE         0b00000010

// SHA256 unit - Corner 5,9
#define SHA2560_OFFSET 0x600
#define SHA2560_CTRL_ADDR 0x00000070010600
#define SHA2560_PTR ((void * const)SHA2560_CTRL_ADDR)
#define SHA2560_CTRL_SIZE _AC(0x100,UL)
