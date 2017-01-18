#pragma once
#include<windows.h>
#include "../ComAll/XSTL.hpp"

static Buf ScreenSnap(HBITMAP hBitmap, HDC dc)
{
	Buf bf;
	BITMAP bmInfo;
	DWORD bmDataSize;
	char *bmData;//λͼ����
	GetObject(hBitmap,sizeof(BITMAP),&bmInfo);//����λͼ�������ȡλͼ��Ϣ
	bmDataSize=bmInfo.bmWidthBytes*bmInfo.bmHeight;//����λͼ���ݴ�С
	//bmData=new char[bmDataSize];//��������
	bmData = (char*)malloc(bmDataSize);
	BITMAPFILEHEADER bfh;//λͼ�ļ�ͷ
	bfh.bfType=0x4d42;
	bfh.bfSize=bmDataSize+54;
	bfh.bfReserved1=0;
	bfh.bfReserved2=0;
	bfh.bfOffBits=54;
	BITMAPINFOHEADER bih;//λͼ��Ϣͷ
	bih.biSize=40;
	bih.biWidth=bmInfo.bmWidth;
	bih.biHeight=bmInfo.bmHeight;
	bih.biPlanes=1;
	bih.biBitCount=24;
	bih.biCompression=BI_RGB;
	bih.biSizeImage=bmDataSize;
	bih.biXPelsPerMeter=0;
	bih.biYPelsPerMeter=0;
	bih.biClrUsed=0;
	bih.biClrImportant=0;
	::GetDIBits(dc,hBitmap,0,bmInfo.bmHeight,bmData,(BITMAPINFO *)&bih,DIB_RGB_COLORS);//��ȡλͼ���ݲ���
	bf.AddBuf(&bfh, sizeof(BITMAPFILEHEADER));
	bf.AddBuf(&bih, sizeof(BITMAPINFOHEADER));
	bf.AddBuf(bmData,bmDataSize);
	free(bmData);
	return bf;
}
static Buf _Jietu()
{
	Buf bf;
	HWND DeskWnd=::GetDesktopWindow();//��ȡ���洰�ھ��
	RECT DeskRC;
	::GetClientRect(DeskWnd,&DeskRC);//��ȡ���ڴ�С
	HDC DeskDC=GetDC(DeskWnd);//��ȡ����DC
	HBITMAP DeskBmp=::CreateCompatibleBitmap(DeskDC,DeskRC.right,DeskRC.bottom);//����λͼ
	HDC memDC=::CreateCompatibleDC(DeskDC);//����DC
	SelectObject(memDC,DeskBmp);//�Ѽ���λͼѡ�����DC��
	BitBlt(memDC,0,0,DeskRC.right,DeskRC.bottom,DeskDC,0,0,SRCCOPY);//����DC
	bf = ScreenSnap(DeskBmp, DeskDC);
	ReleaseDC(DeskWnd,DeskDC);
	DeleteObject(DeskBmp);
	ReleaseDC(DeskWnd,memDC);
	return bf;
}