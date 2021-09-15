
#include <iostream>
#include <vector>
#include "limits.h"
#include <algorithm>
#include <queue>;
#include <stack>;
#include <unordered_map>

using namespace std;

typedef pair<int, float> _p;//pair将一对值组合成一个值，这一对值可以具有不同的数据类型（T1和T2），两个值可以分别用pair的两个公有函数first和second访问。是stl内部提供


class Solution {
public:
	static int search(vector<int>& nums, int target) {
		int max = (int)nums.size();
		int _begin = 0;
		int _end = max - 1;
		while (_begin <= _end) {
			int mid = (_end + _begin) / 2;
			if (nums[mid] == target) {
				return mid;
			}
			else if (nums[mid] < target) {
				_begin = mid - 1 ;
			}
			else{
				_end = mid + 1;
			}
		}
		return -1;
	}
	static double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int m = nums1.size();
		int n = nums2.size();
		int left = (m + n + 1) / 2;
		int right = (m + n + 2) / 2;

		return (double)(findK(nums1, 0, nums2, 0, left) + findK(nums1, 0, nums2, 0, right)) / 2;
	}
	static int findK(vector<int>& nums1, int i, vector<int>& nums2, int j, int k) {
		//如果是空数组
		if (i >= nums1.size())return nums2[j + k - 1];
		if (j >= nums2.size())return nums1[i + k - 1];

		if (k == 1) {
			return (nums1[i] > nums2[j]) ? nums2[j] : nums1[i];
		}

		int midVal1 = (i + k / 2 - 1 < nums1.size()) ? nums1[i + k / 2 - 1] : INT_FAST64_MAX;
		int midVal2 = (j + k / 2 - 1 < nums2.size()) ? nums2[j + k / 2 - 1] : INT_FAST64_MAX;

		if (midVal1 < midVal2) {
			return findK(nums1, i + k / 2, nums2, j, k - k / 2);
		}
		else {
			return findK(nums1, i, nums2, j + k / 2, k - k / 2);
		}
	}
	static int BalancedStringSplit(string s) {
		int count = 0;
		int n = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == 'R') {
				n++;
			}
			else {
				n--;
			}
			if (n == 0) {
				count++;
			}
		}
		return count;
	}
	static int FindMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
		int n = profits.size();
		int count = 0;
		priority_queue<int, vector<int>, less<int>> q;//优先队列：区别于普通队列的先进先出，优先队列可以做到根据优先级出列,此处为大顶堆的实现，小顶堆则是采用greater升序排列即可
		vector<_p> arr;
		for (int i = 0; i < n; ++i)
		{
			arr.push_back({ capital[i],profits[i] });
		}
		sort(arr.begin(), arr.end());
		for (int i = 0; i<k;++i)
		{
			while (count < n && arr[count].first <= w)
			{
				q.push(arr[count].second);
				count++;
			}
			if (!q.empty()) {
				w += q.top();
				q.pop();
			}
			else {
				break;
			}
		}
		return w;
	}
	static int chalkReplacer(vector<int>& chalk, int k) {
		int _left = 0;
		int _right = chalk.size() - 1;

		for (int i = 0; i < chalk.size(); ++i)
		{
			chalk[i] += (i - 1 < 0 ? 0 : chalk[i - 1]);
			if (chalk[i] > k) {
				return i;
			}
		}

		k %= chalk[chalk.size() - 1];

		while (_left < _right)
		{
			int mid = (_left + _right) / 2;
			if (chalk[mid] > k) {
				_right = mid;
			}
			else {
				_left = mid + 1;
			}
		}
		return _right;
	}
	//(9.11 leecode600 没理解)
	static int findIntegers(int n) {
		vector<int> dp(31);//(31)则是构造函数，定义了vector大小于此对应的[n]则是n个vector，多维数组的意思
		dp[0] = dp[1] = 1;
		for (int i = 2; i < 31; ++i)
		{
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		int pre = 0, res = 0;
		for (int i = 29;i >=0;--i)
		{
			int val = 1 << i;
			if ((n & val) != 0) {
				res += dp[i + 1];

				if (pre == 1) {
					break;
				}
				pre = 1;
			}
			else {
				pre = 0;
			}
			if (i == 0) {
				++res;
			}
		}
		return res;
	}
	//(9.12 leecode 678)动态规划，一般都利用vector储存每个子问题的结果，然后把子问题的结果归总成整个问题的结果
	static bool checkValidString(string s) {
		int n = s.size();
		vector<vector<bool>> dp = vector<vector<bool>>(n, vector<bool>(n, false));

		for (int i = 0; i < n; i++)
		{
			if (s[i] == '*') {
				dp[i][i] = true;
			}
		}
		for (int i = 1; i < n; i++) {
			char c1 = s[i - 1];
			char c2 = s[i];

			dp[i - 1][i] = (c1 == '(' || c1 == '*') && (c2 == ')' || c2 == '*');
		}
		for (int i = n - 3; i >= 0; i--) {
			char c1 = s[i];
			for (int j = i + 2; j < n; j++) {
				char c2 = s[j];
				if ((c1 == '(' || c1 == '*') && (c2 == ')' || c2 == '*')) {
					dp[i][j] = dp[i + 1][j - 1];
				}
				for (int k = i; k < j && !dp[i][j]; k++) {
					dp[i][j] = dp[i][k] && dp[k + 1][j];
				}
			}
		}
		return dp[0][n - 1];
	}
	bool checkValidStringByStack(string s) {
		stack<int>leftStack;
		stack<int>starStack;
		int n = s.size();
		for (int i = 0; i < n; ++i) {
			if (s[i] == '(') {
				leftStack.push(i);//将左括号的下标依次入栈
			}
			else if (s[i] == '*') {
				starStack.push(i);//将星号的下标依次入栈
			}
			else {//遇到右括号的情况
				if (!leftStack.empty()) {
					leftStack.pop();//优先检测是否有多的左括号，有的话先拿左括号进行配对
				}
				else if (!starStack.empty()) {
					starStack.pop();//没有左括号就用星号进行配对
				}
				else {
					return false;//证明右括号多出，返回假
				}
			}
		}
		while (!leftStack.empty() && !starStack.empty()) {//将多余的左括号和星号配对
			int leftIndex = leftStack.top();//返回左括号最顶元素
			leftStack.pop();//左括号出栈
			int starIndex = starStack.top();//返回星号最顶元素
			starStack.pop();//星号出栈
			if (leftIndex > starIndex) {//如果有这个情况，则证明左括号的位置在星号右边，即不能和星号配对
				return false;
			}
		}
		return leftStack.empty();
	}
	//(9.13 leecode447)
	static int numberOfBoomerangs(vector<vector<int>>& points) {
		int ans = 0;//记录答案
		for (auto& p : points) {
			unordered_map<int, int> cnt;//利用哈希表存储相同距离出现的次数，key是距离，value是次数
			for (auto& q : points) {
				int dis = (p[0] - q[0]) * (p[0] - q[0]) + (p[1] - q[1]) * (p[1] - q[1]);//直角边平方和求斜边
				++cnt[dis];//给key为dis的值加1，表示，这个距离出现的次数加一
			}
			for (auto m : cnt) {
				ans += m.second * (m.second - 1);//最后总结这个循环各种距离出现的次数，因为例题中设计排列组合，需要将结果排列组合，m个中取出两个两两排列。
			}
		}
		return ans;//返回答案
		//自己写时候的错误：将哈希表声明在循环外，这样就导致，哈希表中记录的数据有重复，因为我们是对vector中的每个元素对应所有元素都遍历了一遍，存储在外面就会导致，遍历到的相同次数比正确的答案多了一倍
		//因为重复了，所以，就导致ans出错。比正确答案大很多
	}
	//(9.14 leecode 524)
	static bool isSame(string dicString,string sString) {
		int n = dicString.size();
		int m = sString.size();
		if (n > m) {//如果n大于m，则表示dic中的字符串比s中的要长，不符合题意，所以return false
			return false;
		}
		int v = 0;//记录位置
		for (char s : dicString) {
			while (v < m && sString[v] != s)
			{
				v++;//如果在m的范围内没搜到，就搜下一个
			}
			if (v >= m) {
				return false;//根据上列发现遍历完整个string都没有搜到这个字符，则表示这个字符串不合题意，所以return false
			}

			v++;//如果进入上列的判断条件，则表示搜索到了，则下一个搜索位置为 v+1
		}//搜索完了，发现整个dictionary的字符都遍历一边也没有return false，则证明匹配，应该返回真
		return true;
	}
	static bool Cmp(string& a, string& b) {
		if (a.size() == b.size()) return a < b;//如果两个字符串的长度都一样，则根据他们存储的地址，因为vector是申请一块连续内存进行存储，那么，下标靠前的存储地址就靠前，所以这里是根据他们的存储地址进行升序排列
		else return a.size() > b.size();//如果不一样长，则优先排列长的
	}
	static string findLongestWord(string s, vector<string>& dictionary) {
		//对dictionary进行一个重排
		sort(dictionary.begin(), dictionary.end(), Cmp);
		//类似foreach，昨天的题也用过，将重排后的dictionary中的每个元素都拿来和s比较
		for (string& t : dictionary) {
			if (isSame(t, s)) {
				return t;//找到了就返回这个字符串
			}
		}
		return " ";//找不到根据题意返回一个空格
	}
	//(9.15 leecode 162)
	//题目要求时间复杂度在logN程度，优先考虑二分法
	int findPeakElement(vector<int>& nums) {
		int left = 0;
		int right = nums.size() - 1;//二分法的两个指针
		while (left < right) {
			int mid = (left + right) / 2;//中间值
			if (nums[mid] < nums[mid + 1]) {//根据题目要求，如果小于后面一个值，根据题意，如果是有峰的情况下必然存在一个峰在后面
				left = mid + 1;//继续二分查找
			}
			else {
				right = mid;//因为题意不可能有连续的两个数相当，所以这个意思是，当大于的时候就移动right指针，继续二分
			}
		}
		return left;//返回符合题意的数的下标
		//这一题能看出自己能想到二分，也能知道大致步骤，但是对于判断更改left和right指针的条件，还有具体怎么更改还是不太清楚，得加强
	}
	
};

int main() {
	string s = "abpcplea";
	vector<string> dic = { "ale","apple","monkey","plea" };
	Solution::findLongestWord(s, dic);
}