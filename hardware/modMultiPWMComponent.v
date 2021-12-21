module modMultiPWMComponent(clk, clkInPWM, reset_n, chipselect, write_n, writedata, address,PWM,clkOutPWM);

parameter NB_PWM = 24; // Nombre de canaux PWM
parameter RESOLUTION = 10; // Nombre de bits des registres de comptage.

input[31:0] writedata;
input clk,reset_n,chipselect,write_n,clkInPWM;
input [1:0] address;

output clkOutPWM;
output[23:0] PWM;

reg [9:0] Ton;
reg [23:0] oe, nLatch;

//Interface avec bus Avalon

assign clkOutPWM = clkInPWM;

always @(posedge(clk))
begin
	if (reset_n == 0)
	begin
		Ton = 0;
		nLatch = {10{1'b1}};
		oe = 0;
	end
	else
	begin
		if((chipselect == 1) && (write_n == 0))
		begin
			case(address)
				2'b00 :
					begin
						Ton <= writedata[9:0];
					end
				2'b01 :
					begin
						nLatch <= writedata[23:0];
					end
				default :
					begin
						oe <= writedata[23:0];
					end
			endcase
		end
	end
end

modMultiPWM #(NB_PWM,RESOLUTION) MonPWM(clkInPWM,PWM,nLatch,Ton,oe);

endmodule 

//ClkIn, PWMout, nLatch, Ton, oe