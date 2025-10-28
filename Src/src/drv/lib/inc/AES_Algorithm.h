#ifndef __AES_ALGORITHM_H_
#define __AES_ALGORITHM_H_

#ifdef __cplusplus
extern "C"
{
#endif

//#include "ccr4001s_reg.h"
#include "algo_drv.h"
#include "type.h"



void LIB_AES_Enable(void);


/**
 * SM4 
*/
void LIB_AES_Disable(void);


int8_t LIB_AES_Cryptographic(ALG_EN_DE_MODE crypt_mode, ALG_KEY_MODE key_mode, ALG_MODE sel_mode, ALG_STREAMMODE stream_mode,
                                   uint32_t * data_in, uint32_t *data_out, uint32_t bytelen, uint32_t* key,
                                   uint32_t* iv, dpa_level_t bDPA);

#ifdef __cplusplus
}
#endif

#endif


