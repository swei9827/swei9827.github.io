#include "MyPhoton.h"
#include <iostream>

static const ExitGames::Common::JString appId = L"7bb7f254-41d5-41bd-9bad-e758b9911186"; // set your app id here
static const ExitGames::Common::JString appVersion = L"1.0";
static const ExitGames::Common::JString PLAYER_NAME = L"Windows";

//LoadBalancing::Listener& listener, const Common::JString& applicationID, 
//const Common::JString& appVersion, nByte connectionProtocol=Photon::ConnectionProtocol::DEFAULT, bool autoLobbyStats=false, nByte regionSelectionMode=RegionSelectionMode::DEFAULT

// functions
MyPhoton::MyPhoton() : mLoadBalancingClient(*this, appId, appVersion, ExitGames::Photon::ConnectionProtocol::TCP, false, ExitGames::LoadBalancing::RegionSelectionMode::SELECT)
{
}

void MyPhoton::run(void)
{
	srand(time(NULL));
	mLoadBalancingClient.service();
}

void MyPhoton::connect(void)
{
	roll = rand() % 1000 + 1;
	std::wcout << "Connecting..." << std::endl;
	mLoadBalancingClient.connect(ExitGames::LoadBalancing::AuthenticationValues(), PLAYER_NAME);
}

void MyPhoton::disconnect(void)
{
	mLoadBalancingClient.disconnect();
}

void MyPhoton::startingPlayer()
{
	float passcode = 1234.0f;

	float data[2] = { passcode , float(roll)};
	mLoadBalancingClient.opRaiseEvent(true, data, 2, 1);
}

void MyPhoton::sendMyData(float grid[])
{
	canMove = false;
	for (int i = 0; i < 9; i++)
	{
		ttt.grid[i] = grid[i];
	}
	mLoadBalancingClient.opRaiseEvent(true, grid, 9, 1);

} 

// protocol implementations

void MyPhoton::debugReturn(int debugLevel, const ExitGames::Common::JString& string)
{
}

void MyPhoton::connectionErrorReturn(int errorCode)
{
	std::wcout << "connectionErrorReturn : " << errorCode << std::endl;
}

void MyPhoton::clientErrorReturn(int errorCode)
{
	std::wcout << "clientErrorReturn : " << errorCode << std::endl;
}

void MyPhoton::warningReturn(int warningCode)
{
	std::wcout << "warningReturn : " << warningCode << std::endl;
}

void MyPhoton::serverErrorReturn(int errorCode)
{
	std::wcout << "serverErrorReturn : " << errorCode << std::endl;
}

void MyPhoton::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
{
	std::wcout << "joinRoomEventAction" << std::endl;

	if (playernrs.getSize() >= 2)
	{
		startingPlayer();
	}

	/*if (mLoadBalancingClient.getLocalPlayer().getIsMasterClient())
	{
		isMaster = true;
		canMove = true;
	}*/
}

void MyPhoton::leaveRoomEventAction(int playerNr, bool isInactive)
{
	std::wcout << "leaveRoomEventAction" << std::endl;
}

void MyPhoton::customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
{
	float* data = ExitGames::Common::ValueObject<float*>(eventContent).getDataCopy();
	
	if (data && data[0] == 1234.0f)
	{
		std::cout << "My Roll : " << roll << "     His/Her Roll : " << data[1] << std::endl;
		if (roll > data[1])
		{
			std::cout << "You First" << std::endl;
			isFirst = true;
			canMove = true;
		}
		else
		{
			std::cout << "He/She First" << std::endl;
			/*isFirst = false;
			canMove = false;*/
		}
	}
	else if (data && data[0] != 1234.0f)
	{
		for (int i = 0; i < 9; i++)
		{
			ttt.grid[i] = data[i];
		}
		canMove = true;
	}
	else
		std::cout << "invalid data" << std::endl;
}

void MyPhoton::connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& cluster)
{
	if (errorCode)
		std::wcout << "Failed to connect : " << errorString.cstr() << std::endl;
	else
	{
		std::wcout << "Connected to Photon Server." << std::endl;

		std::wcout << "Trying to join a random room..." << std::endl;
		mLoadBalancingClient.opJoinRandomRoom();
	}
}

void MyPhoton::disconnectReturn(void)
{
	std::wcout << "disconnected" << std::endl;
}

void MyPhoton::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout << "createRoomReturn" << std::endl;
}

void MyPhoton::joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout << "joinOrCreateRoomReturn" << std::endl;
}

void MyPhoton::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout << "joinRoomReturn" << std::endl;
}

void MyPhoton::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout << "joinRandomRoomReturn" << std::endl;

	if (errorCode)
	{
		std::wcout << "Failed to join a random room : " << errorCode << ", " << errorString.cstr() << std::endl;

		if (errorCode == 32760) //no match found error code
		{
			std::wcout << "Creating a room..." << std::endl;
			//try to create a room and wait;
			ExitGames::Common::JString name;
			name += GETTIMEMS();
			mLoadBalancingClient.opCreateRoom(name, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(2));
		}

		return;
	}
}

void MyPhoton::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout << "leaveRoomReturn" << std::endl;
}

void MyPhoton::joinLobbyReturn(void)
{
	std::wcout << "joinLobbyReturn" << std::endl;
}

void MyPhoton::leaveLobbyReturn(void)
{
	std::wcout << "leaveLobbyReturn" << std::endl;
}

void MyPhoton::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	std::wcout << "onLobbyStatsResponse" << std::endl;
}

void MyPhoton::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	std::wcout << "onLobbyStatsUpdate" << std::endl;
}

void MyPhoton::onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers)
{
	//std::wcout<<availableRegions[0]<<std::endl;
	//std::wcout<<availableRegions[1]<<std::endl;
	//mLoadBalancingClient.selectRegion(availableRegions[0]);
	mLoadBalancingClient.selectRegion("asia");
}
