`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/07 16:08:06
// Design Name: 
// Module Name: sqrt
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

//��ʹ��nand�����  not�������Ե�·ͼ���нṹ������ʵ��
//nand (output,input,...)
//not (output,...,input)
module sqrt(input wire[3:0] i,output wire[2:0] o);
    /*�ȶ����������һ��һ��4bitλ�������i�������һ��3bitλ�������o*/
    
    //����wire������verilog����Ĭ�ϵ��������ͣ����Ϊ����������µĽڵ㽫ʡ��wire����
    not (inva,i[0]),(invb,i[1]),(invc,i[2]),(invd,i[3]);
    //������o[0]�����
    nand 
        y(y_out,inva,invb),
        u1(u1_out,i[0],i[1]);
    not
        invu1(invu1_out,u1_out),
        invy(invy_out,y_out);
    nand
        u2(u2_out,invu1_out,invd),
        u3(u3_out,invy_out,invd),
        u4(u4_out,u3_out,invc);
    nand (o[0],u4_out,u2_out);
    //����o[1]�����   
    nand
        u5(u5_out,i[2],invd),
        u6(u6_out,i[2],y_out),
        u7(u7_out,i[3],u6_out),
        u8(u8_out,u7_out,u5_out);
     not  (invu8,u8_out);
     nand  (o[1],invu8,u2_out);
     //����o[2]�����
     nand
        u9(u9_out,i[2],i[3]);
     not  (invu9,u9_out);
     nand
        u10(u10_out,invu9,y_out);
     not  (o[2],u10_out);
endmodule
