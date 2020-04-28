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
    Node* left;
    Node* right;
    Node* newNode(string elt);
   Node() : elt(), par(NULL), left(NULL), right(NULL) {}; //constructor
};

class Tree {
public:

    class Position { //node position
    private:
        
    public:
        Node* v;
        bool isRoot() const; //root node?
        bool isExternal() const; //external node?
        friend class Tree;
    };
    list<Position> PositionList; //Positions of the nodes
    int size() const; //number of nodes
    bool empty() const; //is tree empty?
    Position root() const; //get the root
    void estimate() const;
    void print() const; //printing the tree
    void read() const; //maakt de tree aan
    Tree() : PositionList() {};
    ~Tree() { PositionList.clear(); };
};


//globale variabelen
Tree boom;
Tree::Position position1;
Tree::Position position2;
Tree::Position position3;
Tree::Position position4;
Tree::Position position5;
Tree::Position position6;
Tree::Position position7;
Tree::Position position8;
Tree::Position position9;
Tree::Position position10;
Tree::Position position11;
Tree::Position position12;
Tree::Position position13;
Tree::Position position14;
Tree::Position position15;
Node rootNode;
Node* rootP = rootNode.newNode("Model_B5 > 0.5");


void Tree::print() const {
    Position root = boom.root();
    cout << "    De ingevoerde data wordt door deze boom gehaald" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << " \t \t" << root.v->elt << endl;
    cout << root.v->left->elt << "\t\t\t\t" << root.v->right->elt << endl;
    cout << "\t\t\t" << root.v->right->left->elt << "\t\t\t" << root.v->right->right->elt << endl;
    cout << "\n\t" << root.v->right->left->left->elt << "\t\t" << root.v->right->left->right->elt << "\t" << root.v->right->right->left->elt << "\t\t" << root.v->right->right->right->elt << endl;
    cout << "\n\t" << root.v->right->left->right->left->elt << "\t\t" << root.v->right->left->right->right->elt << "\t\t" << root.v->right->right->right->left->elt << "\t" << root.v->right->right->right->right->elt << endl;
    cout << "\t\t\t\t\t\t\t\t" << root.v->right->right->right->right->left->elt << "\t" << root.v->right->right->right->right->right->elt << endl;
}

void Tree::read() const {
    rootP->left = rootNode.newNode("4513 of price");
    rootP->right = rootNode.newNode("Condition_fair > 0.5");

    rootP->right->left = rootNode.newNode("Leslie_yes > 0.5");
    rootP->right->left->left = rootNode.newNode("625 of price");
    rootP->right->left->right = rootNode.newNode("Model_T202 > 0.5");
    rootP->right->left->right->left = rootNode.newNode("99 of price");
    rootP->right->left->right->right = rootNode.newNode("77 of price");

    rootP->right->right = rootNode.newNode("Model_T202 > 0.5");
    rootP->right->right->left = rootNode.newNode("270 of Price");
    rootP->right->right->right = rootNode.newNode("Model_M102 > 0.5");
    rootP->right->right->right->left = rootNode.newNode("87 of price");
    rootP->right->right->right->right = rootNode.newNode("Condition_good > 0.5");
    rootP->right->right->right->right->left = rootNode.newNode("1475 of price");
    rootP->right->right->right->right->right = rootNode.newNode("1770 of price");

    position1.v = rootP;
    position2.v = rootP->left;
    position3.v = rootP->right;

    position4.v = rootP->right->left;
    position5.v = rootP->right->left->left;
    position6.v = rootP->right->left->right;
    position7.v = rootP->right->left->right->left;
    position8.v = rootP->right->left->right->right;

    position9.v = rootP->right->right;
    position10.v = rootP->right->right->left;
    position11.v = rootP->right->right->right;
    position12.v = rootP->right->right->right->left;
    position13.v = rootP->right->right->right->right;
    position14.v = rootP->right->right->right->right->left;
    position15.v = rootP->right->right->right->right->right;

    boom.PositionList.push_back(position1);
    boom.PositionList.push_back(position2);
    boom.PositionList.push_back(position3);
    boom.PositionList.push_back(position4);
    boom.PositionList.push_back(position5);
    boom.PositionList.push_back(position6);
    boom.PositionList.push_back(position7);
    boom.PositionList.push_back(position8);
    boom.PositionList.push_back(position9);
    boom.PositionList.push_back(position10);
    boom.PositionList.push_back(position11);
    boom.PositionList.push_back(position12);
    boom.PositionList.push_back(position13);
    boom.PositionList.push_back(position14);
    boom.PositionList.push_back(position15);
}

Node* Node::newNode(string elt) {
    Node* node = new Node;
    node->elt = elt;
    node->left = NULL;
    node->right = NULL;
    return node;
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
    if (v->left == NULL && v->right == 0) {
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
    string schatting;

    cout << "Model: "; //vergelijking met naam, if B3, give prijs
    getline(cin, naam);
    cout << "Leslie: ";   //leslie yes or no, naargelang tak volgen
    getline(cin, leslie);
    cout << "Conditie: ";
    getline(cin, conditie);  // naargelang conditie prijs geven
  

    Position root;
    root = boom.root();

    if (naam == "B3") {
        schatting = root.v->left->elt;
    }
    else if(conditie == "fair") {
        if (leslie == "yes") {
            schatting = root.v->right->left->left->elt;// 625 of price
        }
        else if (naam == "T202") {
            schatting = root.v->right->left->right->left->elt; //99 of price
        }
        else
        {
            schatting = root.v->right->left->right->right->elt; // 77 of price
        }
    }
    else {
         if (naam == "T202") {
             schatting = root.v->right->right->left->elt;//270 of price
    }
         else {
                if (naam == "M102") {
                    schatting = root.v->right->right->right->left->elt; //87 of price
    }
                else {
                         if (conditie == "good") {
                             schatting = root.v->right->right->right->right->left->elt;  //1475 of price
    }
                         else {
                             schatting = root.v->right->right->right->right->right->elt;     //1770 of price
    }
                }

         }
      
    }
   
    

    cout << "De geschatte prijs is: " << schatting << endl; // de prijs hier invoegen
}

int main()
{
    const int depths = 1;
    // Filenames of the rule files
    const string ruleFiles[depths] = {
        //"./tree_gen/rules_d1.json"
        //"./tree_gen/rules_d2.json",
        //"./tree_gen/rules_d3.json",
        //"./tree_gen/rules_d4.json",
        //"./tree_gen/rules_d5.json"
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
    
    boom.read();
    boom.estimate();
    boom.print();

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


//We hebben niet gevonden hoe we de data uit de json file in onze boom krijgen dit hebben we dus geforceerd
//onderstaande code wordt dus niet gebruikt
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