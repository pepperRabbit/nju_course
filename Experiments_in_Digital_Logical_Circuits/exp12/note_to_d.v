module note_to_d(
	input CLOCK_50,
	input mode,
	input [3:0] play_note,
	input [3:0] record_note,
	input [13:0] play_seven,
	input [13:0] record_seven,
	output reg [15:0] wavedata,
	output reg [6:0] seven_high,
	output reg [6:0] seven_low,
	output reg K
	);
	
	reg [3:0] wave;
	
	initial
		wave <= 4'hF;
	
	always @ (CLOCK_50)
	begin	
		if(mode == 1'b0)
		begin
			wave <= play_note;
			seven_high <= play_seven[13:7];
			seven_low <= play_seven[6:0];
		end
		else
		begin
			wave <= record_note;
			seven_high <= record_seven[13:7];
			seven_low <= record_seven[6:0];
		end
		
		case (wave)
			4'h0:wavedata <= 0 * 65536 / 48000;
			4'h1:wavedata <= 262 * 65536 / 48000;
			4'h2:wavedata <= 294 * 65536 / 48000;
			4'h3:wavedata <= 330 * 65536 / 48000;
			4'h4:wavedata <= 349 * 65536 / 48000;
			4'h5:wavedata <= 392 * 65536 / 48000;
			4'h6:wavedata <= 440 * 65536 / 48000;
			4'h7:wavedata <= 494 * 65536 / 48000;
			4'h8:wavedata <= 523 * 65536 / 48000;
			4'h9:wavedata <= 587 * 65536 / 48000;
			4'hA:wavedata <= 659 * 65536 / 48000;
			4'hB:wavedata <= 698 * 65536 / 48000;
			4'hC:wavedata <= 783 * 65536 / 48000;
			4'hD:wavedata <= 880 * 65536 / 48000;
			4'hE:wavedata <= 987 * 65536 / 48000;
			4'hF:wavedata <= 740 * 65536 / 48000;
			default:wavedata <= 0 * 65536 / 48000;
		endcase
		
		K <= 1'b1;
	end
	
endmodule
