`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2025/03/29 20:03:39
// Design Name: 
// Module Name: switch_led_enable
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module switch_led_enable(
    input  wire [1:0] i_sw,       // 2-bit Switch ��J
    input  wire [7:0] i_led_in,   // �Ӧ� PS (AXI GPIO) �� LED ���
    output wire [7:0] o_led_out   // ��X�� LED
    );
    
   // Switch ���� LED ��ܤϦV��X  
    assign o_led_out = (i_sw[0] == 1'b1) ? ~i_led_in : i_led_in;

endmodule