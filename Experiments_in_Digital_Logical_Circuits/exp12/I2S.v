module I2S_Audio(AUD_XCK,
                 reset_n,
                 AUD_BCK,
					  AUD_DATA,
					  AUD_LRCK,
					  audiodata);
input AUD_XCK;
input reset_n;
output reg AUD_BCK;
output AUD_DATA;
output reg AUD_LRCK;
input [15:0] audiodata;


reg [7:0] bck_counter;
reg [7:0] lr_counter;
wire [7:0] bitaddr;

//generate BCK 1.536MHz
always @ (posedge AUD_XCK or negedge reset_n)
begin
       if(!reset_n)
		 begin
		    bck_counter <= 8'd0;
			 AUD_BCK     <= 1'b0;
		 end
		 else
		 begin
		    
			 if(bck_counter >= 8'd5) //div XCK by 12
			 begin
			     bck_counter <= 8'd0;
				  AUD_BCK <= ~AUD_BCK;
			 end
			 else
			   bck_counter <= bck_counter + 8'd1;
		 end
		 
end

//generate LRCK, 48kHz, at negedge of BCK

always @ (negedge AUD_BCK or negedge reset_n)
begin
       if(!reset_n)
		 begin
		    lr_counter <= 8'd0;
			 AUD_LRCK     <= 1'b0;
		 end
		 else
		 begin
		    
			 if(lr_counter >= 8'd15) //div BCK by 32
			 begin
			     lr_counter <= 8'd0;
				  AUD_LRCK <= ~AUD_LRCK;
			 end
			 else
			   lr_counter <= lr_counter + 8'd1;
		end
		 
end

//send data, input data avaible at posedge of lrclk, prepared at the posedge of bck

assign  bitaddr  = 8'd15- lr_counter;
assign  AUD_DATA = audiodata[bitaddr[3:0]];

		

endmodule 

module I2C_Audio_Config ( clk_i2c,
                          reset_n,
								  I2C_SCLK,
								  I2C_SDAT,
								  testbit);
   parameter  total_cmd = 9;

	input clk_i2c;  //10k I2C clock
   input reset_n;
   
   output I2C_SCLK;
	output [2:0] testbit;
   inout  I2C_SDAT;

	reg [23:0] mi2c_data;
	reg  mi2c_go;
	wire mi2c_end;
	reg  [1:0] mi2c_state; //state 0: stop, state 1: sendnext;
	                       //state 2: wait for finish, state 3:move index
	wire [2:0] mi2c_ack;
	wire [7:0] audio_addr;
	
	reg [3:0] cmd_count;
	reg [6:0] audio_reg [15:0]; //register to write
	reg [8:0] audio_cmd [15:0]; //register content

	
initial
begin
   audio_reg[0]= 7'h0f; audio_cmd[0]=9'h0;  //reset
	audio_reg[1]= 7'h06; audio_cmd[1]=9'h0;  //Disable Power Down
	audio_reg[2]= 7'h08; audio_cmd[2]=9'h2;  //Sampling Control
	audio_reg[3]= 7'h02; audio_cmd[3]=9'h79; //Left Volume
	audio_reg[4]= 7'h03; audio_cmd[4]=9'h79; //Right Volume
	audio_reg[5]= 7'h07; audio_cmd[5]=9'h1;  //I2S format
	audio_reg[6]= 7'h09; audio_cmd[6]=9'h1;  //Active
	audio_reg[7]= 7'h04; audio_cmd[7]=9'h16; //Analog path
	audio_reg[8]= 7'h05; audio_cmd[8]=9'h06;  //Digital path

end


assign audio_addr={7'b0011010,1'b0}; //WM8731 addr, always write
assign testbit = cmd_count[2:0];
	

I2C_Controller 	u0	(	.CLOCK(clk_i2c),		//	Controller Work Clock
						.I2C_SCLK(I2C_SCLK),		//	I2C CLOCK
 	 	 	 	 	 	.I2C_SDAT(I2C_SDAT),		//	I2C DATA
						.I2C_DATA(mi2c_data),		//	DATA:[SLAVE_ADDR,SUB_ADDR,DATA]
						.GO(mi2c_go),      			//	GO transfor
						.END(mi2c_end),				//	END transfor 
						.ACK(mi2c_ack),				//	ACK
						.RESET_N(reset_n)	);	
						
always @ (posedge clk_i2c or negedge reset_n)
begin
     if(!reset_n)
	  begin
	     cmd_count  <= 4'b0;
		  mi2c_state <= 4'b0;
	     mi2c_go    <= 1'b0;
	  end
	  else
	  begin
	     case(mi2c_state)
		  2'd0: begin  //stop
		            if(cmd_count ==4'b0)
						   mi2c_state <= 2'd1;
		        end
		  2'd1: begin
		            mi2c_data <= {audio_addr, audio_reg[cmd_count], audio_cmd[cmd_count]};
						mi2c_go   <= 1'b1;
						mi2c_state<= 2'd2;
		        end
		  2'd2: begin
		             if(mi2c_end)
						 begin
						        mi2c_state <= 2'd3;
								  mi2c_go    <= 1'b0;
						 end
		        end
		  2'd3: begin
		            cmd_count <= cmd_count + 4'd1;
						if(cmd_count + 4'd1 < total_cmd)
						   mi2c_state <= 2'd1;  //start next
					   else
						   mi2c_state <= 2'd0;  //last cmd
		        end
		  endcase
	  end
	  
end
								  
								  
endmodule

module I2C_Controller (
	CLOCK,
	I2C_SCLK,//I2C CLOCK
 	I2C_SDAT,//I2C DATA
	I2C_DATA,//DATA:[SLAVE_ADDR,SUB_ADDR,DATA]
	GO,      //GO transfor
	END,     //END transfor 
	W_R,     //W_R
	ACK,      //ACK
	RESET_N,
	//TEST
	//SD_COUNTER,
	//SDO
);
	input  CLOCK;
	input  [23:0]I2C_DATA;	
	input  GO;
	input  RESET_N;	
	input  W_R;
 	inout  I2C_SDAT;	
	output I2C_SCLK;
	output END;	
	output reg [2:0] ACK;

//TEST
//	output [5:0] SD_COUNTER;
//	output SDO;


reg SDO;
reg SCLK;
reg END;
reg [23:0]SD;
reg [5:0]SD_COUNTER;

wire I2C_SCLK=SCLK | ( ((SD_COUNTER >= 4) & (SD_COUNTER <=30))? ~CLOCK :0 );
wire I2C_SDAT=SDO?1'bz:0 ;

reg ACK1,ACK2,ACK3;

//--I2C COUNTER
always @(negedge RESET_N or posedge CLOCK ) begin
if (!RESET_N) SD_COUNTER=6'b111111;
else begin
if (GO==0) 
	SD_COUNTER=0;
	else 
	if (SD_COUNTER < 6'b111111) SD_COUNTER=SD_COUNTER+1;	
end
end
//----

always @(negedge RESET_N or  posedge CLOCK ) begin
if (!RESET_N) begin SCLK=1;SDO=1; ACK1=0;ACK2=0;ACK3=0; END=1; end
else
case (SD_COUNTER)
	6'd0  : begin ACK1=0 ;ACK2=0 ;ACK3=0 ; END=0; SDO=1; SCLK=1; ACK=3'b0; end
	//start
	6'd1  : begin SD=I2C_DATA;SDO=0;end
	6'd2  : SCLK=0;
	//SLAVE ADDR
	6'd3  : SDO=SD[23];
	6'd4  : SDO=SD[22];
	6'd5  : SDO=SD[21];
	6'd6  : SDO=SD[20];
	6'd7  : SDO=SD[19];
	6'd8  : SDO=SD[18];
	6'd9  : SDO=SD[17];
	6'd10 : SDO=SD[16];	
	6'd11 : SDO=1'b1;//ACK

	//SUB ADDR
	6'd12  : begin SDO=SD[15]; ACK1=I2C_SDAT; end
	6'd13  : SDO=SD[14];
	6'd14  : SDO=SD[13];
	6'd15  : SDO=SD[12];
	6'd16  : SDO=SD[11];
	6'd17  : SDO=SD[10];
	6'd18  : SDO=SD[9];
	6'd19  : SDO=SD[8];
	6'd20  : SDO=1'b1;//ACK

	//DATA
	6'd21  : begin SDO=SD[7]; ACK2=I2C_SDAT; end
	6'd22  : SDO=SD[6];
	6'd23  : SDO=SD[5];
	6'd24  : SDO=SD[4];
	6'd25  : SDO=SD[3];
	6'd26  : SDO=SD[2];
	6'd27  : SDO=SD[1];
	6'd28  : SDO=SD[0];
	6'd29  : SDO=1'b1;//ACK

	
	//stop
    6'd30 : begin SDO=1'b0;	SCLK=1'b0; ACK3=I2C_SDAT; end	
    6'd31 : begin SCLK=1'b1; ACK={ACK1,ACK2,ACK3}; end
    6'd32 : begin SDO=1'b1; END=1; end 

endcase
end

endmodule
