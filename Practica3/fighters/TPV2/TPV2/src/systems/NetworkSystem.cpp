// This file is part of the course TPV2@UCM - Samir Genaim

#include "NetworkSystem.h"

#include <iostream>

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Vector2D.h"
#include "GameCtrlSystem.h"
#include "network_messages.h"
#include "FightersSystem.h"
#include "BulletsSystem.h"

NetworkSystem::NetworkSystem() :
		host_(false), //
		side_(0), //
		sock_(), //
		p_(), //
		sockSet_(), //
		port_(), //
		connected_(false), //
		otherPlayerAddr_() {

}

NetworkSystem::~NetworkSystem() {
	if (p_ != nullptr) {
		SDLNet_UDP_Close(sock_);
		SDLNet_FreePacket(p_);
	}
}

void NetworkSystem::recieve(const Message &m) {
	if (!host_)
		return;

	switch (m.id) {
	case _m_GAME_OVER:
		
		break;
	case _m_GAME_START:
		tellOtherClientToStartGame();
		break;
	case _m_BULLET_HIT_FIGHTER:
		
		break;
	default:
		break;
	}
}

void NetworkSystem::initSystem() {
}

bool NetworkSystem::connect() {

	char choice;
	bool done = false;
	bool success = false;

	while (!done) {
		std::cout << "Do you want to be host, client or exit [h/c/e]? "
				<< std::endl;
		std::cin >> choice;
		switch (choice) {
		case 'h':
		case 'H':
			success = initHost();
			done = true;
			break;
		case 'c':
		case 'C':
			success = initClient();
			done = true;
			break;
		case 'e':
		case 'E':
			done = true;
			break;
		default:
			break;
		}
	}

	return success;
}

void NetworkSystem::disconnect() {
	if (!connected_)
		return;

	net::Message m;

	m.id = net::_DISCONNECTING;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_);

}

void NetworkSystem::update() {
	net::Message m;
	while (SDLNetUtils::deserializedReceive(m, p_, sock_) > 0) {
		switch (m.id) {
		case net::_CONNECTION_REQUEST:
			handleConnectionRequest();
			break;
		case net::_FIGHTER_POS:
			handleFighterPos();
		case net::_FIGHTER_VEL:
			handleFighterPos();
			break;
		case net::_CREATE_BULLET:
			handleCreateBullet();
			break;
		case net::_START_GAME_REQUEST:
			handleStartGameRequest();
			break;
		case net::_START_THE_GAME:
			handleStartTheGame();
			break;
		case net::_GAME_OVER_REQUEST:
			handleGameOverRequest();
			break;
		case net::_GAME_OVER:
			handleGameOver();
			break;
		case net::_DISCONNECTING:
			handleDisconnecting();
			break;
		default:
			break;
		}

	}

}

bool NetworkSystem::initConnection(Uint16 port) {
	sock_ = SDLNet_UDP_Open(port);
	if (!sock_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	sockSet_ = SDLNet_AllocSocketSet(1);
	if (!sockSet_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	SDLNet_UDP_AddSocket(sockSet_, sock_);
	p_ = SDLNet_AllocPacket(512);
	if (!p_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	port_ = SDLNetUtils::getSocketPort(sock_);

	return true;
}

bool NetworkSystem::initHost() {

	Uint16 port;
	std::cout << "Enter a port number to use: ";
	if (!(std::cin >> port)) {
		std::cerr << "Invalid port" << std::endl;
		return false;
	}

	if (!initConnection(port))
		return false;

	host_ = true;
	side_ = 0;
	connected_ = false;
	return true;

}

bool NetworkSystem::initClient() {

	Uint16 port;
	std::string host;

	std::cout << "Enter the host and port (separated by space) of the host: "
			<< std::endl;
	if (!(std::cin >> host >> port)) {
		std::cerr << "Invalid host/port" << std::endl;
		return false;
	}

	if (SDLNet_ResolveHost(&otherPlayerAddr_, host.c_str(), port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	host_ = false;

	initConnection(0);

	net::Message m;

	m.id = net::_CONNECTION_REQUEST;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_);

	if (SDLNet_CheckSockets(sockSet_, 3000) > 0) {
		if (SDLNet_SocketReady(sock_)) {
			SDLNetUtils::deserializedReceive(m, p_, sock_);
			if (m.id == net::_REQUEST_ACCEPTED) {
				net::ReqAccMsg m;
				m.deserialize(p_->data);
				side_ = m.side;
				host_ = false;
				connected_ = true;
			}

		}
	}

	if (!connected_) {
		std::cout << "Could not connect to the other player " << std::endl;
		return false;
	}

	return true;

}

void NetworkSystem::sendFighterPosition(Transform *tr) {
	if (!connected_)
		return;

	net::FighterPosMsg m;
	m.id = net::_FIGHTER_POS;
	m.side = side_;
	m.x = tr->pos_.getX();
	m.y = tr->pos_.getY();
	m.rot = tr->rot_;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}

void NetworkSystem::sendNewBullet(float posX, float posY, float rot, float velX, float velY)
{
	if (!connected_)
		return;

	net::BulletCreationMsg m;
	m.id = net::_CREATE_BULLET;
	m.side = side_;
	m.posX = posX;
	m.posY = posY;
	m.rot = rot;
	m.velX = velX;
	m.velY = velY;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}

void NetworkSystem::handleConnectionRequest() {

	if (!connected_ && host_) {
		otherPlayerAddr_ = p_->address;
		connected_ = true;
		net::ReqAccMsg m;
		m.id = net::_REQUEST_ACCEPTED;
		m.side = 1 - side_;
		SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
	}
}

void NetworkSystem::sendStarGameRequest() {
	assert(!isHost());

	net::StartRequestMsg m;

	m.id = net::_START_GAME_REQUEST;
	m.side = side_;
	p_->address = otherPlayerAddr_;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);

}

void NetworkSystem::handleFighterPos() {
	net::FighterPosMsg m;
	m.deserialize(p_->data);
	mngr_->getSystem<FightersSystem>()->setOtherFighterPos(m.x, m.y, m.rot);
}

void NetworkSystem::handleFighterVel()
{
}

void NetworkSystem::handleCreateBullet() {
	net::BulletCreationMsg m;
	m.deserialize(p_->data);
	mngr_->getSystem<BulletsSystem>()->createNewBullet(m.posX, m.posY, m.rot, m.velX, m.velY);
}

void NetworkSystem::handleStartGameRequest() {
	Message m;

	m.id = _m_GAME_START;

	mngr_->send(m);
}

void NetworkSystem::handleStartTheGame() {
	assert(!host_);
	Message m;

	m.id = _m_GAME_START;

	mngr_->send(m);
}

void NetworkSystem::handleGameOver() {
	assert(!host_);
	Message m;

	m.id = _m_GAME_OVER;

	mngr_->send(m);
}

void NetworkSystem::handleGameOverRequest()
{
}

void NetworkSystem::handleDisconnecting() {
	connected_ = false;
	host_ = true;
	//mngr_->getSystem<GameCtrlSystem>()->stopTheGame();
}

void NetworkSystem::tellOtherClientToStartGame() {
	net::Message m;

	m.id = net::_START_THE_GAME;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);
}

void NetworkSystem::tellOtherClientBulletHitFighter(Uint8 winner) {
	net::BulletHitFighterMsg m;

	m.id = net::_BULLET_HIT_FIGHTER;
	m.winner = winner;
	SDLNetUtils::serializedSend(m, p_, sock_, otherPlayerAddr_);

}

