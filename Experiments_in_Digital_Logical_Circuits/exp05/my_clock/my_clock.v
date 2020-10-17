module my_clock(clk, select, change_select, change_in, sec_in, hex0, hex1, hex2, hex3, 
hex4, hex5, led);
input clk;
input [1:0] select;				//功能选择	0:normal  1:set time  2:alarm  3:秒表
input [1:0] change_select;		//调整/闹钟时分秒选择
input change_in;					//调整/闹钟input
input sec_in;						//秒表开关

output reg [6:0] hex0;
output reg [6:0] hex1;
output reg [6:0] hex2;
output reg [6:0] hex3;
output reg [6:0] hex4;
output reg [6:0] hex5;
output reg led;

reg [24:0] count_clk = 0;
reg [5:0] sec = 0;
reg [5:0] min = 0;
reg [4:0] hour = 0;
reg [5:0] set_sec = 0;
reg [5:0] set_min = 0;
reg [4:0] set_hour = 0;
reg [5:0] alm_sec = 0;
reg [5:0] alm_min = 0;
reg [4:0] alm_hour = 0;
reg clk_1s = 0;
reg [16:0] sec_clock = 0;

always @ (posedge clk)
	if(count_clk == 25000000)
	begin
		count_clk <= 0;
		clk_1s <= ~clk_1s;end
	else count_clk <= count_clk + 1;

always @ (posedge clk_1s)
begin
	led = 0;
	if(select != 3) sec_clock = 0;
	if(select == 1)		//手动设置时间
	begin
		sec = set_sec;
		min = set_min;
		hour = set_hour;
	end
	else
	begin
		if(sec < 59) sec = sec + 1;
		else
		begin
			sec = 0;
			if(min < 59) min = min + 1;
			else 
			begin
				min = 0;
				if(hour < 23) hour = hour + 1;
				else hour = 0;
			end		
		end
	end
	
	if(select == 3 && sec_in == 1) sec_clock = sec_clock+1;
	
	if(sec == alm_sec && min == alm_min && hour == alm_hour) led=1;
	
	//show time
	if(select == 1) 		//show time setting
	begin
		case(set_sec%10)
			0: hex0 = 7'b1000000;
			1: hex0 = 7'b1111001;
			2: hex0 = 7'b0100100;
			3: hex0 = 7'b0110000;
			4: hex0 = 7'b0011001;
			5: hex0 = 7'b0010010;
			6: hex0 = 7'b0000010;
			7: hex0 = 7'b1111000;
			8: hex0 = 7'b0000000;
			9: hex0 = 7'b0010000;
			default: hex0 = 7'b1111111;
		endcase 
	
		case(set_sec/10)
			0: hex1 = 7'b1000000;
			1: hex1 = 7'b1111001;
			2: hex1 = 7'b0100100;
			3: hex1 = 7'b0110000;
			4: hex1 = 7'b0011001;
			5: hex1 = 7'b0010010;
			6: hex1 = 7'b0000010;
			7: hex1 = 7'b1111000;
			8: hex1 = 7'b0000000;
			9: hex1 = 7'b0010000;
			default: hex1 = 7'b1111111;
		endcase

		case(set_min%10)
			0: hex2 = 7'b1000000;
			1: hex2 = 7'b1111001;
			2: hex2 = 7'b0100100;
			3: hex2 = 7'b0110000;
			4: hex2 = 7'b0011001;
			5: hex2 = 7'b0010010;
			6: hex2 = 7'b0000010;
			7: hex2 = 7'b1111000;
			8: hex2 = 7'b0000000;
			9: hex2 = 7'b0010000;
			default: hex2 = 7'b1111111;
		endcase

		case(set_min/10)
			0: hex3 = 7'b1000000;
			1: hex3 = 7'b1111001;
			2: hex3 = 7'b0100100;
			3: hex3 = 7'b0110000;
			4: hex3 = 7'b0011001;
			5: hex3 = 7'b0010010;
			6: hex3 = 7'b0000010;
			7: hex3 = 7'b1111000;
			8: hex3 = 7'b0000000;
			9: hex3 = 7'b0010000;
			default: hex3 = 7'b1111111;
		endcase
		
		case(set_hour%10)
			0: hex4 = 7'b1000000;
			1: hex4 = 7'b1111001;
			2: hex4 = 7'b0100100;
			3: hex4 = 7'b0110000;
			4: hex4 = 7'b0011001;
			5: hex4 = 7'b0010010;
			6: hex4 = 7'b0000010;
			7: hex4 = 7'b1111000;
			8: hex4 = 7'b0000000;
			9: hex4 = 7'b0010000;
			default: hex4 = 7'b1111111;
		endcase

		case(set_hour/10)
			0: hex5 = 7'b1000000;
			1: hex5 = 7'b1111001;
			2: hex5 = 7'b0100100;
			3: hex5 = 7'b0110000;
			4: hex5 = 7'b0011001;
			5: hex5 = 7'b0010010;
			6: hex5 = 7'b0000010;
			7: hex5 = 7'b1111000;
			8: hex5 = 7'b0000000;
			9: hex5 = 7'b0010000;
			default: hex5 = 7'b1111111;
		endcase
	end
	else if(select == 2)	//show alarm setting
	begin
		case(alm_sec%10)
			0: hex0 = 7'b1000000;
			1: hex0 = 7'b1111001;
			2: hex0 = 7'b0100100;
			3: hex0 = 7'b0110000;
			4: hex0 = 7'b0011001;
			5: hex0 = 7'b0010010;
			6: hex0 = 7'b0000010;
			7: hex0 = 7'b1111000;
			8: hex0 = 7'b0000000;
			9: hex0 = 7'b0010000;
			default: hex0 = 7'b1111111;
		endcase 
	
		case(alm_sec/10)
			0: hex1 = 7'b1000000;
			1: hex1 = 7'b1111001;
			2: hex1 = 7'b0100100;
			3: hex1 = 7'b0110000;
			4: hex1 = 7'b0011001;
			5: hex1 = 7'b0010010;
			6: hex1 = 7'b0000010;
			7: hex1 = 7'b1111000;
			8: hex1 = 7'b0000000;
			9: hex1 = 7'b0010000;
			default: hex1 = 7'b1111111;
		endcase

		case(alm_min%10)
			0: hex2 = 7'b1000000;
			1: hex2 = 7'b1111001;
			2: hex2 = 7'b0100100;
			3: hex2 = 7'b0110000;
			4: hex2 = 7'b0011001;
			5: hex2 = 7'b0010010;
			6: hex2 = 7'b0000010;
			7: hex2 = 7'b1111000;
			8: hex2 = 7'b0000000;
			9: hex2 = 7'b0010000;
			default: hex2 = 7'b1111111;
		endcase

		case(alm_min/10)
			0: hex3 = 7'b1000000;
			1: hex3 = 7'b1111001;
			2: hex3 = 7'b0100100;
			3: hex3 = 7'b0110000;
			4: hex3 = 7'b0011001;
			5: hex3 = 7'b0010010;
			6: hex3 = 7'b0000010;
			7: hex3 = 7'b1111000;
			8: hex3 = 7'b0000000;
			9: hex3 = 7'b0010000;
			default: hex3 = 7'b1111111;
		endcase
		
		case(alm_hour%10)
			0: hex4 = 7'b1000000;
			1: hex4 = 7'b1111001;
			2: hex4 = 7'b0100100;
			3: hex4 = 7'b0110000;
			4: hex4 = 7'b0011001;
			5: hex4 = 7'b0010010;
			6: hex4 = 7'b0000010;
			7: hex4 = 7'b1111000;
			8: hex4 = 7'b0000000;
			9: hex4 = 7'b0010000;
			default: hex4 = 7'b1111111;
		endcase

		case(alm_hour/10)
			0: hex5 = 7'b1000000;
			1: hex5 = 7'b1111001;
			2: hex5 = 7'b0100100;
			3: hex5 = 7'b0110000;
			4: hex5 = 7'b0011001;
			5: hex5 = 7'b0010010;
			6: hex5 = 7'b0000010;
			7: hex5 = 7'b1111000;
			8: hex5 = 7'b0000000;
			9: hex5 = 7'b0010000;
			default: hex5 = 7'b1111111;
		endcase
	end
	else if(select == 3)		//show sec clock
	begin
		case((sec_clock%60)%10)
			0: hex0 = 7'b1000000;
			1: hex0 = 7'b1111001;
			2: hex0 = 7'b0100100;
			3: hex0 = 7'b0110000;
			4: hex0 = 7'b0011001;
			5: hex0 = 7'b0010010;
			6: hex0 = 7'b0000010;
			7: hex0 = 7'b1111000;
			8: hex0 = 7'b0000000;
			9: hex0 = 7'b0010000;
			default: hex0 = 7'b1111111;
		endcase 
	
		case((sec_clock%60)/10)
			0: hex1 = 7'b1000000;
			1: hex1 = 7'b1111001;
			2: hex1 = 7'b0100100;
			3: hex1 = 7'b0110000;
			4: hex1 = 7'b0011001;
			5: hex1 = 7'b0010010;
			6: hex1 = 7'b0000010;
			7: hex1 = 7'b1111000;
			8: hex1 = 7'b0000000;
			9: hex1 = 7'b0010000;
			default: hex1 = 7'b1111111;
		endcase

		case((sec_clock/60)%10)
			0: hex2 = 7'b1000000;
			1: hex2 = 7'b1111001;
			2: hex2 = 7'b0100100;
			3: hex2 = 7'b0110000;
			4: hex2 = 7'b0011001;
			5: hex2 = 7'b0010010;
			6: hex2 = 7'b0000010;
			7: hex2 = 7'b1111000;
			8: hex2 = 7'b0000000;
			9: hex2 = 7'b0010000;
			default: hex2 = 7'b1111111;
		endcase

		case((sec_clock/60)/10)
			0: hex3 = 7'b1000000;
			1: hex3 = 7'b1111001;
			2: hex3 = 7'b0100100;
			3: hex3 = 7'b0110000;
			4: hex3 = 7'b0011001;
			5: hex3 = 7'b0010010;
			6: hex3 = 7'b0000010;
			7: hex3 = 7'b1111000;
			8: hex3 = 7'b0000000;
			9: hex3 = 7'b0010000;
			default: hex3 = 7'b1111111;
		endcase
		
		case((sec_clock/3600)%10)
			0: hex4 = 7'b1000000;
			1: hex4 = 7'b1111001;
			2: hex4 = 7'b0100100;
			3: hex4 = 7'b0110000;
			4: hex4 = 7'b0011001;
			5: hex4 = 7'b0010010;
			6: hex4 = 7'b0000010;
			7: hex4 = 7'b1111000;
			8: hex4 = 7'b0000000;
			9: hex4 = 7'b0010000;
			default: hex4 = 7'b1111111;
		endcase

		case((sec_clock/3600)/10)
			0: hex5 = 7'b1000000;
			1: hex5 = 7'b1111001;
			2: hex5 = 7'b0100100;
			3: hex5 = 7'b0110000;
			4: hex5 = 7'b0011001;
			5: hex5 = 7'b0010010;
			6: hex5 = 7'b0000010;
			7: hex5 = 7'b1111000;
			8: hex5 = 7'b0000000;
			9: hex5 = 7'b0010000;
			default: hex5 = 7'b1111111;
		endcase
	end
	else
	begin
		case(sec%10)
			0: hex0 = 7'b1000000;
			1: hex0 = 7'b1111001;
			2: hex0 = 7'b0100100;
			3: hex0 = 7'b0110000;
			4: hex0 = 7'b0011001;
			5: hex0 = 7'b0010010;
			6: hex0 = 7'b0000010;
			7: hex0 = 7'b1111000;
			8: hex0 = 7'b0000000;
			9: hex0 = 7'b0010000;
			default: hex0 = 7'b1111111;
		endcase 
	
		case(sec/10)
			0: hex1 = 7'b1000000;
			1: hex1 = 7'b1111001;
			2: hex1 = 7'b0100100;
			3: hex1 = 7'b0110000;
			4: hex1 = 7'b0011001;
			5: hex1 = 7'b0010010;
			6: hex1 = 7'b0000010;
			7: hex1 = 7'b1111000;
			8: hex1 = 7'b0000000;
			9: hex1 = 7'b0010000;
			default: hex1 = 7'b1111111;
		endcase

		case(min%10)
			0: hex2 = 7'b1000000;
			1: hex2 = 7'b1111001;
			2: hex2 = 7'b0100100;
			3: hex2 = 7'b0110000;
			4: hex2 = 7'b0011001;
			5: hex2 = 7'b0010010;
			6: hex2 = 7'b0000010;
			7: hex2 = 7'b1111000;
			8: hex2 = 7'b0000000;
			9: hex2 = 7'b0010000;
			default: hex2 = 7'b1111111;
		endcase

		case(min/10)
			0: hex3 = 7'b1000000;
			1: hex3 = 7'b1111001;
			2: hex3 = 7'b0100100;
			3: hex3 = 7'b0110000;
			4: hex3 = 7'b0011001;
			5: hex3 = 7'b0010010;
			6: hex3 = 7'b0000010;
			7: hex3 = 7'b1111000;
			8: hex3 = 7'b0000000;
			9: hex3 = 7'b0010000;
			default: hex3 = 7'b1111111;
		endcase
		
		case(hour%10)
			0: hex4 = 7'b1000000;
			1: hex4 = 7'b1111001;
			2: hex4 = 7'b0100100;
			3: hex4 = 7'b0110000;
			4: hex4 = 7'b0011001;
			5: hex4 = 7'b0010010;
			6: hex4 = 7'b0000010;
			7: hex4 = 7'b1111000;
			8: hex4 = 7'b0000000;
			9: hex4 = 7'b0010000;
			default: hex4 = 7'b1111111;
		endcase

		case(hour/10)
			0: hex5 = 7'b1000000;
			1: hex5 = 7'b1111001;
			2: hex5 = 7'b0100100;
			3: hex5 = 7'b0110000;
			4: hex5 = 7'b0011001;
			5: hex5 = 7'b0010010;
			6: hex5 = 7'b0000010;
			7: hex5 = 7'b1111000;
			8: hex5 = 7'b0000000;
			9: hex5 = 7'b0010000;
			default: hex5 = 7'b1111111;
		endcase
	end
end


always @ (posedge change_in)
begin
	if(select == 1)		//手动调整时间
	begin
		if(change_select == 0)	//change sec
		begin
			if(set_sec < 59) set_sec = set_sec+1;
			else
			begin
				set_sec = 0;
				if(set_min < 59) set_min = set_min+1;
				else
				begin
					set_min = 0;
					if(set_hour < 23) set_hour = set_hour+1;
					else set_hour = 0;
				end
			end
		end
		else if(change_select == 1)	//change min
		begin
			if(set_min < 59) set_min = set_min+1;
			else
			begin
				set_min = 0;
				if(set_hour < 23) set_hour = set_hour+1;
				else set_hour = 0;
			end
		end
		else if(change_select == 2)	//change hour
		begin
			if(set_hour < 23) set_hour = set_hour+1;
			else set_hour = 0;
		end
	end
	else if(select == 2) 	//set alarm
	begin
		if(change_select == 0)	//change sec
		begin
			if(alm_sec < 59) alm_sec = alm_sec+1;
			else
			begin
				alm_sec = 0;
				if(alm_min < 59) alm_min = alm_min+1;
				else
				begin
					alm_min = 0;
					if(alm_hour < 23) alm_hour = alm_hour+1;
					else alm_hour = 0;
				end
			end
		end
		else if(change_select == 1)	//change min
		begin
			if(alm_min < 59) alm_min = alm_min+1;
			else
			begin
				alm_min = 0;
				if(alm_hour < 23) alm_hour = alm_hour+1;
				else alm_hour = 0;
			end
		end
		else if(change_select == 2)	//change hour
		begin
			if(alm_hour < 23) alm_hour = alm_hour+1;
			else alm_hour = 0;
		end
	end
	
end

endmodule
