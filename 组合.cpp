#include <iostream>
#include <vector>

using namespace std;
//要改变ng+ns的值，就改变people里面的数字
vector<int> people = {1,2,3,4,5,6,7,8,9,10,11,12};
vector<int> combination;
vector<vector<int>> result;

vector<vector<int>> go(int offset, int k) {
	if (k == 0) {
		result.push_back(combination);
		return result;
	}
	//每次递归结束后，要考虑i是不是i <= people.size() - k，如果没有继续i++，如果i大于这个，返回上一次递归
	for (int i = offset; i <= people.size() - k; ++i) {
		combination.push_back(people[i]);
		go(i + 1, k - 1);
		combination.pop_back();//删除combination最后一个元素
	}
	return result;
}
