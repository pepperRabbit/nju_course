module vga_ctrl(
input pclk, //25MHz时钟
input reset, //置位
output hsync, // 行同步和列同步信号
output vsync,
output valid, //消隐信号
output [9:0] h_cnt,
output [9:0] v_cnt
);

// 640x480分辨率下的VGA参数设置
parameter h_frontporch = 96;
parameter h_active = 144;
parameter h_backporch = 784;
parameter h_total = 800;
parameter v_frontporch = 2;
parameter v_active = 35;
parameter v_backporch = 515;
parameter v_total = 525;

// 像素计数值
reg [9:0] x_cnt;
reg [9:0] y_cnt;
wire h_valid;
wire v_valid;

always @(posedge reset or posedge pclk) // 行像素计数
	if (reset == 1'b1) x_cnt <= 1;
	else
	begin
		if (x_cnt == h_total) x_cnt <= 1;
		else x_cnt <= x_cnt + 10'd1;
	end

always @(posedge pclk) // 列 像 素 计 数
	if (reset == 1'b1) y_cnt <= 1;
	else
	begin
		if (y_cnt == v_total & x_cnt == h_total) y_cnt <= 1;
		else if (x_cnt == h_total) y_cnt <= y_cnt + 10'd1;
	end
	
// 生成同步信号
assign hsync = (x_cnt > h_frontporch);
assign vsync = (y_cnt > v_frontporch);

// 生成消隐信号
assign h_valid = (x_cnt > h_active) & (x_cnt <= h_backporch);
assign v_valid = (y_cnt > v_active) & (y_cnt <= v_backporch);
assign valid = h_valid & v_valid;

assign h_cnt = ((h_valid == 1'b1)) ? x_cnt - 144 : {10{1'b0}};
assign v_cnt = ((v_valid == 1'b1)) ? y_cnt - 35 : {10{1'b0}};
	
endmodule
	