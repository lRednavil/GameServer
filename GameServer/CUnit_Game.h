#pragma once
#include "ServerCommon.h"


class CUnit_Game : public CUnitClass
{
	//virtual함수 영역
	virtual void OnClientJoin(DWORD64 sessionID);
	virtual void OnClientLeave(DWORD64 sessionID);

	//message 분석 역할
	//메세지 헤더는 알아서 검증할 것
	//업데이트 스레드 처리 필요시 jobQ에 enQ할것
	virtual void OnRecv(DWORD64 sessionID, CPacket* packet);

	virtual void OnTimeOut(DWORD64 sessionID);

	virtual void OnError(int error, const WCHAR* msg);

	//gameserver용
	//jobQ에 EnQ된 메세지들 처리
	virtual void MsgUpdate();
	//frame단위의 업데이트 처리
	virtual void FrameUpdate();

private:
	void Recv_Echo(DWORD64 sessionID, CPacket* packet);
	void Res_Echo(DWORD64 sessionID, CPacket* packet);

private:
	CLockFreeQueue<JOB> jobQ;
};

