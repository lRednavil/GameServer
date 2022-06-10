#include "TestGameClass.h"


bool CTestGameClass::OnConnectionRequest(WCHAR* IP, DWORD Port)
{
	return true;
}

bool CTestGameClass::OnClientJoin(DWORD64 sessionID)
{
	SetTimeOut(sessionID, INFINITE);
	//MoveClass(L"Auth", sessionID, NULL, 0);
	return true;
}

bool CTestGameClass::OnClientLeave(DWORD64 sessionID)
{
	return true;
}
