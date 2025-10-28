#ifndef __SM4_ALGORITHM_H_
#define __SM4_ALGORITHM_H_

#ifdef __cplusplus
extern "C"
{
#endif

//#include "ccr4001s_reg.h"
#include "algo_drv.h"
#include "type.h"


void LIB_SMS4_Enable(void);
void LIB_SMS4_Disable(void);



int8_t LIB_SM4_Cryptographic(ALG_EN_DE_MODE crypt_mode, ALG_MODE sel_mode, ALG_STREAMMODE strem_mode,
                                   uint32_t *data_in, uint32_t *data_out, uint32_t bytelen,
                                   uint32_t* key, uint32_t* iv, dpa_level_t bDPA);


#ifdef __cplusplus
}
#endif

#endif 

