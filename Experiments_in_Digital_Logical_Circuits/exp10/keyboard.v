module keyboard(clk,clrn,ps2_clk,ps2_data,hex0,hex1,hex2,hex3,hex4,hex5,freq);
input clk,clrn,ps2_clk,ps2_data;

output [6:0] hex0,hex1,hex2,hex3,hex4,hex5;
output reg [15:0] freq;
reg [15:0] freq1;
reg [15:0] freq2;
reg [15:0] freq3;

wire ready,overflow;
wire [7:0] data, asc;

reg nextdata_n;
reg flag1 = 0;
reg flag2 = 0;
reg flag3 = 0;
reg flag4 = 0;
reg always_show = 1;
reg [7:0] count=0;
reg [7:0] outdata=0;
reg [7:0] outdata2=0;
reg [7:0] outdata3=0;

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

show S0(.flag(flag1), .data(outdata[3:0]), .hex(hex0));
show S1(.flag(flag1), .data(outdata[7:4]), .hex(hex1));
show S2(.flag(flag3), .data(outdata2[3:0]), .hex(hex2));
show S3(.flag(flag3), .data(outdata2[7:4]), .hex(hex3));
show S4(.flag(flag4), .data(outdata3[3:0]), .hex(hex4));
show S5(.flag(flag4), .data(outdata3[7:4]), .hex(hex5));

reg [3:0] state = 4'b0000;

always @ (posedge clk2)
begin
	if(flag4) freq = freq3/3 + freq2/3 + freq1/3;
	else if (flag3) freq = freq2/2 + freq1/2;
	else if (flag1) freq = freq1;
	else freq = 0;
end

always @ (posedge clk2)
begin
	if (ready)
	begin
		if (data == 8'hf0)
		begin
			outdata = data;
			flag2 <= 0;
			flag1 <= 0;
			flag3 <= 0;
			flag4 <= 0;
			//freq <= 0;
		end
		else if(!flag2)
		begin
			outdata <= data;
			flag2 <= 1;
			flag1 <= 0;
			flag3 <= 0;
			flag4 <= 0;
		end
		else if(data != 8'hf0 && flag1 && !flag3 && data!=outdata)
		begin
			flag3 <= 1;
			outdata2 <= data;
			case(data)
				8'h1c: freq2 <= 523.25* 65536 / 48000;
				8'h1b: freq2 <= 587.33* 65536 / 48000;
				8'h23: freq2 <= 659.26* 65536 / 48000;
				8'h2b: freq2 <= 698.46* 65536 / 48000;
				8'h34: freq2 <= 783.99* 65536 / 48000;
				8'h33: freq2 <= 880* 65536 / 48000;
				8'h3b: freq2 <= 987.77* 65536 / 48000;
				8'h42: freq2 <= 1046.5* 65536 / 48000;
				default: freq2 <= 0;
			endcase
			//if(freq1) freq <= freq2/2 + freq1/2;
		end
		else if(data != 8'hf0 && flag1 && flag3 && data!=outdata && data!=outdata2)
		begin
			flag4 <= 1;
			outdata3 <= data;
			case(data)
				8'h1c: freq3 <= 523.25* 65536 / 48000;
				8'h1b: freq3 <= 587.33* 65536 / 48000;
				8'h23: freq3 <= 659.26* 65536 / 48000;
				8'h2b: freq3 <= 698.46* 65536 / 48000;
				8'h34: freq3 <= 783.99* 65536 / 48000;
				8'h33: freq3 <= 880* 65536 / 48000;
				8'h3b: freq3 <= 987.77* 65536 / 48000;
				8'h42: freq3 <= 1046.5* 65536 / 48000;
				default: freq3 <= 0;
			endcase
			//if(freq1) freq <= freq2/2 + freq1/2;
		end
		else if(data != 8'hf0 && flag2 && !flag3 && !flag4)
		begin
			outdata <= data;
			flag1 <= 1;
			case(data)
				8'h1c: freq1 <= 523.25* 65536 / 48000;
				8'h1b: freq1 <= 587.33* 65536 / 48000;
				8'h23: freq1 <= 659.26* 65536 / 48000;
				8'h2b: freq1 <= 698.46* 65536 / 48000;
				8'h34: freq1 <= 783.99* 65536 / 48000;
				8'h33: freq1 <= 880* 65536 / 48000;
				8'h3b: freq1 <= 987.77* 65536 / 48000;
				8'h42: freq1 <= 1046.5* 65536 / 48000;
				default: freq1 <= 0;
			endcase
			//freq <= freq1;
			//freq <= freq * 65536 / 48000;
		end

		nextdata_n <= 0;
	end
	else nextdata_n <= 1;
end

endmodule
