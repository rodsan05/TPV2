// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>
#include <vector>
#include <string>

#include "../ecs/System.h"

struct Transform;

class NetworkSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_NETWORK)

	NetworkSystem();
	virtual ~NetworkSystem();

	void recieve(const Message&) override;
	void initSystem() override;
	void update() override;

	bool connect();
	void disconnect();

	inline Uint8 getSide() {
		return side_;
	}

	inline bool isReday() {
		return connected_;
	}

	inline bool isHost() {
		return host_;
	}

	inline Uint16 getPort() {
		return port_;
	}

	void sendFighterPosition(Transform *tr);
	void sendNewBullet(float posX, float posY, float rot, float velX, float velY);
	void sendStarGameRequest();

	std::string getName(int nameId);

private:

	bool initHost();
	bool initClient();
	bool initConnection(Uint16 port);

	void handleConnectionRequest();
	void handleFighterPos();
	void handleFighterVel();
	void handleCreateBullet();
	void handleStartGameRequest();
	void handleStartTheGame();
	void handleBulletHitFighter();
	void handleDisconnecting();

	void tellOtherClientToStartGame();
	void tellOtherClientBulletHitFighter(Uint8 side);

	void string_to_chars(std::string& str, char c_str[11]);

	void chars_to_string(std::string& str, char c_str[11]);

	bool host_;
	Uint8 side_; // 0 left 1 right
	UDPsocket sock_;
	UDPpacket *p_;
	SDLNet_SocketSet sockSet_;
	Uint16 port_;

	std::vector<std::string> names_;
	std::string currName_;

	bool connected_;
	IPaddress otherPlayerAddr_;

};