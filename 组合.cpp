#include <iostream>
#include <vector>

using namespace std;
//Ҫ�ı�ng+ns��ֵ���͸ı�people���������
vector<int> people = {1,2,3,4,5,6,7,8,9,10,11,12};
vector<int> combination;
vector<vector<int>> result;

vector<vector<int>> go(int offset, int k) {
	if (k == 0) {
		result.push_back(combination);
		return result;
	}
	//ÿ�εݹ������Ҫ����i�ǲ���i <= people.size() - k�����û�м���i++�����i���������������һ�εݹ�
	for (int i = offset; i <= people.size() - k; ++i) {
		combination.push_back(people[i]);
		go(i + 1, k - 1);
		combination.pop_back();//ɾ��combination���һ��Ԫ��
	}
	return result;
}
