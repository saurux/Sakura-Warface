#pragma once
/*
struct SHasteParams
{
	float staminaCost;
	float speedMult;
	float strafeMult;
	float inertiaMult;
	float inertiaAccelMult;
};

struct CHasteClassExtension
{
	char pad_0x0008[0x8];
	SHasteParams m_params;
};

struct SAnimSelection
{
	float upperOffset;
	float upperOffset2;
	float middleOffset;
};

struct SClimbAnim
{
	const char* inputId;
	float length;
	float duration;
	float offsetFromTop;
	float playbackMult;
	const char* animName;
};

struct SClimbParams
{
	float minHelperHeight;
	float maxHelperHeight;
	float detectZoneLength;
	float nearZoneLength;
	float lowerAnimStartDist;
	float verticalVelocity;
	SAnimSelection animSelection;
	SClimbAnim animations[4];
};

struct CClimbClassExtension
{
	char pad_0x0008[0x8];
	SClimbParams m_params;
};

struct SSlideParams
{
	float initialStaminaDrop;
	float staminaCost;
	float minHasteTimeBeforeSlide;
	float minSlidingTime;
	float slideInTime;
	float slideInFastTime;
	float slideFromJumpDelay;
	float horzLimitAngle;
	float vertLimitAngle;
	float viewOffsetZ;
	float slideOutVelocity;
	float speedIncreaseCoeff;
	float speed0;
	float time0;
	float speed1;
	float time1;
	float speed2;
	float time2;
	float speed3;
};

struct CSlidePersistent
{
	char pad_0x0008[0x8];
	SSlideParams m_params;
};

struct SKnockBackParams
{
	float horzLimitAnlge;
	float vertLimitAngleMin;
	float vertLimitAngleMax;
	float fallingTime;
	float raisingTimeSingle;
	float raisingTimeCoop;
	float cameraYawOffset;
	float cameraPitchOffset;
	float cameraRoll;
	Vec3 viewOffset;
	float stunDuration;
};

struct CKnockBackPersistent
{
	char pad_0x0008[0x8];
	SKnockBackParams m_params;
};

struct SRaiseAssistParams
{
	float assistTime;
};

struct CRaiseAssistPersistent
{
	char pad_0x0008[0x8];
	SRaiseAssistParams m_params;
};

struct SVaultAnim
{
	const char* inputId;
	float offsetFromTop;
	const char* animName;
};

struct SVaultParams
{
	float detectZoneLength;
	float nearZoneLength;
	float lowerAnimStartDist;
	float verticalVelocity;
	float animSelectionOffset;
	float animLength;
	float animTime;
	float animPlaybackMult;
	float minHelperHeight;
	float maxHelperWidth;
	float groundCheckStartTime;
	float lastSegmentLength;
	float groundMinDist;
	float trajectoryValidationPercent;
	SVaultAnim animations[2];
};

struct CVaultClassExtension
{
	char pad_0x0008[0x8];
	SVaultParams m_params;
};

struct SCoopCinematicParams
{
	float fLocatorRadius;
	float fLocatorViewLimit;
	float fHorzLimitAngle;
	float fVertLimitAngle;
	const char* messageText;
	const char* morePlayersText;
};

struct  CCoopCinematicPersistent
{
	SCoopCinematicParams m_params;
};

struct SCoopClimbParams
{
};

struct CCoopClimbClassExtension
{
	char pad_0x0008[0x8];
	SCoopClimbParams m_params;
};

struct SCoopAssistParams
{
	float singleClimbTime;
	float coopClimbTime;
	float coopClimbAssistingTime;
	float assistEnteringTime0;
	float assistEnteringTime90;
	float assistEnteringTime180;
	float assistStartZoneLength;
	float assistEnteringAnimStartDist;
	Vec3 assistViewOffset;
	Vec3 assistCharacterOffset;
	float climberToAssisterStartDist;
	float assistAnimLength;
	float coopClimbAnimLength;
	float singleClimbAnimLength;
	float singleClimbAnimTime;
	float coopClimbAnimTime;
	float animPlaybackSpeed;
};

struct CCoopAssistClassExtension
{
	char pad_0x0008[0x8];
	SCoopAssistParams m_params;
};

struct SSpecialMovesPersistents
{
	CHasteClassExtension* hasteClassExt;
	CClimbClassExtension* climbPersistent;
	CSlidePersistent* slidePersistent;
	CKnockBackPersistent* knockBackPersistent;
	CRaiseAssistPersistent* raiseAssistPersistent;
	CVaultClassExtension* vaultPersistent;
	CCoopCinematicPersistent* coopCinematicPersistent;
	CCoopClimbClassExtension* coopClimbClassExt;
	CCoopAssistClassExtension* coopAssistClassExt;
};

class CSpecialMovesRegistry
{
public:
	char pad_0x0008[0x8];
	SSpecialMovesPersistents* m_persistents;
};
*/