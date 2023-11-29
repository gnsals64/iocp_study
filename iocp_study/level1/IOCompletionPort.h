#pragma once
#pragma comment(lib, "ws2_32")

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <thread>
#include <vector>
#include <iostream>

#define MAX_SOCKBUF 1024
#define MAX_WORKERTHREAD 4



enum class IOOperation {
	RECV,
	SEND
};

struct stOverlappedEx {
	WSAOVERLAPPED	m_wsaOverlapped;
	SOCKET			m_socketClient;
	WSABUF			m_wsaBuf;
	char			m_szBuf[ MAX_SOCKBUF ];
	IOOperation		m_eOperation;
};

struct stClientInfo {
	SOCKET			m_socketClient;
	stOverlappedEx	m_stRecvOverlappedEx;
	stOverlappedEx	m_stSendOverlappedEx;

	stClientInfo() {
		ZeroMemory( &m_stRecvOverlappedEx, sizeof( stOverlappedEx ));
		ZeroMemory( &m_stSendOverlappedEx, sizeof( stOverlappedEx ));
		m_socketClient = INVALID_SOCKET;
	}
};

class IOCompletionPort {
public:
	IOCompletionPort() {}
	~IOCompletionPort() {
		WSACleanup();
	}


	bool InitSocket() {
		WSADATA wsaData;

		int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (nRet != 0) {
			std::cerr << "[ERROR]fail to WSAStartup() : " << WSAGetLastError() << std::endl;
			return false;
		}

		mListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);
		if (mListenSocket == INVALID_SOCKET) {
			std::cerr << "[ERROR]fail to WSAsockect() : " << WSAGetLastError() << std::endl;
		}

		std::cout << "success init sock" << std::endl;
		return true;
	}

	bool BindandListen(int nBindPort) {
		SOCKADDR_IN		stServerAddr;

		stServerAddr.sin_family = AF_INET;
		stServerAddr.sin_port = htons(nBindPort);
		stServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

		int nRet = bind(mListenSocket, (SOCKADDR*)&stServerAddr, sizeof(SOCKADDR_IN));
		if (nRet != 0) {
			std::cerr << "[ERROR] fail to bind() : " << WSAGetLastError() << std::endl;
			return false;
		}
		//listen backlog : 연결되지않은 요청을 큐에 넣을 수 있는 최대 큐의 길이 큐가 가득차면 에러
		nRet = listen(mListenSocket, 5);
		if (nRet != 0) {
			std::cerr << "[ERROR] fail to listen() : " << WSAGetLastError() << std::endl;
			return false;
		}
		std::cout << "Server registration successful" << std::endl;
		return true;
	}

	bool StartServer(const UINT32 maxClientCount) {
		C
	}

private:
	void	CreateClient(const UINT32 maxClientCount) {
		for (UINT32 i = 0; i < maxClientCount; ++i) {
			mClientInfos.emplace_back();
		}
	}
};


SOCKET		mListenSocket = INVALID_SOCKET;

std::vector<stClientInfo> mClientInfos;