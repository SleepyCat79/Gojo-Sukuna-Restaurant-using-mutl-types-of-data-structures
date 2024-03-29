#include "main.h"
int MAXSIZE;
//GojoRestaurant
class GojoBST {
public:
    int key;
    GojoBST* left;
    GojoBST* right;
    std::chrono::steady_clock::time_point order;
    GojoBST(int key) : key(key), left(nullptr), right(nullptr),order(std::chrono::steady_clock::now()){}
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
void getNodesInOrder(GojoBST* root, vector<pair<int, std::chrono::steady_clock::time_point>>& nodes) {
    if (root != nullptr) {
        getNodesInOrder(root->left, nodes);
        nodes.push_back({root->key, root->order});
        getNodesInOrder(root->right, nodes);
    }
}
GojoBST *delNode(GojoBST *root, int tmp)
{
	if (!root)
	{
		return root;
	}
	if (root->key > tmp)
	{
		root->left = delNode(root->left, tmp);
		return root;
	}
	else if (root->key < tmp)
	{
		root->right = delNode(root->right, tmp);
		return root;
	}
	if (root->left == NULL)
	{
		GojoBST *temp = root->right;
		delete root;
		return temp;
	}
	else if (root->right == NULL)
	{
		GojoBST *temp = root->left;
		delete root;
		return temp;
	}
	else
	{

		GojoBST *succParent = root;
		// Find successor
		GojoBST *succ = root->right;
		while (succ->left != NULL)
		{
			succParent = succ;
			succ = succ->left;
		}

		if (succParent != root)
			succParent->left = succ->right;
		else
			succParent->right = succ->right;

		// Copy Successor Data to root
		root->key = succ->key;

		// Delete Successor and return root
		delete succ;
		return root;
	}
}
void countNodes(GojoBST* root, int& count) {
    if (root != nullptr) {
        countNodes(root->left, count);
        count++;
        countNodes(root->right, count);
    }
}

int getNumberOfNodesInArea(int area) {
    int count = 0;
    if (Gojotable.find(area) != Gojotable.end()) {
        countNodes(Gojotable[area], count);
    }
    return count;
}
void remove(int ID,int Y){
    int n = getNumberOfNodesInArea(ID);
	if (n <= Y)
	{
		GojoBST *tmp = Gojotable[ID];
		Gojotable[ID] = nullptr;
		delete tmp;
	}
	else
	{
        vector<pair<int, std::chrono::steady_clock::time_point>> nodes;
        if (Gojotable.find(ID) != Gojotable.end()) {
        getNodesInOrder(Gojotable[ID], nodes);
        sort(nodes.begin(), nodes.end(), [](const pair<int, std::chrono::steady_clock::time_point>& a, const pair<int, std::chrono::steady_clock::time_point>& b) {
        return a.second < b.second;
    });
    }
		for (int i = 0; i < Y; i++)
		{
			Gojotable[ID] = delNode(Gojotable[ID], nodes[0].first);
			nodes.erase(nodes.begin() + 0);
		}
	}
}
void printAllCustomers() {
    for (auto& area : Gojotable) {
        cout << "Area " << area.first << ":\n";
        printBST(area.second);
    }
}
//SukunaRestaurant
class SKNode{
    public:
    int num;
    int key;
    bool firsttime = true;
    vector<int>customers;
    std::chrono::steady_clock::time_point lastuse;
    SKNode(int key): num(0), key(key), lastuse(std::chrono::steady_clock::now()) {}
};
class minHeap{
    private:
    vector<SKNode*> heap;
    void reheapUp(int i) {
        if (i && heap[(i - 1) / 2]->num > heap[i]->num) {
            swap(heap[i], heap[(i - 1) / 2]);
            reheapUp((i - 1) / 2);
        }
        else if(i && heap[(i - 1) / 2]->num == heap[i]->num){
            if(heap[(i - 1) / 2]->lastuse > heap[i]->lastuse){
                swap(heap[i], heap[(i - 1) / 2]);
                reheapUp((i - 1) / 2);
            }
        }
     }

    void reheapDown(int i){
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < int(heap.size()) && heap[left]->num < heap[largest]->num)
	{
		largest = left;
	}
    else if(left < int(heap.size()) && heap[left]->num == heap[largest]->num){
        if(heap[left]->lastuse < heap[largest]->lastuse){
            largest = left;
        }
    }
	if (right < int(heap.size()) && heap[right]->num < heap[largest]->num)
	{
		largest = right;
	}
    else if(right < int(heap.size()) && heap[right]->num == heap[largest]->num){
        if(heap[right]->lastuse < heap[largest]->lastuse){
            largest = right;
        }
    }
	if (largest != i)
	{
		swap(heap[i], heap[largest]);
		reheapDown(largest);
	}
}
    void waytopreorder(int i, vector<SKNode*>& result) {
        if (i >= int(heap.size())) {
            return;
        }
        result.push_back(heap[i]);
        waytopreorder(2 * i + 1, result); 
        waytopreorder(2 * i + 2, result);
    }
    
public:
int getSize(){
    return heap.size();
}
    bool nodeExists(int key) {
        int heapsize = heap.size();
        for (int i = 0; i < heapsize; i++) {
            if (heap[i]->key == key) {
                return true;
            }
        }
        return false;
    }
    bool isEmpty() const {
        return heap.empty();
    }
    SKNode* operator[](int index) {
        return heap[index];
    }
    void addNode(int key) {
        SKNode* node = new SKNode(key);
        node->num=1;
        heap.push_back(node);
        int i = heap.size() - 1;
        reheapUp(i);
    }
    void addCustomer(int key, int customer) {
        int heapsize=heap.size();
        for (int i = 0; i < heapsize; i++) {
            if (heap[i]->key == key) {
                heap[i]->customers.push_back(customer);
                if(heap[i]->firsttime){
                    heap[i]->firsttime=false;
                    heap[i]->num=heap[i]->customers.size();
                }
                else{
                    heap[i]->num++;
                }
                heap[i]->lastuse = std::chrono::steady_clock::now();
                reheapDown(i);
                break;
            }
        }
    }
    void deleteCustomer(int customerID, int numdelete) {
        int heapsize = heap.size();
        for (int i = 0; i < heapsize; i++) {
            if(heap[i]->key==customerID){
                SKNode* tmp = heap[i];  
                if(tmp->num<=numdelete){
                    for(int j=0;j<tmp->num;j++){
                        cout<<tmp->customers[j]<<"-"<<tmp->key<<endl;
                    }
                    swap(heap[i],heap[heapsize-1]);
                    heap.pop_back();
                    reheapDown(i);
                    heapsize--; 
                    delete tmp;
                }
                else{
                    for(int j=0;j<numdelete;j++){
                        cout<<tmp->customers[0]<<"-"<<tmp->key<<endl;
                        tmp->num--;
                        tmp->lastuse = std::chrono::steady_clock::now();
                        tmp->customers.erase(tmp->customers.begin());
                    }
                    reheapUp(i);
                }
            }
        }
}
 
    vector<SKNode*> preorder(){
        vector<SKNode*> result;
        waytopreorder(0, result);
        return result;
    
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
    int order;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char d, int freq, int order) : data(d), frequency(freq), order(order), left(nullptr), right(nullptr) {}
};
HuffmanNode *rotateRight(HuffmanNode* root){
    HuffmanNode *x = root->left;
    HuffmanNode *y = x->right;
    root->left = y;
    x->right = root;
    return x;

}
HuffmanNode *rotateLeft(HuffmanNode* root){
    HuffmanNode *x = root->right;
    HuffmanNode *y = x->left;
    root->right = y;
    x->left = root;
    return x;

}
int getHeight(HuffmanNode *root){
    if(!root){
        return 0;
    }
    return 1+max(getHeight(root->left),getHeight(root->right));
}
int getBalance(HuffmanNode *N)  
{  
    if (N == NULL)  
        return 0;  
    return getHeight(N->left) - getHeight(N->right);  
}
HuffmanNode *rotate(HuffmanNode *root)
{
	if (!root)
	{
		return nullptr;
	}
	int balance = getBalance(root);
	if (balance > 1 && getBalance(root->left) >= 0)
	{
		return rotateRight(root);
	}
	if (balance > 1 && getBalance(root->left))
	{
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	if (balance < -1 && getBalance(root->right)<=0)
	{
		return rotateLeft(root);
	}
	if (balance < -1 && getBalance(root->right)>0)
	{
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	return root;
}

struct CompareNodes
{
	bool operator()(const HuffmanNode *lhs, const HuffmanNode *rhs) const
	{
		if (lhs->frequency != rhs->frequency)
		{
			return lhs->frequency > rhs->frequency;
		}
		else if (lhs->data != '\0' && rhs->data != '\0' && lhs->frequency == rhs->frequency)
		{
			if (islower(lhs->data) && isupper(rhs->data))
			{
				return false;
			}
			else if (isupper(lhs->data) && islower(rhs->data))
			{
				return true;
			}
			else
			{
				return lhs->data > rhs->data;
			}
		}
		else
		{
			return lhs->order > rhs->order;
		}
	}
};
HuffmanNode *reBalance(HuffmanNode *root, int &count, bool &check)
{
	if (root == nullptr)
	{
		return root;
	}
	if (count == 0 || check)
	{
		return root;
	}
	while (count > 0)
	{
		int balance = getHeight(root->left) - getHeight(root->right);
		if (abs(balance) > 1)
		{
			root = rotate(root);
			count--;
			check = true;
			return root;
		}
		else
			break;
	}
	root->left = reBalance(root->left, count, check);
	root->right = reBalance(root->right, count, check);
	return root;
}
HuffmanNode *turn_back_root(HuffmanNode *root, int &count)
{
	bool check = false;
	while (true)
	{
		root = reBalance(root, count, check);
		if (count == 0 || check == false)
		{
			break;
		}
		else
		{
			check = false;
		}
	}
	return root;
}
HuffmanNode* buildHuffmanTree(vector<pair<char,int>>&frequencymap) {
    int ordercount = 0;
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
    for (const auto& pair : frequencymap) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second, ordercount);
        pq.push(node);
    }
    ordercount++;
    while (pq.size() > 1) {
        HuffmanNode* leftChild = pq.top();
        pq.pop();
        HuffmanNode* rightChild = pq.top();
        pq.pop();
        HuffmanNode* internalNode = new HuffmanNode('\0', leftChild->frequency + rightChild->frequency,ordercount);
        internalNode->left = leftChild;
        internalNode->right = rightChild;
        int countRotate = 3;
		internalNode = turn_back_root(internalNode, countRotate);
		internalNode->order = ordercount;
        if (internalNode->data != '\0')
		{
			return nullptr;
		}
        pq.push(internalNode);
        ordercount++;
    }
    return pq.top();
}
HuffmanNode* lastest;
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
    if(huffmanroot==nullptr){
        return -1;
    }
    unordered_map<char, string> huffmanCode;
    encode(huffmanroot,"",huffmanCode);
    string str = "";
	for (char ch: caesarname) {
		str += huffmanCode[ch];
	}
    string tmp="";
    int strsize=str.size();
    if(strsize<=10){
        for(int i = strsize;i>0;i--){
            tmp+=str[i];
        }
    }
    else{
        for(int i =str.size()-1;i>strsize-11;i--){
            tmp+=str[i];
        }
    }
    return binaryToDecimal(std::stoi( tmp ));
}
void getinres(int result){
    if(result==-1){
        return;
    }
    int id = result%MAXSIZE + 1;
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
    for(long long int i =1;i<=n;i++){
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
    for(int i =1;i<n;i++){
        if(arr[i]<root){
            left.push_back(arr[i]);
        }
        else{
            right.push_back(arr[i]);
        }
    }
    int nleft=left.size();
    int countleft=counthoanvi(left,fact);
    int countright=counthoanvi(right,fact);
    return nCr(n-1,nleft)*countleft*countright;
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
    lastest = huffmanroot;
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
    if(Gojotable.empty()){
        return;
    }
    for(auto area: Gojotable){
        vector<int>postorder = BSTtoPostOrder(area.second);
        reverse(postorder.begin(), postorder.end());
        int fact[postorder.size()];
        int Y=counthoanvi(postorder,fact);
        remove(area.first,Y);
    }
}
void KEITEIKEN(int NUM){
    vector<SKNode> keiteiken;
    for(int i =0;i<sukunaheap.getSize();i++){
        keiteiken.push_back(*sukunaheap[i]);
    }
    sort(keiteiken.begin(),keiteiken.end(),[](SKNode a,SKNode b){
        return a.num==b.num? a.lastuse<b.lastuse:a.num<b.num;
    });
    int count = min(NUM, sukunaheap.getSize());
    while(count>0){
        SKNode tmp = keiteiken.front();
        keiteiken.erase(keiteiken.begin());
        sukunaheap.deleteCustomer(tmp.key,NUM);
        count--;
    }
}
void printEachAreaOfSukuna(SKNode* area, int num) {
    int count = min(num, area->num);
    for (int i = 0; i < count; i++) {
        cout << area->key << "-" << area->customers[i] << endl;
    }
}


void CLEAVE(int NUM){
    vector<SKNode*> preorder = sukunaheap.preorder();
    for(SKNode* area: preorder){
        if(NUM>area->num){
            for (int i = area->num-1; i >= 0; i--) {
                cout << area->key << "-" << area->customers[i] << endl;
            }
        }
        else{
            for(int i =area->num-1;i>=area->num-NUM;i--){
                cout<<area->key<<"-"<<area->customers[i]<<endl;
            }
        }
        
    }
}

void helperhand(HuffmanNode *latest){
    if(!latest){
        return;
    }
    helperhand(latest->left);
    if(latest->data=='\0'){
        cout<<latest->frequency<<endl;
    }
    else{
        cout<<latest->data<<endl;
    }
    helperhand(latest->right);  
}
void HAND(){
    helperhand(lastest);
}

void simulate(string filename)
{
	ifstream ss(filename);
	string str, maxsize, name, num;
	while (ss >> str)
	{
		if (str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
		}
		else if (str == "LAPSE")
		{
			ss >> name;
			LAPSE(name);
		}
		else if (str == "HAND")
		{
			HAND();
		}
		else if (str == "LIMITLESS")
		{
			ss >> num;
			int n = stoi(num);
			LIMITLESS(n);
		}
		else if (str == "CLEAVE")
		{
			ss >> num;
			int n = stoi(num);
			CLEAVE(n);
		}
		else if (str == "KEITEIKEN")
		{
			ss >> num;
			int n = stoi(num);
			KEITEIKEN(n);
		}
		else if (str == "KOKUSEN")
		{
			KOKUSEN();
		}
	}
	return;
}