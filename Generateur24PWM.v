module Generateur24PWM(CLOCK_50,SW,KEY,DRAM_ADDR,DRAM_BA,DRAM_CAS_N,DRAM_CKE,GPIO,DRAM_CS_N,DRAM_DQ,LEDR, LEDG,DRAM_DQM,DRAM_RAS_N,DRAM_WE_N,DRAM_CLK,LCD_RW,LCD_RS,LCD_EN,LCD_DATA);

input CLOCK_50;
input[3:0] KEY;
input [1:0] SW;

output[12:0] DRAM_ADDR;
output[1:0] DRAM_BA;
output DRAM_CAS_N;
output DRAM_CKE;
output DRAM_CS_N;
output[3:0] DRAM_DQM;
output  DRAM_RAS_N;
output DRAM_WE_N;
output DRAM_CLK;
output [35:0] GPIO;
output [17:0] LEDR;
output [7:0] LEDG;

inout[31:0] DRAM_DQ;
inout [7:0] LCD_DATA;
inout LCD_RW;
inout LCD_RS;
inout LCD_EN;

    SDRAM_HAL_Base_sys u0 (
        .buttons_commande_export (KEY[3:1]), // buttons_commande.export
        .clk_clk                 (CLOCK_50),                 //              clk.clk
        .lcd_external_RS         (LCD_RS),         //     lcd_external.RS
        .lcd_external_RW         (LCD_RW),         //                 .RW
        .lcd_external_data       (LCD_DATA[7:0]),       //                 .data
        .lcd_external_E          (LCD_EN),          //                 .E
        .leds_export             ({LEDR[15:0] , LEDG[7:0]}),
		  .pwm_export              (GPIO[23:0]),              //              pwm.export
        .reset_reset_n           (KEY[0]),           //            reset.reset_n
        .sdram_clk_clk           (DRAM_CLK),           //        sdram_clk.clk
        .sdram_ctrl_wire_addr    (DRAM_ADDR),    //  sdram_ctrl_wire.addr
        .sdram_ctrl_wire_ba      (DRAM_BA),      //                 .ba
        .sdram_ctrl_wire_cas_n   (DRAM_CAS_N),   //                 .cas_n
        .sdram_ctrl_wire_cke     (DRAM_CKE),     //                 .cke
        .sdram_ctrl_wire_cs_n    (DRAM_CS_N),    //                 .cs_n
        .sdram_ctrl_wire_dq      (DRAM_DQ),      //                 .dq
        .sdram_ctrl_wire_dqm     (DRAM_DQM),     //                 .dqm
        .sdram_ctrl_wire_ras_n   (DRAM_RAS_N),   //                 .ras_n
        .sdram_ctrl_wire_we_n    (DRAM_WE_N),    //                 .we_n
        .switch_reglage_export   (SW[0]),    //   switch_reglage.export
		  .clk_1khz_export         (GPIO[35])    
    );
	 
endmodule 

