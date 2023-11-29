#include <iostream>
#include<bits/stdc++.h>

using namespace std;


struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    // Constructor
    HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(HuffmanNode* lhs, HuffmanNode* rhs) {
        return lhs->frequency >= rhs->frequency; // Min-heap based on frequency
    }
};
HuffmanNode* buildHuffmanTree(vector<pair<char,int>>frequencymap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
    for (const auto& pair : frequencymap) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        pq.push(node);
    }

    while (pq.size() > 1) {
        HuffmanNode* leftChild = pq.top();
        pq.pop();
        HuffmanNode* rightChild = pq.top();
        pq.pop();

        HuffmanNode* internalNode = new HuffmanNode('\0', leftChild->frequency + rightChild->frequency);
        internalNode->left = leftChild;
        internalNode->right = rightChild;

        pq.push(internalNode);
    }

    return pq.top();
}

void encode(HuffmanNode* root, string str,
			unordered_map<char, string> &huffmanCode){
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->data] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}


vector<pair<char,int>> sortmap(unordered_map<char, int>freq,string name ){
    vector<pair<char,int>>sortfreq(freq.begin(),freq.end());
    sort(sortfreq.begin(),sortfreq.end(),
        [&name](pair<char,int>a,pair<char,int>b){
            return (a.second==b.second) ? name.find(a.first)<name.find(b.first) : a.second<b.second;
        });
    return sortfreq;
}
void printHuffmanCodes(HuffmanNode* root, string code = "") {
    if (root) {
        if (root->data != '\0') {
            cout << root->data << ": " << code << endl;
        }
        printHuffmanCodes(root->left, code + "0");
        printHuffmanCodes(root->right, code + "1");
    }
}
void LAPSE(string name){
	int size = name.length();
	if(size<=3) return;
	unordered_map<char,int>freq;
	for(int i =0;i<size;i++){
		if(name[i]==' ') continue;
		freq[name[i]]++;
	}
	vector<pair<char,int>>sortfreq= sortmap(freq,name);
	vector<pair<char,int>>x;
    string caesarname = "";
    for(int i =0;i<size;i++){
        char tmpc = name[i];
        if (islower(tmpc)) {
            caesarname += (tmpc - 'a' + freq[tmpc]) % 26 + 'a';
        } 
        else if (isupper(tmpc)) {
            caesarname += (tmpc - 'A' + freq[tmpc]) % 26 + 'A';
        }
    }
	for(auto pair:sortfreq){
		char orgi = pair.first;
		int frequency=pair.second;
		char caesar;
        if (islower(orgi)) {
            caesar = (orgi - 'a' + frequency) % 26 + 'a';
        } 
        else if (isupper(orgi)) {
            caesar = (orgi - 'A' + frequency) % 26 + 'A';
        }
		x.emplace_back(caesar, frequency);
	}
    HuffmanNode* huffmanroot = buildHuffmanTree(x);
    unordered_map<char, string> huffmanCode;
    encode(huffmanroot,"",huffmanCode);
    string str = "";
	for (char ch: caesarname) {
		str += huffmanCode[ch];
	}
    int result;
    if(str.size()<10){
        for(int i = str.size();i>0;i++){
            result+=str[i];
        }
    }
    else{
        
    }

}

// Main function
int main() {
    // Example frequency table (character, frequency)

    // Build the Huffman tree
    string s = "aaabbcccDD";
    LAPSE(s);

    return 0;
}
