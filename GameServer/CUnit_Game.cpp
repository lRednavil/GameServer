#include "CUnit_Game.h"


void CUnit_Game::ContentsMonitor()
{
    int tv = time(NULL);

    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_GAME_PLAYER, playerCnt, tv);
    monitorClient.UpdateMonitorInfo(dfMONITOR_DATA_TYPE_GAME_GAME_THREAD_FPS, totalFrame - lastFrame, tv);

    lastFrame = totalFrame;
}

void CUnit_Game::OnClientJoin(DWORD64 sessionID, CPacket* packet)
{
    if (packet == NULL) {
        CRASH();
    }
    PLAYER* player;
    packet->GetData((char*)&player, sizeof(PLAYER*));

    playerMap.insert({ sessionID, player });
    playerCnt++;
}

void CUnit_Game::OnClientLeave(DWORD64 sessionID)
{
    if (playerMap.find(sessionID) != playerMap.end()) {
        playerMap.erase(sessionID);
    }
    playerCnt--;
}

void CUnit_Game::OnClientDisconnected(DWORD64 sessionID)
{
    if (playerMap.find(sessionID) != playerMap.end()) {
        g_playerPool.Free(playerMap[sessionID]);
        playerMap.erase(sessionID);
    }
    playerCnt--;
}

void CUnit_Game::OnRecv(DWORD64 sessionID, CPacket* packet)
{
    WORD type;
    JOB job;

    *packet >> type;

    switch (type) {
    case en_PACKET_CS_GAME_REQ_ECHO:
    {
        job.type = en_PACKET_CS_GAME_REQ_ECHO;
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

void CUnit_Game::OnTimeOut(DWORD64 sessionID)
{
}

void CUnit_Game::OnError(int error, const WCHAR* msg)
{
}

void CUnit_Game::OnEnd()
{
}

void CUnit_Game::MsgUpdate()
{
    JOB job;
    int lim = jobQ.GetSize();

    while (lim--) {
        jobQ.Dequeue(&job);
        switch (job.type) {
        case en_PACKET_CS_GAME_REQ_ECHO:
        {
            Recv_Echo(job.sessionID, job.packet);
        }
        break;

        default:
            Disconnect(job.sessionID);
        }

        PacketFree(job.packet);
    }

}

void CUnit_Game::FrameUpdate()
{
    totalFrame++;
}

void CUnit_Game::Recv_Echo(DWORD64 sessionID, CPacket* packet)
{
    CPacket* sendMsg = PacketAlloc();
    constexpr WORD type = en_PACKET_CS_GAME_RES_ECHO;
    int len = packet->GetDataSize();

    *sendMsg << type;
    packet->GetData(sendMsg->GetWritePtr(), len);
    sendMsg->MoveWritePos(len);

    SendPacket(sessionID, sendMsg);
}
