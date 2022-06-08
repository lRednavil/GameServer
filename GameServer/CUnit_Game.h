#pragma once
#include "ServerCommon.h"


class CUnit_Game : public CUnitClass
{
	//virtual�Լ� ����
	virtual void OnClientJoin(DWORD64 sessionID);
	virtual void OnClientLeave(DWORD64 sessionID);

	//message �м� ����
	//�޼��� ����� �˾Ƽ� ������ ��
	//������Ʈ ������ ó�� �ʿ�� jobQ�� enQ�Ұ�
	virtual void OnRecv(DWORD64 sessionID, CPacket* packet);

	virtual void OnTimeOut(DWORD64 sessionID);

	virtual void OnError(int error, const WCHAR* msg);

	//gameserver��
	//jobQ�� EnQ�� �޼����� ó��
	virtual void MsgUpdate();
	//frame������ ������Ʈ ó��
	virtual void FrameUpdate();

private:
	void Recv_Echo(DWORD64 sessionID, CPacket* packet);
	void Res_Echo(DWORD64 sessionID, CPacket* packet);

private:
	CLockFreeQueue<JOB> jobQ;
};

