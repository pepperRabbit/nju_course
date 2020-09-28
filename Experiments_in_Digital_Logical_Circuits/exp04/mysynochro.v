module mysynochro(clk,clr_n,in_d,out_q2);
	input clk,clr_n,in_d;
	output reg out_q2;
	
	always @ (posedge clk)
		if(!clr_n) out_q2 <=0;
		else  out_q2 <= in_d;
endmodule
