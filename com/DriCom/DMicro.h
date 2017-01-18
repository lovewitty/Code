#pragma once
#pragma warning(disable:4505)
#include "../ComAll/XType.h"

#define ARRAY_COUNT(t) (sizeof(t)/sizeof(t[0]))


//���� ��ʽ˵���� ���� 
//%c, %lc ANSI�ַ� char 
//%C, %wc ���ַ� wchar_t 
//%d, %i ʮ�����з������� int 
//%D ʮ����__int64 __int64 
//%L ʮ�����Ƶ�LARGE_INTEGER LARGE_INTEGER 
//%s, %ls NULL��ֹ��ANSI�ַ��� char* 
//%S, %ws NULL��ֹ�Ŀ��ַ��� wchar_t* 
//%Z ANSI_STRING�ַ��� ANSI_STRING 
//%wZ UNICODE_STRING�ַ��� UNICODE_STRING 
//%u ʮ���Ƶ�ULONG ULONG 
//%x Сд�ַ�ʮ�����Ƶ�ULONG ULONG 
//%X ��д�ַ�ʮ�����Ƶ�ULONG ULONG 
//%p ָ��Pointer 32/64λ  
#define P_USTR(U_STR)	\
	if (NULL != (U_STR))	\
		KdPrint(("%s = %wZ\n",#U_STR,(U_STR)));\
	else\
		KdPrint(("%s = NULL\n",#U_STR));

#define P_CSTR(CSTR)  KdPrint(("%s = %s\n",#CSTR,(CSTR)));
#define P_INT(val)  KdPrint(("%s = %d\n",#val,(val)));
#define P_UINT(val)  KdPrint(("%s = %u\n",#val,(val)));
#define P_ADDR(val)  KdPrint(("%s = %x\n",#val,(val)));

// ���� ZwServiceFunction ��ȡ ZwServiceFunction �� SSDT ������Ӧ�ķ����������
#define SYSCALL_INDEX(ServiceFunction) (*(PULONG)((PUCHAR)ServiceFunction + 1))
// ���� ZwServiceFunction ����÷����� SSDT �е������ţ�Ȼ����ͨ��������������ȡ ntServiceFunction�ĵ�ַ
#define SYSCALL_FUNCTION(ServiceFunction) KeServiceDescriptorTable->ntoskrnl.ServiceTableBase[SYSCALL_INDEX(ServiceFunction)]

#define CHECK_RETV(value,ret)	if (0 == (value))\
{ return (ret); };
#define CHECK_RET(value)	CHECK_RETV(value,0)

#define WORD uint16	


