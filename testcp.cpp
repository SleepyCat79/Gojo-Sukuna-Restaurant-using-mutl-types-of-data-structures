#include <iostream>
#include<bits/stdc++.h>

using namespace std;

const int MAXSIZE=5;
//GojoRestaurant
class GojoBST {
public:
    int key;
    GojoBST* left;
    GojoBST* right;

    GojoBST(int key) : key(key), left(nullptr), right(nullptr) {}
};
unordered_map<int, GojoBST*> Gojotable;
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
void tablegetin(int result,int id){
    if(Gojotable.find(id)==Gojotable.end()){
        Gojotable[id]=new GojoBST(result);
    }
    else{
        Gojotable[id]=insert(Gojotable[id], result);
    }
}
void printBST(GojoBST* root) {
    if (root != nullptr) {
        printBST(root->left);
        cout << root->key << endl;
        printBST(root->right);
    }
}
void remove(int area,int Y){
    GojoBST* root = Gojotable[area];
    queue<GojoBST*>q;
    if(root!=nullptr){
        q.push(root);
    }
    while(!q.empty()&&Y>0){
        GojoBST* tmp = q.front();
        q.pop();
        if(tmp->left!=nullptr){
            q.push(tmp->left);
        }
        if(tmp->right!=nullptr){
            q.push(tmp->right);
        }
        delete tmp;
        Y--;
    }
    if(Y>0){
        Gojotable.erase(area);
    }
    else{
        Gojotable[area] = (q.empty() ? nullptr : q.front());
    }
}
//SukunaRestaurant
class SKNode{
    public:
    int num;
    int key;
    vector<int>customers;
    SKNode(int key):num(0),key(key){}
};
class minHeap{
    private:
    vector<SKNode*> heap;
    void heapify(int i){
        int smallest = i;
        int left = 2*i+1;
        int right = 2*i+2;
        if(left<heap.size() && heap[left]->num<heap[smallest]->num){
            smallest = left;
        }
        if(right<heap.size() && heap[right]->num<heap[smallest]->num){
            smallest = right;
        }
        if(smallest!=i){
            swap(heap[i],heap[smallest]);
            heapify(smallest);
        }

    }
public:
bool nodeExists(int key) {
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i]->key == key) {
                return true;
            }
        }
        return false;
    }
    void addNode(int key) {
        SKNode* node = new SKNode(key);
        heap.push_back(node);
        int i = heap.size() - 1;
        while (i != 0 && heap[(i - 1) / 2]->key > heap[i]->key) {
            swap(heap[(i - 1) / 2], heap[i]);
            i = (i - 1) / 2;
        }
    }
    void addCustomer(int key, int customer) {
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i]->key == key) {
                heap[i]->customers.push_back(customer);
                heap[i]->num++;
                break;
            }
        }
    }
    vector<SKNode*>& getHeap() {
        return heap;
    }
};
minHeap sukunaheap;
//Huffman Tree
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};
struct CompareNodes {
    bool operator()(HuffmanNode* lhs, HuffmanNode* rhs) {
        return lhs->frequency >= rhs->frequency; 
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
    return binaryToDecimal(std::stoi( tmp ));
}
void getinres(int result){
    int id = result%MAXSIZE + 1;
    cout<<id<<" "<<result<<endl;
    if(result%2!=0){
        tablegetin(result,id);
    }
    else{
        if(sukunaheap.nodeExists(id)){
            sukunaheap.addCustomer(id,result);
        }
        else{
            sukunaheap.addNode(id);
            sukunaheap.addCustomer(id,result);
        }
    }
}
//stuff for Kokusen
void factorial(int fact[],int n){
    fact[0]=1;
    for(int i =1;i<=n;i++){
        fact[i]=fact[i-1]*i;
    }
}
int nCr(int n,int r){
    int fact[n+1];
    factorial(fact,n);
    return fact[n]/(fact[r]*fact[n-r]);
}
int counthoanvi(vector<int>& arr,int fact[]){
    int n = arr.size();
    if(n<=2){
        return 1;
    }
    vector<int>left;
    vector<int>right;
    int root=arr[0];
    for(int i =0;i<n;i++){
        if(arr[i]<root){
            left.push_back(arr[i]);
        }
        else if(arr[i]>root){
            right.push_back(arr[i]);
        }
    }
    int nleft=left.size();
    int nright=right.size();
    int countleft=counthoanvi(left,fact);
    int countright=counthoanvi(right,fact);
    return nCr(n-1,nleft)*countleft*countright;
}
void simulate(string filename)
{
	cout << "Good Luck";
	return;
}
vector<int> BSTtoPostOrder(GojoBST* root) {
    vector<int> arr;
    if (root) {
        vector<int> left = BSTtoPostOrder(root->left);
        vector<int> right = BSTtoPostOrder(root->right);
        arr.insert(arr.end(), left.begin(), left.end());
        arr.insert(arr.end(), right.begin(), right.end());
        arr.push_back(root->key);
    }
    return arr;
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
    getinres(result);
}

void LIMITLESS(int NUM){
    if (Gojotable.find(NUM) != Gojotable.end()) {
        printBST(Gojotable[NUM]);
    } 
    else {
        return;
    }
}
void KOKUSEN(){
    for(auto area: Gojotable){
        vector<int>postorder = BSTtoPostOrder(area.second);
        int rootforhvi = postorder.back();
        postorder.pop_back();
        postorder.push_back(postorder.front());
        postorder.insert(postorder.begin(),rootforhvi);
        int fact[postorder.size()];
        int Y=counthoanvi(postorder,fact);
        remove(area.first,Y);
    }
}
//idea:tinh hoan vi cua tat ca leftnode va rightnode + lai =>so hoan vi hop li. Cong thuc rat chuan, so loop trong loop no bi segmant fault, ban tim cach test di.

int main(){
    string s = "aaabbcccDD";
    LAPSE ("Johnuigfifbahjasbdfhjbasdhjf");
    LAPSE ("iuasgfuigweibjaskdfbjksadf");
    LAPSE ("iuiwehruihqwUIAGSIDiernbsandfb");
    LAPSE ("uiewhqruihqiuwerhnbdasnbfnmasd");
    LIMITLESS(2);
    KOKUSEN();
    cout<<"Kokusen: "<<endl;
    LIMITLESS(2);
}