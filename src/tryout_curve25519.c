/*
===============================================================================
 Name        : tryout_curve25519.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
 */

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include "curve25519/curve25519_dh.h"
#include "curve25519/ed25519_signature.h"
#include "curve25519/BaseTypes.h"
// TODO: insert other include files here

// TODO: insert other definitions and declarations here


int dh_test()
{
	int rc = 0;
	unsigned char alice_public_key[32], alice_shared_key[32];
	unsigned char bruce_public_key[32], bruce_shared_key[32];

	unsigned char alice_secret_key[32] = { /* #1234 */
			0x03,0xac,0x67,0x42,0x16,0xf3,0xe1,0x5c,
			0x76,0x1e,0xe1,0xa5,0xe2,0x55,0xf0,0x67,
			0x95,0x36,0x23,0xc8,0xb3,0x88,0xb4,0x45,
			0x9e,0x13,0xf9,0x78,0xd7,0xc8,0x46,0xf4 };

	unsigned char bruce_secret_key[32] = { /* #abcd */
			0x88,0xd4,0x26,0x6f,0xd4,0xe6,0x33,0x8d,
			0x13,0xb8,0x45,0xfc,0xf2,0x89,0x57,0x9d,
			0x20,0x9c,0x89,0x78,0x23,0xb9,0x21,0x7d,
			0xa3,0xe1,0x61,0x93,0x6f,0x03,0x15,0x89 };

	curve25519_dh_CalculatePublicKey(alice_public_key, alice_secret_key);
	curve25519_dh_CalculatePublicKey(bruce_public_key, bruce_secret_key);
	curve25519_dh_CreateSharedKey(alice_shared_key, bruce_public_key, alice_secret_key);
	curve25519_dh_CreateSharedKey(bruce_shared_key, alice_public_key, bruce_secret_key);
	if (memcmp(alice_shared_key, bruce_shared_key, 32) != 0)
	{
		rc++;

	}
	return rc;
}

void curve25519_test()
{
	int i;
	int res;
	U8 secret_key[32],  mehdi_publickey[32];
	unsigned char pubkey[32], privkey[64], sig[64];

	curve25519_dh_CalculatePublicKey_fast(mehdi_publickey, secret_key);

	ed25519_CreateKeyPair(pubkey, privkey, 0, secret_key);
	ed25519_SignMessage(sig, privkey, 0, (const unsigned char*)"abc", 3);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0,4);


	while(1)
	{
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 4, 1);
		res=ed25519_VerifySignature(sig, pubkey, (const unsigned char*)"abc", 3);
		Chip_GPIO_WritePortBit(LPC_GPIO, 0, 4, 0);
		res=ed25519_VerifySignature(sig, pubkey, (const unsigned char*)"abc", 3);

	}
	if(res)
	{

	}

}

int main(void) {

#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	// Set the LED to the state of "On"
	Board_LED_Set(0, true);
#endif
#endif

	// TODO: insert code here

	// Force the counter to be placed into memory
	volatile static int i = 0 ;
	// Enter an infinite loop, just incrementing a counter

	dh_test();

	 curve25519_test();

	printf("Hello world\n");
	while(1) {
		i++ ;
	}
	return 0 ;
}
