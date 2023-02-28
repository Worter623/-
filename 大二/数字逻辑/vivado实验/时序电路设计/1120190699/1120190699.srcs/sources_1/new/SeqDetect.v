`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/07 22:22:49
// Design Name: 
// Module Name: SeqDetect
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

/*ͨ���������������ġ����еĽ�����ʵ��״̬ͼ
���ʹ���¼��������*/
module SeqDetect(clk,reset,X,Z);
    /*�������������������Ĭ�����붼��wire�ͱ�����
    ʵ��������Ҳֻ����wire�ͱ���
    �������Ϊ��Ҫ��always����ڲ�����ֵ��
    ����always�ڲ�����ֵ��ֻ����reg���ͱ�����
    ����ֻ�ܽ�������Ϊreg�ͱ���*/
    input clk,X,reset;
    output reg Z;
    /*��3bitλ�ļĴ����������洢��ǰ״̬����һ״̬*/
    reg [2:0] state,next_state;
    //�ò������ΪS��A��B��C��D���״̬��״̬���룬���Ƕ���3bitλ��
    parameter S=3'b000,A=3'b001,B=3'b010,C=3'b011,D=3'b100;
    
    /*��һ�����̣��������ڴ洢����ʶ����״̬��״̬�Ĵ���
    ��Ϊ��ʱ���߼�����if-else��䡢����ִ�еķ�������ֵ���
    ÿ��clk��0��Ϊ1�����ߵ�resetΪ1���ý��̽��ᱻִ��
    �����ʱresetΪ1����δ��ʼ����������У��ȳ�ʼ����ǰ״̬Ϊ״̬S
    ���resetΪ0����������Ѿ���ʼ����ʱ�ӵ�����������
    ����һ״̬��ֵ������ǰ״̬*/
    always @(posedge clk or posedge reset)
    begin
        if (reset)
            state<=S;
        else
            state<=next_state;
    end
    
    /*�ڶ������̣�������һ״̬����������״̬ת������
    ���ڸý���������߼�����˳��ִ�е�������ֵ��䣬
    ���ۺ�ʱֻҪ���뷢���仯����״̬�����仯�����̾ͻᱻִ��
    ��Ϊ������Ҫ�õ���·�жϣ�������case��������if-else
    ����ʵ�ֵ��ǻ��ڵ�ǰ״̬������X�ж���һ״̬
    ��ʵ����ʵ����״̬��ͼ�����ÿһ����*/    
    always @(X or state)
    begin
        case(state)
            S: next_state = X ? S : A;
            A: next_state = X ? S : B;
            B: next_state = X ? S : C;
            C: next_state = X ? S : D;
            D: next_state = X ? S : D;
        endcase
    end
    
    /*���������̣�������������������Z��ֵ
    ���ڸý���������߼�����˳��ִ�е�������ֵ���
    ִ�н��̵������͵ڶ���������ͬ
    ����·�У������Ϊ��TCI
    ��״̬S��A��B��C�У��������Ĭ��ֵ0
    ��״̬D�У��������X=0����ô���1*/  
    always @(X or state)
    begin
        case(state)
            S: Z=1'b0;
            A: Z=1'b0;
            B: Z=1'b0;
            C: Z=1'b0;
            D: Z=X ? 1'b0 : 1'b1;
        endcase
    end
    
endmodule
