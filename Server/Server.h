#pragma once
#include <Windows.h>
#include <string>
#include <map>
#include <iostream>
#include <functional>

//ÿ�δ������ݵİ�ͷ
struct Header
{
	char type[20];  //���õĹ�������
	UINT64  size;   //���ݴ�С
};

class Server
{
	typedef std::function<void(PBYTE pPayload, UINT64& size)> _FUNC;  //����ע����¼�����
	typedef std::tuple<std::string, HANDLE, _FUNC> _NODE;  //ÿ���¼��ڵ�

	struct Event
	{
		std::string type;
		_FUNC func;
	};

public:
	Server();
	Server(const Server&) = delete;
	~Server() { CloseHandle(m_hMap); }

	void createShm(const std::string& mapName, size_t size);
	void appendRcvEvent(const std::string& eventName, const _FUNC& func);

	void eventLoop(const std::string& eventName);

private:

	HANDLE m_hMap;
	size_t m_mapSize;
	std::string m_eventName;
	std::map<std::string, _FUNC> m_handlers;
};