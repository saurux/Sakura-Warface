#pragma once
#include <vector>
#include <map>
#include <Header/Header.hpp>

class CMovementSystem {
private:
	std::map<std::string, Vec3> coords = { 
		// blackwood
		{"bw_point1", Vec3(796.854f, 743.855f, 112.305f)}, 
		{"bw_point2", Vec3(870.483f, 676.580f, 120.f)}, {"bw_point3", Vec3(777.338f, 793.213f, 111.f)},
		{"bw_point4", Vec3(713.547f, 894.316f, 104.880f)}, {"bw_point5", Vec3(718.449f, 903.037f, 104.885f)},
		{"bw_point6", Vec3(2599.654f, 758.864f, 105.005f)}, {"bw_point7", Vec3(2635.431f, 748.882f, 101.005f)},
		{"bw_point8", Vec3(802.598f, 773.456f, 111.f)}, {"bw_point9", Vec3(887.340f, 852.413f, 105.750f)},
		{"bw_point10", Vec3(894.528f, 847.858f, 105.760f)}, {"bw_point11", Vec3(3024.646f, 3012.328f, 176.250f)},
		{"bw_point12", Vec3(2972.512f, 3005.870f, 183.750f)}, {"bw_point13", Vec3(882.605f, 832.075f, 134.856f)},
		// blackshark
		{"bsh_point1", Vec3(266.514f, 268.724f, 193.999f)}, {"bsh_point2", Vec3(258.209f, 266.135f, 189.340f)},
		{"bsh_point3", Vec3(293.260f, 266.496f, 192.875f)}
	};
	CActor* pActor;
	void GetInvincible(short int type)
	{
		if (type == 0)
		{
			SM_Network::SKnockBackMessage msg;
			ZeroMemory(&msg, sizeof(SM_Network::SKnockBackMessage));
			msg.handle = SMessageHandler::Singleton();
			msg.type = SM_Network::ESMType::eSMT_KnockBack; // 3
			msg.msgType = SM_Network::EMessageType::eMT_Start; // 2 - end
			msg.instant = 0;
			msg.opcode = 0;

			CRMIBodyImpl<SM_Network::SKnockBackMessage>* response = pActor->GetGameObject()->CreateKnockbackBody(&msg);

			if (response)
			{
				_InterlockedIncrement((volatile unsigned __int32*)((__int64)response + 0x38));
				pActor->GetGameObject()->InvokeRMI<SM_Network::SKnockBackMessage>(&response, 256, -1);
			}
		}

		else if (type == 1)
		{
			SM_Network::SKnockBackMessage msg;
			ZeroMemory(&msg, sizeof(SM_Network::SKnockBackMessage));
			msg.handle = SMessageHandler::Singleton();
			msg.type = SM_Network::ESMType::eSMT_KnockBack; // 3
			msg.msgType = SM_Network::EMessageType::eMT_End; // 2 - end
			msg.instant = 0;
			msg.opcode = 0;

			CRMIBodyImpl<SM_Network::SKnockBackMessage>* response = pActor->GetGameObject()->CreateKnockbackBody(&msg);

			if (response)
			{
				_InterlockedIncrement((volatile unsigned __int32*)((__int64)response + 0x38));
				pActor->GetGameObject()->InvokeRMI<SM_Network::SKnockBackMessage>(&response, 256, -1);
			}
		}
	}
	void GetInvincible()
	{
		SM_Network::SClimbMessage msg;
		ZeroMemory(&msg, sizeof(SM_Network::SClimbMessage));
		msg.type = SM_Network::ESMType::eSMT_Climb;
		msg.msgType = SM_Network::EMessageType::eMT_Start;
		msg.instant = 0;
		msg.opcode = 0;
		msg.animIndex = 0;
		msg.animFinished = false;
		msg.helperClosestPoint = ZERO;
		msg.animStartPose.t = ZERO;
		msg.animStartPose.q.v = ZERO;
		msg.serverTime = SSystemGlobalEnvironment::Singleton()->GetGame()->GetGameFramework()->GetServerTime();
		auto method = this->pActor->GetGameObject()->CreateClimbBody(&msg);
		auto method_2 = method;
		if (method) {
			_InterlockedIncrement((volatile unsigned __int32*)((__int64)method_2 + 0x38));
			this->pActor->GetGameObject()->DoInvokeRMI(&method, 256, -1);

			SM_Network::SClimbMessage msg;
			ZeroMemory(&msg, sizeof(SM_Network::SClimbMessage));
			msg.type = SM_Network::ESMType::eSMT_Climb;
			msg.msgType = SM_Network::EMessageType::eMT_End;
			msg.instant = 0;
			msg.opcode = 0; // -1
			msg.animIndex = 0;
			msg.animFinished = true;
			msg.animStartPose.t = this->pActor->GetPosition();
			msg.animStartPose.q.v = ZERO; // mainly for invsible
			msg.helperClosestPoint = this->pActor->GetPosition();
			msg.serverTime = SSystemGlobalEnvironment::Singleton()->GetGame()->GetGameFramework()->GetServerTime();

			auto method = this->pActor->GetGameObject()->CreateClimbBody(&msg);
			auto method_2 = method;

			if (method) {
				_InterlockedIncrement((volatile unsigned __int32*)((__int64)method_2 + 0x38));
				this->pActor->GetGameObject()->DoInvokeRMI(&method, 256, -1);
			}
		}
	}
public:
	CMovementSystem(CActor* pActor) : pActor(pActor) {}
	void SetPosition(Vec3 vPosition) {
		if (CGameObject* pGameObject = this->pActor->GetGameObject()) {
			SM_Network::SKnockBackMessage msg;
			ZeroMemory(&msg, sizeof(SM_Network::SKnockBackMessage));

			msg.type = SM_Network::ESMType::eSMT_KnockBack; // 3
			msg.msgType = SM_Network::EMessageType::eMT_Message; // 2 - end
			msg.instant = 0; // 0
			msg.opcode = 0; // 2
			msg.serverTime = 0;
			msg.startPos = vPosition;
			msg.serverTime = 0;

			pGameObject->SendRequest(SM_Network::ESMType::eSMT_KnockBack, &msg);
		}
	}

	void SetInvincible(bool bRageMode = false) {
		if (!bRageMode) {
			this->GetInvincible();
		}

		if (bRageMode) {
			this->GetInvincible(0);
			this->GetInvincible(1);
		}
	}
};

class CPlayerHandler {
public:
	static void Update() {
		SSystemGlobalEnvironment* pEnv = SSystemGlobalEnvironment::Singleton();
		CGame* pGame = pEnv->GetGame();
		CGameFramework* pGameFramework = pGame->GetGameFramework();

		CActor* mActor = pGameFramework->GetClientActor();

		if (mActor) {

		}
	}
};