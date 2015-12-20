/*
===============================================================================
 Name        : tryout_curve25519.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
 */

#include "curve25519_dh.h"
#include "ed25519_signature.h"
#include "BaseTypes.h"

void curve25519_test()
{
	int i=0;
	int res=0;
	U8 secret_key[32]={0};
	U8 mehdi_publickey[32]={0};
	unsigned char pubkey[32]={0};
	unsigned char privkey[64]={0};
	unsigned char sig[64]={0};

	//curve25519_dh_CalculatePublicKey_fast(mehdi_publickey, secret_key);

	//ed25519_CreateKeyPair(pubkey, privkey, 0, secret_key);
	//ed25519_SignMessage(sig, privkey, 0, (const unsigned char*)"abc", 3);

		res=ed25519_VerifySignature(sig, pubkey, (const unsigned char*)"abc", 3);

}

int main(void) {


	 curve25519_test();

	return 0 ;
}
