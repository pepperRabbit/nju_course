module record_module(
	input CLOCK_50,
	input mode,//模式
	input recording,//是否能够录音
	input flag,//判断当前数值是否有效
	input [3:0] note,//键盘输入音符编码
	input start,
	input record_start,
	
	output reg [3:0] record_note,//录音音符编码 
	output reg [6:0] out_dis0,//低位
	output reg [6:0] out_dis1//高位
	);
	
	reg [3:0] record_reg [149:0];//录音reg
	reg [7:0] number;//reg录音指针
	reg [7:0] p_num;//录音播放指针
	reg [31:0] clk_count1;
	reg [31:0] clk_count2;
	reg clk_1;
	reg clk_2;
	reg reflag;
	
	initial
	begin
		number <= 8'd1;
		p_num <= 8'b0;
	end

		
	always @ (posedge clk_1)
	begin			
		if (mode == 1'b1)//录音模式
		begin
			if(reflag == 1'b0 && record_start == 1'b1)
			begin
				$readmemh("music_record.txt",record_reg,0,149);	//init reg
				p_num <= 8'b0;
				number <= 8'd1;
				reflag <= 1'b1;
			end
			else if(record_start == 1'b0)
				reflag <= 1'b0;
				
			if (recording == 1'b1)//录音
			begin
				if(record_start == 1'b1)
				begin
					if(flag == 1'b1)
					begin
						record_reg[number] <= note;
						record_note <= note;
					end
					else
					begin	
						record_reg[number] <= 4'd0;
						record_note <= 4'b0;
					end
					number <= number + 8'b1;
				
					if(number >= 150)
						number <= 8'b0;
				end
				else
					record_note <= 4'd0;
			end
			else//播放录音
			begin
				if(start)
				begin
					record_note <= record_reg[p_num];
					p_num <= p_num + 8'd1;
					if(p_num > number)
						p_num <= 8'd0;
				end
				else
					record_note <= 4'd0;
			end
		end
		else
			record_note <= 4'd0;
	end
	
	
	//储存时钟
	always @(posedge CLOCK_50)
	if(mode == 1'b1)
		if(clk_count1==6250000)
		begin
			clk_count1=0;
			clk_1=~clk_1;
		end
		else
			clk_count1=clk_count1+1;
	
	//记录时间
	always @(posedge CLOCK_50)
	if(mode == 1'b1)
		if(clk_count2==25000000)
		begin
			clk_count2=0;
			clk_2=~clk_2;
		end
		else
			clk_count2=clk_count2+1;
	
	//七段数码管显示
	always @(posedge clk_2)
	begin
		if(recording)
		begin	
			out_dis0=(number/4)%10;//低位
			out_dis1=number/40;//高位
		end
		else
		begin
			out_dis0=(p_num/4)%10;//低位
			out_dis1=p_num/40;//高位
		end
		case(out_dis0)
			0:out_dis0=7'b1000000;
			1:out_dis0=7'b1111001;
			2:out_dis0=7'b0100100;
			3:out_dis0=7'b0110000;
			4:out_dis0=7'b0011001;
			5:out_dis0=7'b0010010;
			6:out_dis0=7'b0000010;
			7:out_dis0=7'b1111000;
			8:out_dis0=7'b0000000;
			9:out_dis0=7'b0010000;
		endcase
		
		case(out_dis1)
			0:out_dis1=7'b1000000;
			1:out_dis1=7'b1111001;
			2:out_dis1=7'b0100100;
			3:out_dis1=7'b0110000;
			4:out_dis1=7'b0011001;
			5:out_dis1=7'b0010010;
			6:out_dis1=7'b0000010;
			7:out_dis1=7'b1111000;
			8:out_dis1=7'b0000000;
			9:out_dis1=7'b0010000;
		endcase
	end
endmodule
