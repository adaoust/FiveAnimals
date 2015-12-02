//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#include "ActionCards.h"

void ActionCard::printRow(EvenOdd evenOdd) {
	switch (evenOdd) {
	case EvenOdd::EVEN:
		cout << (char) toupper(getAnimalChar(_animals[0][0])) << (char) toupper(getAnimalChar(_animals[0][1]));
		break;
	case EvenOdd::ODD:
		cout << (char) toupper(getAnimalChar(_animals[1][0])) << (char) toupper(getAnimalChar(_animals[1][1]));
		break;
	default:
		cout << "  ";
	}
}

// Bear Action.
QueryResult BearAction::query() {
    cout << "Bear Action!" << endl << " -> Enter the name of the player you wish to exchange your hand with: ";
    string playerName = "";
    cin >> playerName;
    QueryResult qr = QueryResult();
    qr.append(playerName);
    // Why can't we verify ?
	return qr;
}

void BearAction::perfom(Table& table, Player* players, QueryResult queryResult) {
    string playerName = queryResult.getNext();
    // What is player ?
}
 
// Deer Action.
QueryResult DeerAction::query() {
    cout << "Deer Action!" << endl << " -> Enter the name of the player you wish to exchange your secret animal with: ";
	return QueryResult();
}

void DeerAction::perfom(Table& table, Player* players, QueryResult queryResult) {
}

// Hare Action.
QueryResult HareAction::query() {
    cout << "Hare Action!" << endl << " -> Enter the coordinates 'x0,y0,x1,y1' of which card you want to move and where: ";
	return QueryResult();
}

void HareAction::perfom(Table& table, Player* players, QueryResult queryResult) {
}

// Moose Action.
QueryResult MooseAction::query() {
    cout << "Moose Action!" << endl << " -> Secret animals are rotating!" << endl;
	return QueryResult();
}

void MooseAction::perfom(Table& table, Player* players, QueryResult queryResult) {
}

// Wolf Action.
QueryResult WolfAction::query() {
    cout << "Wolf Action!" << endl << " -> Enter the location 'x,y' of the card you want to put in your hand: ";
	return QueryResult();
}

void WolfAction::perfom(Table& table, Player* players, QueryResult queryResult) {
}