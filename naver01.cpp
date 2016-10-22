#include <cstdio>
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main() {
	string name;
	map<string, int> m;
	int max=0;
	map<string, int>::iterator it;

	while(getline(cin, name)) {
		it = m.find(name);
		if(it == m.end()) {
			m[name] = 1;
		} else {
			m[name]++;
		}
		if (max < m[name]) max = m[name];
	}

	for(it = m.begin();it != m.end();++it) {
		if (it->second == max) {
			cout << it->first << endl;
		}
	}
	return 0;
}