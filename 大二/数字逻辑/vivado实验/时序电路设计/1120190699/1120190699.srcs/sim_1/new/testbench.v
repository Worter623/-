`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/07 23:13:33
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
    /*���ͱ���Z�洢����module���������
    �Ĵ�������clk��X��resetΪ����module�ṩ����*/
    wire Z;
    reg clk,X,reset;
    
    /*���屻������Ϊһ��11 bitλ������
    ����Ĵ������ɵ�λ����λ�洢
    ����һ��integer��forѭ�������ʹ��
    ��ʼ��integerΪ0*/
    reg [0:10] test_sequence=11'b100_0010_0010;
    integer i=0;

    SeqDetect test(clk,reset,X,Z);
    
    /*�ṩʱ�������źţ�ÿ��50����ı�һ��*/
    always begin
        clk=1'b1;
        #50;
        clk=1'b0;
        #50;
    end
    
    /*���濪ʼʱ�����̼���reset��
    ʹ״̬����ʼ��������״̬S
    resetʧЧ����forѭ�����ÿ��100����
    ���ش洢��test_sequence�е�X����ֵ
    ����ֵ���ص�ʱ������ʱ�ӵ�������
    �����stop����������*/
    initial begin
        reset=1'b1;
        X=1'b0;
        #20;
        reset=1'b0;
        for(i=0;i<11;i=i+1)
        begin
            X=test_sequence[i];
            #100;
        end
        $stop;
    end
   
endmodule
