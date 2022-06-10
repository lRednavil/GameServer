#include "CUnit_Game.h"

void CUnit_Game::OnClientJoin(DWORD64 sessionID, CPacket* packet)
{
    if (packet == NULL) {
        CRASH();
    }

    PLAYER* player;
    packet->GetData((char*)&player, sizeof(PLAYER*));

    playerMap.insert({ sessionID, player });
}

void CUnit_Game::OnClientLeave(DWORD64 sessionID)
{
    if (playerMap.find(sessionID) != playerMap.end()) {
        playerMap.erase(sessionID);
    }
}

void CUnit_Game::OnClientDisconnected(DWORD64 sessionID)
{
    if (playerMap.find(sessionID) != playerMap.end()) {
        g_playerPool.Free(playerMap[sessionID]);
    }
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
        _FILE_LOG(LOG_LEVEL_DEBUG, L"GAME_DEBUG_LOG", L"default Msg Enqueued");
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

void CUnit_Game::MsgUpdate()
{
    JOB job;

    while (jobQ.Dequeue(&job)) {
        switch (job.type) {
        case en_PACKET_CS_GAME_REQ_LOGIN:
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
}

void CUnit_Game::Recv_Echo(DWORD64 sessionID, CPacket* packet)
{
    CPacket* sendMsg = PacketAlloc();

    INT64 accountNo;
    LONGLONG sendTick;

    *packet >> accountNo >> sendTick;

    *sendMsg << accountNo << sendTick;

    Res_Echo(sessionID, sendMsg);
}

void CUnit_Game::Res_Echo(DWORD64 sessionID, CPacket* packet)
{
    SendPacket(sessionID, packet);
}
