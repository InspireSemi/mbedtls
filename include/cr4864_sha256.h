/* InspireSemi hardware SHA256 driver */

/* Changes Copyright (c) 2020 InspireSemi LLC. */

#include <stdint.h>

#ifdef __ASSEMBLER__
#define _AC(X,Y)        X
#else
#define _AC(X,Y)        (X##Y)
#endif /* !__ASSEMBLER__*/

#define     ADDR(hb, clx, cly, crx, cry, offset) ( (hb<<29)|(clx<<25)|(cly<<21)|(crx<<18)|(cry<<15)|offset )
// Boot/Corner Cluster
#define  CLUSTER0_X     0
#define  CLUSTER0_Y     0
//Corner Core
#define  CLUSTER9_X     0
#define  CLUSTER9_Y     9
//Corner Core
#define  CLUSTER70_X     7
#define  CLUSTER70_Y     0
//Corner Core
#define  CLUSTER79_X     7
#define  CLUSTER79_Y     9
// Core 0
#define  CLUSTER0_X     0
#define  CLUSTER0_Y     0
// SHA2 Mapping
#define SHA2_X          0
#define SHA2_Y          1

#define  HB_1           1

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

// SHA256 unit - Corner 7,9
#define SHA2560_OFFSET 0x600
#define SHA2560_CTRL_ADDR ADDR(HB_1,CLUSTER79_X,CLUSTER79_Y,SHA2_X,SHA2_Y,SHA2560_OFFSET)
#define SHA2560_PTR ((void * const)SHA2560_CTRL_ADDR)
#define SHA2560_CTRL_SIZE _AC(0x100,UL)
