/*
	本音乐播放器可以实现的功能：
	1.暂停播放/继续播放/重新播放。
	2.切歌（直接切换到下一首歌）
	3.音乐播放的快进与后退
	4.单曲循环播放、顺序循环播放与随机顺序播放
	5.显示当前音乐已经播放的时间
*/

module play(
	input CLOCK_50,
	input mode,     //判断是否是播放状态
   input button1,  //拓展按钮修改——切歌 （=1的时候有效）
   input button2,  //快进4个音
   input button3,  //后退4个音
   input [1:0]select,   //选择模式（0：单曲循坏 1：顺序播放 2：随机播放）
   input start,    //开始播放，暂停播放 start=1时表示播放，=0时表示暂停
   input restart, //重新播放
	output reg [6:0]out_dis0,  //低位
   output reg [6:0]out_dis1, //高位
	output reg [3:0]F//返回的4位二进制码
);
	 
	 reg flag=0; //作为修改EN模块的传入参数,当需要EN修改的时候flag置为1  
	 reg [1:0]EN=0;   //歌曲播放选择
    reg [3:0]ram1[120:0]; //南大校歌
    reg [3:0]ram2[70:0]; //Canon
    reg [3:0]ram3[63:0]; //ChildHood Memory
    reg [31:0]clk_count2=0; //读取音频输出数据计数
    reg [31:0]clk_count3=0; //时间七段译码器输出计数
    reg clk_2=0;    //读取音频输出数据频率时钟
    reg [3:0]choice=4'b0000;
    reg [31:0]number;   //音频ram文件的按位读取操作计数
	 reg clk_3=0;
	 reg [19:0] rand;//随机数
		
	initial
		number <= 0;
		
//歌曲播放            
always @(posedge CLOCK_50)
begin
rand = rand + 2'b1;
if(mode == 1'b0)
   if(clk_count2==12500000)
   begin
      clk_count2=0;
      clk_2=~clk_2;     
	end
   else
		clk_count2=clk_count2+1;
end
		
//记录时间
always @(posedge CLOCK_50)
if(mode == 1'b0)
   if(clk_count3==25000000)
   begin
      clk_count3=0;
      clk_3=~clk_3;
   end
	else
		clk_count3=clk_count3+1;

always @(posedge CLOCK_50)
begin
    case(EN)
        2'b00:$readmemh("music1.txt",ram1,0,120);
        2'b01:$readmemh("music2.txt",ram2,0,70);
        2'b10:$readmemh("music3.txt",ram3,0,63);
        default:;
    endcase
end

always @(posedge clk_2)
begin
if(mode == 1'b0)
begin
	if(button1==1)//切歌了，自然从0开始
		number=0;
	if(restart==1)//重新播放当前歌曲，number清零
		number=0;
	if(button2==1)//快进
		number=number+4;
	if(button3==1&&number>10)//快退
		number=number-4;
		
	if(start==1)//歌曲播放
	begin
		if(EN==0)
		begin
			if(number>=121)
			begin
				flag=1;
				number=0;
			end
			else
			begin
				flag=0;
				F=ram1[number];
				number=number+1;
			end
		end
		
		else if(EN==1)
		begin
			if(number>=71)
			begin 
				flag=1;
				number=0;
			end
			else
			begin
				flag=0;
				F=ram2[number];
				number=number+1;
			end
		end
		
		else
		begin
			if(number>=64)
			begin 
				flag=1;
				number=0;
			end
			else
			begin
				flag=0;
				F=ram3[number];
				number=number+1;
			end
		end
	end
	else
		F = 4'h0;
end
end

always @(negedge clk_2)
if(mode == 1'b0)
begin
	if(flag==1||button1==1)//歌曲结束了自然切歌，或者是手动切歌
	begin
		if(select==0)
			EN=EN;//歌曲不变，单曲循环  附：若在单曲循环模式下切歌等效于重新播放。
		else if(select==1)//循环播放
		begin
			if(EN!=2)
				EN=EN+1;
			else
				EN=0;
		end
		else//随机播放 
		begin
			EN[0] = rand[10];
         EN[1] = rand[15];
         if(EN == 2'b11)
				EN = 2'b00;
		end
	end
end


//七段数码管显示
always @(posedge clk_3)
begin
	out_dis0=(number/2)%10;//低位
	out_dis1=number/20;//高位
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
