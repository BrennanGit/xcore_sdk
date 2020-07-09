// Copyright (c) 2020, XMOS Ltd, All rights reserved

#ifndef FREERTOS_TLS_SUPPORT_H_
#define FREERTOS_TLS_SUPPORT_H_

#define DRBG_SEED_STRING_DEFAULT "XCOREAI"

#include "mbedtls/ssl.h"
#include "mbedtls/x509_crt.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"

/**
 * Context required for sending and receiving in the
 * FreeRTOS+TCP and mbedtls setup
 */
typedef struct tls_ctx
{
	Socket_t socket;
	int flags;
} tls_ctx_t;

/**
 * Get the platform shared entropy context
 *
 * \returns       returns pointer to shared mbedtls_entropy_context
 */
mbedtls_entropy_context* get_shared_entropy_ctx( void );

/**
 * Get the platform shared drbg context
 *
 * \returns       returns pointer to shared mbedtls_ctr_drbg_context
 */
mbedtls_ctr_drbg_context* get_shared_drbg_ctx( void );

/**
 * Function which can be used as a default debug function
 * for mbedtls_ssl_conf_dbg
 *
 * \param[in]     ctx		     Context for callback
 * \param[in]     level		     Debug level
 * \param[in]     file		     File name
 * \param[in]     line		     Line number
 * \param[in]     str		     Message
 *
 * \returns       None
 */
void default_mbedtls_debug( void *ctx, int level,
							const char *file, int line,
							const char *str );

/**
 * Populate an mbedtls certificate, found at filepath
 *
 * \param[in/out] cert            Pointer to the cert to populate
 * \param[in]     filepath    	  Filepath that cert is located at
 *
 * \returns       pdPASS on success
 * 				  pdFAIL on failure
 */
int get_cert( mbedtls_x509_crt* cert, const char* filepath );

/**
 * Populate an mbedtls key, found at filepath
 *
 * \param[in/out] key             Pointer to the key to populate
 * \param[in]     filepath    	  Filepath that key is located at
 *
 * \returns       pdPASS on success
 * 				  pdFAIL on failure
 */
int get_key( mbedtls_pk_context* key, const char* filepath );

/**
 * Receive from network driver using TLS
 *
 * \param[in]     ctx		     Context to use containing the network,
 * 								 TLS, and any other tls_support information
 * \param[in/out] buf            Pointer to the buffer to receive into
 * \param[in]     len    		 Maximum number of bytes to read
 *
 * \returns       return value of configured network receive function
 */

/**
 * Populate an mbedtls certificate, with the default CA certificate
 * location.
 *
 * CA chain location can be specified with by defining DEVICE_CA_CHAIN_FILEPATH
 *
 * \param[in/out] cert            Pointer to the cert to populate
 *
 * \returns       pdPASS on success
 * 				  pdFAIL on failure
 */
int get_ca_cert( mbedtls_x509_crt* ca_cert );

/**
 * Populate an mbedtls certificate, with the default device certificate
 * location.
 *
 * Certificate location can be specified with by defining DEVICE_CERT_FILEPATH
 *
 * \param[in/out] cert            Pointer to the cert to populate
 *
 * \returns       pdPASS on success
 * 				  pdFAIL on failure
 */
int get_device_cert( mbedtls_x509_crt* cert );

/**
 * Populate an mbedtls key, with the default key location.
 *
 * Private key location can be specified with by defining DEVICE_PRV_KEY_FILEPATH
 *
 * \param[in/out] prvkey          Pointer to the key to populate
 *
 * \returns       pdPASS on success
 * 				  pdFAIL on failure
 */
int get_device_prvkey( mbedtls_pk_context* prvkey );

/**
 * Calloc in FreeRTOS
 *
 * \param[in]     n		     	 Number of objects
 * \param[in]     size    		 Size of each object
 *
 * \returns       return pointer to region of n*size bytes, initialized to all 0x00
 */
void* freertos_calloc( size_t n, size_t size );
/**
 * Configure platform memory macros
 */
#define MBEDTLS_PLATFORM_FREE_MACRO vPortFree
#define MBEDTLS_PLATFORM_CALLOC_MACRO freertos_calloc

#ifdef DRBG_SEED_STRING
static const char* drbg_seed_string = ( char* )DRBG_SEED_STRING;
#else
static const char* drbg_seed_string = ( char* )DRBG_SEED_STRING_DEFAULT;
#endif

#endif /* FREERTOS_TLS_SUPPORT_H_ */