module D_trigger(in_d,clk,en,out_qt);
	input en,clk,in_d;
	output reg out_qt;
	
	always @ (posedge clk)
		if(en) out_qt <= in_d;
		else out_qt <= out_qt;
endmodule
