#pragma once
#include "ServerCommon.h"


class CUnit_Game : public CUnitClass
{
public:
	void ContentsMonitor();

private:
	//virtual�Լ� ����
	//packet�� �ִ� ��� ��븸 �ϰ� �������� �� ��
	virtual void OnClientJoin(DWORD64 sessionID, CPacket* packet);
	//packet�� �ִ� ��� ��븸 �ϰ� �������� �� ��
	virtual void OnClientLeave(DWORD64 sessionID);
	
	virtual void OnClientDisconnected(DWORD64 sessionID);

	//message �м� ����
	//�޼��� ����� �˾Ƽ� ������ ��
	//������Ʈ ������ ó�� �ʿ�� jobQ�� enQ�Ұ�
	virtual void OnRecv(DWORD64 sessionID, CPacket* packet);

	virtual void OnTimeOut(DWORD64 sessionID);

	virtual void OnError(int error, const WCHAR* msg);

	virtual void OnEnd();

	//gameserver��
	//jobQ�� EnQ�� �޼����� ó��
	virtual void MsgUpdate();
	//frame������ ������Ʈ ó��
	virtual void FrameUpdate();

private:
	void Recv_Echo(DWORD64 sessionID, CPacket* packet);

private:
	CLockFreeQueue<JOB> jobQ;
	std::unordered_map<DWORD64, PLAYER*> playerMap;
	int playerCnt = 0;
	int totalFrame = 0;
	int lastFrame = 0;
};

