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

// SHA256 unit - SE corner
#define SHA2560_CTRL_ADDR _AC(0x2EE00600,UL)
#define SHA2560_CTRL_SIZE _AC(0x100,UL)
