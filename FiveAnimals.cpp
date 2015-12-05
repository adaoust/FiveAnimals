//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#include <iostream>
#include <string>
#include <algorithm>

#include "ActionCards.h"
#include "AnimalCardFactory.h"
#include "Deck.h"
#include "Player.h"
#include "Table.h"

using namespace std;

int main() {

	Deck<AnimalCard> deck;
	Table table;
	Player * players[5];
	int numPlayers;
	bool playing;

	{ // Setup
		deck = AnimalCardFactory::getFactory()->getDeck();
		table = Table();
		playing = true;
		numPlayers = 0;
		cout << "|---------------------------------------------|" << endl;
		cout << "|  Welcome to the awesome Five Animals Game!  |" << endl;
		cout << "|---------------------------------------------|" << endl << endl;
		bool ready = false;
		cout << "Enter the players' names (Leave empty to start game):" << endl;

		// Random Secret Animal
		vector<Animal> secretAnimals = vector<Animal>();
		secretAnimals.push_back(Animal::BEAR);
		secretAnimals.push_back(Animal::DEER);
		secretAnimals.push_back(Animal::HARE);
		secretAnimals.push_back(Animal::MOOSE);
		secretAnimals.push_back(Animal::WOLF);
		shuffle(begin(secretAnimals), end(secretAnimals), default_random_engine((int)time(0)));

		do {
			cout << " >> Name: ";
			string playerName;
			getline(cin, playerName);
			if (playerName != "") {
				bool nameValid = true;
				for (int i = 0; i < numPlayers; i++) {
					if (players[i]->getName() == playerName) nameValid = false;
				}
				if (nameValid) {
					players[numPlayers] = new Player(playerName, secretAnimals.back());
					secretAnimals.pop_back();
					numPlayers++;
				}
				else {
					cout << " >> This name is already choosen!" << endl;
				}
			}
			else {
				// Make sure all the players have different names.
				if (numPlayers < 2) cout << " >> At least 2 players are required to play!" << endl;
				else ready = true;
			}
		} while (numPlayers < 5 && !ready);
		for (int i = 0; i < numPlayers && playing; i++) {
			Player * player = players[i];
			for (int j = 0; j < 3; j++) {
				player->getHand() += deck.draw();
			}
		}
	}
	cout << endl;
	cout << "|---------------------------------------------|" << endl;
	cout << "|             Let the game begin!             |" << endl;
	cout << "|---------------------------------------------|" << endl << endl;

	while (playing) {
		// Check for Pause.
		for (int i = 0; i < numPlayers && playing; i++) {
			Player * player = players[i];
			cout << player->getName() << "'s Turn!" << endl;
			player->getHand() += deck.draw();
			cout << endl;
			table.print();
			player->print();
			cout << endl;
			bool turnOver = true;
			bool skipTurn = false;
			do {
				try {
					// Get the number of the card to play.
					bool cardNumValid = true;
					int cardNum = 0;
					do {
						cout << " >> Choose a card, or type SKIP to skip your turn: ";
						string cardNumStr;
						getline(cin, cardNumStr);
						if (cardNumStr == "SKIP") {
							cardNumValid = true;
							skipTurn = true;
							cout << " >> Turn skipped!" << endl;
						}
						else {
							try {
								cardNum = stoi(cardNumStr);
								cardNumValid = true;
							}
							catch (...) {
								cout << " >> Can't convert your input to an integer!" << endl;
								cardNumValid = false;
							}
							if (cardNumValid && (cardNum < 1 || cardNum > player->getHand().numCards())) {
								cout << " >> '" << cardNum << "' is an invalid card number!" << endl;
								cardNumValid = false;
							}
						}
					} while (!cardNumValid);
					if (!skipTurn) {
						// Playing the card.
						shared_ptr<AnimalCard> cardPtr = player->getHand()[cardNum - 1];
						AnimalCard* card = cardPtr.get();

						if (ActionCard* actionCard = dynamic_cast<ActionCard*>(card)) {
							QueryResult qr = actionCard->query();

							// Append the Current player's name to the result for perform to use.
							if (dynamic_cast<BearAction*>(actionCard) ||
								dynamic_cast<DeerAction*>(actionCard) ||
								dynamic_cast<WolfAction*>(actionCard)) {
								qr.append(player->getName());
								qr.append(to_string(numPlayers));
							}

							// Needs the amount of players
							if (dynamic_cast<MooseAction*>(actionCard)) {
								qr.append(to_string(numPlayers));
							}

							actionCard->perfom(table, players, qr);

							/*	If the action is a bear action, the hand will switch
								so we need to remove the card from the other player's hand */
							if (dynamic_cast<BearAction*>(actionCard)) {
								// Pop unnecessary things.
								qr.getNext();
								qr.getNext();
								// Get other player from qr
								Player * other = findPlayerByName(players, qr.getNext(), numPlayers);
								// Remove bear action card from other player's hand
								other->getHand() -= cardPtr;
							}
							else {
								player->getHand() -= cardPtr;
							}

						}
						else {

							string cardXStr, cardYStr;
							int cardX, cardY;

							cout << " >> Enter the coordinates 'x,y' of where you want to place the selected card" << endl;


							bool cardXValid = false;
							do {
								cout << " >> Enter 'x': ";
								getline(cin, cardXStr);
								try {
									cardX = stoi(cardXStr);
									cardXValid = true;
								}
								catch (...) {
									cout << " >> Can't convert your input to an integer!" << endl;
									cardXValid = false;
								}
								if (cardXValid && (cardX < 0 || cardX >= 103)) {
									cout << " >> '" << cardX << "' is outside the table!" << endl;
									cardXValid = false;
								}
							} while (!cardXValid);



							bool cardYValid = false;
							do {
								cout << " >> Enter 'y': ";
								getline(cin, cardYStr);
								try {
									cardY = stoi(cardYStr);
									cardYValid = true;
								}
								catch (...) {
									cout << " >> Can't convert your input to an integer!" << endl;
									cardYValid = false;
								}
								if (cardYValid && (cardY < 0 || cardY >= 103)) {
									cout << " >> '" << cardY << "' is outside the table!" << endl;
									cardYValid = false;
								}
							} while (!cardYValid);

							int matches = table.addAt(cardPtr, cardY, cardX);

							player->getHand() -= cardPtr;

							for (int i = 0; i < matches; i++) {
								player->getHand() += deck.draw();
							}

						}

						turnOver = true;
						cout << endl << player->getName() << "'s Turn is over.." << endl;

					}
				}
				catch (string e) {
					cout << " >> [" << e << "]: It seems that an error ocured, play your turn again!";
					turnOver = false;
				}

				cout << endl;
				// Check for win and change playing to false if someone wins.
				for (int i = 0; i < numPlayers; i++) {
					playing = !table.win(players[i]->getSecretAnimal());
					if (!playing) {
						cout << "Player " << players[i]->getName() << " won!" << endl;
						break;
					}
				}
			} while (!turnOver);

		}
	}
	return 0;
}



/*

 <FiveAnimals>

	<Player name="" secretAnimal="">
		<Hand numCards="">
			<Card type="" animals="" />
		</Hand>
	</Player>

	<Deck>
		<Card type="SplitTwo" animals="w,w,m,m" />
		<Card type="SplitTwo" animals="w,w,m,m" />
		<Card type="SplitTwo" animals="w,w,m,m" />
	</Deck>

	<Table>
		<Card x="" y="" type="" animals="" />
	</Table>

 </FiveAnimals>
 */



