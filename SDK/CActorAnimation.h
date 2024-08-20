#pragma once

class CActorAnimation
{
public:
	using fnStopAnimations = void(__fastcall*)(CActorAnimation*);

	void StopAnimations() { return fnStopAnimations(0x1415E93D0)(this); } // ResultCameraA first xref
};