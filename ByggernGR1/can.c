/*
 * can.c
 *
 * Created: 04.10.2016 16:26:48
 *  Author: nikolasn
 */ 

#include "can.h"
#include "mcp.h"
#include "MCP2515_macros.h"
#include <stdio.h>
#include <avr/delay.h>

void can_init(){
	 mcp_init();
	 volatile uint8_t canStat = mcp_read(MCP_CANSTAT);	 
	 
	//Set to loopback mode - should be done in CAN driver
	//Input descriptions: ADress of register, mask (first 3 bits), mode
	mcp_bitModify(MCP_CANCTRL, MODE_MASK ,MODE_LOOPBACK);
	
	canStat = mcp_read(MCP_CANSTAT);
	if((canStat &MODE_MASK) != MODE_CONFIG ){
		printf("Not in loopback mode - %d\n",canStat);
	}else{
		printf("In loopback mode\n");
	}
	//turn off rollover mode
	mcp_bitModify(MCP_RXB0CTRL, MCP_ROLLOVER_OFF,0x04);
	//set interrupts to fire
	mcp_bitModify(MCP_CANINTE,MCP_RX_INT,0xFF );
}



void can_send(can_message *message){
	uint8_t len = message->length & 0x0F;
	
	mcp_requestSend(MCP_TXB0SIDL, 0x00);
	mcp_requestSend(MCP_TXB0SIDH, 0x00);
	mcp_requestSend(MCP_TXB0DLC, len);
	
	
	mcp_write(MCP_TXB0D0, message->data, len);
	
	mcp_requestSend(1);
}

can_message can_recieve(){
	can_message message;
	
	volatile uint8_t canIntf = mcp_read(MCP_CANINTF);	 
	
	if(1/*mcp_read(MCP_CANSTAT) & 0x0C*/){
		message.length = mcp_read(MCP_RXB1DLC) & 0x0F;
		for(uint8_t i = 0; i < message.length; i++){
			message.data[i] = mcp_read(MCP_RXB1D0 + i);
		}
	}else{
		printf("No new message\n");
	}
	
	//on the MCP_CANINTF register, set bit 0 to value 0. E.g. mask 0B00000001, value 0
	mcp_bitModify(MCP_CANINTF, 1, 0);
	
	return message;
}

// can_message* myMessage;
// myMessage->id = 0;
// myMessage->length = 8;
// myMessage->data = [1, 0, 2, 0, 0, 0, 0, 0];