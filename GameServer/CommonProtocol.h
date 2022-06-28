enum en_PACKET_TYPE
{
	//------------------------------------------------------
	// Game Server
	//------------------------------------------------------
	en_PACKET_CS_GAME_SERVER = 1000,

	//------------------------------------------------------------
	// �α��� ��û
	//
	//	{
	//		WORD	Type
	//
	//		INT64	AccountNo
	//		char	SessionKey[64]
	//
	//		int		Version			// 1 
	//	}
	//
	//------------------------------------------------------------
	en_PACKET_CS_GAME_REQ_LOGIN,

	//------------------------------------------------------------
	// �α��� ����
	//
	//	{
	//		WORD	Type
	//
	//		BYTE	Status (0: ���� / 1: ����)
	//		INT64	AccountNo
	//	}
	//
	//	���� ���̴� ������ �������� �Ǵ��ϰ� ����
	//	Status ����� �����Ѵٴ� �̾߱�
	//
	//  en_PACKET_CS_GAME_RES_LOGIN define �� ���.
	//------------------------------------------------------------
	en_PACKET_CS_GAME_RES_LOGIN,



	//------------------------------------------------------------
	// �׽�Ʈ�� ���� ��û
	//
	//	{
	//		WORD		Type
	//
	//		INT64		AccountoNo
	//		LONGLONG	SendTick
	//	}
	//
	//------------------------------------------------------------	
	en_PACKET_CS_GAME_REQ_ECHO = 5000,

	//------------------------------------------------------------
	// �׽�Ʈ�� ���� ���� (REQ �� �״�� ������)
	//
	//	{
	//		WORD		Type
	//
	//		INT64		AccountoNo
	//		LONGLONG	SendTick
	//	}
	//
	//------------------------------------------------------------
	en_PACKET_CS_GAME_RES_ECHO,

	//------------------------------------------------------------
	// ��Ʈ��Ʈ
	//
	//	{
	//		WORD		Type
	//	}
	//
	//
	// Ŭ���̾�Ʈ�� �̸� 30�ʸ��� ������.
	// ������ 40�� �̻󵿾� �޽��� ������ ���� Ŭ���̾�Ʈ�� ������ ������� ��.
	//------------------------------------------------------------	
	en_PACKET_CS_GAME_REQ_HEARTBEAT,

	//------------------------------------------------------
// Monitor Server Protocol
//------------------------------------------------------


////////////////////////////////////////////////////////
//
//   MonitorServer & MoniterTool Protocol / ������ ���� ����.
//
////////////////////////////////////////////////////////

//------------------------------------------------------
// Monitor Server  Protocol
//------------------------------------------------------
en_PACKET_SS_MONITOR = 20000,
//------------------------------------------------------
// Server -> Monitor Protocol
//------------------------------------------------------
//------------------------------------------------------------
// LoginServer, GameServer , ChatServer  �� ����͸� ������ �α��� ��
//
// 
//	{
//		WORD	Type
//
//		int		ServerNo		//  �� �������� ���� ��ȣ�� �ο��Ͽ� ���
//	}
//
//------------------------------------------------------------
en_PACKET_SS_MONITOR_LOGIN,

//------------------------------------------------------------
// ������ ����͸������� ������ ����
// �� ������ �ڽ��� ����͸����� ��ġ�� 1�ʸ��� ����͸� ������ ����.
//
// ������ �ٿ� �� ��Ÿ ������ ����͸� �����Ͱ� ���޵��� ���ҋ��� ����Ͽ� TimeStamp �� �����Ѵ�.
// �̴� ����͸� Ŭ���̾�Ʈ���� ���,�� ����Ѵ�.
// 
//	{
//		WORD	Type
//
//		BYTE	DataType				// ����͸� ������ Type �ϴ� Define ��.
//		int		DataValue				// �ش� ������ ��ġ.
//		int		TimeStamp				// �ش� �����͸� ���� �ð� TIMESTAMP  (time() �Լ�)
//										// ���� time �Լ��� time_t Ÿ�Ժ����̳� 64bit �� ���񽺷����
//										// int �� ĳ�����Ͽ� ����. �׷��� 2038�� ������ ��밡��
//	}
//
//------------------------------------------------------------
en_PACKET_SS_MONITOR_DATA_UPDATE,
};


//#endif



enum en_PACKET_SS_MONITOR_DATA_UPDATE
{
	dfMONITOR_DATA_TYPE_LOGIN_SERVER_RUN = 1,		// �α��μ��� ���࿩�� ON / OFF
	dfMONITOR_DATA_TYPE_LOGIN_SERVER_CPU = 2,		// �α��μ��� CPU ����
	dfMONITOR_DATA_TYPE_LOGIN_SERVER_MEM = 3,		// �α��μ��� �޸� ��� MByte
	dfMONITOR_DATA_TYPE_LOGIN_SESSION = 4,		// �α��μ��� ���� �� (���ؼ� ��)
	dfMONITOR_DATA_TYPE_LOGIN_AUTH_TPS = 5,		// �α��μ��� ���� ó�� �ʴ� Ƚ��
	dfMONITOR_DATA_TYPE_LOGIN_PACKET_POOL = 6,		// �α��μ��� ��ŶǮ ��뷮


	dfMONITOR_DATA_TYPE_GAME_SERVER_RUN = 10,		// GameServer ���� ���� ON / OFF
	dfMONITOR_DATA_TYPE_GAME_SERVER_CPU = 11,		// GameServer CPU ����
	dfMONITOR_DATA_TYPE_GAME_SERVER_MEM = 12,		// GameServer �޸� ��� MByte
	dfMONITOR_DATA_TYPE_GAME_SESSION = 13,		// ���Ӽ��� ���� �� (���ؼ� ��)
	dfMONITOR_DATA_TYPE_GAME_AUTH_PLAYER = 14,		// ���Ӽ��� AUTH MODE �÷��̾� ��
	dfMONITOR_DATA_TYPE_GAME_GAME_PLAYER = 15,		// ���Ӽ��� GAME MODE �÷��̾� ��
	dfMONITOR_DATA_TYPE_GAME_ACCEPT_TPS = 16,		// ���Ӽ��� Accept ó�� �ʴ� Ƚ��
	dfMONITOR_DATA_TYPE_GAME_PACKET_RECV_TPS = 17,		// ���Ӽ��� ��Ŷó�� �ʴ� Ƚ��
	dfMONITOR_DATA_TYPE_GAME_PACKET_SEND_TPS = 18,		// ���Ӽ��� ��Ŷ ������ �ʴ� �Ϸ� Ƚ��
	dfMONITOR_DATA_TYPE_GAME_DB_WRITE_TPS = 19,		// ���Ӽ��� DB ���� �޽��� �ʴ� ó�� Ƚ��
	dfMONITOR_DATA_TYPE_GAME_DB_WRITE_MSG = 20,		// ���Ӽ��� DB ���� �޽��� ť ���� (���� ��)
	dfMONITOR_DATA_TYPE_GAME_AUTH_THREAD_FPS = 21,		// ���Ӽ��� AUTH ������ �ʴ� ������ �� (���� ��)
	dfMONITOR_DATA_TYPE_GAME_GAME_THREAD_FPS = 22,		// ���Ӽ��� GAME ������ �ʴ� ������ �� (���� ��)
	dfMONITOR_DATA_TYPE_GAME_PACKET_POOL = 23,		// ���Ӽ��� ��ŶǮ ��뷮

	dfMONITOR_DATA_TYPE_CHAT_SERVER_RUN = 30,		// ������Ʈ ChatServer ���� ���� ON / OFF
	dfMONITOR_DATA_TYPE_CHAT_SERVER_CPU = 31,		// ������Ʈ ChatServer CPU ����
	dfMONITOR_DATA_TYPE_CHAT_SERVER_MEM = 32,		// ������Ʈ ChatServer �޸� ��� MByte
	dfMONITOR_DATA_TYPE_CHAT_SESSION = 33,		// ä�ü��� ���� �� (���ؼ� ��)
	dfMONITOR_DATA_TYPE_CHAT_PLAYER = 34,		// ä�ü��� �������� ����� �� (���� ������)
	dfMONITOR_DATA_TYPE_CHAT_UPDATE_TPS = 35,		// ä�ü��� UPDATE ������ �ʴ� �ʸ� Ƚ��
	dfMONITOR_DATA_TYPE_CHAT_PACKET_POOL = 36,		// ä�ü��� ��ŶǮ ��뷮
	dfMONITOR_DATA_TYPE_CHAT_UPDATEMSG_POOL = 37,		// ä�ü��� UPDATE MSG Ǯ ��뷮
	dfMONITOR_DATA_TYPE_CHAT_ACCEPT_TPS = 38,


	dfMONITOR_DATA_TYPE_MONITOR_CPU_TOTAL = 40,		// ������ǻ�� CPU ��ü ����
	dfMONITOR_DATA_TYPE_MONITOR_NONPAGED_MEMORY = 41,		// ������ǻ�� �������� �޸� MByte
	dfMONITOR_DATA_TYPE_MONITOR_NETWORK_RECV = 42,		// ������ǻ�� ��Ʈ��ũ ���ŷ� KByte
	dfMONITOR_DATA_TYPE_MONITOR_NETWORK_SEND = 43,		// ������ǻ�� ��Ʈ��ũ �۽ŷ� KByte
	dfMONITOR_DATA_TYPE_MONITOR_AVAILABLE_MEMORY = 44,		// ������ǻ�� ��밡�� �޸�
};

//#endif