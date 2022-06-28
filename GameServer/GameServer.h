#pragma once
#include "ServerCommon.h"

class CTestServer : public CGameServer
{
public:
	void ContentsMonitor();

	virtual void Init();
	//accept ����, IP filterinig ���� ����
	virtual bool OnConnectionRequest(WCHAR* IP, DWORD Port);
	//return false; �� Ŭ���̾�Ʈ �ź�.
	//return true; �� ���� ���
	virtual bool OnClientJoin(DWORD64 sessionID);
	virtual bool OnClientLeave(DWORD64 sessionID);

	virtual void OnStop();

private:
	CProcessMonitor processMonitor;
	CProcessorMonitor processorMonitor;
	CMonitorClient monitorClient;
};

