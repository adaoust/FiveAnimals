//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#include "ActionCards.h"

Player * findPlayerByName(Player ** player, string name, int numPlayer) {
	for (int i = 0; i < numPlayer; i++) {
		if (player[i]->getName() == name) {
			return player[i];
		}
	}
	throw string("InvalidPlayerNameException");
}
void ActionCard::printRow(EvenOdd evenOdd) {
	switch (evenOdd) {
	case EvenOdd::EVEN:
		cout << (char)toupper(getAnimalChar(_animals[0][0])) << (char)toupper(getAnimalChar(_animals[0][1]));
		break;
	case EvenOdd::ODD:
		cout << (char)toupper(getAnimalChar(_animals[1][0])) << (char)toupper(getAnimalChar(_animals[1][1]));
		break;
	default:
		cout << "  ";
	}
}

// Bear Action.
QueryResult BearAction::query() {
	cout << " >> [~ Bear Action ~]: Enter the name of the player you wish to exchange your hand with." << endl;
	cout << " >> Name: ";
	string playerName = "";
	getline(cin, playerName);
	QueryResult qr = QueryResult();
	qr.append(playerName);
	return qr;
}

void BearAction::perfom(Table& table, Player** players, QueryResult queryResult) {
	int numPlayer;
	try {
		numPlayer = stoi(queryResult.getNext());
	} catch (...) {
		throw string("InvalidNumberOfPlayerException");
	}
	Player * p1 = findPlayerByName(players, queryResult.getNext(), numPlayer);
	Player * p2 = findPlayerByName(players, queryResult.getNext(), numPlayer);
    if (p1 == p2) {
        throw string("InvalidPlayerException");
    }
	p1->swapHand(p2->getHand());
}

// Deer Action.
QueryResult DeerAction::query() {
	cout << " >> [~ Deer Action ~]: Enter the name of the player you wish to exchange your secret animal with." << endl;
	cout << " >> Name: ";
	string playerName = "";
	getline(cin, playerName);
	QueryResult qr = QueryResult();
	qr.append(playerName);
	return qr;
}

void DeerAction::perfom(Table& table, Player** players, QueryResult queryResult) {
	int numPlayer;
	try {
		numPlayer = stoi(queryResult.getNext());
	} catch (...) {
		throw string("InvalidNumberOfPlayerException");
	}
	Player * p1 = findPlayerByName(players, queryResult.getNext(), numPlayer);
	Player * p2 = findPlayerByName(players, queryResult.getNext(), numPlayer);
    if (p1 == p2) {
        throw string("InvalidPlayerException");
    }
	p1->swapSecretAnimal(p2->getSecretAnimal());
}

// Hare Action.
QueryResult HareAction::query() {
	QueryResult qr = QueryResult();
	cout << " >> [~ Hare Action ~]: Enter the coordinates 'x0,y0,x1,y1' of which card you want to move and where." << endl;
	cout << " >> Enter 'x0': ";
	string coordinate;
	getline(cin, coordinate);
	qr.append(coordinate);
	cout << " >> Enter 'y0': ";
	getline(cin, coordinate);
	qr.append(coordinate);
	cout << " >> Enter 'x1': ";
	getline(cin, coordinate);
	qr.append(coordinate);
	cout << " >> Enter 'y1': ";
	getline(cin, coordinate);
	qr.append(coordinate);
	return qr;
}

void HareAction::perfom(Table& table, Player** players, QueryResult queryResult) {
	int x0, x1, y0, y1;
	try {
		y1 = stoi(queryResult.getNext());
		x1 = stoi(queryResult.getNext());
		y0 = stoi(queryResult.getNext());
		x0 = stoi(queryResult.getNext());
	} catch (...) {
		throw string("InvalidCoordinatesException");
	}
	if (table.get(y0, x0) == nullptr) {
		throw string("NoSuchCardException");
	}
	if (table.get(y0, x0)->getAnimal(0, 0) == Animal::START) {
		throw string("StartCardCanNotBeMovedException");
	}
	shared_ptr<AnimalCard> card = table.pickAt(y0, x0);
	try {
		table.addAt(card, y1, x1);
	} catch (string e) {
		table.addWithoutCheck(card, y0, x0);
		throw e;
	}


}

// Moose Action.
QueryResult MooseAction::query() {
	cout << " >> [~ Moose Action ~]: Secret animals rotate!" << endl;
	return QueryResult();
}

void MooseAction::perfom(Table& table, Player** players, QueryResult queryResult) {
	try {
		int numPlayer = stoi(queryResult.getNext());
		for (int i = 1; i < numPlayer; i++) {
			players[i]->swapSecretAnimal(players[0]->getSecretAnimal());
		}
	} catch (...) {
		throw string("InvalidNumberOfPlayerException");
	}
}

// Wolf Action.
QueryResult WolfAction::query() {
	QueryResult qr;
	cout << " >> [~ Wolf Action ~]: Enter the location 'x,y' of the card you want to put in your hand." << endl;
	cout << " >> Enter 'x': ";
	string coordinate;
	getline(cin, coordinate);
	qr.append(coordinate);
	cout << " >> Enter 'y': ";
	getline(cin, coordinate);
	qr.append(coordinate);
	return qr;
}

void WolfAction::perfom(Table& table, Player** players, QueryResult queryResult) {
	int numPlayer;
	try {
		numPlayer = stoi(queryResult.getNext());
	} catch (...) {
		throw string("InvalidNumberOfPlayerException");
	}
	Player * p = findPlayerByName(players, queryResult.getNext(), numPlayer);
	int x, y;
	try {
		y = stoi(queryResult.getNext());
		x = stoi(queryResult.getNext());
	} catch (...) {
		throw string("InvalidCoordinatesException");
	}

	if (table.get(y, x) == nullptr) {
		throw string("NoSuchCardException");
	}

	if (table.get(y, x)->getAnimal(0, 0) == Animal::START) {
		throw string("StartCardCanNotBeMovedException");
	}
	p->getHand() += table.pickAt(y, x);
}