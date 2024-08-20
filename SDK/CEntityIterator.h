#pragma once

#include "CEntity.h"

class CEntityIterator
{
public:
	virtual ~CEntityIterator() {}; //0
	virtual void AddRef() = 0; //1
	virtual void Release() = 0; //2
	virtual void MoveFirst() = 0; //3
	virtual bool IsEnd() = 0; //4
	virtual CEntity* This() = 0; //5
	virtual CEntity* Next() = 0; //6
	//CEntity* Next() { return VirtualFunction<CEntity*(__thiscall*)(void*)>(this, 48 / 8)(this); }
};