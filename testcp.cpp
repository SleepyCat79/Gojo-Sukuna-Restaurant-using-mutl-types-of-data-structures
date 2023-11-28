

// C++ implementation to
// print the characters and
// frequencies in order
// of its occurrence
#include <bits/stdc++.h>
using namespace std;

template <typename E>
class HuffNode{
    public: 
    virtual ~HuffNode(){}
    virtual int weight()=0;
    virtual bool isLeaf()=0;
};
template <typename E>
class LeafNode: public HuffNode<E>{
    private:
    E it;
    int wgt;
    public:
    LeafNode(const E& val,int freq): it(val),wtg(freq);
    int weight(){return wgt;}
    E val(){return it;}
    bool isLeaf(){return true;}
};
template <typename E>
class IntlNode: public HuffNode<E>{
    private:
    HuffNode<E>* lc;
    HuffNode<E>* rc;
    int wgt;
    public:
    IntlNode(HuffNode<E>* L,HuffNode<E>* r): wgt(l->weight()+r->weight()),lc(l),rc(r){}
    int weight(){return wgt;}
    bool isLeaf(){return true;}
    HuffNode<E>* left() const{return lc;}
    void setLeft(HuffNode<E>* b){lc = b;}
    HuffNode<E>* left() const{return rc;}
    void setRight(HuffNode<E>* b){rc = b;}
};

template <typename E>
class HuffTree{
    private:
    HuffNode<E>* Root;
    public:
    HuffTree(E& val, int freq) : Root(new LeafNode<E>(val,freq)){}
    HuffTree(HuffTree<E>* L, HuffTree<E>* r): Root(new IntlNode<E>(l->root(), r->root())){}
    ~HuffTree(){delete Root;}
    HuffNode<E>* root(){return Root;}
    int weight(){return Root->weight();}
};

template <typename E>
struct minTreecomp{
    bool operator()(const HuffTree<E>* x, const HuffTree<E>* Y) const{
        return x->weight()>y->weight();
    }
};

template <typename E>
HuffTree<E>* buildHuff(unordered_map<E, int>& freq){
    priority_queue<HuffTree<E>*, vector<HuffTree<E>*>, minTreecomp<E>> forest;
    for(auto& pair: freq){
        forest,push(new HuffTree<E>(pair.first,pair.second));
    }
    whille(forest.size()>1){
        HuffTree<E>* temp1 = forest.top();
        forest.pop();
        HuffTree<E>* temp2 = forest.top();
        forest.pop();
        forest.push(new HuffTree<E>(temp1, temp2));
    }
    return forest.top();
};

void sortmap(unordered_map<char, int>&freq) {
    unordered_map<int, vector<char>> sortedFreq;

    for (auto& pair : freq) {
        sortedFreq[pair.second].push_back(pair.first);
    }

    for (auto& pair : sortedFreq) {
        sort(pair.second.begin(), pair.second.end());
    }

    freq.clear();

    for (auto& pair : sortedFreq) {
        for (char c : pair.second) {
            freq[c] = pair.first;
        }
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
	sortmap(freq);
	unordered_map<char,int>x;
	for(const auto& pair:freq){
		char orgi = pair.first;
		int frequency=pair.second;
		char caesar = (orgi-'a'+frequency) % 26 + 'a';
		x[caesar]=frequency;
	}

}
 
// Driver Code
int main()
{
    string s = "Vo Nguyen Gia Huy";
    LAPSE(s);
}
 
// This code is contributed by rutvik_56