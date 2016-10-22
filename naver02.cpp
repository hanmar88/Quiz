#include <cstdio>
#include <stack>
using namespace std;

#define min(a,b) ((a)<(b))?(a):(b)
#define OPEN 0
#define CLOSE 1
#define MOD 100000000
#define STR_SIZE 10005

char *OPERATOR[3] = {"()", "{}", "[]"};
int OP_VAL[3] = {1, 2, 3}; // () = 1, {} = 2, [] = 3

typedef struct Item{
	int operand, depth;
	Item(int _operand, int _depth) {
		operand = _operand;
		depth = _depth;
	}
} item;

void calc_op(stack<item> &s, int cur_depth, int operand) {
	if (s.empty() || s.top().depth < cur_depth) {
		s.push(item(operand, cur_depth));
		return;
	}
	item _top = s.top();
	if (_top.depth == cur_depth) { // +
		s.pop();
		calc_op(s, min(_top.depth, cur_depth), (_top.operand + operand) % MOD);
	} else if (_top.depth > cur_depth) { // *
		s.pop();
		calc_op(s, min(_top.depth, cur_depth), (_top.operand * operand) % MOD);
	}
}

int calc(char *str) {
	stack<char> s;
	stack<item> s_operand;
	char c;
	for (int i = 0;str[i] != '\0';i++) {
		c = str[i];
		for (int j = 0;j < 3;j++) {
			if (c == OPERATOR[j][OPEN]) {
				s.push(c);
			} else if (c == OPERATOR[j][CLOSE]) {
				if (!s.empty() && s.top() == OPERATOR[j][0]) {
					s.pop();
					calc_op(s_operand, s.size(), OP_VAL[j]);
				} else {
					return 0;
				}
			}
		}
	}
	if (!s.empty()) {
		return 0;
	} 
    return s_operand.top().operand;
}

int main() {
	int tc;
	char str[STR_SIZE];
	scanf("%d", &tc);

	while (tc--) {
		scanf("%s", str);
		printf("%d\n", calc(str));
	}

	return 0;
}