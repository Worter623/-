.386				;����ʹ��80386ָ�
.model flat,stdcall	;�ڴ�ģʽΪflatģʽ��ָ�����ù���Ϊstdcall
option casemap:none	;Win32�ĺ����Ǵ�Сд���е�

includelib msvcrt.lib
include msvcrt.inc
scanf	PROTO C:ptr sbyte, :VARARG
printf	PROTO C:ptr sbyte, :VARARG


.data
divu	dword	10

numCharA	byte	150	dup(0)									;���ַ���������룬��СΪ100���ֽ�
numCharB	byte	150	dup(0)									;ʹ��dup�����ʼ��Ϊ0
resultChar	byte	300	dup(0)

numIntA		dword	150	dup(0)
numIntB		dword	150 dup(0)
resultInt	dword	300 dup(0)

lengthA			dword	0
lengthB			dword	0
lengthResult	dword	0

InputMsg	byte	"Please input a multiplier: ",0				;��������ַ���
OutputMsg	byte	"The result of %s * %s is %s",0DH,0AH,0
OutputMsgN	byte	"The result of %s * %s is %s%s",0DH,0AH,0
Fmts		byte	"%s", 0
Fmtd		byte	"%d", 0

NegativeFlag		byte	0												;���ű�־λ��0��1��	
NegativeSymbol		byte	"-"

.code

;-------------------int���鵹��ת�ַ�����-------------------
int2str proc	C
	MOV		ecx,	lengthResult
	MOV		esi,	0 

LOOP_IN:							;ѭ����resultint����������0-9+��0��ת�ַ�0-9��ջ
	MOV		eax,	dword ptr resultInt[4 * esi] 
	ADD		eax,	30H 
	PUSH	eax
	INC		esi
	LOOP	LOOP_IN

	MOV		ecx,	lengthResult
	MOV		esi,	0

LOOP_OUT:							;ѭ����ջ����eax������ֽ�al����resultchar��
	POP		eax
	MOV		byte ptr resultChar[esi], al 
	INC		esi
	LOOP	LOOP_OUT
	ret
int2str endp
;-------------------int���鵹��ת�ַ�����-------------------


;-------------------�ַ����鵹��תint����-------------------
str2int	proc	C	CharNumber:ptr byte,	IntNumber:ptr dword,	len:dword
	MOV		ecx,	len						;�ַ�������Ϊѭ���Ĵ�����ecx����ѭ������
	MOV		esi,	CharNumber				;esi��λ��ָ��

LOOP_IN:									;ѭ��ÿ����ȡ�ַ�������һ���ֽڵ��ַ�0-9ת����0-9����ջ
	MOVZX	eax,	byte ptr[esi]			;��ָ�봦ȡһ���ֽڵ��ַ�����չ��32λ����λ��0
	SUB		eax,	30H						;30H���ַ�0��Ascii��
	PUSH	eax 
	INC		esi
	LOOP	LOOP_IN

	MOV		ecx,	len						;�ַ����飺��λ����ջ int���飺��λ�ȳ�ջ�����ڸ�λ
	MOV		esi,	IntNumber
	
LOOP_OUT:
	POP		eax
	MOV		dword ptr[esi], eax
	ADD		esi, 4							;int˫�֣��ĸ��ֽ�
	LOOP	LOOP_OUT	
	ret
str2int endp
;-------------------�ַ����鵹��תint����-------------------

;--------------------����A�����ַ�����תintA���飬��¼A����------------------------
ConvertStringA	proc	C
	CMP		numCharA,	2DH						;2DH�Ƿ��ŵ�ascii�룬���A�Ƿ��Ǹ���
	JNE		APositive
	XOR		NegativeFlag,1						;A�Ǹ������ı�־�����ַ�������ʱ��������
	invoke	crt_strlen,	offset(numCharA + 1)	;����strlen�������ַ������ȣ��������eax��
	MOV		lengthA,	eax
	invoke	str2int, offset(numCharA + 1),	offset numIntA, lengthA 
	ret
APositive:										;A������
	invoke	crt_strlen, offset numCharA
	MOV		lengthA,	eax
	invoke	str2int, offset numCharA,	offset numIntA, lengthA
	ret
ConvertStringA endp
;--------------------����A�����ַ�����תintA���飬��¼A����------------------------


;--------------------����B�����ַ�����תintB���飬��¼B����------------------------
ConvertStringB	proc	C
	CMP		numCharB,	2DH      
	JNE		BPositive
	XOR		NegativeFlag, 1 
	invoke	crt_strlen, offset (numCharB + 1) 
	MOV		lengthB,	eax
	invoke	str2int, offset (numCharB + 1), offset numIntB, lengthB ;�ַ�����ת����byte����תdword����
	ret
BPositive:
	invoke	crt_strlen, offset numCharB ;���ַ������ȣ��������eax��
	MOV		lengthB,	eax
	invoke	str2int, offset numCharB, offset numIntB, lengthB
	ret
ConvertStringB endp
;--------------------����B�����ַ�����תintB���飬��¼B����------------------------

;---------------------������ˣ�ģ����ʽ-----------------
BigIntMultiply	proc	C
	MOV		ebx, -1
ALOOP: 
	INC		ebx
	CMP		ebx, lengthA
	JNB		ENDLOOPMUL				;���ѭ������ebx���ڵ���A���Ƚ���ѭ��
	XOR		ecx, ecx
BLOOP:
	MOV		eax, dword ptr numIntA[4 * ebx]
	MUL		numIntB[4 * ecx]		;eax�洢��������˵Ľ��
	MOV		esi, ecx
	ADD		esi, ebx				;esi�洢�������������±�֮��
	ADD		resultInt[4 * esi], eax ;������λ��˵Ľ���ӵ�result����Ӧλ��
	INC		ecx
	CMP		ecx, lengthB 
	JNB		ALOOP					;ѭ������ecx���ڵ���B����ʱ������λѭ����������һλѭ��ѭ��
	JMP		BLOOP
ENDLOOPMUL:
	MOV		ecx, lengthA
	ADD		ecx, lengthB
	INC		ecx	
	MOV		[lengthResult], ecx		;����������ΪlengthA + lengthB + 1

	XOR		ebx, ebx				;�����λ
CARRYLOOP:
	CMP		ebx, ecx
	JNB		ENDLOOPCARRY			;ѭ������ebx���ڵ��ڽ����������ѭ��
	MOV		eax, resultInt[4 * ebx]
	XOR		edx, edx
	DIV		divu
	ADD		resultInt[4 * ebx + 4], eax 
	MOV		resultInt[4 * ebx], edx 
	INC		ebx
	JMP		CARRYLOOP
ENDLOOPCARRY:
	MOV		ecx, lengthResult		;��ȥ���������λ��Ŀǰ��ĩλ�������0
MOVEZEROLOOP:
	CMP		dword ptr resultInt[4 * ecx], 0
	JNZ		ENDMUL					;result��ĩλ��Ϊ0
	DEC		ecx						;ÿ��⵽һ��0��ʵ�ʳ��ȼ�һ 
	JMP		MOVEZEROLOOP
ENDMUL:
	INC		ecx						;ʵ�ʳ��ȣ�����±�+1
	MOV		[lengthResult], ecx
	ret
BigIntMultiply endp
;---------------------������ˣ�ģ����ʽ-----------------

;----------------------������------------------------------
main:
	invoke	printf,	offset InputMsg							;�������A��B�������ַ�����
	invoke	scanf,	offset Fmts,	offset numCharA 
	invoke	printf,	offset InputMsg
	invoke	scanf,	offset Fmts,	offset numCharB

	invoke	ConvertStringA									;���鵹���ַ�����תint���飬��¼����
	invoke	ConvertStringB									
	invoke	BigIntMultiply
	
	invoke	int2str											;int����ת�ַ����飬�������
	CMP		NegativeFlag,0									;��ӡ���
	JE		Positive
	invoke	printf,	offset OutputMsgN,	offset numCharA,	offset numCharB,	offset NegativeSymbol,	offset resultChar
	ret
Positive:
	invoke	printf,	offset OutputMsg,	offset numCharA,	offset numCharB,	offset resultChar
	ret
;----------------------������------------------------------

end main
