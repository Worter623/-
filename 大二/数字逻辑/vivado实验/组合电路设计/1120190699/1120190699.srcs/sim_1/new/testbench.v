`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/07 17:01:52
// Design Name: 
// Module Name: testbench
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


module testbench();
    reg[3:0] i;
    wire[2:0] o;
    //���濪ʼʱ���ȶ�������Ϊ0010�����ӦΪ001
    initial begin
        i=4'b0010;
        //10�����Ժ󣬶�������Ϊ0101�����ӦΪ010
        #10;
        i=4'b0101;
        //�ֹ���10���룬��������Ϊ1000�����ӦΪ011
        #10;
        i=4'b1000;
        //�ֹ���10���룬��������Ϊ1101�����ӦΪ100
        #10;
        i=4'b1101;
    end
    //�Ĵ���iΪ���룬wire������¼���
    sqrt  test(i,o);
    
endmodule
