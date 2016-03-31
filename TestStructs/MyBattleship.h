#pragma once

#include <string>
#include <list>
#include <vector>
#include <map>

void MyBattleship_UnitTest();

namespace Battleship
{
	/*
		This is an overcomplicated version of BattleShip done as a thought experiment based upon an inocent interview question
		https://en.wikipedia.org/wiki/Battleship_(game)
		*MOST* of it is framework just for placeboat and firemissle
	*/

	enum BoatType
	{
		boatAircraftCarrier,
		boatBattleship,
		boatSubmarine,
		boatDestroyer,
		boatPatrolBoat,
		boatJetSki,
		NUM_BOATS,
		FIRST_BOAT = boatAircraftCarrier,
		INVALID_BOAT = -1,
	};

	enum Direction
	{
		Up, Right, Down, Left
	};

	struct Point
	{
		size_t x;
		size_t y;
		
		Point(size_t x = 0, size_t y = 0);
		Point(const Point &copy);
		bool operator<(const Point &other) const;
	};
	typedef std::vector<Point> LocactionArray;

	// Describe what is at a given Point in the ocean
	enum HitState
	{
		EmptyWater = 0,   // nothting but water
		BoatSection,      // part of a boat
		BurningBoat,      // a boat piece that was hit
		Missed,           // missle that missed
	};

	enum Extents
	{
		FIELD_SIZE = 10
	};

	enum PlayerIndex
	{
		Player0 = 0,   // Avoid confusion later on over IDs
		Player1 = 1,
		NUM_PLAYERS = 2,
		INVALID_PLAYER = -1,
	};

	struct MyBoat
	{
		BoatType m_type;
		size_t m_health;
		std::map<Point, HitState> m_locs;

		MyBoat();
		MyBoat(const MyBoat &copy);
		MyBoat& operator=(const MyBoat& copy);
		MyBoat(BoatType boatType, Point startLoc, Direction direction);

		void Init(BoatType boatType, Point startLoc, Direction direction);
		HitState HitTest(Point loc) const;
		HitState AttackBoat(Point loc);
		bool IsIntersecting(const MyBoat &other) const;
		bool IsFloating() const;
	};

	class Game
	{
	protected:
		enum GameState
		{
			WaitingForPlayers,
			BoatDeployment,
			LaunchMissles,
			GameOver,
		} m_gameState = WaitingForPlayers;

		struct PlayerData
		{
			std::string m_name;
			bool m_ready;
			std::map<BoatType, MyBoat> m_deployedBoats;
			std::map<Point, HitState> m_attackedTargets;

			PlayerData()
				: m_ready(false)
			{}
		};

		PlayerData m_player[NUM_PLAYERS];
		PlayerIndex m_turn;

		void LogHacker(PlayerIndex playerIdx, const char *message, const char *funcName, const char *fileName, int lineNumber)
		{
			// in a production environment we would track the actions
			// and have buisness logic here to handle the attack.
			// Never give immediate feedback to bad actors as that can allow
			// them to more quickly refine their strategies.
			// Until then..
			//assert(!"Hack attempt detected");
			printf("PossibleHackAttempt:{msg:%s, func:%s, file:%s, line:%d, player:%d}\n",
				message, funcName, fileName, lineNumber, playerIdx);
		}

		void StateChange(GameState newState);

	public:
		Game() 
			: m_turn(INVALID_PLAYER)
		{}

		bool IsValidPlayer(PlayerIndex playerIdx) const;
		bool IsPlayerTurn(PlayerIndex playerIdx) const;
		PlayerIndex PlayerJoin(const std::string &name);
		bool DeployShip(PlayerIndex playerIdx, BoatType boatType, Point loc, Direction direction);
		bool SetPlayerReady(PlayerIndex playerIdx, bool ready);
		bool FireMissile(PlayerIndex playerIdx, Point loc, HitState &hitResult, bool &sinkResult);
	};

}; // namespace Battleship