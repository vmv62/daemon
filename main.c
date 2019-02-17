#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <modbus/modbus.h>

int main(int argc, char **argv){
	modbus_t *ctx;
	modbus_mapping_t *mbm;
	uint8_t *buffer;

	buffer = (uint8_t *)malloc(128);

	ctx = modbus_new_tcp("127.0.0.1", 1502);

	mbm = modbus_mapping_new(5, 5, 5, 5);

	mbm->tab_input_registers[0] = 10;
	mbm->tab_input_registers[1] = 500;
	mbm->tab_input_registers[2] = 760;

	mbm->tab_registers[0] = 43;
	mbm->tab_registers[1] = 11;
	mbm->tab_registers[2] = 43;

	int s = modbus_tcp_listen(ctx, 1);
	modbus_tcp_accept(ctx, &s);

	int req_len;
	while(1){
		req_len = modbus_receive(ctx, buffer);
		printf("Received %d simbols\n", req_len);
		modbus_reply(ctx, buffer, req_len, mbm);
	}

	modbus_mapping_free(mbm);
	modbus_free(ctx);
return 0;
}
