//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#include <iostream>
#include <string>

#include "AnimalCardFactory.h"
#include "Deck.h"
#include "Player.h"
#include "Table.h"

using namespace std;



int main() {
	
	Deck<AnimalCard> deck;
	Table table;
	Player * players [5];
	int numPlayers;
	bool playing;
	
	{ // Setup
		deck = AnimalCardFactory::getFactory()->getDeck();
		table = Table();
		playing = true;
		players[0] = new Player("PlayerOne", Animal::BEAR);
		players[1] = new Player("PlayerTwo", Animal::DEER);
		numPlayers = 2;
		for (int i = 0; i < numPlayers && playing; i++) {
			Player * player = players[i];
			player->getHand() += deck.draw();
			player->getHand() += deck.draw();
			player->getHand() += deck.draw();
		}
	}
	
	while (playing) {
		// Check for Pause.
		for (int i = 0; i < numPlayers && playing; i++) {
			Player * player = players[i];
			cout << player->getName() << "'s Turn!" << endl;
			player->getHand() += deck.draw();
			cout << endl;
			table.print();
			player->print();
			bool turnOver = true;
			do {
				try {
					// Player's Turn.
				} catch (string e) {
					turnOver = false;
				}
				// Check for win and change playing to false if someone wins.
				playing = false;
			} while (!turnOver);
		}
	}
	return 0;
}
