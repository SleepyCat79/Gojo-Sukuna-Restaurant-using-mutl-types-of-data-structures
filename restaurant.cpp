#include "main.h"
const int MAXSIZE=2^10;
struct GojoHash{
    vector<int>customer[MAXSIZE];
    public:
    void insert(int name){
        bool collision =false;
        int id = getId(name);
        if(customer[id].size()==0){
            collision=false;
        }
        else{
            collision=true;
        }
        if(!collision ){
            customer->emplace_back(id,name);
        }
        else{
            insert(name);
        }
    }
    private:
    int getId(int name){
        return name%MAXSIZE + 1;
    }
};

struct GojoBST{
    int key;
    GojoBST *left, *right;
    GojoBST(int key):key(key){}
};
struct SKNode{
    int num;
    int key;
    vector<int>customers;
};

GojoBST* insert(GojoBST* root,int key){
    if(!root){
        return new GojoBST(key);
    }
    if(key>=root->key){
        root->right=insert(root->right,key);
    }
    else{
        root->left=insert(root->left,key);
    }
    return root;
}

struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};
struct CompareNodes {
    bool operator()(const SKNode& a, const SKNode& b) const {
        return a.num > b.num;
    }
};
priority_queue<SKNode, vector<SKNode>, CompareNodes> minHeap;

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
int binaryToDecimal(int n) 
{ 
    int num = n; 
    int dec_value = 0; 
  
    int base = 1; 
  
    int temp = num; 
    while (temp) { 
        int last_digit = temp % 10; 
        temp = temp / 10; 
  
        dec_value += last_digit * base; 
  
        base = base * 2; 
    } 
  
    return dec_value; 
}
bool sortmap(pair<char,int>a,pair<char,int>b){
    return a.second==b.second? a.first<b.first:a.second<b.second;
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
int getresult(string caesarname, HuffmanNode* huffmanroot){
    unordered_map<char, string> huffmanCode;
    encode(huffmanroot,"",huffmanCode);
    string str = "";
	for (char ch: caesarname) {
		str += huffmanCode[ch];
	}
    int result;
    string tmp="";
    if(str.size()<=10){
        for(int i = str.size();i>0;i--){
            tmp+=str[i];
        }
    }
    else{
        for(int i =str.size()-1;i>str.size()-11;i--){
            tmp+=str[i];
        }
    }
    return binaryToDecimal(std::stoi( str ));
}
void simulate(string filename)
{
	cout << "Good Luck";
	return;
}
void LAPSE(string name){
	int size = name.length();
	unordered_map<char,int>freq;
	for(int i =0;i<size;i++){
		if(name[i]==' ') continue;
		freq[name[i]]++;
	}
    if(freq.size()<3){
        return;
    }
	unordered_map<char,int>x;
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
	for(auto pair:freq){
		char orgi = pair.first;
		int frequency=pair.second;
		char caesar;
        if (islower(orgi)) {
            caesar = (orgi - 'a' + frequency) % 26 + 'a';
        } 
        else if (isupper(orgi)) {
            caesar = (orgi - 'A' + frequency) % 26 + 'A';
        }
		x[caesar]+=frequency;
	}
    vector<pair<char,int>>caesar(x.begin(),x.end());
    x.clear();
    sort(caesar.begin(),caesar.end(),sortmap);
    HuffmanNode* huffmanroot = buildHuffmanTree(caesar);
    int result = getresult(caesarname,huffmanroot);
    
}