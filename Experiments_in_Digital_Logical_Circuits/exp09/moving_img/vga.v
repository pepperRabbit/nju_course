module vga(clk,vga_clk,hsync,vsync,valid,vga_r,vga_g,vga_b,VGA_SYNC_N);
input clk;

output vga_clk;
output hsync,vsync,valid,VGA_SYNC_N;
output [7:0] vga_r,vga_g,vga_b;

wire [23:0] data;
wire [9:0] h_cnt;
wire [9:0] v_cnt;
reg [13:0] rom_addr = 14'b0;
wire area;
reg [9:0] img_x=10'd200;
reg [9:0] img_y=10'd200;
parameter img_len=10'd100;
parameter img_height=10'd100;
reg [23:0] vga_data;

assign area = ((v_cnt >= img_y) & (v_cnt <= img_y + img_height - 1) 
& (h_cnt >= img_x) & (h_cnt <= img_x + img_len - 1)) ? 1'b1 : 1'b0;

assign VGA_SYNC_N = 0;

clkgen #(25000000) my_vgaclk(clk,1'b0,1'b1,vga_clk);
rom R(.address(rom_addr), .clock(vga_clk), .q(data));

vga_ctrl V(.pclk(vga_clk), .reset(1'b0), .hsync(hsync), .vsync(vsync), .valid(valid), 
.h_cnt(h_cnt), .v_cnt(v_cnt));

always @ (posedge vga_clk)
begin
	if (valid == 1'b1)
	begin
		if (area == 1'b1)
		begin
			rom_addr <= rom_addr + 14'b1;
         vga_data <= data;
		end
		else
      begin
         rom_addr <= rom_addr;
         vga_data <= 24'b0;
      end
	end
	else
   begin
		vga_data <= 24'hFFFFFF;
      if (v_cnt == 0) rom_addr <= 14'b0;
   end
end

assign vga_r = vga_data[23:16];
assign vga_g = vga_data[15:8];
assign vga_b = vga_data[7:0];

reg [7:0] speed_cnt;
wire speed_ctrl;

always @(posedge vga_clk)
if ((v_cnt[5] == 1'b1) & (h_cnt == 1)) speed_cnt <= speed_cnt + 8'h01;

debounce D(.sig_in(speed_cnt[5]), .clk(vga_clk), .sig_out(speed_ctrl));

reg [1:0] flag = 2'b0;

always @ (posedge vga_clk)
begin
	if (speed_ctrl == 1'b1)
	begin
		if(img_x == 1)
		begin
			if(img_y == 1) flag = 2'b00;
			else if(img_y == 480-img_height) flag = 2'b01;
			else flag[1] = (~flag[1]);
		end
		else if(img_x == 640-img_len)
		begin
			if(img_y == 1) flag=2'b10;
			else if(img_y == 480-img_height) flag = 2'b11;
			else flag[1] = (~flag[1]);
		end
		else if(img_y == 1) flag[0] = (~flag[0]);
		else if(img_y == 480-img_height) flag[0] = (~flag[0]);
		else flag = flag;
		
		case (flag)
			2'b00 :
			begin
				img_x <= img_x + 10'b0000000001;
				img_y <= img_y + 10'b0000000001;
			end
			2'b01 :
			begin
				img_x <= img_x + 10'b0000000001;
				img_y <= img_y - 10'b0000000001;
			end
			2'b10 :
			begin
				img_x <= img_x - 10'b0000000001;
				img_y <= img_y + 10'b0000000001;
			end
			2'b11 :
			begin
				img_x <= img_x - 10'b0000000001;
				img_y <= img_y - 10'b0000000001;
			end
			default :
			begin
				img_x <= img_x + 10'b0000000001;
				img_y <= img_y + 10'b0000000001;
			end
		endcase
	end
end

endmodule
