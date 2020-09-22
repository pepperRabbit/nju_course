module alu(select,a,b,res,carry,overflow,zero,hex0,hex1,hex2,hex3,hex4,hex5,negative);
	input [2:0] select;
	input [3:0] a,b;
	
	output reg [6:0] hex0, hex1, hex2, hex3, hex4, hex5;
	output reg [3:0] res;
	output reg carry, overflow, zero, negative;
	
	integer i;
	reg [3:0] c, neg_res, neg_a, neg_b;
	
	always @ (select or a or b) begin
		case (select)
			0: begin {carry, res} = a + b;
				overflow = (a[3] == b[3] && a[3] != res[3]);
				zero = ~(|res); 
				negative = 0;
				if(res[3]==1) negative=1;end
				
			1: begin c = ~b + 1;
				{carry, res} = a + c;
				overflow = (a[3] == c[3] && a[3] != res[3]);
				zero = ~(|res);
				negative = 0;
				if(res[3]==1) negative=1;end
				
			2: begin carry = 0; overflow = 0; negative = 0;
				res = ~a;
				zero = ~(|res);
				if(res[3]==1) negative=1;end
				
			3: begin carry = 0; overflow = 0; negative = 0;
				res = a & b;
				zero = ~(|res);
				if(res[3]==1) negative=1;end
				
			4: begin carry = 0; overflow = 0; negative = 0;
				res = a | b;
				zero = ~(|res);
				if(res[3]==1) negative=1;end
				
			5: begin carry = 0; overflow = 0;
				res = a ^ b;
				zero = ~(|res);
				negative = 0;
				if(res[3]==1) negative=1;end
				
			6: begin carry = 0; overflow = 0; zero = 0; negative = 0;
				if(a[3]==0 && b[3]==1) res = 1;
				else if(a[3] == 1 && b[3] == 0) res = 0;
				else begin
					if(a>b) res = 1;
					else res = 0;end
				end
				
			7: begin carry = 0; overflow = 0; zero = 0; negative = 0;
				if(a==b) res = 1;
				else res = 0;end
		endcase	
		
		if(res[3] == 1) begin neg_res = ~res + 1;
			case (neg_res % 10)
				0: hex0 = 7'b1000000;
				1: hex0 = 7'b1111001;
				2: hex0 = 7'b0100100;
				3: hex0 = 7'b0110000;
				4: hex0 = 7'b0011001;
				5: hex0 = 7'b0010010;
				6: hex0 = 7'b0000010;
				7: hex0 = 7'b1111000;
				8: hex0 = 7'b0000000;
				9: hex0 = 7'b0000100;
				default: hex0 = 7'b1111111;
			endcase
			case ((neg_res / 10) % 10)
				0: hex1 = 7'b1000000;
				1: hex1 = 7'b1111001;
				2: hex1 = 7'b0100100;
				3: hex1 = 7'b0110000;
				4: hex1 = 7'b0011001;
				5: hex1 = 7'b0010010;
				6: hex1 = 7'b0000010;
				7: hex1 = 7'b1111000;
				8: hex1 = 7'b0000000;
				9: hex1 = 7'b0000100;
				default: hex1 = 7'b1111111;
			endcase
		end
		else begin
			case (res % 10)
				0: hex0 = 7'b1000000;
				1: hex0 = 7'b1111001;
				2: hex0 = 7'b0100100;
				3: hex0 = 7'b0110000;
				4: hex0 = 7'b0011001;
				5: hex0 = 7'b0010010;
				6: hex0 = 7'b0000010;
				7: hex0 = 7'b1111000;
				8: hex0 = 7'b0000000;
				9: hex0 = 7'b0000100;
				default: hex0 = 7'b1111111;
			endcase
			case ((res / 10) % 10)
				0: hex1 = 7'b1000000;
				1: hex1 = 7'b1111001;
				2: hex1 = 7'b0100100;
				3: hex1 = 7'b0110000;
				4: hex1 = 7'b0011001;
				5: hex1 = 7'b0010010;
				6: hex1 = 7'b0000010;
				7: hex1 = 7'b1111000;
				8: hex1 = 7'b0000000;
				9: hex1 = 7'b0000100;
				default: hex1 = 7'b1111111;
			endcase
		end
				
		if(a[3] == 1) begin neg_a = ~a + 1;
			case (neg_a % 10)
				0: hex4 = 7'b1000000;
				1: hex4 = 7'b1111001;
				2: hex4 = 7'b0100100;
				3: hex4 = 7'b0110000;
				4: hex4 = 7'b0011001;
				5: hex4 = 7'b0010010;
				6: hex4 = 7'b0000010;
				7: hex4 = 7'b1111000;
				8: hex4 = 7'b0000000;
				9: hex4 = 7'b0000100;
				default: hex4 = 7'b1111111;
			endcase
			case ((neg_a / 10) % 10)
				0: hex5 = 7'b1000000;
				1: hex5 = 7'b1111001;
				2: hex5 = 7'b0100100;
				3: hex5 = 7'b0110000;
				4: hex5 = 7'b0011001;
				5: hex5 = 7'b0010010;
				6: hex5 = 7'b0000010;
				7: hex5 = 7'b1111000;
				8: hex5 = 7'b0000000;
				9: hex5 = 7'b0000100;
				default: hex5 = 7'b1111111;
			endcase
		end
		else begin
			case (a % 10)
				0: hex4 = 7'b1000000;
				1: hex4 = 7'b1111001;
				2: hex4 = 7'b0100100;
				3: hex4 = 7'b0110000;
				4: hex4 = 7'b0011001;
				5: hex4 = 7'b0010010;
				6: hex4 = 7'b0000010;
				7: hex4 = 7'b1111000;
				8: hex4 = 7'b0000000;
				9: hex4 = 7'b0000100;
				default: hex4 = 7'b1111111;
			endcase
			case ((a / 10) % 10)
				0: hex5 = 7'b1000000;
				1: hex5 = 7'b1111001;
				2: hex5 = 7'b0100100;
				3: hex5 = 7'b0110000;
				4: hex5 = 7'b0011001;
				5: hex5 = 7'b0010010;
				6: hex5 = 7'b0000010;
				7: hex5 = 7'b1111000;
				8: hex5 = 7'b0000000;
				9: hex5 = 7'b0000100;
				default: hex5 = 7'b1111111;
			endcase
		end
		
		if(b[3] == 1) begin neg_b = ~b + 1;
			case (neg_b % 10)
				0: hex2 = 7'b1000000;
				1: hex2 = 7'b1111001;
				2: hex2 = 7'b0100100;
				3: hex2 = 7'b0110000;
				4: hex2 = 7'b0011001;
				5: hex2 = 7'b0010010;
				6: hex2 = 7'b0000010;
				7: hex2 = 7'b1111000;
				8: hex2 = 7'b0000000;
				9: hex2 = 7'b0000100;
				default: hex2 = 7'b1111111;
			endcase
			case ((neg_b / 10) % 10)
				0: hex3 = 7'b1000000;
				1: hex3 = 7'b1111001;
				2: hex3 = 7'b0100100;
				3: hex3 = 7'b0110000;
				4: hex3 = 7'b0011001;
				5: hex3 = 7'b0010010;
				6: hex3 = 7'b0000010;
				7: hex3 = 7'b1111000;
				8: hex3 = 7'b0000000;
				9: hex3 = 7'b0000100;
				default: hex3 = 7'b1111111;
			endcase
		end
		else begin
			case (b % 10)
				0: hex2 = 7'b1000000;
				1: hex2 = 7'b1111001;
				2: hex2 = 7'b0100100;
				3: hex2 = 7'b0110000;
				4: hex2 = 7'b0011001;
				5: hex2 = 7'b0010010;
				6: hex2 = 7'b0000010;
				7: hex2 = 7'b1111000;
				8: hex2 = 7'b0000000;
				9: hex2 = 7'b0000100;
				default: hex2 = 7'b1111111;
			endcase
			case ((b / 10) % 10)
				0: hex3 = 7'b1000000;
				1: hex3 = 7'b1111001;
				2: hex3 = 7'b0100100;
				3: hex3 = 7'b0110000;
				4: hex3 = 7'b0011001;
				5: hex3 = 7'b0010010;
				6: hex3 = 7'b0000010;
				7: hex3 = 7'b1111000;
				8: hex3 = 7'b0000000;
				9: hex3 = 7'b0000100;
				default: hex3 = 7'b1111111;
			endcase
		end
	end
endmodule
