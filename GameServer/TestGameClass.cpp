#include "TestGameClass.h"


bool CTestGameClass::OnConnectionRequest(WCHAR* IP, DWORD Port)
{
	return true;
}

bool CTestGameClass::OnClientJoin(DWORD64 sessionID)
{
	MoveClass(L"Auth", sessionID, 0);
	return true;
}

bool CTestGameClass::OnClientLeave(DWORD64 sessionID)
{
	return true;
}
