module signal(
	input clk, //50MHz
	input [7:0] data,
	input ready,
	
	//需要输出的信号============================================================================
	output reg start,//暂停0 or 开始1-------------------------回车
	output reg [1:0] mode,//三种模式：单曲0，循环1，随机2-------左边键盘数字1 2 3
	output reg next,//切歌，高电平有效-------------------------waived
	output reg restart,//重新播放，高电平有效-------------------waived
	output reg record_mode,//录音：非录音模式0，录音模式1-------[：播放  ]：录音
	output reg recording,//录音1，播放录音0--------------------；录音  ‘ 播放录音
	output reg record_start,//开始录音1，停止录音0-------------空格
	output reg record_flag,//当前按键信号是否写入录音reg
	output reg [5:0] sound,//音量-----------------------------方向上下键
							 //音量反馈在Sin_Generator模块中是使信号右移，则数越大，音量越小
	output reg [3:0] note,//音符序号---------------------------Q~U低音区，A~J中音区
	output reg [7:0] out_dis1	//mode
	//=========================================================================================
	);
	
	
	reg flag;//记录键盘data是否有效
	
	initial 
	begin
		flag <= 1'b1;
		start <= 1'b0;
		mode <= 2'b01;
		next <= 1'b0;
		record_mode <= 1'b0;
		recording <= 1'b0;
		record_start <= 1'b0;
		sound <= 5'd4;
		note <= 4'b0;
	end
	
	always @ (negedge clk)
	begin
		if(next == 1'b1)
			next <= 1'b0;
				
		if(restart == 1'b1)
			restart <= 1'b0;
				
		if(ready == 1)
		begin
			if(data == 8'b11110000 || flag == 0)  //无效信号
			begin		
				record_flag <= 1'b0;
				
				if(flag == 0)
				begin
					flag <= 1;
				end
				else
					flag <= 0;		
			end
			else
			begin
				case(data)
					8'h5A:begin start <= ~start; end	// enter 开始暂停
					8'h16:begin mode <= 2'b00; end	// 1 单曲播放
					8'h1E:begin mode <= 2'b01; end	// 2 列表循环
					8'h26:begin mode <= 2'b10; end	// 3 随机播放
					8'h74:begin next <= 1'b1; end		// WAIVED
					8'h6B:begin restart <= 1'b1; end	// WAIVED
					8'h54:begin // [ 切换到非录音模式，如果当前正在录音则停止，并且下次切换到录音模式时播放录音
								record_mode <= 1'b0; 
								record_start <= 1'b0; 
								recording <= 1'b0;
								record_flag <= 1'b0;
								start <= 1'b0;
							end
					8'h5B:begin	// ] 录音模式
								record_mode <= 1'b1; 
								start <= 1'b0;
							end
					8'h52:begin recording <= 1'b0; record_start <= 1'b0; end	// ' 播放录音
					8'h4C:begin	// ; 录音
								if(record_mode == 1'b1)//当处于录音模式时才能开启录音功能
									recording <= 1'b1;
							end
					8'h29:begin	// space: start/stop record
								if(recording == 1'b1)//当正在录音的时候才能开始或停止录音
									record_start <= ~record_start;
							end
					8'h75:begin	// PgUp: volume+
								if(sound > 5'b00000)//当不为0时才能减
									sound = sound - 3'b001;
							end
					8'h72:begin	// PgDn: volume-
								if(sound < 5'b10000)//当不为16时才能加
									sound = sound + 3'b001;
							end
					default:
					begin
						if(record_start == 1'b1)
						begin
							record_flag <= 1'b1;
							case (data)
								8'h15:begin note <= 4'h1; end
								8'h1D:begin note <= 4'h2; end
								8'h24:begin note <= 4'h3; end
								8'h2D:begin note <= 4'h4; end
								8'h2C:begin note <= 4'h5; end
								8'h35:begin note <= 4'h6; end
								8'h3C:begin note <= 4'h7; end
								8'h1C:begin note <= 4'h8; end
								8'h1B:begin note <= 4'h9; end
								8'h23:begin note <= 4'hA; end
								8'h2B:begin note <= 4'hB; end
								8'h34:begin note <= 4'hC; end
								8'h33:begin note <= 4'hD; end
								8'h3B:begin note <= 4'hE; end
								default: record_flag <= 1'b0;
							endcase
						end
					end
				endcase
			end
		end
		case(mode)
			0:out_dis1 <= 7'b1000000;
			1:out_dis1 <= 7'b1111001;
			2:out_dis1 <= 7'b0100100;
		endcase
	end
endmodule
	
module change_next(nextdata_n, ready);
	input ready;
	output reg nextdata_n;
	
	always @ (ready)
	begin
		if(ready == 1)
			nextdata_n <= 0;
		else
			nextdata_n <= 1;
	end
endmodule
