#pragma once

class CWorldQuery
{
public:
	__int32 GetLookAtEntityId() { return this->m_lookAtEntityId; }
private:
	char pad_0x0000[0x170]; //0x0000
	__int32 m_lookAtEntityId; //0x0170
};
