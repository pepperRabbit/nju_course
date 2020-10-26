module ram(clk, we, inaddr, inaddr1, indata, hex0, hex1, outdata2);
	input clk;
	input we;
	input [3:0] inaddr;
	input [3:0] inaddr1;
	wire [3:0] addr;
	wire [3:0] addr1;
	wire [7:0] outdata1;
	input [7:0] indata;
	output [6:0] hex0, hex1;
	output [7:0] outdata2;
	assign addr = inaddr;
	assign addr1 = inaddr1;
	ram1 R1(.clk(clk), .we(we), .inaddr(inaddr), .outaddr(addr), .indata(indata), .outdata(outdata1));
	ram2port R2(.clock(clk), .data(indata), .wren(we), .wraddress(inaddr1), .rdaddress(addr1), .q(outdata2));
	show S(.outdata(outdata1), .HEX0(hex0), .HEX1(hex1));
endmodule
