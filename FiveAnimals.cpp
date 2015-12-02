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
	
	Deck<AnimalCard> deck = AnimalCardFactory::getFactory()->getDeck();
	
	Table table = Table();
	
	Player * players [5];
	
	players[0] = new Player("PlayerOne", Animal::BEAR);
	players[1] = new Player("PlayerTwo", Animal::DEER);
	
	(*players)->getHand() += deck.draw();
	players[0]->getHand() += deck.draw();
	players[0]->getHand() += deck.draw();
	players[0]->getHand() += deck.draw();
	players[0]->getHand() += deck.draw();
	players[0]->getHand() += deck.draw();
	
	players[1]->getHand() += deck.draw();
	players[1]->getHand() += deck.draw();
	players[1]->getHand() += deck.draw();
	
	players[0]->print();
	cout << endl;
	players[1]->print();
	cout << endl;
	
	table.addAt(deck.draw(), 51, 52);
	table.addAt(deck.draw(), 52, 51);
	table.addAt(deck.draw(), 53, 52);
	table.addAt(deck.draw(), 52, 53);
	
	table.print();
	
	//string s;
	//cin >> s;
	return 0;
}

//    00 01 02 03 04 05
//
// 00
//
//
// 01    ww bb       mm
//       ww bb       mm
//
// 02       dd cc ww wm
//          dd cc dd wm
//
// 03
//
