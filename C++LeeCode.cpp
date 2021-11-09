
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
typedef pair<int, int> _Pos;

//9.22所用结构体
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}

};
class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
	
};

class Node1 {
public:
	int val;
	Node1* prev;
	Node1* next;
	Node1* child;
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
	Node1* DFS(Node1* node) {
		Node1 *cur = node;
		Node1* lastPtr = nullptr;//用于指明当前的位置
		while (cur) {
			Node1* _next = cur->next;//储存cur的下一个节点，用于合并孩子节点的尾节点
			if (cur->child != nullptr) {
				Node1* last_Child = DFS(cur->child);

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
	Node1* flatten(Node1* head) {
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
	//10.11
	//leecode273
		//用来存储对应的英文单词
	vector<string> singles = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
	vector<string> teens = { "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
	vector<string> tens = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
	vector<string> thousands = { "", "Thousand", "Million", "Billion" };

	string numberToWords(int num) {
		string sb;
		if (num == 0) {
			return "Zero";
		}
		//根据英文每三位标逗号知道是每三位算一次，题意的范围最大则是1000000000，所以只有三次循环，为此减去3个0
		for (int i = 3, uint = 1000000000; i >= 0; i--, uint /= 1000) {
			int cur = num / uint;
			if (cur != 0) {
				num -= cur * uint;
				string curr;
				recursion(curr, cur);//确定这三位数中具体对应的英文
				curr = curr + thousands[i] + " ";//再加上现在算好的千位和空格
				sb += curr;
			}
		}
		while (sb.back() == ' ') {
			sb.pop_back();//如果最后一个是空格，根据题意，需要删除
		}
		return sb;
	}
	void recursion(string& curr, int curNum) {
		if (curNum == 0) {
			return;
		}
		else if (curNum < 10) {
			curr += singles[curNum] + " ";//个位数上的计算
		}
		else if (curNum < 20) {
			curNum %= 10;
			curr += teens[curNum] + " ";//10~20的teens计算
		}
		else if (curNum < 100) {
			curr += tens[curNum / 10] + " ";
			recursion(curr, curNum % 10);//20以上的十位计算，再递归计算个位
		}
		else {
			curr += singles[curNum / 100] + " Hundred ";
			recursion(curr, curNum % 100);//前几个都不符合则表示是百位，所以百位的计算，在递归计算十位和各位
		}
	}
	//leecode217
	bool containsDuplicate(vector<int>& nums) {
		unordered_set<int> _set;
		for (int i = 0; i < nums.size(); ++i) {
			if (_set.count(nums[i])) {
				return true;
			}
			_set.insert(nums[i]);
		}
		return false;
	}
	//leecode053
	int maxSubArray(vector<int>& nums) {
		int n = nums.size();
		vector<int> dp(n);
		dp[0] = nums[0];
		int ans = dp[0];
		for (int i = 1; i < n; ++i) {
			dp[i] = max(nums[i], dp[i - 1] + nums[i]);
			ans = max(ans, dp[i]);
		}
		return ans;
	}
	//10.12
	//leecode029 没理解，只知道大概意思，找时间再看看
	int divide(int dividend, int divisor) {
		if (dividend == 0) return 0;
		if (divisor == 1) return dividend;
		if (divisor == -1) {
			if (dividend > INT_MIN) return -dividend;// 只要不是最小的那个整数，都是直接返回相反数就好啦
			return INT_MAX;// 是最小的那个，那就返回最大的整数啦
		}
		long a = dividend;
		long b = divisor;
		int sign = 1;
		if ((a > 0 && b < 0) || (a < 0 && b>0)) {
			sign = -1;
		}
		a = a > 0 ? a : -a;
		b = b > 0 ? b : -b;
		long res = div(a, b);
		if (sign > 0)return res > INT_MAX ? INT_MAX : res;//根据题意，溢出就采用最大值
		return -res;
	}
	int div(long a, long b) {
		if (a < b) return 0;
		long count = 1;
		long tb = b; // 在后面的代码中不更新b
		while ((tb + tb) <= a) {
			count = count + count; // 最小解翻倍
			tb = tb + tb; // 当前测试的值也翻倍
		}
		return count + div(a - tb, b);
	}
	//leecode 001
	vector<int> twoSum(vector<int>& nums, int target) {
		int n = nums.size();
		vector<int> ans;
		for (int i = 0; i < n - 1; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (nums[i] + nums[j] == target) {
					ans.push_back(i);
					ans.push_back(j);
				}
			}
		}
		return ans;
	}
	//leecode088
	static void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		for (int i = 0; i != n; ++i) {
			nums1[m + i] = nums2[i];
		}
		sort(nums1.begin(), nums1.end());
	}
	//leecode070
	int climbStairs(int n) {
		vector<int> dp(n + 3);
		dp[0] = 0;
		dp[1] = 1;
		dp[2] = 2;
		for (int i = 3; i <= n; ++i) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n];
	}
	//leecode746
	int minCostClimbingStairs(vector<int>& cost) {
		int n = cost.size();
		vector<int> dp(n + 1);
		dp[0] = dp[1] = 0;
		for (int i = 2; i <= n; ++i) {
			dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
		}
		return dp[n];
	}
	//10.13
	//leecode412
	vector<string> fizzBuzz(int n) {
		vector<string> answer;
		for (int i = 1; i <= n; i++) {
			string curr;
			if (i % 3 == 0) {
				curr += "Fizz";
			}
			if (i % 5 == 0) {
				curr += "Buzz";
			}
			if (curr.size() == 0) {
				curr += to_string(i);
			}
			answer.emplace_back(curr);
		}
		return answer;
	}
	//leecode350
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		if (nums1.size() > nums2.size()) {
			return intersect(nums2, nums1);
		}
		unordered_map <int, int> m;
		for (int num : nums1) {
			++m[num];
		}
		vector<int> intersection;
		for (int num : nums2) {
			if (m.count(num)) {
				intersection.push_back(num);
				--m[num];
				if (m[num] == 0) {
					m.erase(num);
				}
			}
		}
		return intersection;
	}
	//leecode121
	int maxProfit(vector<int>& prices) {
		int inf = 1e9;
		int minprice = inf, maxprofit = 0;
		for (int price : prices) {
			maxprofit = max(maxprofit, price - minprice);
			minprice = min(price, minprice);
		}
		return maxprofit;
	}
	//leecode198
	int rob(vector<int>& nums) {
		if (nums.empty()) {
			return 0;
		}
		int n = nums.size();
		if (n == 1) {
			return nums[0];
		}
		vector<int> dp(n, 0);
		dp[0] = nums[0];
		dp[1] = max(dp[0], nums[1]);
		for (int i = 2; i < n; ++i) {
			dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
		}
		return dp[n - 1];
	}
	//leecode213
	int robRange(vector<int>& nums, int start, int end) {
		int first = nums[start];
		int second = max(nums[start], nums[start + 1]);
		for (int i = start + 2; i <= end; ++i) {
			int temp = second;
			second = max(first + nums[i], second);
			first = temp;
		}
		return second;
	}
	int Rob(vector<int>& nums){
		int n = nums.size();
		if (n == 1) {
			return nums[0];
		}
		if (n == 2) {
			return max(nums[0], nums[1]);
		}
		return max(robRange(nums, 0, n - 2), robRange(nums, 1, n - 1));
	}
	//leecode740
	int deleteAndEarn(vector<int>& nums) {
		int n = nums.size();
		int _max = 0;
		if (n == 1) {
			return nums[0];
		}
		for (int i = 0; i < n; ++i) {
			_max = max(_max, nums[i]);
		}
		vector<int> temps(_max + 1);
		for (int temp : nums) {
			++temps[temp];
		}
		int first = temps[0];
		int second = max(temps[0], temps[1]);
		for (int i = 2; i <= _max; ++i) {
			int temp = second;
			second = max(first + temps[i] * i, second);
			first = temp;
		}
		return second;
	}
	//10.14
	//
	static int peakIndexInMountainArray(vector<int>& arr) {
		int l = 0, r = arr.size() - 1;
		while (l < r) {
			int mid = (l + r + 1) / 2;
			if (arr[mid] > arr[mid - 1]) {
				l = mid;
			}
			else {
				r = mid - 1;
			}
		}
		return l;
	}
	//
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> ans(numRows);
		for (int i = 0; i < numRows; ++i) {
			ans[i].resize(i + 1);
			ans[i][0] = ans[i][i] = 1;
			for (int j = 1; j < i; ++j) {
				ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
			}
		}
		return ans;
	}
	//leecode556  a不动矩阵
	vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
		int m = nums.size();
		int n = nums[0].size();
		if (m * n != r * c) return nums;

		vector<vector<int>> ans(r, vector<int>(c));
		for (int i = 0; i < m * n; i++) {
			ans[i / c][i % c] = nums[i / n][i % n];
		}
		return ans;
	}
	//leecode055
	//每次都跳最大距离，完整循环完就是跳完了，途中a变0了就是跳不动了
	bool canJump(vector<int>& nums) {
		int n = nums.size();
		int a = nums[0];
		int b = 0;
		for (int i = 1; i < n; ++i) {
			if (a == 0) {
				return false;
			}
			b = max(a - 1, nums[i]);
			a = b;
		}
		return true;
	}
	//leecode045 
	//一次跳跃，在能跳的最远的范围内，所有的尝试都可以视为第二次跳跃，所以用for循环来迭代找到所有的第二次
	//跳跃中能够跳的最远的
	int jump(vector<int>& nums)
	{
		int ans = 0;
		int start = 0;
		int end = 1;//一次跳跃的最远范围
		while (end < nums.size())
		{
			int maxPos = 0;
			for (int i = start; i < end; i++)
			{
				// 能跳到最远的距离
				maxPos = max(maxPos, i + nums[i]);
			}
			start = end;      // 下一次起跳点范围开始的格子
			end = maxPos + 1; // 下一次起跳点范围结束的格子
			ans++;            // 跳跃次数
		}
		return ans;
	}
	//10.15
	//leecode038
	string countAndSay(int n) {
		string prev = "1";
		for (int i = 2; i <= n; ++i) {
			string cur = "";
			int start = 0;
			int curPos = 0;
			while (curPos < prev.size()) {
				while (curPos < prev.size() && prev[curPos] == prev[start]) {
					curPos++;
				}
				cur += to_string(curPos - start) + prev[start];
				start = curPos;
			}
			prev = cur;
		}
		return prev;
	}
	//leecode 918
	int maxSubarraySumCircular(vector<int>& nums) {
		int sum = nums[0];
		vector<int>dpmax(nums);
		vector<int>dpmin(nums);
		for (int i = 1; i < nums.size(); i++) {
			dpmax[i] = max(dpmax[i - 1] + nums[i], nums[i]);
			dpmin[i] = min(dpmin[i - 1] + nums[i], nums[i]);
			sum += nums[i];
		}
		int maxv = *max_element(dpmax.begin(), dpmax.end());
		int minv = *min_element(dpmin.begin(), dpmin.end());
		return max(maxv, sum - minv == 0 ? maxv : sum - minv);
	}
	//10.16
	//leecode230
	int kthSmallest(TreeNode* root, int k) {
		stack<TreeNode*>_stack;
		while (!_stack.empty() || root != nullptr) {
			if (root != nullptr) {
				_stack.push(root);
				root = root->left;
			}
			else {
				root = _stack.top();
				_stack.pop();
				--k;
				if (k == 0) {
					break;
				}
				root = root->right;
			}
		}
		return root->val;
	}
	//10.19
	//
	//一是自写的方法，二是题解，因为题中会有负数给出，所以，如果是一中一直向下运算的话，其实并不是最优子结构
	//因为题中有负数，存在负负得正大过之前数的情况，所以在比较最大的同时，我们还需要维护一个最小值，并且进行三者比较
	int maxProduct(vector<int>& nums) {
		int n = nums.size();
		vector<int> dp(n);
		dp[0] = 0;
		dp[1] = nums[0];
		for (int i = 2; i <= n; ++i) {
			dp[i] = max(dp[i - 1] * nums[i - 1], nums[i - 1]);
		}
		return dp[n];
	}
	int MaxProduct(vector<int>& nums) {
		vector <int> maxF(nums), minF(nums);
		for (int i = 1; i < nums.size(); ++i) {
			maxF[i] = max(maxF[i - 1] * nums[i], max(nums[i], minF[i - 1] * nums[i]));
			minF[i] = min(minF[i - 1] * nums[i], min(nums[i], maxF[i - 1] * nums[i]));
		}
		return *max_element(maxF.begin(), maxF.end());//这里是迭代器迭代出最大的元素
	}
	//
	static int getMaxLen(vector<int>& nums) {
		int length = nums.size();
		int maxlength = 0;
		vector<int> dpZ(length + 1,0);
		vector<int> dpF(length + 1,0);
		if (nums[0] > 0) {
			dpZ[0] = 1;
		}
		else if (nums[0] < 0) {
			dpF[0] = 1;
		}
		maxlength = dpZ[0];
		for (int i = 1; i < length; ++i) {
			if (nums[i] > 0) {
				dpZ[i] = dpZ[i - 1] + 1;
				dpF[i] = (dpF[i - 1] > 0) ? dpF[i - 1] + 1 : 0;
			}
			else if (nums[i] < 0) {
				dpF[i] = dpZ[i - 1] + 1;
				dpZ[i] = (dpF[i - 1] > 0) ? dpF[i - 1] + 1 : 0;
			}
			else {
				dpZ[i] = 0;
				dpF[i] = 0;
			}
			maxlength = max(maxlength, dpZ[i]);
		}
		return maxlength;
	}
	//10.20
	//赶项目水一天
	int minMoves(vector<int>& nums) {
		int minNum = *min_element(nums.begin(), nums.end());
		int res = 0;
		for (int num : nums) {
			res += num - minNum;
		}
		return res;
	}
	//10.30
	vector<int> singleNumber(vector<int>& nums) {
		unordered_map<int, int> _map;
		for (int num : nums) {
			_map[num]++;
		}
		vector<int> ans;
		for (const auto &item : _map) {
			if (item.second == 1) {
				ans.push_back(item.first);
			}
		}
		return ans;
	}
	//11.1
	//leecode575
	int distributeCandies(vector<int>& candyType) {
		return min(unordered_set<int>(candyType.begin(), candyType.end()).size(), candyType.size() / 2);
	}
	//11.2
	//
	void deleteNode(ListNode* node) {
		node->val = node->next->val;
		node->next = node->next->next;
	}
	//11.4
	//367. 有效的完全平方数
	static bool isPerfectSquare(int num) {
		int l = 0;
		int r = num;
		while (l <= r) {
			int mid = (l + r) / 2;
			long sq = (long)mid * mid;
			if (sq == num) {
				return true;
			}
			else if (sq > num) {
				r = mid - 1;
			}
			else {
				l = mid+1;
			}
		}
		return false;
	}

};
class Datastruvture {
public:
	static vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		if (nums2.size() > nums1.size()) {
			return intersect(nums2, nums1);
		}
		unordered_map<int, int> a;
		vector<int> ret;
		for (int i = 0; i < nums1.size(); ++i) {
			a[nums1[i]]++;
		}
		for (int i = 0; i < nums2.size(); ++i) {
			if (a.count(nums2[i])) {//count函数只能返回这个key-value对存不存在，存在返回1，不存在返回0；
				a[nums2[i]]--;
				ret.push_back(nums2[i]);
				if (a[nums2[i]] == 0) {
					a.erase(nums2[i]);
				}
			}
		}
		return ret;
	}
	int firstUniqChar(string s) {
		unordered_map<char, int> ans;
		for (char _s : s) {
			ans[_s]++;
		}
		for (int i = 0; i < s.size(); ++i) {
			if (ans[s[i]] == 1) {
				return i;
			}
		}
		return -1;
	}
	bool canConstruct(string ransomNote, string magazine) {
		unordered_map<char, int> mag;
		for (char m : magazine) {
			mag[m]++;
		}
		for (char r : ransomNote) {
			if (mag.count(r)) {
				--mag[r];
				if (mag[r] == 0) {
					mag.erase(r);
				}
			}
			else {
				return false;
			}
		}
		return true;
	}
	bool isAnagram(string s, string t) {
		unordered_map<char, int> ans;
		for (auto _s : s) {
			ans[_s]++;
		}
		for (auto _t : t) {
			if (ans.count(_t)) {
				--ans[_t];
				if (ans[_t] == 0) {
					ans.erase(_t);
				}
			}
			else {
				return false;
			}
		}
		if (ans.empty()) {
			return true;
		}
		return false;
	}
	static bool hasCycle(ListNode* head) {
		unordered_map<ListNode*, int>ans;
		ListNode* node = head;
		while (node->next != nullptr) {
			if (ans.count(node) == 1) {
				return false;
			}
			ans[node]++;
			node = node->next;
		}
		return true;
	}
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == nullptr) {
			return l2;
		}
		else if (l2 == nullptr) {
			return l1;
		}
		else if (l1->val > l2->val) {
			l2->next = mergeTwoLists(l1, l2->next);
			return l2;
		}
		else {
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}

	}
	//对于链表的删除操作，我们只需要获取要删除节点的next，然后让他的前一个节点指向这个next就可以了，其次就是设计内存管理的话，再将要删除的节点释放
	ListNode* removeElements(ListNode* head, int val) {
		struct ListNode* dummyHead = new ListNode(0, head);
		struct ListNode* temp = dummyHead;
		while (temp->next != NULL) {
			if (temp->next->val == val) {
				temp->next = temp->next->next;
			}
			else {
				temp = temp->next;
			}
		}
		return dummyHead->next;
	}
	ListNode* reverseList(ListNode* head) {
		ListNode* prev = nullptr;
		ListNode* curr = head;
		while (curr != nullptr) {
			ListNode* next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		return prev;
	}
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head) {
			return head;
		}

		ListNode* cur = head;
		while (cur->next) {
			if (cur->val == cur->next->val) {
				cur->next = cur->next->next;
			}
			else {
				cur = cur->next;
			}
		}

		return head;
	}
	int findRepeatNumber(vector<int>& nums) {
		unordered_map<int, int>_map;
		for (auto num : nums) {
			if (_map.count(num)) {
				return num
			}
			else {
				_map[num]++;
			}
		}
		return -1;
	}
	int search(vector<int>& nums, int target) {
		unordered_map<int, int>_map;
		for (auto num : nums) {
			_map[num]++;
		}
		return _map[target];
	}
};
class DP {
public:
	//传统动规思路，超时
	int maxScoreSightseeingPair(vector<int>& values) {
		int n = values.size();
		vector<int> dp(n + 1);
		dp[0] = 0;
		for (int i = 1; i <= n - 1; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				int temp = values[i - 1] + values[j - 1];
				int temp1 = dp[i - 1];
				dp[i] = max(dp[i], max(dp[i - 1], (values[i - 1] + values[j - 1] + i - j)));
			}
		}
		return dp[n - 1];
	}
	//一次遍历思路
	int MaxScoreSightseeingPair(vector<int>& values) {
		int ans = 0, mx = values[0] + 0;
		//对于前面的两次遍历，这个一次遍历的思路就在于，无论j怎么遍历，i都是不变的，所以两次遍历会消耗性能，只用在一次遍历操作结束后，在更新i和i的值就行
		for (int j = 1; j < values.size(); ++j) {
			ans = max(ans, mx + values[j] - j);
			// 边遍历边维护
			mx = max(mx, values[j] + j);
		}
		return ans;
	}
	//1.dp[i],第I天股票卖出去后的最大收益
	//2.因为要求最大收益，那就是dp[i] = max(dp[i],price[i] - price[j])
	//3.dp[0] = dp[1] = 0
	//4.从左到右遍历i，然后在0~i的范围内遍历j
	//超时
	int maxProfit(vector<int>& prices) {
		int n = prices.size();
		vector<int> dp(n + 1);
		dp[0] = dp[1] = 0;
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j < i; ++j)
			{
				dp[i] = max(dp[i - 1], max(dp[i], prices[i - 1] - prices[j - 1]));
			}
		}
		return dp[n];
	}
	//发现只用维护两个变量，一个是遍历到该位置的最小买入金额，还有一个是最大的利润，所以可以只用一次遍历，然后在遍历中更新
	int MaxProfit(vector<int>& prices) {
		int minPrice = 1e9;
		int maxPrice = 0;
		for (auto price : prices) {
			maxPrice = max(maxPrice, price - minPrice);
			minPrice = min(minPrice, price);
		}
		return maxPrice;
	}
	//类似01背包问题
	int MaxProfit2(vector<int>& prices) {
		int n = prices.size();
		vector<vector<int>> dp(n, vector<int>(2));
		dp[0][0] = 0, dp[0][1] = -prices[0];
		for (int i = 1; i < n; ++i) {
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);//手中没有股票，出售的情况
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);//手中持有股票，不出售的情况
		}
		return dp[n - 1][0];
	}
	//740. 删除并获得点数
	//将原数组按照每个数出现的次数重新构建一个新数组，把原先的问题当成跳楼梯问题中的跳两步或者是打家劫舍中的隔一家才能拿问题
	int deleteAndEarn(vector<int>& nums) {
		int n = nums.size();
		int _max = 0;
		if (n == 1) {
			return nums[0];//确定边界
		}
		for (int i = 0; i < n; ++i) {
			_max = max(_max, nums[i]);//确定循环次数
		}
		vector<int> temps(_max + 1);
		for (int temp : nums) {
			++temps[temp];//重新构建数组，根据nums中每个数出现的次数来构建
		}
		//滚动数组DP
		int first = temps[0];
		int second = max(temps[0], temps[1]);
		for (int i = 2; i <= _max; ++i) {
			int temp = second;
			second = max(first + temps[i] * i, second);
			first = temp;
		}
		return second;
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
//10.19
//
struct TrieNode {
	vector<TrieNode*> child;
	bool isEnd;
	TrieNode() {
		this->child = vector<TrieNode*>(26, nullptr);
		this->isEnd = false;
	}
public:
	void insert(TrieNode *root,const string& str) {
		TrieNode *node = root;
		for (auto& c : str) {
			if (node->child[c - 'a'] == nullptr) {
				node->child[c - 'a'] = new TrieNode();
			}
			node = node->child[c - 'a'];
		}
		node->isEnd = true;
	}
};

class WordDictionary {
private:
	TrieNode* trie;
public:
	WordDictionary() {
		trie = new TrieNode();
	}

	void addWord(string word) {
		trie->insert(trie, word);
	}

	bool search(string word) {
		return dfs(trie, 0, word);
	}
	bool dfs(TrieNode* cur, int index, const string& word) {
		if (index == word.size()) {
			return cur->isEnd;
		}
		char c = word[index];
		if (c >= 'a' && c <= 'z') {
			TrieNode* child = cur->child[c - 'a'];
			if (child != nullptr && dfs(child, index + 1, word)) {
				return true;
			}
		}
		else if (c == '.') {
			for (int i = 0; i < 26; ++i) {
				TrieNode* child = cur->child[i];
				if (child != nullptr && dfs(child, index + 1, word)) {
					return true;
				}
			}
		}
		return false;
	}
};

class Offer {
	stack<int> inStack;
	stack<int> outStack;
public:
	void appendTail(int value) {
		while (!inStack.empty()) {
			int temp = inStack.top();
			inStack.pop();
			outStack.push(temp);
		}
		inStack.push(value);
	}

	int deleteHead() {
		if (inStack.empty() && outStack.empty()) {
			return -1;
		}
		if (outStack.size() != 0) {
			while (outStack.size() > 1) {
				int temp = outStack.top();
				outStack.pop();
				inStack.push(temp);
			}
			return outStack.top();
		}
		else {
			return inStack.top();
		}
	}
	//剑指 Offer 06. 从尾到头打印链表
	vector<int> reversePrint(ListNode* head) {
		stack<int> val;
		vector<int> ans;
		ListNode* node = head;
		while (node != nullptr) {
			val.push(node->val);
			node = node->next;
		}
		while (!val.empty()) {
			ans.push_back(val.top());
			val.pop();
		}
		return ans;
	}
	//剑指 Offer 24. 反转链表
	//链表题都应该画图，画图可以理解，通过局部反转最终反转整个链表
	ListNode* reverseList(ListNode* head) {
		ListNode* prev = nullptr;
		ListNode* curr = head;
		while (curr) {
			ListNode* next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		return prev;
	}
	//剑指 Offer 35. 复杂链表的复制
	//看不懂题，水了
	unordered_map<Node*, Node*> cachedNode;

	Node* copyRandomList(Node* head) {
		if (head == nullptr) {
			return nullptr;
		}
		if (!cachedNode.count(head)) {
			Node* headNew = new Node(head->val);
			cachedNode[head] = headNew;
			headNew->next = copyRandomList(head->next);
			headNew->random = copyRandomList(head->random);
		}
		return cachedNode[head];
	}
};
class MinStack {
	stack<int> mainStack;
	stack<int> minStack;
	int minPtr = INT_MAX;
public:
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		if (minStack.empty() || minStack.top() > x) {
			minStack.push(x);
		}
		else {// 如果数据栈中当前最小值 < x, 则继续将最小值设置为上次的最小值
			minStack.push(minStack.top());
		}
		mainStack.push(x);
	}

	void pop() {
		mainStack.pop();
		minStack.pop();
	}

	int top() {
		return mainStack.top();
	}

	int min() {
		return minStack.top();
	}
};
int main() {
	ListNode* head = new ListNode;
	head->val = 3;
	ListNode* node = new ListNode;
	node->val = 2;
	head->next = node;
	ListNode* node1 = new ListNode;
	node1->val = 0;
	node->next = node1;
	ListNode* node2 = new ListNode;
	node2->val = 4;
	node1->next = node2;
	node2->next = node;
	Datastruvture::hasCycle(head);
}