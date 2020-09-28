module myasynochro(clk,clr_n,in_d,out_q);
	input clk,clr_n,in_d;
	output reg out_q;
	
	always @ (posedge clk or negedge clr_n)
		if(!clr_n) out_q <= 0;
		else out_q <= in_d;
endmodule
			