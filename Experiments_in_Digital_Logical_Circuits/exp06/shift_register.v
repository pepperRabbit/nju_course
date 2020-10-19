module shift_register(clk,select,in_data,in_left,Q);
input clk;
input [3:0] select;
input [7:0] in_data;
input in_left;

output reg [7:0] Q;

reg q0=0;
reg temp=0;

always @ (posedge clk)
	case(select)
		0: Q = 0;
		1: Q = in_data;
		2: Q = {q0, Q[7:1]};			//逻辑右移
		3: Q = {Q[6:0], q0};			//逻辑左移
		4: Q = {Q[7], Q[7:1]};		//算术右移
		5: Q = {in_left, Q[7:1]};
		6: Q = {Q[0], Q[7:1]};		//循环右移
		7: Q = {Q[6:0], Q[7]};		//循环左移
		8: begin
				temp = (Q[0]^Q[1]^Q[2]^Q[3]) ^ ~(Q[1]|Q[2]|Q[3]|Q[4]|Q[5]|Q[6]|Q[7]);
				Q = {temp,Q[7:1]};
			end		//random
	endcase
	

endmodule
