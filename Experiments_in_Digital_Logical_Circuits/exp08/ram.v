module ram(data, data_asc,flag);
	input [7:0] data;
	input flag;
	output reg [7:0] data_asc;
	reg [7:0] ram [255:0];

	initial
	begin
		$readmemh("C:/intelFPGA_lite/exp/exp08/ram.txt", ram, 0, 255);
	end

	always
	begin
		data_asc = ram[data];
		if(flag) data_asc = data_asc - 8'h20;
	end
endmodule
