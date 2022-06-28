#include "GameServer.h"

void CTestServer::Init()
{
    WCHAR IP[16] = L"0.0.0.0";
    DWORD PORT;
    DWORD createThreads;
    DWORD runningThreads;
    bool isNagle;
    DWORD maxConnect;
    DWORD snap;

    GetPrivateProfileString(L"ChatServer", L"IP", L"0.0.0.0", IP, 16, L".//ServerSettings.ini");
    PORT = GetPrivateProfileInt(L"ChatServer", L"PORT", NULL, L".//ServerSettings.ini");
    createThreads = GetPrivateProfileInt(L"ChatServer", L"CreateThreads", NULL, L".//ServerSettings.ini");
    runningThreads = GetPrivateProfileInt(L"ChatServer", L"RunningThreads", NULL, L".//ServerSettings.ini");
    isNagle = GetPrivateProfileInt(L"ChatServer", L"isNagle", NULL, L".//ServerSettings.ini");
    maxConnect = GetPrivateProfileInt(L"ChatServer", L"MaxConnect", NULL, L".//ServerSettings.ini");
    snap = GetPrivateProfileInt(L"ChatServer", L"SnapLatency", 4, L".//ServerSettings.ini");

    if ((PORT * createThreads * runningThreads * maxConnect * snap) == 0) {
        _FILE_LOG(LOG_LEVEL_ERROR, L"INIT_LOG", L"INVALID ARGUMENTS or No ini FILE");
        CRASH();
    }

    Start(IP, PORT, createThreads, runningThreads, isNagle, maxConnect, snap);
    monitorClient.Init();
}

bool CTestServer::OnConnectionRequest(WCHAR* IP, DWORD Port)
{
	return true;
}

bool CTestServer::OnClientJoin(DWORD64 sessionID)
{
	SetTimeOut(sessionID, INFINITE);
	MoveClass(L"Auth", sessionID, NULL, 0);
	return true;
}

bool CTestServer::OnClientLeave(DWORD64 sessionID)
{
	return true;
}

void CTestServer::OnStop()
{
}


void CTestServer::ContentsMonitor()
{
    if (IsServerOn() == false) return;
    int tv = time(NULL);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_SERVER_RUN, 1, tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_SERVER_CPU, processMonitor.ProcessTotal(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_SERVER_MEM, processMonitor.ProcessPrivateBytes() / 1024 / 1024, tv); // Mbyte단위로
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_SESSION, GetSessionCount(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_AUTH_PLAYER, playerMap.size(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_GAME_PLAYER, updateCnt - lastUpdateCnt, tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_ACCEPT_TPS, GetAcceptTPS(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_PACKET_RECV_TPS, GetRecvTPS(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_PACKET_SEND_TPS, GetSendTPS(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_AUTH_THREAD_FPS, GetSendTPS(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_GAME_THREAD_FPS, GetSendTPS(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_PACKET_POOL, GetPacketPoolUse(), tv);

    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_MONITOR_CPU_TOTAL, processorMonitor.ProcessorTotal(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_MONITOR_NONPAGED_MEMORY, processorMonitor.NonPagedMemory() / 1024 / 1024, tv); // Mbytes단위로
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_MONITOR_NETWORK_RECV, processorMonitor.EthernetRecvTPS() / 1024, tv); //Kbytes단위로
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_MONITOR_NETWORK_SEND, processorMonitor.EthernetSendTPS() / 1024, tv); //Kbytes단위로
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_MONITOR_AVAILABLE_MEMORY, processorMonitor.AvailableMemory(), tv);


    processMonitor.UpdateProcessTime();
    processorMonitor.UpdateHardwareTime();
}