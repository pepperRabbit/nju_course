module trigger(en,clk,in_d,out1,out2);
input en,clk,in_d;
output reg out1,out2;

always @ (posedge clk)
if(en)
	begin
	out1 = in_d;
	out2 = out1;
	end
else
	begin
	out1 = out1;
	out2 = out2;
	end
endmodule
