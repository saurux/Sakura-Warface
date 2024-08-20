#pragma once

namespace Settings {
	// Visuals
	bool bSilhouettePlayer	   = false;
	bool bSilhouetteObject	   = false;
	bool bSilhouetteWeapon	   = false;
	bool bClaymoreDetectRadius = false;
	bool bFlashbangDisable	   = false;

	// Player
	bool bFlyMode			= false;
	bool bInvinsible		= false;
	bool bDesynchronization = false;
	bool bTeleportMode		= false;
	bool bFastCrouch		= false;
	bool bFastClimb			= false;
	bool bCrashPlayers		= false;
	bool bClimbExtra		= false;
	bool bSpamX				= false;

	// Weapon
	bool bNoRecoil		= false;
	bool bNoSpread		= false;
	bool bNoSway		= false;
	bool bFastKnife		= false;
	bool bFastReload	= false;
	bool bFastZoom		= false;
	bool bRapidFire		= false;

	// Aiming
	bool bSilentAim		= false;
	bool bFovAim		= false;
	bool bFireHit		= false;
	bool bKnifeHit		= false;
	bool bWallshot		= false;
	bool bKillBosses	= false;

	// Miscellaneous
	bool bVotingEnable			= false;
	bool bDisableKickByAFK		= false;
	bool bSuicide				= false;
	bool bKickSelf				= false;
	bool bCustomNickname		= false;
	bool bCustomStatistics		= false;
	bool bCommunication			= false;
	bool bSpawnAnalyse			= false;

	int hitWait = 100, hitCount = 1;
	float nFovRadius = 90;
}