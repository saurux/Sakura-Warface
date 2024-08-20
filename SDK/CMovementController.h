#pragma once

struct SStanceStateQuery;
struct CMovementRequest {};

struct SStanceState 
{
	Vec3 pos;///0-8
	Vec3 entityDirection;//c-14
	Vec3 animationBodyDirection;//18-20
	Vec3 upDirection;//24-2C
	Vec3 weaponPosition;//30-38
	Vec3 aimDirection;//3C-44
	Vec3 fireDirection;//48-50
	Vec3 eyePosition;//54-5C
	Vec3 eyeDirection;//60-68
	float lean;//6C
	float peekOver;//70
	AABB m_StanceSize;//74-88
	AABB m_ColliderSize;//8C-94,98-A0
};

struct SMovementState : public SStanceState 
{
	DWORD Unk;//Vec3 fireTarget;//A4
	EStance stance;//A8
	Vec3 animationEyeDirection;//AC-B4
	Vec3 movementDirection, lastMovementDirection;//B8-C0,C4-CC
	float desiredSpeed;//D0
	float minSpeed;
	float normalSpeed;
	float maxSpeed;
	float slopeAngle;
	bool atMoveTarget;
	bool isAlive;
	bool isAiming;
	bool isFiring;
	bool isVisible;
	bool isMoving;
};

struct CMovementController
{
	virtual ~CMovementController() {}
	virtual bool RequestMovement(CMovementRequest& request) = 0;
	virtual void GetMovementState(SMovementState& state) = 0;
	virtual bool GetStanceState(const SStanceStateQuery& query, SStanceState& state) = 0;
};