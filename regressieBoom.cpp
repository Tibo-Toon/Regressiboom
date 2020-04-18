#include <iostream>
#include <string>
#include <list>
#include "regressieBoom.h"
#include "json.h"

using namespace std;


class Node {
public:
    string elt;
    Node* par;
    Node* child1;
    Node* child2;
    Node() : elt(), par(NULL), child1(NULL), child2(NULL) {}; //constructor
};

class Tree {
public:

    class Position { //node position
    private:
        Node* v;
    public:
        string& operator*(); //get element   geen idee wa deze hoort te doen???
        Position child1() const; //get node’s pos.
        Position child2() const; //get node's pos.
        bool isRoot() const; //root node?
        bool isExternal() const; //external node?
        friend class Tree;
    };
    list<Position> PositionList; //Positions of the nodes
    int size() const; //number of nodes
    bool empty() const; //is tree empty?
    Position root() const; //get the root
    void estimate() const;
};

Tree::Tree() {
    
}

Tree::Position::Position() {

}

Tree::~Tree() {
    PositionList.clear();
}

Tree::Position Tree::Position::child1() const {
    Tree pos;
    for (Position const& i : pos.PositionList) //moet ik nog een oplossing voor zoeken
    {

    }
}


Tree::Position Tree::root() const {
    for (auto const& i : PositionList) //loopt alle elementen af in de list
    {
        if (i.isRoot() == true) {
            return i;
            break;
        }
    }
}

bool Tree::empty() const {
    if (PositionList.empty()) {
        return true;
    }
    else {
        return false;
    }
}

int Tree::size() const {
    return PositionList.size();
}


bool Tree::Position::isRoot() const {
    if (v->par == NULL) {
        return true;
    }
    else {
        return false;
    }
}

bool Tree::Position::isExternal() const {
    if (v->child1 == NULL && v->child2 == 0) {
        return true;
    }
    else {
        return false;
    }
}

void Tree::estimate() const {
    string naam;
    string leslie;
    string conditie;

    cout << "Model: ";
    getline(cin, naam);
    //vergelijking met naam, if B3, give prijs

    cout << "Leslie: ";
    getline(cin, leslie);
    //leslie yes or no, naargelang tak volgen

    cout << "Conditie: ";
    getline(cin, conditie);
    // naargelang conditie prijs geven

    cout << "De geschatte prijs is: " << endl; // de prijs hier invoegen
}

int main()
{
    const int depths = 5;
    // Filenames of the rule files
    const string ruleFiles[depths] = {
        "./tree_gen/rules_d1.json",
        "./tree_gen/rules_d2.json",
        "./tree_gen/rules_d3.json",
        "./tree_gen/rules_d4.json",
        "./tree_gen/rules_d5.json"
    };
    try {
        // Load the tree a bunch of times
        for (int j = 0; j < depths; j++)
        {
            // Load the rules from the rule file into the tree
            // Open the file
            std::ifstream ruleFile(ruleFiles[j]);

            // Return false if the file wasn't opened correctly
            if (!ruleFile)
            {
                throw "File not found!";
            }

            // Parse the file's contents into the root node
            readJSON(ruleFile, 0);
            cout << endl;
            ruleFile.close();
        }
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }

    // Wait for user confirmation
    cout << endl << "Press enter to continue..." << endl;
    cin.get();
    return 0;
}

void indent(int l) {
    for (int i = 0; i <= l; i++) {
        cout << "\t";
    }
}

void readJSON(std::ifstream& fileStream, int l)
{
    string name;

    // Look for the start of a this JSON object
    json::seek('{', fileStream);

    bool foundName = false;
    while (true)
    {
        char c = json::seek("\"}", fileStream);

        if (c == '}')
        {
            break;
        }

        else if (c == '"')
        {
            std::string  key = json::parseUntill('"', fileStream);
            json::seek(':', fileStream);

            if (key == "name")
            {
                json::seek('"', fileStream);
                name = json::parseUntill('"', fileStream);

                foundName = true;
                //Print contents of name field (either a condition or target field e.g. price)
                indent(l);
                cout << name << endl;

            }
            else if (key == "children")
            {
                char first = json::seek("[n", fileStream);
                switch (first)
                {
                case 'n': // "children" : null -> leaf node
                    // In this case you know it is a leaf node and can treat the contents appropriately
                    // name field will contain target value
                    break;
                case '[': // "children" : [{...}, {...}]
                    // name field will contain condition (to either select left or right child)
                    indent(++l); cout << "left: ";
                    readJSON(fileStream, l);
                    json::seek(',', fileStream);
                    indent(l); cout << "right: ";
                    readJSON(fileStream, l);
                    json::seek(']', fileStream);
                    break;
                }
            }

            char end = json::seek(",}", fileStream);
            if (end == '}')
                break;
        }
    }

    //A name field must always be present
    if (!foundName)
    {
        throw "Name field not found in json object!";
    }

}