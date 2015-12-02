//
// Authors:
// Alexandre D'Aoust - 7206757
// Maxime Bélair - 7432263 
// CSI2772 Project
//

#ifndef QUERYRESULT_H
#define QUERYRESULT_H

class QueryResult {
    
private:
    
    vector<string> result;
    
public:
    
    QueryResult() {
        result = vector<string>();
    };
    
    void append(string str) {
        result.push_back(str);
    }
    
    string getNext() {
        string next = result.back();
        result.pop_back();
        return next;
    }
    
};

#endif