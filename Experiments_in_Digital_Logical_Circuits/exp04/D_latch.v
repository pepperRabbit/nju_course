module D_latch(clk,in_d,en,out_ql);
	input clk,in_d,en;
	output reg out_ql;
	
	always @ (*)
	if(en) begin
		if(clk) out_ql <= in_d; end
	else out_ql <= out_ql;
endmodule
