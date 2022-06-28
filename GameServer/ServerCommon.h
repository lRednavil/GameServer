#pragma once
#include <Windows.h>

#pragma comment(lib, "WS2_32")
#pragma comment(lib, "NetworkLibrary")

#include <unordered_map>

#include "CommonProtocol.h"
#include "include/LockFreeMemoryPool.h"
#include "include/LockFreeQueue.h"
#include "include/LockFreeStack.h"
#include "include/TLSMemoryPool.h"
#include "include/SerializedBuffer.h"
#include "include/ErrorReason.h"

#include "include/ProcessMonitor.h"
#include "include/ProcessorMonitor.h"

#include "include/Logging.h"
#include "include/Dump.h"

#include "include/LanClient.h"
#include "include/GameServer.h"

#include "MonitorClient.h"
struct JOB {
	WORD type;

	DWORD64 sessionID;
	CPacket* packet;
};

struct PLAYER {
	INT64 accountNo;
	char sessionKey[64];
};

extern CTLSMemoryPool<PLAYER> g_playerPool;
