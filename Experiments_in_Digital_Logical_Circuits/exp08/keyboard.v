module keyboard(clk,clrn,ps2_clk,ps2_data,hex0,hex1,hex2,hex3,hex4,hex5);
input clk,clrn,ps2_clk,ps2_data;

output [6:0] hex0,hex1,hex2,hex3,hex4,hex5;

wire ready,overflow;
wire [7:0] data, asc;

reg nextdata_n;
reg flag1 = 1;
reg flag2 = 1;
reg flag3 = 0;
reg always_show = 1;
reg [7:0] count=0;
reg [7:0] outdata=0;

reg [6:0] count_clk = 0;
reg clk2 = 0;
always @(posedge clk)
begin
	if(count_clk == 100)
	begin
		count_clk <= 0;
		clk2 <= ~clk2;
	end
	else
		count_clk <= count_clk + 1;
end

ps2_keyboard P(.clk(clk), .clrn(clrn), .ps2_clk(ps2_clk), .ps2_data(ps2_data),
.data(data), .ready(ready), .nextdata_n(nextdata_n), .overflow(overflow));

ram R(.data(outdata), .data_asc(asc), .flag(flag3));

show S0(.flag(flag1), .data(outdata[3:0]), .hex(hex0));
show S1(.flag(flag1), .data(outdata[7:4]), .hex(hex1));
show S2(.flag(flag1), .data(asc[3:0]), .hex(hex2));
show S3(.flag(flag1), .data(asc[7:4]), .hex(hex3));
show S4(.flag(always_show), .data(count[3:0]), .hex(hex4));
show S5(.flag(always_show), .data(count[7:4]), .hex(hex5));

always @ (posedge clk2)
begin
	if (ready)
	begin
		if (data == 8'hf0)
		begin
			outdata <= data;
			count <= count + 1;
			flag2 <= 0;
			flag1 <= 0;
		end
		else if(!flag2)
		begin
			outdata <= data;
			flag2 <= 1;
			flag1 <= 0;
		end
		else if(data != 8'hf0 && flag2)
		begin
			outdata <= data;
			flag1 <= 1;
		end
		
		if(data == 8'h12 && outdata != 8'hf0) flag3 <= 1;
		else if(data == 8'h12 && outdata == 8'hf0) flag3 <= 0;
		nextdata_n <= 0;
	end
	else nextdata_n <= 1;
end

endmodule
