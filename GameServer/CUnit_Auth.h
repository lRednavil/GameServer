#pragma once
#include "ServerCommon.h"


class CUnit_Auth : public CUnitClass
{
public:
	void ContentsMontior();

private:
	//virtual함수 영역
	//packet이 있는 경우 사용만 하고 해제하지 말 것
	virtual void OnClientJoin(DWORD64 sessionID, CPacket* packet);
	//packet이 있는 경우 사용만 하고 해제하지 말 것
	virtual void OnClientLeave(DWORD64 sessionID);

	virtual void OnClientDisconnected(DWORD64 sessionID);

	//message 분석 역할
	//메세지 헤더는 알아서 검증할 것
	//업데이트 스레드 처리 필요시 jobQ에 enQ할것
	virtual void OnRecv(DWORD64 sessionID, CPacket* packet);

	virtual void OnTimeOut(DWORD64 sessionID);

	virtual void OnError(int error, const WCHAR* msg);

	virtual void OnEnd();

	//gameserver용
	//jobQ에 EnQ된 메세지들 처리
	virtual void MsgUpdate();
	//frame단위의 업데이트 처리
	virtual void FrameUpdate();

private:
	void Recv_Login(DWORD64 sessionID, CPacket* packet);
	void Res_Login(DWORD64 sessionID, BYTE res, PLAYER* player);

private:
	CLockFreeQueue<JOB> jobQ;
	int playerCnt = 0;
	int totalFrame = 0;
	int lastFrame = 0;
};

