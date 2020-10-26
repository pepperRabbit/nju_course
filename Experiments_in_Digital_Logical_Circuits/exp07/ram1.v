module ram1(clk, we, inaddr, outaddr, indata, outdata);
input clk;
input we;
input [3:0] inaddr;
input [3:0] outaddr;
input [7:0] indata;
//output reg [6:0] HEX0;
//output reg [6:0] HEX1;
output reg [7:0] outdata;

reg [7:0] ram [15:0];


initial
begin
	$readmemh("C:/intelFPGA_lite/exp/exp07/mem1.txt", ram, 0, 15);
end

always @(posedge clk)
begin
	if (we)
		ram[inaddr] <= indata;
	else
		outdata <= ram[outaddr];
end

endmodule
