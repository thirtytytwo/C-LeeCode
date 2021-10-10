
#include <iostream>
#include <vector>
#include "limits.h"
#include <algorithm>
#include <queue>;
#include <stack>;
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <cmath>
#include <string>
#include <set>

using namespace std;

typedef pair<int, float> _p;//pair将一对值组合成一个值，这一对值可以具有不同的数据类型（T1和T2），两个值可以分别用pair的两个公有函数first和second访问。是stl内部提供

//9.22所用结构体
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	
};

class Node {
public:
	int val;
	Node* prev;
	Node* next;
	Node* child;
};

//10.5
class Iterator {
	struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	
		// Returns the next element in the iteration.
		int next();
	
		// Returns true if the iteration has more elements.
		bool hasNext() const;
	
};

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
	//(9.12 leecode678)动态规划，一般都利用vector储存每个子问题的结果，然后把子问题的结果归总成整个问题的结果
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
	//(9.14 leecode524)
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
		}//搜索完了，发现整个dictionary的字符都遍历一边也没有returnfalse,则证明匹配，应该返回真
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
	//(9.15 leecode162)
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
	//9.16 leecode212 BFS解法
	unordered_set<string> s, t;
	vector<string> res;
	vector<vector<char>> copy;
	int n, m;
	int dx[4] = { -1, 0, 1, 0 };//尤其注意这四个方向是否为顺序遍历，不要耍小聪明
	int dy[4] = { 0, -1, 0, 1 };
	void dfs(int i, int j, string cur, vector<vector<bool>>& vis) {
		if (cur.size() > 10) {
			return;
		}
		if (s.count(cur)) {
			t.insert(cur);
		}
		for (int k = 0; k < 4; ++k) {
			int xx = i + dx[k];
			int yy = j + dy[k];
			if (xx >= 0 && xx < n && yy >= 0 && yy < m && !vis[xx][yy]) {
				vis[xx][yy] = true;
				dfs(xx, yy, cur + copy[xx][yy], vis);
				vis[xx][yy] = false;
			}
		}
	}
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		for (string item : words) {
			s.insert(item);
		}
		copy = board;
		n = board.size();
		m = board[0].size();

		string s;
		vector<vector<bool>> vis(n, vector<bool>(m));

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				vis[i][j] = true;
				dfs(i, j, s + board[i][j], vis);
				vis[i][j] = false;
			}
		}
		for (string tt : t) {
			res.push_back(tt);
		}
		return res;
		//采用BFS搜索办法，如果出现测试不能全部通过，则注意四个方向的遍历，是否是围成圆的顺序方向，解答错误原因就是因为，先便利了x轴的两个方向然后再遍历y轴的两个方向
	}
	//9.17
	static bool isValidSudoku(vector<vector<char>>& board) {
		int h = board[0].size();
		int v = board.size();
		vector<unordered_set<int>> horizontal(h);
		vector<unordered_set<int>> vertical(v);
		vector<unordered_set<int>> nine(h *v);	

		for (int i = 0; i < v; ++i) {
			for (int j = 0; j < h; ++j) {
				if (board[i][j] != '.') {
					int index = board[i][j] - '0';
					if (horizontal[j].count(index) || vertical[i].count(index) || nine[i / 3 * 3 + j / 3].count(index)) {
						return false;
					}
					else {
						horizontal[j].insert(index);
						vertical[i].insert(index);
						nine[i / 3 * 3 + j / 3].insert(index);
					}
				}
			}
		}
		return true;
	}
	//9.19
	//BFS算法，超时
	int BFS(int n,int current,int copy, int count) {
		if (current == n) {
			return count;
		}
		if (current > n) {
			return 1000000;
		}

		count++;
		if (copy == 0) {
			return BFS(n, current, current, count);
		}
		if (copy == current) {
			return BFS(n, current + copy, copy, count);
		}
		else {
			return (BFS(n, current, current, count) < BFS(n, current + copy, copy, count)) ? BFS(n, current, current, count) : BFS(n, current + copy, copy, count);
		}

	}
	int minSteps(int n) {
		return BFS(n, 1, 0, 0);
	}
	//动态规划
	static int MinSteps(int n) {
		//记录当前A字母个数时的粘贴次数，动态规划，把一个大的n分解成每一步的相加，空间换时间
		vector<int> ans(n + 1, 0);//因为下面for循环=n的条件下也符合情况，但是只有n个元素的话会导致访问vec越界的情况，所以n+1
		for (int i = 2; i <= n; ++i) {
			ans[i] = i;//一个个粘贴，次数最多的解法
			for (int j = 1; j * j <= i; ++j) {//这里其实j<=i也是也可以的，但是作者做了小优化，目前也不理解
				if (i % j == 0) {
					ans[i] = ans[j] + i / j;//利用因数，减少次数
				}
			}
		}
		return ans[n];
	}
	//9.20感冒，先粘贴，理解往后推迟一天 leecode673
	//9.21已上注释，但还不是很完善，这一题简易版在300，建议有空去做一下
	static int findNumberOfLIS(vector<int>& nums) {
		int n = nums.size(), maxLen = 0, ans = 0;
		vector<int> dp(n), cnt(n);
		for (int i = 0; i < n; ++i) {
			//初始化，假设每个位置的最长子序列就只有他自己，每个位置的最长子序列个数也只有他自己
			dp[i] = 1;
			cnt[i] = 1;
			for (int j = 0; j < i; ++j) {
				if (nums[i] > nums[j]) {
					if (dp[j] + 1 > dp[i]) {
						dp[i] = dp[j] + 1;//更新前面数字比他小的个数
						cnt[i] = cnt[j]; // 重置计数
					}
					else if (dp[j] + 1 == dp[i]) {//如果出现这个情况，就表示前一个数字并不是递增，所以现在这个位置是统计第二个子序列位置了，计数+1
						cnt[i] += cnt[j];
					}
				}
			}
			if (dp[i] > maxLen) {
				maxLen = dp[i];
				ans = cnt[i]; // 重置计数
			}
			else if (dp[i] == maxLen) {//这里同理当dp[i]等于之前计算得到的最大长度时，则表示，这个递增子序列已经遍历完了，将对应的个数加到答案中
				ans += cnt[i];
			}
		}
		return ans;
	}
	//9.21 leecode中秋福利题58
	static int lengthOfLastWord(string s) {
		int count = 0;
		int index = s.length() - 1;
		while (s[index] == ' ') {
			index--;//去除string最尾的空格
		}
		while (index >= 0 && s[index] != ' ') {
			//>=0是因为需要考虑s中只有一个char的情况，>0会遍历不到那一个字符
			//从末尾遍历s，符合条件让文字长度加1
			count++;
			index--;
		}
		return count;
	}
	//9.22 leecode725
	vector<ListNode*> splitListToParts(ListNode* head, int k) {
		int n = 0;
		ListNode* temp = head;
		while (temp != nullptr)//通过用temp指向head，不影响head的情况下遍历链表计数
		{
			n++;
			temp = temp->next;
		}
		
		int z = n / k;//每组中元素的个数
		int y = n % k;//除不尽的元素个数要在前几组中来分配，也就是+1
		vector<ListNode*>ans(k, nullptr);//储存答案的vector，因为链表的特点，只用储存分离后的各个头节点即可
		ListNode* cur = head;
		for (int i = 0; i < k && cur != nullptr; i++) {//根据有多少组进行循环
			ans[i] = cur;//将头节点存入vector
			int partSize = z + (i < y ? 1 : 0);//判断是不是要余元素
			for (int j = 1; j < partSize; j++) {
				cur = cur->next;//遍历到要分离的地方
			}
			//分离节点
			ListNode* a = cur->next;
			cur->next = nullptr;
			cur = a;
		}
		return ans;
	}
	//9.23 leecode326 太容易，没有上传的必要
	//9.24 leecode430
	Node* DFS(Node* node) {
		Node *cur = node;
		Node* lastPtr = nullptr;//用于指明当前的位置
		while (cur) {
			Node* _next = cur->next;//储存cur的下一个节点，用于合并孩子节点的尾节点
			if (cur->child != nullptr) {
				Node* last_Child = DFS(cur->child);

				//链接孩子节点头部
				_next = cur->next;
				cur->next = cur->child;
				cur->child->prev = cur;

				if (_next) {//如果next不为空，则合并孩子节点的尾节点
					last_Child->next = _next;
					_next->prev = last_Child;
				}
				//将这个已经搜索过的孩子地址设空，避免重复搜索
				cur->child = nullptr;
				//更新最尾的位置
				lastPtr = last_Child;
			}
			else {
				//如果没有孩子节点则一直更新最尾位置
				lastPtr = cur;
			}
			//更新当前链表位置
			cur = _next;
		}
		return lastPtr;//这个返回其实是没有必要的，因为整个深度算法运行完，链表已经排好了

	}
	Node* flatten(Node* head) {
		DFS(head);
		return head;
	}
	//9.26 leecode583
	int minDistance(string word1, string word2) {
		//获取两个string的大小
		int n = word1.size();
		int m = word2.size();

		//dp数组，加一是为了在nm处也要做计算，防止溢出
		vector<vector<int>> dp(n + 1, vector<int>(m + 1));
		//初始化两个数组，根据题意，假设每个字符都不想等，都要删除的情况
		for (int i = 1; i <= n; ++i) {
			dp[i][0] = i;
		}
		for (int j = 1; j <= m; ++j) {
			dp[0][j] = j;
		}
		//遍历数组
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				char c = word1[i-1];
				char d = word2[j-1];

				if (c == d) {//如果字符相等，则不用删除任何字符，所以结果就等于上一个的结果
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {//如果不相等，那么要不就是word1删除一个要不就是word2删除一个，根据题意选最小的结果
					dp[i][j] = ((dp[i][j - 1] < dp[i - 1][j]) ? dp[i][j - 1] : dp[i - 1][j]) + 1;
				}
			}
		}
		//返回最后一处的结果，就是答案
		return dp[n][m];
	}
	//9.27 leecode639
	long long dp[100003];
	//防止内存溢出的方法
	int mod = 1e9 + 7;
	int numDecodings(string s) {
		dp[0] = 1;
		dp[1] = (s[0] == '*' ? 9 : 1);//初始化第一个字符的编码方案次数

		if (s[0] == '0') dp[0] = dp[1] = 0;//如果第一个是零则前一个数编码方案次数为零，这里dp[0]不算在内代码也是可以运行的
		for (int i = 1; i < s.size(); i++) {//分析子问题
			//当第i个数是数字时的分析子问题
			if (s[i] != '*') {
				//只考虑这个字符的情况
				if (s[i] != '0') {
					dp[i + 1] = dp[i];
				}
				//考虑组合前面一个字符的情况
				if (s[i - 1] == '1') {
					dp[i + 1] += dp[i - 1];
				}
				else if (s[i - 1] == '2' && s[i] < '7') {
					dp[i + 1] += dp[i - 1];
				}
				else if (s[i - 1] == '*') {
					if (s[i] < '7') dp[i + 1] += (dp[i - 1] * 2);
					else dp[i + 1] += dp[i - 1];
				}
			}
			//当第i个数是*时的分析子问题
			else {
				//只考虑这个字符的情况
				dp[i + 1] += dp[i] * 9;
				//考虑组合前一个字符的情况
				if (s[i - 1] == '1')dp[i + 1] += dp[i - 1] * 9;
				else if (s[i - 1] == '2')dp[i + 1] += dp[i - 1] * 6;
				else if (s[i - 1] == '*')dp[i + 1] += dp[i - 1] * 15;
			}
			//防止溢出的手法
			dp[i + 1] %= mod;
		}
		return dp[s.size()];
		//对于同样是计算前i个字符的次数加上第i个字符配合，有些时候时dpi-1，有些时候时dpi，首先，对于dpi的理解，就是第i个数之前的所有结果的次数，是上一个循环中计算出的dpi+1
		//那么在dpi的使用场景中，都是当单独把i个字符编译，是只考虑这个字符的情况，那么如果要组合，就不能用dpi，因为dpi包括了这个字符，得用dpi-1
	}
	// 9.28 leecode437
	//深度搜索，递归方法
	int DfsSum(TreeNode* root, int targetSum) {
		if (!root) {
			return 0;//如果当前节点是空，就返回零
		}
		
		int ans = 0;

		if (root->val == targetSum) {
			ans++;//如果当前的节点等于剩余的targetsum，则证明这条路径成立，路径数加一
		}
		//DFS左右子节点寻找路径
		ans += DfsSum(root->left, targetSum - root->val);
		ans += DfsSum(root->right, targetSum - root->val);

		return ans;
	}
	int pathSum(TreeNode* root, int targetSum) {
		if (!root) {
			return 0;//如果当前节点是空，就返回零，及这里不可能有路径
		}

		int ans = DfsSum(root, targetSum);//当前这个节点存在的路径树

		//DFS左右节点，以左右节点为root再调用DFSSum
		ans += pathSum(root->left, targetSum);
		ans += pathSum(root->right, targetSum);

		//返回所有节点的路径数
		return ans;
	}
	//9.29 leecode517
	//贪心算法
	int findMinMoves(vector<int>& machines) {
		//定义三个int，分别是，衣服总数，最小分配次数，还有前i个洗衣机衣服总数（局部总数）
		int sum = 0;
		int ans = 0;
		int localSum = 0;

		//遍历一边数组，求衣服总数
		for (int i = 0; i < machines.size(); i++) {
			sum += machines[i];
		}
		//如果衣服总数和洗衣机数不能除尽，则表示会有剩余，不能平均分配完全
		if (sum % machines.size() !=0) {
			return -1;
		}
		//衣服平均数
		int avg = sum / machines.size();

		for (int i = 0; i < machines.size(); i++) {
			localSum += machines[i];
			//比较出最大的结果，因为这三个结果都是对于各个情况最小的，所以比较最大的这样既满足另外两个的分配次数，又能保证结果是所有都通过后的最小值
			ans = max(ans, max(machines[i] - avg, abs(localSum - avg * (i + 1))));
		}
		return ans;
	}
	//9.30 leecode223
	int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
		int area = (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1);

		int overlapLong = max(0, (min(ax2, bx2) - max(ax1, bx1)));
		int overlapWidth = max(0, (min(by2, ay2) - max(ay1, by1)));

		return area - (overlapLong * overlapWidth);
	}
	//10.2 leecode405
	string hex = "0123456789abcdef";
	string toHex(int num) {
		if (num == 0) {
			return "0";
		}

		long long n = num < 0 ? (long long)num + (1ll << 32) : num;

		string s;
		while (n) {
			int mod = n % 16;
			n /= 16;
			s += hex[mod];
		}

		reverse(s.begin(), s.end());
		return s;
	}
	//10.3 leecode166
	static string fractionToDecimal(int numerator, int denominator) {
		long long num = numerator, den = denominator;//用longlong防止int范围溢出
		string ans;
		long long test = num * den;
		if (test == 0) {
			return "0";//证明有一个树是0，返回0即可
		}
		if (test < 0) {
			ans += "-";//证明为负数，那么则要在答案前面加负号
		}
		//把两个数变为绝对值进行计算
		num = abs(num);
		den = abs(den);
		//计算整数部分
		long long pre = num / den;
		ans += std::to_string(pre);
		//如果计算完整数部分刚好等于0，那么就是证明能整除直接返回就行
		if (num % den == 0) {
			return ans;
		}
		//加上小数点
		ans += ".";
		//将整数部分用到的数减去
		num = num - (num / den) * den;

		int index = ans.size();
		unordered_map <int, int>pos;//哈希表，用于存储数出现的位置，key是数值，value是该数在ans中出现的位置
		while (num && (pos.find(num) == pos.end())) {//如果找不到，而且num没被除尽
			pos[num] = index++;//先将num出现的位置作为value保存在哈希表中，然后再将位置加1
			num *= 10;//补位，让下一位除为整数
			ans += char('0' + num / den);//asc表，加上零之后进行转码成char类型
			num = num - (num / den) * den;//减去计算完的部分
		}
		if (num != 0) {//如果哈希表找到了值，而且num还没被除尽的情况下，加括号
			int lastPos = pos[num];
			ans = ans.substr(0, lastPos)/*从0到第一次出现重复的位置*/ + '(' + ans.substr(lastPos)/*从第一次重复的位置一直到末尾*/ + ')';
		}
		return ans; 
	}
	//10.4
	string licenseKeyFormatting(string s, int k) {
		// 1. 先提取密钥
		string key;
		// 遍历密钥字符串，将破折号除去
		for (char c : s) {
			if (c != '-') {
				key += c;
			}
		}

		// 2. 转化为大写字母，注意这里遍历时要加 & 符号，表示引用，可以直接修改。若不加则没有修改
		for (char& c : key) {
			if (c <= 'z' && c >= 'a') {
				c = c - 'a' + 'A';
			}
		}

		// 3. 分组
		// 结果字符串
		string ret;
		int n = key.size();
		// 除第一组外，其余各组均为 k 个字符
		int group = n / k;
		if (n % k == 0) {
			// 共 group 组，每组 k 个
			for (int i = 0; i < group; ++i) {
				// 第 i 组字符为 [i * k, (i + 1) * k)
				ret += key.substr(i * k, k);
				// 除最后一组外，均加上破折号
				if (i < group - 1) ret += '-';
			}
		}
		else {
			// 共 group + 1 组，第一组 n % k 个，其余组 k 个
			ret += key.substr(0, n % k);
			if (group > 0) {
				// 还有其余组
				// 先加一个破折号
				ret += '-';
				for (int i = 0; i < group; ++i) {
					// 第 i 组字符为 [i * k + n % k, (i + 1) * k + n % k)
					ret += key.substr(i * k + n % k, k);
					// 除最后一组外，均加上破折号
					if (i < group - 1) ret += '-';
				}
			}
		}
		return ret;
	}
	//10.6 lecode414
	int thirdMax(vector<int>& nums) {
		set<int> ans;//set和Map差不多，只不过他的key就是value，而且不能改，并且set默认less排序
		for (int i = 0; i < nums.size(); ++i) {
			ans.insert(nums[i]);
			if (ans.size() > 3) {
				ans.erase(ans.begin());//删除最小的数
			}
		}
		if (ans.size() == 3) {
			return *ans.begin();//等于三返回最小的，也就是第三个大的
		}
		return *ans.rbegin();//小于3，这样就返回最大的，rbegin和begin的差别就是前者是返回反转后的第一个，后者是返回第一个
	}
	//10.7 leecode434 简单说一下，简单的遍历模拟， 只不过我之前找错了应该让计数器加一的点，其实不是应该是空格，而是空格后面的字符，i==0是边界情况
	int countSegments(string s) {
		int ret = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] != ' ' && (i == 0 || s[i - 1] == ' ')) {
				ret++;
			}
		}
		return ret;
	}
	//10.8 leecode187
	vector<string> findRepeatedDnaSequences(string s) {
		vector<string> ans;
		unordered_map<string, int> map;
		int n = s.size();//因s.size()的类型是unsigned，比范围比int小，如果下次做题遇到遍历越界，可能就是这个问题
		for (int i = 0; i <= s.size() - 10; ++i) {
			string _s = s.substr(i,10);
			if (++map[_s] == 2) {
				ans.push_back(_s);
			}
		}
		return ans;
	}
	//10.10 leecode441
	static int arrangeCoins(int n) {
		long long l = 1, r = n;
		while (l < r)
		{
			long long mid = (l + r + 1) / 2;//加一是因为编程中除法是取整除的部分，这题中只取整数部分会有死循环，所以加一让他取偏大的结果
			long long sum = (1 + mid) * mid / 2;
			if (sum <= n) {
				l = mid;
			}
			else {
				r = mid - 1;
			}
		}
		return l;
	}
};

//10.5 leecode284 没有什么好讲解的，基本上都是leecode原本封装好的函数，不过有几个疑问，第一个就是对于::和->和.的引用方法方式到底有什么差别，还有就是有点忘记接口的用法了，将这些列入明天复习计划
class PeekingIterator : public Iterator {
private:
	bool Flag;
	int nextValue;
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
		Flag = Iterator::hasNext();
		if (Flag) {
			nextValue = Iterator::next();
		}
	}

	int peek() {
		return nextValue;
	}

	int next() {
		int ret = nextValue;
		Flag = Iterator::hasNext();
		if (Flag) {
			nextValue = Iterator::next();
		}
	}

	bool hasNext() const {
		return Flag;
	}

};
//10.9 leecode352
class SummaryRanges {
public:
	unordered_set<int> _set;//集合用来存储val出现的次数
	vector<vector<int>> _ret;

	SummaryRanges() {
	}

	//二分查找，用来搜寻值val + 1或者val - 1的下标位置
	int binarySearch(int Target,int Rightorleft) {
		int right = _ret.size() - 1;
		int left = 0;
		int ans;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (_ret[mid][Rightorleft] > Target) {
				right = mid - 1;
			}
			else if (_ret[mid][Rightorleft] == Target) {
				ans = mid;
				return ans;
			}
			else {
				left = mid + 1;
			}
		}
		return ans;
	}
	void addNum(int val) {
		if (_set.count(val)) {//如果存在了，就不用重复计算了
			return;
		}
		_set.insert(val);//记录val的出现
		if (_set.count(val - 1) && _set.count(val + 1)) {//如果两个边界都出现，就合并两个区间
			int left = binarySearch(val - 1, 1);
			int right = binarySearch(val + 1, 0);

			_ret[left][1] = _ret[right][1];
			_ret.erase(_ret.begin() + right);//清除，从begin位置迭代器移动right次，也就是清楚right位置
		}
		else if (_set.count(val - 1)) {//如果只出现左半边，就合并左区间，并且把左区间的右边界设成val
			int ans = binarySearch(val - 1, 1);
			_ret[ans][1] = val;
		}
		else if (_set.count(val + 1)) {//同上理
			int ans = binarySearch(val + 1, 0);
			_ret[ans][0] = val;
		}
		else {
			//如果没有就自己立一个区间
			_ret.push_back(vector<int>{val, val});
		}
		//题目要求，从小到大排序
		sort(_ret.begin(), _ret.end());
	}

	vector<vector<int>> getIntervals() {
		return _ret;
	}
};

int main() {
	Solution::arrangeCoins(5);
}