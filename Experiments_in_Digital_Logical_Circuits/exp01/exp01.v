module exp01(x0,x1,x2,x3,y,f);
	input [1:0] x0,x1,x2,x3,y;
	output reg [1:0] f;
	
	always @ (*)
		case (y)
			0: f = x0;
			1: f = x1;
			2: f = x2;
			3: f = x3;
			default: f = 2'b0;
			endcase
endmodule
