#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class TreeNode{
    public:
        TreeNode(char currChar, int passedFrequency){
            nodeCharacter = currChar;
            charFrequency = passedFrequency;
            left = nullptr;
            right = nullptr;
    }
        TreeNode(int passedFrequency, TreeNode *leftChild, TreeNode *rightChild){
            charFrequency = passedFrequency;
            left = leftChild;
            right = rightChild;
        }
        char nodeCharacter;
        int charFrequency;
        TreeNode *left;
        TreeNode *right;
};

class QueueCompare {
public:
    // Compare the keys of the nodes
    // return true if x's key > y's key; false otherwise
    // bool operator()(T x, T y) where T is the type of the priority_queue
    bool operator()(TreeNode x, TreeNode y) {
        return x.charFrequency > y.charFrequency;
    }
};

class HuffmanTree{
    public:
        string huffmanCompress(ifstream &inputFile, map<char, string> codes, int &count){
            string currentLine;
            string result;
            //Removing any error flags and resetting the filestream back to the beginning of the file.

            inputFile.clear();
            inputFile.seekg(0, ios_base::beg);
            //For each line and each character of the line, add it's corresponding code in the codes map to the
            //resultant string
            while(getline(inputFile, currentLine)){
                for(int i = 0; i < currentLine.length(); i++){
                    result += codes.at(currentLine[i]);
                    count++;
                }
                if(!inputFile.eof()){
                    result += codes.at('\n');
                    count++;
                }
            }
            return result;
        }


};

map<char, int> createMap(ifstream &inputFile){
    string currentLine;
    char currentCharacter;
    map<char, int> charFreq;

    //For each character, if it's already in the map, increment it's corresponding value.
    //If not, add the character to the map
    while(getline(inputFile, currentLine)){
        for(int i = 0; i < currentLine.length(); i++){
            currentCharacter = currentLine[i];
            if(charFreq.find(currentCharacter) != charFreq.end()){
                charFreq.at(currentCharacter) += 1;
            }
            else{
                charFreq.insert({currentCharacter, 1});
            }
        }
        if(!inputFile.eof()){
            charFreq['\n'] += 1;
        }
    }
    return charFreq;
}

TreeNode buildHuffmanTree(map<char, int> charFreq){
    priority_queue<TreeNode, vector<TreeNode>, QueueCompare> minQueue;
    int frequencySum;

    //For each character in the map, create a node with the character frequency and current
    //character, than insert it into the minQueue
    for(auto i = charFreq.begin(); i != charFreq.end(); i++){
        TreeNode *node = new TreeNode(i->first, i->second);
        minQueue.push(*node);
    }
    //While the minQueue has more than one node
    //Grab the two lowest priority values, remove them from the queue, 
    //Then create a new parent node for those left and right values and enqueue it
    while(minQueue.size() > 1){
        TreeNode *left = new TreeNode(minQueue.top());
        minQueue.pop();
        TreeNode *right = new TreeNode(minQueue.top());
        minQueue.pop();
        frequencySum = left->charFrequency + right->charFrequency;
        TreeNode *parent = new TreeNode(frequencySum, left, right);
        minQueue.push(*parent);
    }
    return minQueue.top();
}

map<char, string> getHuffmanCodes(TreeNode *node, string prefix, map<char, string>&codes){
    if(node->left == nullptr && node->right == nullptr){
        codes.insert({node->nodeCharacter, prefix});
    }
    else{
        getHuffmanCodes(node->left, prefix + "0", codes);
        getHuffmanCodes(node->right, prefix + "1", codes);
    }
    return codes;
}
int main(int argc, char *argv[]) {
    // this is an example min priority_queue with type int
    // you will need to change the type to your node class
   ifstream inFile(argv[1], ios::in);
   if(!inFile){
       cout << "File could not be opened\n";
       return 1;
   }
    // priority_queue<type, underlying_storage_container, comparer> minQueue;
    // priority_queue<T, vector<T>, QueueCompare> minQueue; where T is the type of the priority_queue
    map<char, int> characterFrequencies = createMap(inFile);
    TreeNode *root = new TreeNode(buildHuffmanTree(characterFrequencies));
    
    map<char, string> huffmanCodes;
    huffmanCodes = getHuffmanCodes(root, "", huffmanCodes);
    
    int count = 0;
    HuffmanTree Tree;
    string compressedData = Tree.huffmanCompress(inFile, huffmanCodes, count);

    cout << "Uncompressed length: " << (count * 8) << "bits\n";
    cout << "Compressed length: " << compressedData.length() << "bits\n";
    cout << "CHAR|FREQ|CODE_LEN\n";

    for(auto i = characterFrequencies.begin(); i != characterFrequencies.end(); i++){
        cout << "'" << i->first << "'|" << i->second << "|" << (huffmanCodes.at(i->first)).length() << "\n";
    }

    return 0;
}
