/*
 * mem.c
 *
 * Created: 06.09.2016 11:48:47
 *  Author: nikolasn
 */ 
#include <avr/io.h>

void mem_init(){
	//Enable ext ram:
	MCUCR |= (1 << SRE);
	
	//Mask out pins PC7-PC4:
	SFIOR |= (1 << XMM2);
	
	
	
}

void mem_test(){
	volatile char *extRam = (char *) 0x1800; //Start address for the SRAM
	uint16_t extRamSize = 0x800;
	uint16_t writeErrors = 0;
	uint16_t retrievalErrors = 0;
	printf("Starting SRAM test...\n");
	
	//rand() stores some internal state, so calling this function in a loop will yield different seeds each time unless srand() is called before this function.
	uint16_t seed = rand();
	srand(seed);
	
	for (uint16_t i = 0; i < extRamSize; i++){
		uint8_t someValue = rand();
		extRam[i] = someValue;
		uint8_t retrievedValue = extRam[i];
		
		if (retrievedValue != someValue){
			printf("Write phase error: extRam[%4d] = %02X (should be %02X) \n", i, retrievedValue, someValue);
			writeErrors ++;
	
		}
	}
	
	//Retrieval phase: Check that no values were changed during or after the write phase
	
	srand(seed); //Reset the PRNG to the state it had before the write phase
	
	for(uint16_t i = 0; i < extRamSize; i++){
		uint8_t someValue = rand();
		uint8_t retrievedValue = extRam[i];
		
		if (retrievedValue != someValue){
			printf("Retrieval phase error: extRam[%4d] = %02X (should be %02X) \n", i, retrievedValue, someValue);
			retrievalErrors ++;	
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase \n\n", writeErrors, retrievalErrors);
	
}

void mem_testLatch() {
	volatile char *extRam = (char *) 0x1800; //Start address for the SRAM
	
	uint8_t someValue = 0x01;
	
	extRam[0x01] = someValue;
}

