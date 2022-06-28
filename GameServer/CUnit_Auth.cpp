#include "CUnit_Auth.h"

void CUnit_Auth::ContentsMontior()
{
    int tv = time(NULL);

    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_AUTH_PLAYER, playerCnt, tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_AUTH_THREAD_FPS, totalFrame - lastFrame, tv);

    lastFrame = totalFrame;
}

void CUnit_Auth::OnClientJoin(DWORD64 sessionID, CPacket* packet)
{
    playerCnt++;
}

void CUnit_Auth::OnClientLeave(DWORD64 sessionID)
{
    playerCnt--;
}

void CUnit_Auth::OnClientDisconnected(DWORD64 sessionID)
{
    playerCnt--;
}

void CUnit_Auth::OnRecv(DWORD64 sessionID, CPacket* packet)
{
    WORD type;
    JOB job;

    *packet >> type;

    switch (type) {
    case en_PACKET_CS_GAME_REQ_LOGIN:
    {
        job.type = en_PACKET_CS_GAME_REQ_LOGIN;
        job.sessionID = sessionID;
        job.packet = packet;

        jobQ.Enqueue(job);
    }
    break;
    
    case en_PACKET_CS_GAME_REQ_HEARTBEAT:
    {
        PacketFree(packet);
        break;
    }
    default:
    {
        Disconnect(sessionID);
        PacketFree(packet);
    }
    }

}

void CUnit_Auth::OnTimeOut(DWORD64 sessionID)
{
    
}

void CUnit_Auth::OnError(int error, const WCHAR* msg)
{
}

void CUnit_Auth::MsgUpdate()
{
    JOB job;

    while (jobQ.Dequeue(&job)) {
        switch (job.type) {
        case en_PACKET_CS_GAME_REQ_LOGIN:
        {
            Recv_Login(job.sessionID, job.packet);
        }
        break;

        default:
            Disconnect(job.sessionID);
        }

        PacketFree(job.packet);
    }

}

void CUnit_Auth::FrameUpdate()
{
    totalFrame++;
}

void CUnit_Auth::Recv_Login(DWORD64 sessionID, CPacket* packet)
{
    
    INT64 accountNo;
    char sessionKey[64];

    int version;

    PLAYER* player = g_playerPool.Alloc();
    
    *packet >> player->accountNo;
    packet->GetData(player->sessionKey, 64);

    *packet >> version;

    if (version != 1) {
        Res_Login(sessionID, 0, player);
        g_playerPool.Free(player);
        Disconnect(sessionID);
        return;
    }

    Res_Login(sessionID, 1, player);
}

void CUnit_Auth::Res_Login(DWORD64 sessionID, BYTE res, PLAYER* player)
{
    CPacket* packet = PacketAlloc();
    constexpr WORD type = en_PACKET_CS_GAME_RES_LOGIN;

    CPacket* moveInfo;

    *packet << (WORD)type << res << player->accountNo;
    
    if (res == 0) {
        g_playerPool.Free(player);
    }
    else {
        moveInfo = InfoAlloc();
        moveInfo->PutData((char*)&player, sizeof(void*));
        MoveClass(L"Game", sessionID, moveInfo);
    }

    SendPacket(sessionID, packet);
}
