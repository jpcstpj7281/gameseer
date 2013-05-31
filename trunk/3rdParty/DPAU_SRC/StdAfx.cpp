// stdafx.cpp : source file that includes just the standard includes
//	DPAU.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

void InsertSort(STPOSITION a[])
{
	//����������
	int i,j,n=0;
	STPOSITION temp;

	//������Ч����
	while(a[n].mPosition!=0)
		n++;

	for(i=0;i<n-1;i++)
	{
		temp=a[i+1];
		j=i;
		while(j>-1&&temp.mPosition<a[j].mPosition)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=temp;
	}
}

int BitsOfNumber(int val)
{
	//������ֵλ��
	if((val/1)<10)
		return 0;	//��
	if((val/10)<10)
		return 1;	//ʮ
	else if((val/100)<10)
		return 2;	//��
	else if((val/1000)<10)
		return 3;	//ǧ
	else if((val/10000)<10)
		return 4;	//��
	else
		return 0;	//��Ч
}

int NodesOfFreqRange(int start,int end,STDPG *stDpg)
{
	//���ݷ�Χ,������10���������㹲�ж��ٲ�
	//��20,30,...,90,100,200,300,...,900,1000,2000,...,10000,20000
	int mBits=0,mNodes=0,mElems=0;
	int mPrevs=0,mCarrys=0;

	mPrevs=mBits=BitsOfNumber(start);
	while(1)
	{
		mBits=BitsOfNumber(start);

		if(mPrevs!=mBits)
		{
			//�������10->100,100->1000,1000->10000�Ƚ�λ
			stDpg->mElements[mCarrys]=mElems;
			stDpg->mCarryVal[mCarrys]=start;
			mElems=0;
			mCarrys++;
		}
		if(start>=end)
			break;

		mPrevs=mBits;
		start=(int)(start+pow((double)10,mBits));
		mNodes++;
		mElems++;
	}
	stDpg->mTotal=mNodes;	//�ܹ��ڵ�
	stDpg->mCarrys=mCarrys;	//���ڽ�λ�ĵ�
	stDpg->mElements[mCarrys]=mElems;

	return 0;
}

CString NumOfFreqStr(int freq)
{
	//�����Թ��ʵ�λ��ͷ��ʾ��Ƶ������
	CString str;

	str.Format(_T("%dHz"),0);

	if(freq<1000)
		str.Format(_T("%dHz"),freq);
	if(freq>=1000)
		str.Format(_T("%dKHz"),freq/1000);
	return str;
}

int CalcXPos(int sFreq,int eFreq,int freq,CRect *rect)
{
	//��������Ĳ����������X�����λ��
	int step=(int)((rect->right-rect->left)/(log10((float)eFreq)-log10((float)sFreq)))-4;
	
	float fLog=(float)(log10((float)freq)-log10((float)sFreq));
	return (int)(rect->left+fLog*step);
}

int CalcFreq(int x,int sFreq,int eFreq,CRect *rect)
{
	//�������������ֵ���������ϵ��Ƶ��ֵ
	int freq;
	int step=(int)((rect->right-rect->left)/(log10((float)eFreq)-log10((float)sFreq)))-4;
	freq=pow(10,(x+step*log10((float)sFreq)-rect->left)/(step));
	return freq;
}
