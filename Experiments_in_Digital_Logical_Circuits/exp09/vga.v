module vga(clk,vga_clk,hsync,vsync,valid,vga_r,vga_g,vga_b,VGA_SYNC_N);
input clk;

output vga_clk;
output hsync,vsync,valid,VGA_SYNC_N;
output [7:0] vga_r,vga_g,vga_b;

//reg [23:0] vga_data;

wire [9:0] h_addr;
wire [9:0] v_addr;
wire [11:0] vga_data;
wire [18:0] addr;

assign VGA_SYNC_N = 0;
assign addr = h_addr*512 + v_addr[8:0];

/*always
begin
	if((h_addr%150)<50) vga_data=24'hFF0000;
	else if((h_addr%150)<100) vga_data=24'h00FF00;
	else vga_data=24'h0000FF;
end*/

clkgen #(25000000) my_vgaclk(clk,1'b0,1'b1,vga_clk);
rom R(.address(addr), .clock(vga_clk), .q(vga_data));

vga_ctrl V(.pclk(vga_clk), .reset(1'b0), .vga_data({vga_data}), .h_addr(h_addr), 
.v_addr(v_addr), .hsync(hsync), .vsync(vsync), .valid(valid), .vga_r(vga_r), 
.vga_g(vga_g), .vga_b(vga_b));

endmodule
