#include "CUnit_Auth.h"

void CUnit_Auth::OnClientJoin(DWORD64 sessionID)
{
    _FILE_LOG(LOG_LEVEL_DEBUG, L"Auth_Log", L"Client Join");
}

void CUnit_Auth::OnClientLeave(DWORD64 sessionID)
{
    _FILE_LOG(LOG_LEVEL_DEBUG, L"Auth_Log", L"Client Leave");
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
}

void CUnit_Auth::Recv_Login(DWORD64 sessionID, CPacket* packet)
{
    
    INT64 accountNo;
    char sessionKey[64];

    int version;

    *packet >> accountNo;
    packet->GetData(sessionKey, 64);
    *packet >> version;

    if (version != 1) {
        Res_Login(sessionID, 0);
        Disconnect(sessionID);
        return;
    }

    Res_Login(sessionID, 1);
    MoveClass(L"Game", sessionID);
}

void CUnit_Auth::Res_Login(DWORD64 sessionID, BYTE res)
{
    CPacket* packet = PacketAlloc();


}
