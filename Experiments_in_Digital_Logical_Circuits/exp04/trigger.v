module trigger(clk,clr_n,in_d,out_q,out_q2);
	input clk,clr_n,in_d;
	output out_q,out_q2;
	
	myasynochro asco(clk,clr_n,in_d,out_q);
	mysynochro sco(clk,clr_n,in_d,out_q2);
	
endmodule
