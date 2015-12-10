//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <memory>

#include "tinyxml.h"
#include "ActionCards.h"
#include "AnimalCardFactory.h"
#include "Deck.h"
#include "Player.h"
#include "Table.h"

using namespace std;
shared_ptr<AnimalCard> getCardFromXml(TiXmlElement* cardElem) {
	string type = cardElem->Attribute("type");
	string animalsStr = cardElem->Attribute("animals");

	if (type == "NoSplit") {
		return make_shared<NoSplit>(NoSplit(getAnimal(animalsStr[0])));
	}
	else if (type == "SplitTwo") {
		if (animalsStr[0] == animalsStr[1]) {
			return make_shared<SplitTwo>(SplitTwo(getAnimal(animalsStr[0]), getAnimal(animalsStr[4]), true));
		}
		else {
			return make_shared<SplitTwo>(SplitTwo(getAnimal(animalsStr[0]), getAnimal(animalsStr[2]), false));
		}
	}
	else if (type == "SplitThree") {
		if (animalsStr[0] == animalsStr[1]) { // dir 0
			return make_shared<SplitThree>(SplitThree(getAnimal(animalsStr[0]), getAnimal(animalsStr[4]), getAnimal(animalsStr[6]), 0));
		}
		else if (animalsStr[1] == animalsStr[2]) { // dir 1
			return make_shared<SplitThree>(SplitThree(getAnimal(animalsStr[2]), getAnimal(animalsStr[0]), getAnimal(animalsStr[4]), 1));
		}
		else if (animalsStr[2] == animalsStr[3]) { // dir 2
			return make_shared<SplitThree>(SplitThree(getAnimal(animalsStr[4]), getAnimal(animalsStr[0]), getAnimal(animalsStr[2]), 2));
		}
		else if (animalsStr[3] == animalsStr[1]) { // dir 3
			return make_shared<SplitThree>(SplitThree(getAnimal(animalsStr[0]), getAnimal(animalsStr[2]), getAnimal(animalsStr[6]), 3));
		}
	}
	else if (type == "SplitFour") {
		return make_shared<SplitFour>(SplitFour(getAnimal(animalsStr[0]), getAnimal(animalsStr[2]), getAnimal(animalsStr[4]), getAnimal(animalsStr[6])));
	}
	else if (type == "StartCard") {
		return make_shared<StartCard>(StartCard());
	}
	else if (type == "Joker") {
		return make_shared<Joker>(Joker());
	}
	else if (type == "BearAction") {
		return make_shared<BearAction>(BearAction());
	}
	else if (type == "DeerAction") {
		return make_shared<DeerAction>(DeerAction());
	}
	else if (type == "HareAction") {
		return make_shared<HareAction>(HareAction());
	}
	else if (type == "MooseAction") {
		return make_shared<MooseAction>(MooseAction());
	}
	else if (type == "WolfAction") {
		return make_shared<WolfAction>(WolfAction());
	}
}

TiXmlElement  getXMLCard(AnimalCard* aCard) {

	if (aCard != nullptr) {

		TiXmlElement card = TiXmlElement("Card");
		string type = "";

		if (dynamic_cast<Joker*>(aCard)) {
			type = "Joker";
		}
		else if (dynamic_cast<BearAction*>(aCard)) {
			type = "BearAction";
		}
		else if (dynamic_cast<DeerAction*>(aCard)) {
			type = "DeerAction";
		}
		else if (dynamic_cast<HareAction*>(aCard)) {
			type = "HareAction";
		}
		else if (dynamic_cast<MooseAction*>(aCard)) {
			type = "MooseAction";
		}
		else if (dynamic_cast<WolfAction*>(aCard)) {
			type = "WolfAction";
		}
		else if (dynamic_cast<StartCard*>(aCard) || aCard->getAnimal(0,0) == Animal::START) {
			type = "StartCard";
		}
		else if (dynamic_cast<NoSplit*>(aCard)) {
			type = "NoSplit";
		}
		else if (dynamic_cast<SplitTwo*>(aCard)) {
			type = "SplitTwo";
		}
		else if (dynamic_cast<SplitThree*>(aCard)) {
			type = "SplitThree";
		}
		else if (dynamic_cast<SplitFour*>(aCard)) {
			type = "SplitFour";
		}

		string animals = "x,x,x,x";
		if (dynamic_cast<ActionCard*>(aCard)) {
			animals[0] = toupper(getAnimalChar(aCard->getAnimal(0, 0)));
			animals[2] = toupper(getAnimalChar(aCard->getAnimal(0, 1)));
			animals[4] = toupper(getAnimalChar(aCard->getAnimal(1, 0)));
			animals[6] = toupper(getAnimalChar(aCard->getAnimal(1, 1)));
		}
		else {
			animals[0] = getAnimalChar(aCard->getAnimal(0, 0));
			animals[2] = getAnimalChar(aCard->getAnimal(0, 1));
			animals[4] = getAnimalChar(aCard->getAnimal(1, 0));
			animals[6] = getAnimalChar(aCard->getAnimal(1, 1));
		}
		card.SetAttribute("type", type.c_str());
		card.SetAttribute("animals", animals.c_str());
		return card;
	}
}
int main() {

	Deck<AnimalCard> deck;
	Table table;
	Player * players[5];
	int numPlayers;
	int startPlayer = 0;
	bool playing;

	{ // Setup
		table = Table();
		playing = true;
		numPlayers = 0;
		cout << "|---------------------------------------------|" << endl;
		cout << "|  Welcome to the awesome Five Animals Game!  |" << endl;
		cout << "|---------------------------------------------|" << endl << endl;

		cout << "Load a saved game of start a new one." << endl;
		string answer;
		do {
			cout << " >> Enter 'load' or 'new': ";
			getline(cin, answer);
			if (answer != "load" && answer != "new") {
				cout << " >> [UnrecognizedAnswerException]: It seems that an error ocured." << endl;
			}
		} while (!(answer == "load" || answer == "new"));

		if (answer == "load") {
			deck = Deck<AnimalCard>(); // Creates an Empty Deck.
			cout << endl << "Enter the name of the file you wish to load." << endl;
			string fileName;
			bool fileLoaded = false;
			do {
				cout << " >> File Path: ";
				getline(cin, fileName);
				TiXmlDocument savedDocument = TiXmlDocument(fileName.c_str());
				fileLoaded = savedDocument.LoadFile();
				if (fileLoaded) {

					TiXmlElement* fiveAnimalsElem = savedDocument.FirstChild()->ToElement();

					startPlayer = stoi(fiveAnimalsElem->Attribute("startPlayer"));

					for (TiXmlElement* player = fiveAnimalsElem->FirstChild("Player")->ToElement(); player; player = player->NextSiblingElement("Player")) {
						TiXmlElement* playerElem = player->ToElement();
						string playerName = playerElem->Attribute("name");
						string secretAnimal = playerElem->Attribute("secretAnimal");
						players[numPlayers] = new Player(playerName, getAnimal(secretAnimal));

						TiXmlElement* hand = playerElem->FirstChild("Hand")->ToElement();
						for (TiXmlElement* card = hand->FirstChild("Card")->ToElement(); card; card = card->NextSiblingElement("Card")) {
							players[numPlayers]->getHand() += getCardFromXml(card->ToElement());
						}

						numPlayers++;
					}

					TiXmlElement* deckElem = fiveAnimalsElem->FirstChild("Deck")->ToElement();
					for (TiXmlElement* card = deckElem->FirstChild("Card")->ToElement(); card; card = card->NextSiblingElement("Card")) {
						deck.push_back(getCardFromXml(card->ToElement()));
					}

					TiXmlElement* tableElem = fiveAnimalsElem->FirstChild("Table")->ToElement();
					for (TiXmlElement* card = tableElem->FirstChild("Card")->ToElement(); card; card = card->NextSiblingElement("Card")) {

						TiXmlElement* cardElem = card->ToElement();
						int x = stoi(cardElem->Attribute("x"));
						int y = stoi(cardElem->Attribute("y"));
						table.addWithoutCheck(getCardFromXml(cardElem), y, x);
					}
				}
				else {
					cout << " >> [FileLoadingExeption}: It seems that an error ocured while trying to load you saved game. Try loading another file." << endl;
				}
			} while (!fileLoaded);

		}
		else {
			deck = AnimalCardFactory::getFactory()->getDeck(); // Creates a deck with new cards.
			bool ready = false;
			cout << endl << "Enter the players' names (Leave empty to start game):" << endl;

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
	}
	cout << endl;
	cout << "|---------------------------------------------|" << endl;
	cout << "|             Let the game begin!             |" << endl;
	cout << "|---------------------------------------------|" << endl << endl;

	while (playing) {
		// Check for Pause.
		for (int i = startPlayer; i < numPlayers && playing; i++) {
			startPlayer = 0;
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
						cout << " >> Choose a card, 'skip' or 'save' to end your turn: ";
						string cardNumStr;
						getline(cin, cardNumStr);
						if (cardNumStr == "skip" || cardNumStr == "save") {

							if (cardNumStr == "skip") {
								cardNumValid = true;
								skipTurn = true;
								turnOver = true;
								cout << " >> Turn skipped!" << endl;
							}
							else {

								bool saved = false;
								do {

									string dir, fileName;

									cout << " >> Enter the location of where you want to save your file: ";
									getline(cin, dir);
									cout << " >> Enter the name of your save file: ";
									getline(cin, fileName);

									string fullPath = dir + ((dir[dir.length() - 1] == '/') ? "" : "/") + fileName;
									TiXmlDocument saveDocument = TiXmlDocument(fullPath.c_str());
									TiXmlElement fiveAnimals = TiXmlElement("FiveAnimals");
									fiveAnimals.SetAttribute("startPlayer", i);


									for (int p = 0; p < numPlayers; p++) {
										TiXmlElement playerNode = TiXmlElement("Player");

										playerNode.SetAttribute("name", players[p]->getName().c_str());
										playerNode.SetAttribute("secretAnimal", getAnimalString(players[p]->getSecretAnimal()).c_str());

										TiXmlElement hand = TiXmlElement("Hand");
										for (int c = 0; c < players[p]->getHand().numCards(); c++) {
											TiXmlElement card = getXMLCard(players[p]->getHand()[c].get());
											hand.InsertEndChild(card);
										}

										playerNode.InsertEndChild(hand);
										fiveAnimals.InsertEndChild(playerNode);
									}

									TiXmlElement deckElem = TiXmlElement("Deck");
									for (int c = 0; c < deck.size(); c++) {
										TiXmlElement card = getXMLCard(deck.draw().get());
										deckElem.InsertEndChild(card);
									}
									fiveAnimals.InsertEndChild(deckElem);

									TiXmlElement tableElem = TiXmlElement("Table");
									for (int x = 0; x < 103; x++) {
										for (int y = 0; y < 103; y++) {
											AnimalCard * aCard = table.get(y, x).get();
											if (aCard != nullptr) {
												TiXmlElement card = getXMLCard(aCard);
												card.SetAttribute("x", x);
												card.SetAttribute("y", y);

												tableElem.InsertEndChild(card);
											}
										}
									}
									fiveAnimals.InsertEndChild(tableElem);


									saveDocument.InsertEndChild(fiveAnimals);
									saveDocument.SaveFile();

									// Exit out of the game.
									turnOver = true;
									skipTurn = true;
									cardNumValid = true;
									saved = true;
									playing = false;

									cout << " >> Game Saved!";

								} while (!saved);

							}
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
				if (playing) {
					for (int i = 0; i < numPlayers; i++) {
						playing = !table.win(players[i]->getSecretAnimal());
						if (!playing) {
							cout << "Player " << players[i]->getName() << " won!" << endl;
							break;
						}
					}
				}
			} while (!turnOver);

		}
	}

	for (int i = 0; i < numPlayers; i++) {
		delete players[i];
	}

	return 0;
}

