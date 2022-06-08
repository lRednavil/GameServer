#pragma once
#include "ServerCommon.h"

class CTestGameClass : public CGameServer
{
public:
	//accept 직후, IP filterinig 등의 목적
	virtual bool OnConnectionRequest(WCHAR* IP, DWORD Port);
	//return false; 시 클라이언트 거부.
	//return true; 시 접속 허용
	virtual bool OnClientJoin(DWORD64 sessionID);
	virtual bool OnClientLeave(DWORD64 sessionID);


};

