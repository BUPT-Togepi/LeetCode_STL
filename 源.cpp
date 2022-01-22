#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<list>
#include<stack>
#include<map>
#include<unordered_map>
using namespace std;
/******************************************************************数组*************************************************************************/
//1.二分法查找
//1.1给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target,写一个函数搜索 nums 中的 target，如果目标值存在返回下标,否则返回 - 1。
int search(vector<int>& nums, int target)
{
	int size = nums.size();
	int left = 0, right = size - 1, middle = middle = left + ((right - left) >> 1);//防止溢出写法。注意加括号，右移运算符优先级很低！
	while (left <= right)
	{
		if (nums[middle] == target) return middle;
		else if (nums[middle] > target)
		{
			right = middle - 1;
		}
		else
		{
			left = middle + 1;
		}
		middle = (right + left) >> 1;
	}
	return -1;
}
//1.2若无此元素，则返回其应插入的位置
int search_2(vector<int>& nums, int target)
{
	int size = nums.size();
	int left = 0, right = size - 1, middle = left + ((right - left) >> 1);
	while (left <= right)
	{
		if (nums[middle] == target) return middle;
		else if (nums[middle] > target)
		{
			right = middle - 1;
		}
		else
		{
			left = middle + 1;
		}
		middle = (right + left) >> 1;
	}
	return right + 1;
	//目标值在所有数之前，right=-1，返回值正好为right+1；若在所有数之后，则right循环后仍为初始值，+1正好；
	//在之间则区间最后聚拢位置应为较小位，例如下表3，4聚为3，则最终插入位置在其后，也是right+1
}
//1.3给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
vector<int> search_3(vector<int>& nums, int target)
{
	int size = nums.size();
	int left = 0, right = size - 1, middle = (right + left) >> 1;
	int pos = -1;
	vector<int> answer(2, -1);
	while (left <= right)
	{
		if (nums[middle] == target)
		{
			pos = middle;
			break;
		}
		else if (nums[middle] > target)
		{
			right = middle - 1;
		}
		else
		{
			left = middle + 1;
		}
		middle = (right + left) >> 1;
	}
	//先找到目标区间的一个数，然后双向扩散查找边界即可
	if (pos != -1)
	{
		int left = pos, right = pos;
		for (int i = pos; i >= 0; --i)
		{
			if (nums[i] == target) left = i;
			else break;
		}
		for (int i = pos; i < size; ++i)
		{
			if (nums[i] == target) right = i;
			else break;
		}
		answer[0] = left; answer[1] = right;
	}
	return answer;
}
//1.4给你一个非负整数x,计算并返回x的算术平方根
int asqrt(int x)
//x的算术平方根一定小于x，相当于查找问题
{
	int left = 1, right = x, middle;
	while (left <= right)
	{
		middle = left+((right-left)>> 1);
		if (middle == x / middle) return middle;
		if (middle > x / middle) right = middle;
		if (middle < x / middle) left = middle + 1;//特殊点：左右不能都变化为中间值的加减1
		if (left == right)
		{
			return left - 1;
		}
	}
	return 0;
}

//2.双指针法
//2.1给你一个数组nums和一个值val,你需要原地移除所有数值等于val的元素,并返回移除后数组的新长度
int removeElement(vector<int>& nums, int val)
{
	//双指针法删除特定元素得到的新数组前n项为删除后的数组，遗留的项是原数组的后几项，
	//因此若题目变形为把val挪移到数组末尾即可用这一算法，先删然后把遗留项置为val即可完成
	int slow = 0, fast = 0;
	int size = nums.size();
	for (; fast < size; ++fast)
	{
		//两指针中的fast一直探路，得到非val后上报给slow处更新，fast没探测到新值时slow不动
		if (nums[fast] != val)
		{
			nums[slow] = nums[fast];
			++slow;
		}
	}
	return slow;
}
//2.2给你一个有序数组nums,请你原地删除重复出现的元素,使每个元素只出现一次,返回删除后数组的新长度
int removeDuplicates(vector<int>& nums)
{
	int slow = 0, fast = 0;
	int size = nums.size();
	if (size == 0||size==1) return size;
	for (; fast < size; ++fast)
	{
		if (nums[slow] != nums[fast])
		{
			++slow;
			nums[slow] = nums[fast];
		}
	}
	return slow+1;
}
//2.3给定s和t两个字符串,当它们分别被输入到空白的文本编辑器后,请你判断二者是否相等。#代表退格字符。
bool backspaceCompare(string s, string t)
{
	//本题思路为先算出真实字符串然后比较是否相等即可
	//首先字符串入栈，栈顶为‘#’则弹出然后退格记录加1以待非‘#’出现时完成退格（弹出）操作
	stack<char> container1,container2;
	for(auto elem:s)
	{
		container1.push(elem);
	}
	int jump = 0;
	string ss,tt;
	while (!container1.empty())
	{
		char temp = container1.top();
		if (temp == '#')
		{
			container1.pop();
			jump++;
		}
		else if(temp!='#'&&jump!=0)
		{
			container1.pop();
			jump--;
		}
		else
		{
			ss += temp;
			container1.pop();
		}
	}
	jump = 0;
	for (auto elem : t)
	{
		container2.push(elem);
	}
	while (!container2.empty())
	{
		char temp = container2.top();
		if (temp == '#')
		{
			container2.pop();
			jump++;
		}
		else if (temp != '#' && jump != 0)
		{
			container2.pop();
			jump--;
		}
		else
		{
			tt += temp;
			container2.pop();
		}
	}
	if (ss == tt) return true;
	return false;
}
//2.4给你一个按非递减顺序排序的整数数组nums,返回每个数字的平方组成的新数组,要求也按非递减顺序排序。
vector<int> sortedSquares(vector<int>& A) {
	int k = A.size() - 1;
	vector<int> result(A.size(), 0);
	//本题双指针并不一起出发，而是在数组的两端；新建一数组，双指针哪端平方大就取哪个数然后前进一步
	for (int i = 0, j = A.size() - 1; i <= j;) 
	{ 
		if (A[i] * A[i] < A[j] * A[j]) {
			result[k--] = A[j] * A[j];
			j--;
		}
		else {
			result[k--] = A[i] * A[i];
			i++;
		}
	}
	return result;
}

//3.滑动窗口
//3.1给定一个含有n个正整数的数组和一个正整数target找出该数组中满足其和≥target的长度最小的连续子数组,并返回其长度。
int minSubArrayLen(int target, vector<int>& nums)
{
	int i = 0, j = 0,sum=0,length=INT32_MAX;//i为窗口左边界，j为右边界，sum为窗口和，length为窗口长度
	for (; j < nums.size(); ++j)
	{
		sum += nums[j];//扩张右边界以更新窗口大小
		while (sum >= target)
		{
			int now_length = j - i + 1;
			if (now_length < length) length = now_length;
			sum -= nums[i];//缩小左边界以更新窗口大小
			++i;
		}
	}
	if (length == INT32_MAX) return 0;
	else return length;
}
//3.2给你一个字符串s,一个字符串t。返回s中涵盖t所有字符的最小子串。如果s中不存在涵盖t所有字符的子串,则返回空字符串""。
string minWindow(string s, string t)
{
	int i = 0, j = 0, length = INT32_MAX;//i为窗口左边界，j为右边界，sum为窗口和，length为窗口长度
	pair<int, int> answer;
	int t_code[70] = { 0 }, s_code[70] = { 0 };//因字符串大小写都有，以A为起始，A-z少于70所以用一个70数组做哈希处理
	for (auto elem : t)
		t_code[elem - 'A']++;
	auto size1 = s.size(), size2 = t.size();
	if (size2 > size1) return "";
	bool flag = false;
	for (; j < size1; ++j)
	{
		s_code[s[j] - 'A']++;
		for (int k = 0; k < 70; ++k)
		{
			if (t_code[k] > s_code[k])
			{
				flag = false;
				break;
			}
			if (k == 69) flag = true;//符合匹配要求后才可以移动左窗口边界
		}
		while (flag)
		{
			int now_length = j - i + 1;
			if (now_length < length)
			{
				length = now_length;
				answer.first = i; answer.second = j;
			}
			s_code[s[i] - 'A']--;
			if (t_code[s[i] - 'A'] > s_code[s[i] - 'A'])//只需判断减小后的那一个字符数量即可
				flag = false;
			++i;
		}
	}
	if (length == INT32_MAX) return "";
	else return s.substr(answer.first, answer.second - answer.first + 1);
}
//3.3水果成篮，只准采摘两种编号的树果，求最多树果量。即寻找一个最大窗口，窗口内最多两种编号。
int totalFruit(vector<int>& nums)
{
	int i = 0, j = 0, length = 0;//i为窗口左边界，j为右边界，sum为窗口和，length为窗口长度
	auto size = nums.size();
	if (size == 1) return 1;
	int cnt = 0;
	vector<int> fruits(100000, 0);//题目中树最多100000种，故作此哈希
	for (; j < nums.size(); ++j)
	{
		if (fruits[nums[j]] == 0) cnt++;
		fruits[nums[j]]++;
		if (cnt <= 2)
		{
			length = length > j - i + 1 ? length : j - i + 1;
		}
		while (cnt > 2)//种类数太多则持续收缩左窗口
		{
			fruits[nums[i]]--;
			if (fruits[nums[i]] == 0) cnt--;
			++i;
		}
	}
	return length;
}
//3.4给你一个正整数n,生成一个包含1到n^2所有元素,且元素按顺时针顺序螺旋排列的n x n正方形矩阵matrix 。
vector<vector<int>> generateMatrix(int n)
{
	vector<vector<int>> answer(n, vector<int>(n, 0));
	int i = 0, j = 0, sum = 1;
	int wall = 0;//当前遍历的层数
	while (1)
	{
		answer[i][j] = sum;
		sum++;
		if (sum > n * n) break;//数超出范围了了就跳出
		if (i == wall && j < n-1-wall)//顺时针第一条边：横边
		{
			j++;
			continue;
		}
		else if (j == n - 1-wall&&i<n-1-wall)//第一列边
		{
			i++;
			continue;
		}
		else if (j >wall && i == n - 1-wall)//第二横边
		{
			j--;
			continue;
		}
		else if (i >wall+1 && j == wall)//第二列边
		{
			i--;
			continue;
		}
		else if (i == wall+1 && j == wall)//第二列边终结点，先赋值后判断，终结点已赋值因此改i，j即可
		{
			wall++;
			i = wall;
			j = wall;//新一层的起始点
		}
	}
	return answer;
}
//3.5给你一个m行n列的矩阵matrix,请按照顺时针螺旋顺序,返回矩阵中的所有元素。
vector<int> spiralOrder(vector<vector<int>>& matrix)
{
	//思路与上题相同，注意行列不同维度，稍加修改判定条件即可
	vector<int> answer;
	int i = 0, j = 0, num = 0;
	int m = matrix.size(), n = matrix[0].size();//m行n列
	int wall = 0;
	while (1)
	{
		answer.push_back(matrix[i][j]);
		num++;
		if (num == m * n) break;
		if (i == wall && j < n - 1 - wall)//顺时针第一条边：横边
		{
			j++;
			continue;
		}
		else if (j == n - 1 - wall && i < m - 1 - wall)//第一列边
		{
			i++;
			continue;
		}
		else if (j > wall && i == m - 1 - wall)//第二横边
		{
			j--;
			continue;
		}
		else if (i > wall + 1 && j == wall)//第二列边
		{
			i--;
			continue;
		}
		else if (i == wall + 1 && j == wall)//第二列边终结点，先赋值后判断，终结点已赋值因此改i，j即可
		{
			wall++;
			i = wall;
			j = wall;//新一层的起始点
		}
	}
	return answer;
}

/******************************************************************链表*************************************************************************/
//1.虚拟头节点
//1.1
int main()
{
	cout << "hello,STL!" << endl;
	
}