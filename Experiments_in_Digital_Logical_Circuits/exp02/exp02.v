module exp02(i, en, res, flag, hex);
	input [7:0] i;
	input en;
	output reg [2:0] res;
	output reg flag;
	output reg [6:0] hex;
	integer j;
	
	always @ (*)
	begin
		if(i == 0) flag = 0;
		else flag = 1;
		
		res = 0;
		if(en) //begin
			//for(j = 0; j <= 7; j = j + 1)
				//if(i[j] == 1) res = j;
		//end
			casex (i)
				8'b1???????: res = 3'b111;
				8'b01??????: res = 3'b110;
				8'b001?????: res = 3'b101;
				8'b0001????: res = 3'b100;
				8'b00001???: res = 3'b011;
				8'b000001??: res = 3'b010;
				8'b0000001?: res = 3'b001;
				default: res = 3'b000;
			endcase
		
		case (res)
		0: hex = 7'b1000000;
		1: hex = 7'b1111001;
		2: hex = 7'b0100100;
		3: hex = 7'b0110000;
		4: hex = 7'b0011001;
		5: hex = 7'b0010010;
		6: hex = 7'b0000010;
		7: hex = 7'b1111000;
		default: hex = 7'b1111111;
		endcase
	end
endmodule
		
		
		
