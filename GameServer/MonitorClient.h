#pragma once
class CMonitorClient : public CLanClient
{
public:
	//�õ��Լ� �ۼ���
	virtual void Init();
	//connect���� ȣ��
	virtual bool OnConnect();
	//message �м� ����
	virtual void OnRecv(CPacket* packet);
	//������ ��� ����(�Ƹ� ����Ȯ���� disconnect)
	virtual void OnExpt();

	virtual void OnDisconnect();

	virtual void OnError(int error, const WCHAR* msg);

	//�����Լ� �ۼ���
	virtual void OnStop();

public:
	void UpdateMonitorInfo(BYTE dataType, int value, int timeVal);

private:
	void Req_Login();
};

