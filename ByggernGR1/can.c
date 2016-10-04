/*
 * can.c
 *
 * Created: 04.10.2016 16:26:48
 *  Author: nikolasn
 */ 

#include "can.h"
#include "MCP2515.h"

void can_init(){
	 mcp_init();
	//Set to loopback mode - should be done in CAN driver
	mcp_bitModify(0x0F, 0b11100000, 0b01000000);
}

void can_send(can_message* message){
	uint8_t len = message->length & 0x0F
	
	mcp_write(TXB1S, message->data, len)
	
	
}

can_message can_recieve(){
	
	
	
}

can_message* myMessage;
myMessage->id = 0;
myMessage->length = 8;
myMessage->data = [1, 0, 2, 0, 0, 0, 0, 0];