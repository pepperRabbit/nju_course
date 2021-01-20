module vga(clk,asciires,waddr,h_addr,v_addr,vga_data);
input clk;
input [7:0] asciires;
input [11:0] waddr;
input [9:0] h_addr,v_addr;

output reg [23:0] vga_data;

reg [7:0] ram_vga[2099:0];
reg [11:0] rom_font[4095:0];
initial begin
	$readmemh("C:/intelFPGA_lite/exp/exp11/vga_font.txt",rom_font,0,4095);
end

wire [9:0] x,y;
wire [11:0] font_data;
wire [11:0] ramaddr;
wire [7:0] ascii;
wire [11:0] romfont_addr,offset_x,offset_y;
assign x=h_addr/9;
assign y=v_addr>>4;
assign ramaddr=x+(y<<6)+(y<<2)+(y<<1);
assign ascii=ram_vga[ramaddr];
assign offset_x=h_addr-(x<<3)-x;
assign offset_y=v_addr-(y<<4);
assign romfont_addr={ascii,4'b0000}+offset_y;
assign font_data=rom_font[romfont_addr];

always@(posedge clk)begin
	if(asciires!=8'h0) ram_vga[waddr]<=asciires;
	
	if(h_addr >= 630) vga_data = 24'h0;
	else if(font_data[offset_x]==1'b1) vga_data = 24'hffffff;
	else vga_data = 24'h0;
end

endmodule
