// stdafx.cpp : source file that includes just the standard includes
//	DPAU.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

void InsertSort(STPOSITION a[])
{
	//对数组排序
	int i,j,n=0;
	STPOSITION temp;

	//计算有效个数
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
	//返回数值位数
	if((val/1)<10)
		return 0;	//个
	if((val/10)<10)
		return 1;	//十
	else if((val/100)<10)
		return 2;	//百
	else if((val/1000)<10)
		return 3;	//千
	else if((val/10000)<10)
		return 4;	//万
	else
		return 0;	//无效
}

int NodesOfFreqRange(int start,int end,STDPG *stDpg)
{
	//根据范围,计算以10倍递增计算共有多少步
	//如20,30,...,90,100,200,300,...,900,1000,2000,...,10000,20000
	int mBits=0,mNodes=0,mElems=0;
	int mPrevs=0,mCarrys=0;

	mPrevs=mBits=BitsOfNumber(start);
	while(1)
	{
		mBits=BitsOfNumber(start);

		if(mPrevs!=mBits)
		{
			//存在如从10->100,100->1000,1000->10000等进位
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
	stDpg->mTotal=mNodes;	//总共节点
	stDpg->mCarrys=mCarrys;	//存在进位的点
	stDpg->mElements[mCarrys]=mElems;

	return 0;
}

CString NumOfFreqStr(int freq)
{
	//返回以国际单位词头表示的频率描述
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
	//根据输入的参数计算出在X坐标的位置
	int step=(int)((rect->right-rect->left)/(log10((float)eFreq)-log10((float)sFreq)))-4;
	
	float fLog=(float)(log10((float)freq)-log10((float)sFreq));
	return (int)(rect->left+fLog*step);
}

int CalcFreq(int x,int sFreq,int eFreq,CRect *rect)
{
	//根据输入的坐标值计算对数关系的频率值
	int freq;
	int step=(int)((rect->right-rect->left)/(log10((float)eFreq)-log10((float)sFreq)))-4;
	freq=pow(10,(x+step*log10((float)sFreq)-rect->left)/(step));
	return freq;
}
