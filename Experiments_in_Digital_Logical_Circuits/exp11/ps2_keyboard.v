module ps2_keyboard(clk,ps2_clk,ps2_data,out_ascii,waddr,hex0,hex1,hex2,hex3);
	input clk,ps2_clk,ps2_data;
	output reg [7:0] out_ascii;
	output reg [11:0] waddr;
	output [6:0] hex0,hex1,hex2,hex3;
	
	reg [7:0] data;
	reg [7:0] temp,ascii;
	reg cap=0;
	reg [6:0] row,col;
	// internal signal, for test
	reg [9:0] buffer; // ps2_data bits
	//reg [7:0] fifo[7:0]; // data fifo
	//reg [2:0] w_ptr,r_ptr; // fifo write and read pointers
	reg [3:0] count; // count ps2_data bits
	// detect falling edge of ps2_clk
	reg [2:0] ps2_clk_sync;
	
	reg [7:0] rom_ascii[255:0];
	initial begin
		$readmemh("C:/intelFPGA_lite/exp/exp11/rom_ascii.txt",rom_ascii,0,255);
	end
	
	show S0(1'b1,waddr[3:0],hex0);
	show S1(1'b1,waddr[7:4],hex1);
	show S2(1'b1,out_ascii[3:0],hex2);
	show S3(1'b1,out_ascii[7:4],hex3);

	always @(posedge clk) begin
		ps2_clk_sync <= {ps2_clk_sync[1:0],ps2_clk};
	end

	wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];

	always @(posedge clk) 
	begin
		if (sampling) begin
			if (count == 4'd10) begin
				if ((buffer[0] == 0) && // start bit
					(ps2_data) && // stop bit
					(^buffer[9:1])) begin // odd parity
					data <= buffer[8:1]; // kbd scan code
					temp <= data;
					if(cap) ascii<=rom_ascii[buffer[8:1]]-8'h20;
					else ascii<=rom_ascii[buffer[8:1]];
					if(buffer[8:1]==8'h58)begin
						cap<=~cap;
					end
					else if(buffer[8:1]==8'h5a)begin	//enter
						row=(row==29?0:row+1);
						col<=0;
						waddr<=row*70+col;
					end
					else 
					begin
						waddr<=row*70+col;
						if(col==69) 
						begin
							col<=0;
							row<=(row==29?0:row+1);
						end
						else col<=col+1;
					end
				end
				else data<=buffer[8:1];
				count <= 0; // for next
			end 
			else begin
				buffer[count] <= ps2_data; // store ps2_data
				count <= count + 3'b1;
			end
		end
	end
	
	always@(ascii)
	begin			
		if(temp!=8'hf0&&buffer[8:1]!=8'hf0) out_ascii<=ascii;
		else out_ascii<=8'h0;
	end

endmodule
