#include "stdafx.h"

#include "MyBattleship.h"
#include <string>
#include <map>
#include <set>
#include <list>
#include <assert.h>
#include <vector>
#include <assert.h>

//
// utility macros for param checks
//

#ifndef BATTLESHIP_LOG_HACK_ATTEMPT
#define BATTLESHIP_LOG_HACK_ATTEMPT(player_index, msg)   LogHacker(player_index, msg, __func__, __FILE__, __LINE__)
#endif //BATTLESHIP_LOG_HACK_ATTEMPT

#ifndef VALIDATE_CURRENT_GAMESTATE_RETURNS
#define VALIDATE_CURRENT_GAMESTATE_RETURNS(requiredGameState, player_index, returns)  \
	if (m_gameState != requiredGameState) { \
		LogHacker(player_index, "Wrong GameState", __func__, __FILE__, __LINE__); \
		return returns; \
	}
#endif //VALIDATE_CURRENT_GAMESTATE_RETURNS

#ifndef VALIDATE_PLAYER_INDEX_RETURNS
#define VALIDATE_PLAYER_INDEX_RETURNS(player_index, returns) \
	if (!IsValidPlayer(player_index)) { \
		LogHacker(player_index, "bad player index", __func__, __FILE__, __LINE__); \
		return returns; \
	}
#endif // VALIDATE_PLAYER_INDEX_RETURNS

#ifndef VALIDATE_PLAYER_TURN_RETURNS
#define VALIDATE_PLAYER_TURN_RETURNS(player_index, returns) \
	if (!IsPlayerTurn(player_index)) {\
		LogHacker(player_index, "not this players turn", __func__, __FILE__, __LINE__); \
		return returns; \
	}
#endif //VALIDATE_PLAYER_TURN_RETURNS

namespace Battleship {

struct BoatDefinition
{
	BoatType    m_boat;
	size_t      m_size;
	std::string m_name; // LOCALIZATION TODO: replace with a DB ID
};

static BoatDefinition s_boatDefs[NUM_BOATS] = {
	{ boatAircraftCarrier, 5, "Aircraft Carrier" },
	{ boatBattleship,      4, "Battleship" },
	{ boatSubmarine,       3, "Submarine" },
	{ boatDestroyer,       3, "Destroyer" },
	{ boatPatrolBoat,      2, "Submarine" },
	{ boatJetSki,          1, "JetSki" },
};

bool IsLocationOnMap(const Point &loc, int fieldSize)
{
	return (loc.x >= 0 && loc.x < fieldSize && loc.y >= 0 && loc.y < fieldSize);
}

bool IsValidBoat(BoatType boat)
{
	return ((int)boat >= FIRST_BOAT && boat < NUM_BOATS);
}

// Get all the points for a boat
bool ExpandLocationPoints(BoatType boat, Point startLoc, Direction direction, int enforcedFieldSize, LocactionArray &points)
{
	if (!IsValidBoat(boat))
	{
		assert(!"Bad boat type");
		return false;
	}

	points.reserve(s_boatDefs[boat].m_size);
	points.resize(0);

	Point pin = startLoc;

	for (int offset = 0; offset < s_boatDefs[boat].m_size; offset++)
	{
		switch (direction)
		{
		case Direction::Up:
			pin.x = startLoc.x;
			pin.y = startLoc.y - offset;
			break;

		case Direction::Right:
			pin.x = startLoc.x + offset;
			pin.y = startLoc.y;
			break;

		case Direction::Down:
			pin.x = startLoc.x;
			pin.y = startLoc.y + offset;
			break;

		case Direction::Left:
			pin.x = startLoc.x - offset;
			pin.y = startLoc.y;
			break;

		default:
			assert(!"missed something");
		}

		if (enforcedFieldSize > 0 && !IsLocationOnMap(pin, enforcedFieldSize))
		{
			return false;
		}

		points.push_back(pin);
	}
	return true;
}

Point::Point(size_t x, size_t y)
	: x(x)
	, y(y)
{
}

Point::Point(const Point &copy)
	: x(copy.x)
	, y(copy.y)
{
}

bool Point::operator<(const Point &other) const
{
	if (x < other.x)
	{
		return true;
	}
	else if (x == other.x && y < other.y)
	{
		return true;
	}
	return false;
}

MyBoat::MyBoat(const MyBoat &copy)
	: m_type(copy.m_type)
	, m_health(copy.m_health)
	, m_locs(copy.m_locs)
{}

MyBoat& MyBoat::operator=(const MyBoat& copy)
{
	m_type = copy.m_type;
	m_health = copy.m_health;
	m_locs = copy.m_locs;
	return *this;
}

MyBoat::MyBoat() 
{
	Init(INVALID_BOAT, Point(-1,-1), Direction::Right);
}

MyBoat::MyBoat(BoatType boatType, Point startLoc, Direction direction)
{
	Init(boatType, startLoc, direction);
}

void MyBoat::Init(BoatType boatType, Point startLoc, Direction direction)
{
	m_type = boatType;
	m_health = 0;
	m_locs.clear();

	if (boatType >= 0 && boatType < NUM_BOATS)
	{
		LocactionArray locations;
		ExpandLocationPoints(boatType, startLoc, direction, FIELD_SIZE, locations);

		for (size_t i = 0; i < locations.size(); i++)
		{
			m_locs[locations[i]] = HitState::BoatSection;
			m_health++;
		}
	}
}

bool MyBoat::IsIntersecting(const MyBoat &other) const
{
	for (auto it = m_locs.begin(); it != m_locs.end(); it++)
	{
		if (other.m_locs.find(it->first) != other.m_locs.end())
		{
			return true;
		}
	}
	return false;
}

bool MyBoat::IsFloating() const
{
	return m_health > 0;
}

HitState MyBoat::HitTest(Point loc) const
{
	auto it = m_locs.find(loc);
	if (it == m_locs.end())
	{
		return HitState::Missed;
	}
	return it->second;
}

HitState MyBoat::AttackBoat(Point loc)
{
	auto it = m_locs.find(loc);
	if (it == m_locs.end())
	{
		return HitState::Missed;
	}

	switch (it->second)
	{
	case HitState::BoatSection:
		assert(m_health > 0);
		it->second = HitState::BurningBoat;
		m_health--;
		return HitState::BurningBoat;

	case HitState::BurningBoat:
		// that did nothing except waste a turn
		return HitState::BurningBoat;

	case HitState::EmptyWater:
	case HitState::Missed:
		assert(!"boat is in an invalid state!");
		break;

	default:
		assert(!"I seem to be missing something");
	}

	return HitState::Missed;
}

bool Game::IsValidPlayer(PlayerIndex playerIdx) const
{
	return (int)playerIdx >= 0 && playerIdx < NUM_PLAYERS;
}

bool Game::IsPlayerTurn(PlayerIndex playerIdx) const
{
	if (!IsValidPlayer(playerIdx))
		return false;

	if (m_gameState == GameState::LaunchMissles && m_turn == playerIdx)
		return true;

	if (m_gameState == GameState::BoatDeployment)
		return true;

	return false;
}

PlayerIndex Game::PlayerJoin(const std::string &name)
{
	VALIDATE_CURRENT_GAMESTATE_RETURNS(WaitingForPlayers, INVALID_PLAYER, INVALID_PLAYER);

	if (name.empty())
	{
		BATTLESHIP_LOG_HACK_ATTEMPT(PlayerIndex::INVALID_PLAYER, "invalid name");
		return PlayerIndex::INVALID_PLAYER;
	}

	for (int index = 0; index < NUM_PLAYERS; index++)
	{
		if (m_player[index].m_name.empty())
		{
			// free slot
			m_player[index].m_name = name;

			// change the state?
			if (index == NUM_PLAYERS - 1)
			{
				StateChange(BoatDeployment);
			}

			return (PlayerIndex)index;
		}
	}

	assert(!"should be unreachable");
	return INVALID_PLAYER;
}

bool Game::DeployShip(PlayerIndex playerIdx, BoatType boatType, Point loc, Direction direction)
{
	// Validate params
	VALIDATE_CURRENT_GAMESTATE_RETURNS(BoatDeployment, playerIdx, false);
	VALIDATE_PLAYER_INDEX_RETURNS(playerIdx, false);
	VALIDATE_PLAYER_TURN_RETURNS(playerIdx, false);

	// UGH! Got to rename this 
	PlayerData &player = m_player[playerIdx];

	// Have they marked themseves as ready?  We don't want cheaters sneaking in boats last minute
	if (player.m_ready)
	{
		BATTLESHIP_LOG_HACK_ATTEMPT(playerIdx, "Player attempted to deploy a boat AFTER they marked themselves as ready");
		return false;
	}

	// Has this ship already been deployed?
	if (player.m_deployedBoats.find(boatType) != player.m_deployedBoats.end())
	{
		BATTLESHIP_LOG_HACK_ATTEMPT(playerIdx, "That boat has already sailed");
		return false;
	}

	// Make a new boat
	MyBoat newBoat(boatType, loc, direction);

	// Before we place it, ensure there is no overlap
	for (auto it = player.m_deployedBoats.begin(); it != player.m_deployedBoats.end(); it++)
	{
		if (it->second.IsIntersecting(newBoat))
		{
			BATTLESHIP_LOG_HACK_ATTEMPT(playerIdx, "The ClientUI should have blocked this");
			return false;
		}
	}

	player.m_deployedBoats[boatType] = newBoat;

	return true;
}

bool Game::SetPlayerReady(PlayerIndex playerIdx, bool ready)
{
	VALIDATE_CURRENT_GAMESTATE_RETURNS(BoatDeployment, playerIdx, false);
	VALIDATE_PLAYER_INDEX_RETURNS(playerIdx, false);
	VALIDATE_PLAYER_TURN_RETURNS(playerIdx, false);

	m_player[playerIdx].m_ready = ready;

	// Once all players have readied up, switch the game state
	int readyCount = 0;
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (m_player[i].m_ready)
		{
			readyCount++;
		}
	}
	if (readyCount == NUM_PLAYERS)
	{
		StateChange(LaunchMissles);
	}

	return true;
}

bool Game::FireMissile(PlayerIndex playerIdx, Point loc, HitState &hitResult, bool &sinkResult)
{
	hitResult = HitState::EmptyWater;
	sinkResult = false;

	// Validate params
	VALIDATE_CURRENT_GAMESTATE_RETURNS(LaunchMissles, playerIdx, false);
	VALIDATE_PLAYER_INDEX_RETURNS(playerIdx, false);
	VALIDATE_PLAYER_TURN_RETURNS(playerIdx, false);

	if (!IsLocationOnMap(loc, FIELD_SIZE))
	{
		BATTLESHIP_LOG_HACK_ATTEMPT(playerIdx, "Point is not on the map");
		return false;
	}

	//
	// Launch the missle!
	//
	PlayerData &playerSend = m_player[playerIdx];
	PlayerData &playerDest = m_player[playerIdx==Player0?Player1:Player0];

	for (auto it = playerDest.m_deployedBoats.begin(); it != playerDest.m_deployedBoats.end(); it++)
	{
		switch (it->second.AttackBoat(loc))
		{
		case HitState::BoatSection:
			assert(!"unreachable?");
			break;

		case HitState::EmptyWater:
			break;

		case HitState::BurningBoat:
			playerSend.m_attackedTargets[loc] = HitState::BurningBoat;
			sinkResult = (it->second.m_health == 0);
			return true;
			break;

		case HitState::Missed:
			break;

		default:
			assert(!"missing 'case'");
		}
	}

	return true;
}

void Game::StateChange(GameState newState)
{
	// validates state change
	bool validChange = false;
	switch (m_gameState)
	{
	case WaitingForPlayers:
		validChange = (newState == BoatDeployment);
		m_turn = INVALID_PLAYER;
		break;
	case BoatDeployment:
		validChange = (newState == LaunchMissles);
		m_turn = Player0;
		break;
	case LaunchMissles:
		validChange = (newState == GameOver);
		m_turn = INVALID_PLAYER;
		break;
	case GameOver:
		validChange = (newState == WaitingForPlayers);
		m_turn = INVALID_PLAYER;
		break;
	default: 
		assert(!"missing handler");
	}

	assert(validChange);
	if (validChange)
	{
		m_gameState = newState;
	}
}

}; // namespace Battleship


void MyBattleship_UnitTest()
{
	printf("\nTESTING MyBattleship\n");

	Battleship::Game game;

	Battleship::PlayerIndex joe = game.PlayerJoin("Joe");
	Battleship::PlayerIndex bob = game.PlayerJoin("Bob");
	Battleship::PlayerIndex tom = game.PlayerJoin("Tom");

	assert(joe >= 0 && "Joe should have a valid ID");
	assert(bob >= 0 && "Bob should have a valid ID");
	assert(tom < 0 && "Tom was late to the party and shouldn't have recvd and ID as the game is full");

	struct DeploymentData {
		Battleship::BoatType boat;
		Battleship::Point loc;
		Battleship::Direction direction;
		bool expected_result;
	};

	DeploymentData deploy[] = {
		{ Battleship::BoatType::boatJetSki, Battleship::Point(0,0), Battleship::Direction::Right, true },
		{ Battleship::BoatType::boatJetSki, Battleship::Point(0,0), Battleship::Direction::Right, false },
	};

	bool result;

	for (auto data : deploy)
	{
		result = game.DeployShip(joe, data.boat, data.loc, data.direction);
		assert(result == data.expected_result);

		result = game.DeployShip(bob, data.boat, data.loc, data.direction);
		assert(result == data.expected_result);
	}

	game.SetPlayerReady(joe, true);
	game.SetPlayerReady(joe, false);
	game.SetPlayerReady(joe, true);
	game.SetPlayerReady(bob, true);
	game.SetPlayerReady(tom, false);

	Battleship::HitState hitResult;
	bool sinkResult;
	game.FireMissile(joe, Battleship::Point(0, 0), hitResult, sinkResult);
	game.FireMissile(bob, Battleship::Point(0, 0), hitResult, sinkResult);
	game.FireMissile(tom, Battleship::Point(0, 0), hitResult, sinkResult);
	
	printf("\nTESTING MyBattleship COMPLETE\n");
}

