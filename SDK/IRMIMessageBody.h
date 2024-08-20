#pragma once

#include <string>
#include <SDK/Math/Math.h>

struct SNetMessageDef;
struct SNetProtocolDef;
struct SGameObjectExtensionRMI;

struct ISerialize;
struct IRMIListener;
struct IProtocolBuilder;
struct INetMessageSink;
struct IRMIMessageBody;
struct CNetChannel;

typedef ISerialize* TSerialize;

enum ENetReliabilityType
{
	eNRT_ReliableOrdered,
	eNRT_ReliableUnordered,
	eNRT_UnreliableOrdered,
	eNRT_UnreliableUnordered,
	eNRT_NumReliabilityTypes
};

enum ERMIAttachmentType
{
	eRAT_PreAttach = 0,
	eRAT_PostAttach = 1,
	eRAT_NoAttach,
	eRAT_Urgent,
	eRAT_Independent,
	eRAT_NumAttachmentTypes
};

enum EDisconnectionCause
{
	//! This cause must be first! - timeout occurred.
	eDC_Timeout = 0,
	//! Incompatible protocols.
	eDC_ProtocolError,
	//! Failed to resolve an address.
	eDC_ResolveFailed,
	//! Versions mismatch.
	eDC_VersionMismatch,
	//! Server is full.
	eDC_ServerFull,
	//! User initiated kick.
	eDC_Kicked,
	//! Teamkill ban/ admin ban.
	eDC_Banned,
	//! Context database mismatch.
	eDC_ContextCorruption,
	//! Password mismatch, cdkey bad, etc.
	eDC_AuthenticationFailed,
	//! Misc. game error.
	eDC_GameError,
	//! DX11 not found.
	eDC_NotDX11Capable,
	//! The nub has been destroyed.
	eDC_NubDestroyed,
	//! Icmp reported error.
	eDC_ICMPError,
	//! NAT negotiation error.
	eDC_NatNegError,
	//! Punk buster detected something bad.
	eDC_PunkDetected,
	//! Demo playback finished.
	eDC_DemoPlaybackFinished,
	//! Demo playback file not found.
	eDC_DemoPlaybackFileNotFound,
	//! User decided to stop playing.
	eDC_UserRequested,
	//! User should have controller connected.
	eDC_NoController,
	//! Unable to connect to server.
	eDC_CantConnect,
	//! Arbitration failed in a live arbitrated session.
	eDC_ArbitrationFailed,
	//! Failed to successfully join migrated game.
	eDC_FailedToMigrateToNewHost,
	//! The session has just been deleted.
	eDC_SessionDeleted,
	//! Kicked due to having a high ping.
	eDC_KickedHighPing,
	//! Kicked due to reserved user joining.
	eDC_KickedReservedUser,
	//! Class registry mismatch.
	eDC_ClassRegistryMismatch,
	//! Global ban.
	eDC_GloballyBanned,
	//! Global ban stage 1 messaging.
	eDC_Global_Ban1,
	//! Global ban stage 2 messaging.
	eDC_Global_Ban2,
	//! This cause must be last! - unknown cause.
	eDC_Unknown
};

enum EMessageParallelFlags
{
	eMPF_BlocksStateChange = 0x0001,
	eMPF_DecodeInSync = 0x0002,
	eMPF_NoSendDelay = 0x0004,
	eMPF_DiscardIfNoEntity = 0x0008,
	eMPF_StateChange = 0x0010,
	eMPF_DontAwake = 0x0020,
	eMPF_AfterSpawning = 0x0040
};

struct SNetProtocolDef
{
	size_t          nMessages;
	SNetMessageDef* vMessages;
};

struct INetAtSyncItem
{
	virtual ~INetAtSyncItem() {}
	virtual bool Sync() = 0;
	virtual bool SyncWithError(EDisconnectionCause& disconnectCause, std::string& disconnectMessage) = 0;
	virtual void DeleteThis() = 0;
};

struct SGameObjectExtensionRMI
{
	typedef struct INetAtSyncItem* (*DecoderFunction)(ISerialize*, EntityId*, CNetChannel*);

	DecoderFunction decoder; // 0x0000
	const char* description; // 0x0008
	const void* pBase; // 0x0010
	SNetMessageDef* pMsgDef; // 0x0018
	ERMIAttachmentType attach; // 0x0020
	bool isServerCall; // 0x0024
	bool lowDelay; // 0x0028
	ENetReliabilityType reliability; // 0x002C
};

struct IRMIListener
{
	virtual ~IRMIListener() {}
	virtual void OnSend(CNetChannel* pChannel, int userId, uint32 nSeq) = 0;
	virtual void OnAck(CNetChannel* pChannel, int userId, uint32 nSeq, bool bAck) = 0;
};

struct IProtocolBuilder
{
	virtual ~IProtocolBuilder() {}
	virtual void AddMessageSink(INetMessageSink* pSink, const SNetProtocolDef& protocolSending, const SNetProtocolDef& protocolReceiving) = 0;
};

struct INetMessageSink
{
	virtual ~INetMessageSink() {}

	virtual void DefineProtocol(IProtocolBuilder* pBuilder) = 0;
	virtual bool HasDef(const SNetMessageDef* pDef) = 0;
};

typedef std::pair<bool, INetAtSyncItem*> TNetMessageCallbackResult;

/*
struct SNetMessageDef
{
	typedef TNetMessageCallbackResult(*HandlerType)(
		uint32 nUser,
		INetMessageSink*,
		TSerialize,
		uint32 curSeq,
		uint32 oldSeq,
		uint32 timeFraction32,
		EntityId* pRmiObject,
		CNetChannel* pChannel
		);
	HandlerType         handler;
	const char* description;
	ENetReliabilityType reliability;
	uint32              nUser;
	uint32              parallelFlags;
	bool                CheckParallelFlag(EMessageParallelFlags flag) const
	{
		return (parallelFlags & flag) != 0;
	}
	struct ComparePointer
	{
		bool operator()(const SNetMessageDef* p1, const SNetMessageDef* p2)
		{
			return strcmp(p1->description, p2->description) < 0;
		}
	};
};
*/

struct SNetMessageDef
{
	//std::pair<bool, INetAtSyncItem*>* (__cdecl* handler)(std::pair<bool, INetAtSyncItem*>* result, unsigned int, INetMessageSink*, CSerializeWrapper<ISerialize>, unsigned int, unsigned int, unsigned int*, INetChannel*);
	char pad_0x0008[8];
	const char* description;
	ENetReliabilityType reliability;
	unsigned int nUser;
	unsigned int parallelFlags;
};

/*
struct IRMIMessageBody
{
	IRMIMessageBody(
		ENetReliabilityType reliability_,
		ERMIAttachmentType attachment_,
		EntityId objId_,
		uint8 funcId_,
		IRMIListener* pListener_,
		int userId_,
		EntityId dependentId_) :
		reliability(reliability_),
		attachment(attachment_),
		objId(objId_),
		dependentId(dependentId_),
		funcId(funcId_),
		pMessageDef(0),
		userId(userId_),
		pListener(pListener_),
		m_cnt(0)
	{
	}
	IRMIMessageBody(
		ENetReliabilityType reliability_,
		ERMIAttachmentType attachment_,
		EntityId objId_,
		SNetMessageDef* pMessageDef_,
		IRMIListener* pListener_,
		int userId_,
		EntityId dependentId_) :
		reliability(reliability_),
		attachment(attachment_),
		objId(objId_),
		dependentId(dependentId_),
		funcId(0),
		pMessageDef(pMessageDef_),
		userId(userId_),
		pListener(pListener_),
		m_cnt(0)
	{
	}

	virtual ~IRMIMessageBody() = 0;
	virtual void   SerializeWith(TSerialize ser) = 0;
	virtual size_t GetSize() = 0;
	virtual void DeleteThis() = 0;

	ENetReliabilityType reliability; // 0x08
	ERMIAttachmentType  attachment; // 0x0C
	EntityId            objId;  // 0x10
	EntityId            dependentId;  // 0x14
	uint8               funcId; // 0x18

	//! Can optionally set this to send a defined message instead of a script style function.
	SNetMessageDef* pMessageDef;

	//! These two define a listening interface for really advance user stuff.
	int     userId;
	IRMIListener* pListener;

	const char* GetDescription()
	{
		return pMessageDef->description;
	}

	volatile unsigned int m_cnt;
};
*/

struct IRMIMessageBody
{
	char pad_0x0008[8];
	ENetReliabilityType reliability;
	ERMIAttachmentType attachment;
	const unsigned int objId;
	const unsigned int dependentId;
	const char funcId;
	SNetMessageDef* pMessageDef;
	const int userId;
	IRMIListener* pListener;
	volatile int m_cnt;
};


struct CRMIBody : IRMIMessageBody {
};

template <typename T>
struct CRMIBodyImplement : CRMIBody {
	T m_params;
};

template <typename T> 
struct CRMIBodyImpl : CRMIBody
{
public:
	T m_params;

	CRMIBodyImpl(const SGameObjectExtensionRMI* method, EntityId id, const T& params, IRMIListener* pListener, int userId, EntityId dependentId) :
		IRMIMessageBody(method->reliability, method->attach, id, method->pMsgDef, pListener, userId, dependentId)
	{
		m_params = params;
	}
};