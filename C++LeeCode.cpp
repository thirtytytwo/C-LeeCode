
#include <iostream>
#include <vector>
#include "limits.h"
#include <algorithm>
#include <queue>;

using namespace std;

typedef pair<int, int> _p;//pair将一对值组合成一个值，这一对值可以具有不同的数据类型（T1和T2），两个值可以分别用pair的两个公有函数first和second访问。是stl内部提供


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
};

int main() {
	string n = "(*)";
	cout << Solution::checkValidString(n)<<endl;
}