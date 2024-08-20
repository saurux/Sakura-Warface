#pragma once

class CEntityClass
{
public:
	const char* GetName() { return VirtualFunction<const char* (__fastcall*)(void*)>(this, 0x10 / 8)(this); }
	bool IsEntityRight()
	{
		if (!strcmp(this->GetName(), ("Mantis")) && !strcmp(this->GetName(), ("Helicopter")))
		{
			return false;
		}

		return true;
	}
};