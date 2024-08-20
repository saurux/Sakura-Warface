#pragma once

template <typename T, typename M = INT32>
struct CMaskedVarT
{
private:
	union UVal
	{
		T asVarType;
		M asMaskType;
	};

	UVal m_val;
	M m_mask;
public:
	CMaskedVarT() {};
	
	ILINE CMaskedVarT& operator = (const T let)
	{
		UVal u;
		u.asVarType = let;
		m_val.asMaskType = (u.asMaskType ^ m_mask);
		return (*this);
	}

	ILINE T Get () 
	{
		UVal  w;
		w.asMaskType = 0;
		if (m_mask > 0) w.asMaskType = (m_val.asMaskType ^ m_mask);
		return w.asVarType;
	}
};

enum EGameStatType
{
	eGS_InvalidStat = 0xFFFFFFFF,
	eGS_Absorption = 0,
	eGS_Accuracy,
	eGS_ActivateDuration,
	eGS_AimAccuracy,
	eGS_AiSoundRadius,
	eGS_AmmoAmount,
	eGS_ArmorHealth,
	eGS_ArmorRegenHps,
	eGS_ArmorRegenTimeout,
	eGS_ArmsDamageMult,
	eGS_AutoZoomIn,
	eGS_AutoZoomOut,
	eGS_BallisticIronsight,
	eGS_BayonetMeleeDuration,
	eGS_BayonetMeleeOutDuration,
	eGS_BlindAmountMul,
	eGS_BodyDamageMult,
	eGS_BoltAction,
	eGS_BoltActionDuration,
	eGS_BulletPierceability,
	eGS_ClaymoreActivationDelayMul,
	eGS_ClaymoreDetectorRadius,
	eGS_ClipSize,
	eGS_CrouchSpeedMul,
	eGS_CustomizeInDuration,
	eGS_CustomizeOutDuration,
	eGS_Damage,
	eGS_DamageDropMinDistance,
	eGS_DamageDropPerMeter,
	eGS_DamageMin,
	eGS_DamageUnderbarrel,
	eGS_DeselectDuration,
	eGS_DeselectDurationBuff,
	eGS_ExtraAmmoPistolMul,
	eGS_ExtraAmmoPrimaryMul,
	eGS_FireUnderbarrelDuration,
	eGS_FireUnderbarrelOnRelease,
	eGS_FlashbangTimeMul,
	eGS_FovMul,
	eGS_HeadDamageMult,
	eGS_HealthMul,
	eGS_HipAccuracy,
	eGS_HolsterInDuration,
	eGS_HpRegenerationHps,
	eGS_HpRegenerationTimeout,
	eGS_IgnoreBulletBody,
	eGS_SuppressIgnoreBulletBody,
	eGS_IgnoreBulletHead,
	eGS_SuppressIgnoreBulletHead,
	eGS_KnockBackChance,
	eGS_KnockBackMinDistance,
	eGS_KnockBackMaxDistance,
	eGS_KnockBackResistance,
	eGS_KnockBackStaminaDamage,
	eGS_LegsDamageMult,
	eGS_Unk55,
	eGS_Unk56,
	eGS_MeleeDamage,
	eGS_MeleeDuration,
	eGS_MeleeDurationBuff,
	eGS_MeleeKnockBackChance,
	eGS_MeleeKnockBackStaminaDamage,
	eGS_CyborgDamageBuff,
	eGS_MeleeOutDuration,
	eGS_MeleeRadius,
	eGS_MeleeRange,
	eGS_MeleeRes,
	eGS_Range,
	eGS_RclAtt,
	eGS_RclDec,
	eGS_RclDecDelay,
	eGS_RclMax,
	eGS_RclRnd,
	eGS_RclSmth,
	eGS_ReloadDuration,
	eGS_ReloadDurationBuff,
	eGS_ReloadUnderbarrelDuration,
	eGS_ResArms,
	eGS_ResBody,
	eGS_ResHead,
	eGS_ResLegs,
	eGS_Resistance,
	eGS_Rpm,
	eGS_MoveSoundVolumeDamping,
	eGS_SecondaryMeleeDamage,
	eGS_SecondaryMeleeDuration,
	eGS_SecondaryMeleeDurationBuff,
	eGS_SecondaryMeleeOutDuration,
	eGS_SecondaryMeleeRadius,
	eGS_SecondaryMeleeRange,
	eGS_SelectDuration,
	eGS_SelectDurationBuff,
	eGS_SlideDistMul,
	eGS_SplashRes,
	eGS_SprdAtt,
	eGS_SprdDec,
	eGS_SprdDecDelay,
	eGS_SprdMax,
	eGS_SprdMin,
	eGS_SprintSpeedMul,
	eGS_SprintTimeMul,
	eGS_StaminaMul,
	eGS_SwayDec,
	eGS_SwayMinX,
	eGS_SwayMinY,
	eGS_SwaySpeedMult,
	eGS_ThrowDelayDuration,
	eGS_ThrowDuration,
	eGS_ThrowFireDelayDuration,
	eGS_TossDuration,
	eGS_ZoomFactor,
	eGS_ZoomInDuration,
	eGS_ZoomInDurationBuff,
	eGS_ZoomOutDuration,
	eGS_ZoomOutDurationBuff,
	eGS_ZoomedBoltActionDuration,
	eGS_PoisonGrenadeDamageMul,
	eGS_InSlotSelectDuration,
	eGS_InSlotDeselectDuration,
	eGS_UseInSlotWeaponChange,
	eGS_CameraShakeMul,
	eGS_SprdInverted,
	eGS_StrafeMultiplier,
	eGS_ClimbExtraHeight,
	eGS_ArmorAbsorbRatio,
};

struct CStatsArray
{
private:
	using CStatsMap = std::map<INT16, CMaskedVarT<float>>;
	CStatsMap m_stat;

public:
	ILINE float GetValue(EGameStatType name)
	{
		if (!this->m_stat.empty())
		{
			auto it = m_stat.find(name);
			if (it == m_stat.end()) return 1001.f;
			return it->second.Get();
		}
	}

	ILINE void SetValue(EGameStatType name, float value)
	{
		if (!this->m_stat.empty())
		{
			for (auto it = this->m_stat.begin(); it != this->m_stat.end(); it++)
			{
				if (it->first == name)
				{
					it->second = value;
				}
			}
		}
	}
};

class CWeaponParameters
{
private:
	char pad_0x0000[0x68];
	CStatsArray m_stats;
public:
	CStatsArray* GetStatsArray() { return &this->m_stats; }
};