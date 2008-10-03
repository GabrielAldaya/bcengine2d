#pragma once
//-----------------------------------------------------------------------------------------
#include "functions.h"
using namespace std;
//-----------------------------------------------------------------------------------------
class  Attribute 
{
//-----------------------------------------------------------------------------------------
public:
	Attribute();
	Attribute(int iDa�o, int iCa, int iResAcd,
				int iResFir, int iResFro ,int iResSon,int iResElec,int iStr, 
				int iDex,  int iCon, int iInt,int iWis, int iCha, 
				int iReDa, int iHps, int iMana, int iSlotOcu, int iSref,
				int iSStr, int iSwill);
	~Attribute();
//-----------------------------------------------------------------------------------------
	void setDa�o(int iDa�o);
	int  getDa�o();
	void setCa(int iCa);
	int  getCa();
	void setResAcd(int iResAcd);
	int  getResAcd();
	void setResFir(int iResFir);
	int  getResFir();
	void setResFro(int iResFro);
	int  getResFro();
	void setResSon(int iResSon);
	int  getResSon();
	void setResElec(int iResElec);
	int  getResElec();
	void setStr(int iStr);
	int  getStr();
	void setDex(int iDex);
	int  getDex();
	void setCon(int iCon);
	int  getCon();
	void setInt(int iInt);
	int  getInt();
	void setWis(int iWis);
	int  getWis();
	void setCha(int iCha);
	int  getCha();
	void setReDa(int iReDa);
	int  getReDa();
    void setHps(int iHps);
	int  getHps();
    void setMana(int iMana);
	int  getMana();
	void setSlotOcu(int iSlotOcu);
	int  getSlotOcu();
	void setSref(int iSref);
	int  getSref();
	void setSstr(int iSStr);
	int  getSstr();
	void setSwill(int iSwill);
	int  getSwill();
//-----------------------------------------------------------------------------------------
private:
	int m_iDa�o;
	int m_iCa;
	int m_iResAcd;
	int m_iResFir;
	int m_iResFro;
	int m_iResSon;
	int m_iResElec;
	int m_iStr;
	int m_iDex;
	int m_iCon;
	int m_iInt;
	int m_iWis;
	int m_iCha;
	int m_iReDa;
	int m_iHps;
	int m_iMana;
	int m_iSlotOcu;
	int m_iSref;
	int m_iSstr;
	int m_iSwill; 
};
//-----------------------------------------------------------------------------------------
#include "attribute.inl"
//-----------------------------------------------------------------------------------------