#include "GameServer.h"

void CTestServer::Init()
{
    WCHAR IP[16] = L"0.0.0.0";
    DWORD PORT;
    DWORD createThreads;
    DWORD runningThreads;
    bool isNagle;
    DWORD maxConnect;
    DWORD sendLatency;
    DWORD packetSize;

    GetPrivateProfileString(L"GameServer", L"IP", L"0.0.0.0", IP, 16, L".//ServerSettings.ini");
    PORT = GetPrivateProfileInt(L"GameServer", L"PORT", NULL, L".//ServerSettings.ini");
    createThreads = GetPrivateProfileInt(L"GameServer", L"CreateThreads", NULL, L".//ServerSettings.ini");
    runningThreads = GetPrivateProfileInt(L"GameServer", L"RunningThreads", NULL, L".//ServerSettings.ini");
    isNagle = GetPrivateProfileInt(L"GameServer", L"isNagle", NULL, L".//ServerSettings.ini");
    maxConnect = GetPrivateProfileInt(L"GameServer", L"MaxConnect", NULL, L".//ServerSettings.ini");
    sendLatency = GetPrivateProfileInt(L"GameServer", L"sendLatency", 4, L".//ServerSettings.ini");
    packetSize = GetPrivateProfileInt(L"GameServer", L"packetSize", 1460, L".//ServerSettings.ini");

    if ((PORT * createThreads * runningThreads * maxConnect * sendLatency) == 0) {
        _FILE_LOG(LOG_LEVEL_ERROR, L"INIT_LOG", L"INVALID ARGUMENTS or No ini FILE");
        CRASH();
    }

    Start(IP, PORT, createThreads, runningThreads, isNagle, maxConnect, sendLatency, packetSize);
    monitorClient.Init();
}

bool CTestServer::OnConnectionRequest(WCHAR* IP, DWORD Port)
{
	return true;
}

bool CTestServer::OnClientJoin(DWORD64 sessionID)
{
	SetTimeOut(sessionID, 1000000);
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

    DWORD64 recvTPS = GetRecvTPS();
    DWORD64 sendTPS = GetSendTPS();

    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_SERVER_RUN, 1, tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_SERVER_CPU, processMonitor.ProcessTotal(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_SERVER_MEM, processMonitor.ProcessPrivateBytes() / 1024 / 1024, tv); // Mbyte단위로
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_SESSION, GetSessionCount(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_ACCEPT_TPS, GetAcceptTPS(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_PACKET_RECV_TPS, recvTPS, tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_PACKET_SEND_TPS, sendTPS, tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_PACKET_POOL, GetPacketPoolUse(), tv);

    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_MONITOR_CPU_TOTAL, processorMonitor.ProcessorTotal(), tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_MONITOR_NONPAGED_MEMORY, processorMonitor.NonPagedMemory() / 1024 / 1024, tv); // Mbytes단위로
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_MONITOR_NETWORK_RECV, processorMonitor.EthernetRecvTPS() / 1024, tv); //Kbytes단위로
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_MONITOR_NETWORK_SEND, processorMonitor.EthernetSendTPS() / 1024, tv); //Kbytes단위로
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_MONITOR_AVAILABLE_MEMORY, processorMonitor.AvailableMemory(), tv);

    wprintf(L"Recv TPS : %llu  || Send TPS : %llu \n", recvTPS, sendTPS);

    processMonitor.UpdateProcessTime();
    processorMonitor.UpdateHardwareTime();
}