
//=======================================================
//  This code is generated by Terasic System Builder
//=======================================================

module clock(

	//////////// CLOCK //////////
	CLOCK_50,

	//////////// SW //////////
	SW0,	//start
	SW1,	//stop
	SW2,	//zero

	//////////// LED //////////
	LEDR,

	//////////// Seg7 //////////
	HEX0,
	HEX1
	
);



//=======================================================
//  REG/WIRE declarations
//=======================================================
input CLOCK_50;
input SW0,SW1,SW2;

output reg LEDR;
output reg [6:0] HEX0;
output reg [6:0] HEX1;

reg [24:0] count_clk = 0;
reg clk_1s = 0;
reg [3:0] left = 0;
reg [3:0] right = 0;
reg [6:0] count = 0;


//=======================================================
//  Structural coding
//=======================================================
always @ (posedge CLOCK_50)
begin
	if(count_clk == 25000000)
	begin
		count_clk <= 0;
		clk_1s <= ~clk_1s;end
	else count_clk <= count_clk + 1;
end

always @ (posedge clk_1s)
begin
	LEDR = 0;
	if(SW0) //start
	begin
		if(SW1) ;	//stop, do nothing
		
		else if(SW2) begin	//zero
			count = 0;
			right = 0;
			left = 0;end
			
		else begin
			if(count<100) begin	//show numbers
				right = count%10;
				left = count/10;end
				
			if(count>98) 	//flash
				LEDR = count % 2;
				
			count = count+1;
		end
			
		case(left)
			0: HEX1 = 7'b1000000;
			1: HEX1 = 7'b1111001;
			2: HEX1 = 7'b0100100;
			3: HEX1 = 7'b0110000;
			4: HEX1 = 7'b0011001;
			5: HEX1 = 7'b0010010;
			6: HEX1 = 7'b0000010;
			7: HEX1 = 7'b1111000;
			8: HEX1 = 7'b0000000;
			9: HEX1 = 7'b0010000;
			default: HEX1 = 7'b1111111;
		endcase
			
		case(right)
			0: HEX0 = 7'b1000000;
			1: HEX0 = 7'b1111001;
			2: HEX0 = 7'b0100100;
			3: HEX0 = 7'b0110000;
			4: HEX0 = 7'b0011001;
			5: HEX0 = 7'b0010010;
			6: HEX0 = 7'b0000010;
			7: HEX0 = 7'b1111000;
			8: HEX0 = 7'b0000000;
			9: HEX0 = 7'b0010000;
			default: HEX0 = 7'b1111111;
		endcase
	end
	else begin
		count = 0;
		left = 0;
		right = 0;
		HEX0 = 7'b1000000;
		HEX1 = 7'b1000000;
	end
end

endmodule
