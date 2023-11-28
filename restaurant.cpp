#include "main.h"

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
void simulate(string filename)
{
	cout << "Good Luck";
	return;
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