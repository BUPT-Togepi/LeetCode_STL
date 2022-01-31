#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<list>
#include<stack>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
using namespace std;
/***************************************************************数组*********************************************************************/
//1.二分法查找
//1.1给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target,写一个函数搜索 nums 中的 target，如果目标值存在返回下标,否则返回-1。
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
//1.2若无此元素，则返回其应插入的位置。
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
//2.1给你一个数组nums和一个值val,你需要原地移除所有数值等于val的元素,并返回移除后数组的新长度。
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
//2.2给你一个有序数组nums,请你原地删除重复出现的元素,使每个元素只出现一次,返回删除后数组的新长度。
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

/*****************************************************************链表*******************************************************************/
 //Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
//1.虚拟头节点
//1.1给你一个链表的头节点head和一个整数val,请你删除链表中所有value为val的节点,并返回新的头节点。
ListNode* removeElements(ListNode* head, int val)
{
	if (head == nullptr) return head;
	auto vir=new ListNode(0, head);//虚拟头节点，指针指向原头节点
	head = vir;//把头指针换到新头上
	ListNode* cur = vir;
	while (cur->next!=nullptr)
	{
		if (cur->next->val == val)
		{
			ListNode* temp = cur->next;
			cur->next = cur->next->next;
			delete temp;
		}
		else cur = cur->next;
	}
	head = vir->next;
	delete vir;
	return head;
}
//1.2给你一个链表,两两交换其中相邻的节点,并返回交换后链表的头节点。
ListNode* swapPairs(ListNode* head)
{
	auto vir = new ListNode(0, head);//虚拟头节点，指针指向原头节点
	head = vir;//把头指针换到新头上
	ListNode* cur = vir;
	//cur->1->2->3->4 : cur->2 2->1 1->3 cur=2
	while (cur->next != nullptr && cur->next->next != nullptr)
	{
		ListNode* temp1 = cur->next;//1
		ListNode* temp2 = cur->next->next->next;//下一轮反转的起始点
		cur->next = cur->next->next;//cur->2
		cur->next->next = temp1;//2->1
		cur->next->next->next = temp2;//1->3
		cur = cur->next->next;//cur=3
	}
	return vir->next;
}

//2.双指针法
//2.1给你单链表的头节点head,请你反转链表,并返回反转后的链表。
ListNode* reverseList(ListNode* head)
{
	//一前一后两个指针形成一条指向，走到尾巴即可调换全部方向
	ListNode* pre = nullptr;
	ListNode* cur = head;
	while (cur != nullptr)
	{
		ListNode* temp=cur->next;
		cur->next = pre;
		pre = cur;
		cur = temp;
	}
	return pre;
}
//2.2删除倒数第n个节点（虚拟头节点+双指针）并返回头节点指针。
ListNode* removeNthFromEnd(ListNode* head, int n)
{
	auto vir = new ListNode(0, head);//虚拟头节点，指针指向原头节点
	head = vir;//把头指针换到新头上
	ListNode* cur = vir;
	ListNode* fast = cur;
	while (n > 0)
	{
		fast = fast->next;
		--n;
	}
	while (fast->next != nullptr)//因为是删除节点，未到目的节点就需停下，因此是判断fast->next的值；若仅仅是找到倒数第n节点
		//则fast为null时cur正好就是倒数第n节点
	{
		cur = cur->next;
		fast = fast->next;
	}
	ListNode* d = cur->next;
	cur->next = cur->next->next;
	delete d;
	return vir->next;
}

//3.链表常见结论
//3.1链表相交问题,两链表在某一结点汇聚为一条链表,求这个汇聚点
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
{
	//暴力解法为将某一链表的所有指针存在set内，便历另一链表并与set比对即可，空间复杂度太高
	//本解法让长链表指针先走，使二者在长度上为同一起跑线，若有交点则指针相等
	int len1 = 0, len2 = 0;
	ListNode* p1 = headA;
	ListNode* p2 = headB;
	while (p1 != nullptr)
	{
		len1++;
		p1 = p1->next;
	}
	while (p2 != nullptr)
	{
		len2++;
		p2 = p2->next;
	}
	ListNode* cur1=headA;ListNode* cur2=headB;
	if (len1 <= len2)
	{
		for (int i = 0; i < len2 - len1; ++i)
		{
			cur2 = cur2->next;
		}
	}
	else
	{
		for (int i = 0; i < len1 - len2; ++i)
			cur1 = cur1->next;
	}
	while (cur1!=nullptr)
	{
		if (cur1 == cur2) return cur1;
		else
		{
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
	}
	return nullptr;
}
//3.2给定一个链表,返回链表开始入环的第一个节点。如果链表无环,则返回null。
ListNode* detectCycle(ListNode* head)
{
	//首先判断是否成环
	ListNode* slow = head;
	ListNode* fast = head;
	while (fast!=nullptr&&fast->next != nullptr)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)//快指针必定先入环，能重合就说明一定有环存在
		{
			while (head != fast)
			{
				head = head->next;
				fast = fast->next;//有环时快指针与头指针都一步一步走，相遇则为环节点
			}
			return fast;
		}
	}
	return nullptr;
}

/*****************************************************************哈希表*******************************************************************/
//所需哈希类别较小时用数组，例如字母频率问题，使用set或map类容器空间复杂度过高；
// 类别较多考虑set，若需求为找寻哈希数值及其频率这一类二元数据返回值则必须map。
//1.数组哈希
//1.1给你一个字符串数组words,请你找出所有在words的每个字符串中都出现的共用字符(包括重复字符)并以数组形式返回。
vector<string> commonChars(vector<string>& words)
{
	int code[26] = { 0 };
	for (auto elem : words[0])
		code[elem - 'a']++;
	for (int i = 1; i < words.size(); ++i)
	{
		int code_temp[26] = { 0 };
		for (auto elem : words[i])
			code_temp[elem - 'a']++;
		for (int i = 0; i < 26; ++i)//以第一个单词的哈希表为基础，使用余下的哈希表进行更新即可
		{
			if (code[i] != 0&& code_temp[i] != 0)
			{
				if (code_temp[i] < code[i])
					code[i] = code_temp[i];
			}
			if (code_temp[i] == 0) code[i] = 0;
		}
	}
	vector<string> answer;
	for (int i = 0; i < 26; ++i)
	{
		for (int j = 0; j < code[i]; ++j)
		{
			string temp;
			temp+=('a'+i);
			answer.push_back(temp);
		}
	}//把哈希表还原为字符串数组返回（题目要求）
	return answer;
}

//2.set
//2.1给定两个数组,编写一个函数来计算它们的交集。（交集中每个元素是唯一的）
vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
{
	unordered_set<int> ordered(nums1.begin(), nums2.end());
	unordered_set<int> answer;
	for (auto elem : nums2)
	{
		if (ordered.find(elem) != ordered.end()) answer.insert(elem);//因为elem可能有重的，所以用set去保存结果
	}
	return vector<int>(answer.begin(), answer.end());
}
//2.2对于一个正整数,每一次将该数替换为它每个位置上的数字的平方和。然后重复这个过程直到这个数变为1,称此数为快乐数。
int happy(int n)
{
	int sum = 0;
	while (n)
	{
		sum += (n % 10) * (n % 10);//取个位则%10即可，除掉个位则/10即可
		n /= 10;
	}
	return sum;
}
bool isHappy(int n)
{
	//每次计算快乐数的结果数存在一容器内，此数若再次出现则说明出现了循环，必不是快乐数。问题转化为有没有重复出现某一数。
	unordered_set<int> code;
	while (1)
	{
		int sum = happy(n);
		if (sum == 1) return true;
		if (code.find(sum) != code.end()) return false;
		else code.insert(sum);
		n = sum;
	}
}

//3.map
//3.1给定一个整数数组nums和一个整数目标值target,请你在该数组中找出和为目标值target的那两个整数,并返回它们的数组下标。
vector<int> twoSum(vector<int>& nums, int target)
{
	//本题要返回数组下标，因此set受限
	unordered_map<int, int> code;
	for (int i = 0; i < nums.size(); ++i)
	{
		auto it = code.find(target - nums[i]);
		if (it != code.end()) return{ i,it->second };
		code.insert(pair<int, int>(nums[i], i));
		//本题不允许使用相同元素，那么在插入元素之前查找就一定找不到自己；因此边查边插效果最好
	}
	return {};
}
//3.2给定四个包含整数的长度相等数组列表A,B,C,D,计算有多少个元组(i,j,k,l),使得 A[i] + B[j] + C[k] + D[l] = 0。
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4)
{
	int answer = 0;
	unordered_map<int, int> code;//若求四数之和，先求两数之和及其出现频率
	int size = nums1.size();
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			int temp = nums1[i] + nums2[j];
			auto it = code.find(temp); 
			if (it != code.end()) it->second++;
			else code.insert(pair<int, int>(temp, 1));
		}
	}
	//思想在于把四数之和转为两数之和；
	//AB两数已有map存储，CD不需要复制这一操作，直接find即可
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			int temp = -(nums3[i] + nums4[j]);
			auto it = code.find(temp);
			if (it != code.end()) answer += it->second;
		}
	}
	return answer;
}

//4.双指针法巧解n数之和
//4.1给定一个已按照非递减顺序排列的整数数组numbers,请你从数组中找出两个数满足相加之和等于目标数target,返回下标；
 vector<int> twoSum2(vector<int>& numbers, int target) 
 {
for (int i = 0; i < numbers.size(); ++i)
{
	if (i > 0 && numbers[i] == numbers[i - 1]) continue;//去重操作
	int left = i + 1;
	while (left < numbers.size())
	{
		if (numbers[i] + numbers[left] == target) return { i,left};
		else if (numbers[i] + numbers[left] > target) break;
		else
		{
			left++;
			while (left < numbers.size() && numbers[left] == numbers[left - 1])//此处判断先后顺序不可弄反；
				//例如数组最后两数相等，left会加到最后一个下标，left++后越界，先判断右句则内存访问越界
				left++;
		}
	}
}
return {};
}
//给你一个n个整数的数组nums,判断nums中是否存在三个元素a,b,c,使得a+b+c=0?请你找出所有和为0且不重复的三元组。
//结果中可以同一数值出现多次，例如数组中有两个-1，答案可以为{-1,-1,2}；不重复是指三元组组成元素不同，有上述答案后再来一个{2,-1,-1}即使所占元素不同也不行
vector<vector<int>> threeSum(vector<int>& nums)
{
	//本题目若想先算两数之和会很麻烦，因为要多处去重
	//本题思想自然可以用于解决两数之和问题，乃至n数之和问题
	vector<vector<int>> answer;
	int size = nums.size();
	sort(nums.begin(), nums.end());
	for (int i = 0; i < size; ++i)
	{
		if (nums[i] > 0) break;//最小值都比零大则往后必定无解
		if (i > 0 && nums[i] == nums[i - 1]) continue;//相邻值相等则下一组解与上一组必同解或同时无解，跳过
		int left = i + 1, right = size - 1;
		while (left < right)//对于一个nums[i]来说可能有多个解
		{
			if (nums[left] + nums[right] + nums[i] > 0) right--;
			else if (nums[left] + nums[right] + nums[i] < 0) left++;
			else
			{
				answer.push_back(vector<int>{nums[left],nums[right],nums[i]});//找到一组答案
				while (right > left && nums[right] == nums[right - 1]) right--;
				while (right > left && nums[left] == nums[left + 1]) left++;//去重
				right--;
				left++;//收缩到非重复值上再进行下一轮求解。意思是最左的i不变，让left right之间距离逐渐变小找到多组解
			}
		}
	}
	return answer;
}
//找四数之和为target的元组
vector<vector<int>> fourSum(vector<int>& nums, int target)
{
	vector<vector<int>> answer;
	int size = nums.size();
	sort(nums.begin(), nums.end());
	for (int k = 0; k < size; ++k)
	{
		//if (nums[k] > target) break;不同于上题的target=0，本题target可能为负值，例如-11，nums[k]=-5>targe
		// 因此往后找负数也可以达成求和目的；因此target>=0时才可以像这样进行break
		//四数之和则比三数之和多一层循环，nums[k]在后续被当作定值
		if (k > 0 && nums[k] == nums[k - 1]) continue;
		for (int i = k + 1; i < size; i++)
		{
			if (i > k + 1 && nums[i] == nums[i - 1]) continue;
			int left = i + 1;
			int right =size- 1;
			while (left < right)
			{
				/*if (nums[k] > target - (nums[left] + nums[right]+ nums[i])) right--;
				else if (nums[k]  < target - (nums[left] + nums[right] + nums[i])) left++;*/
				//上述注释更能表达含义，但是右侧求和比重大，可能溢出，因此挪去左边一个以求平衡
				if (nums[k] + nums[i] > target - (nums[left] + nums[right])) right--;
			    else if (nums[k] + nums[i] < target - (nums[left] + nums[right] )) left++;
				else
				{
					answer.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
					while (right > left && nums[right] == nums[right - 1]) right--;
					while (right > left && nums[left] == nums[left + 1]) left++;
					right--;
					left++;
				}
			}
		}
	}
	return answer;
}

/*****************************************************************字符串*******************************************************************/
//1.1花式反转字符串。给定一个字符串s和一个整数k,从字符串开头算起,每计数至2k个字符,就反转这2k字符中的前k个字符。剩余字符数在k到2k时反转前k，剩余字符小于k则全部反转
string reverseStr(string s, int k)
{
	auto it = s.begin();
	for (int i = 0; i < s.size(); i += 2 * k,it+=2*k)
	{
		if (i + k <= s.size()) reverse(it, it + k);
		else//剩余不足k个元素时完全反转
		{
			reverse(it, s.end());
		}
	}
	return s;
}
//1.2给你一个字符串s,逐个翻转字符串中的所有单词。
string reverseWords(string s)
{
	//题目要求使用o（1）额外空间，因此额外字符串用不了；erase函数时间复杂度o（n），用erase时还要外加一层循环，复杂度n^2;所以首先双指针法原地去除冗余空格
	int slow = 0, fast = 0;
	while (s[fast] == ' ' && fast < s.size()) fast++;//去除句子最左边空格
	while (fast < s.size())
	{
		if (fast > 1 && s[fast] == ' ' && s[fast - 1] == ' ')
		{
			fast++;
			continue;
		}
		else s[slow++] = s[fast++];//赋上最后一个有效之后还会自加一次，因此slow比对应的下标大1
	}
	while (slow>=1&&s[slow-1] == ' ')
	{
		slow--;
	}
	s.resize(slow);
	//去除多余的空格（冗余空格：1.整个句子左右两侧的空格；2.每个单词之间冗余的空格）
	reverse(s.begin(), s.end());//整体反转，然后逐个单词反转
	auto left = s.begin();
	auto right = s.begin();
	bool flag = false;
	for (; right != s.end(); ++right)
	{
		if (flag == true) left = right;
		if (*right == ' ')
		{
			reverse(left, right);
			flag = true;
		}
		else flag = false;
	}
	reverse(left, s.end());
	return s;
}
//1.3将字符串左边若干字符移到右侧
string reverseLeftWords(string s, int n) 
{
	//若想要不用额外空间完成则可以三次反转；否则字符串拼接操作后的substr会耗费额外空间哦
	reverse(s.begin(), s.begin() + n);
	reverse(s.begin() + n, s.end());
	reverse(s.begin(), s.end());
	return s;
}
//2.将空格替换为%20（不使用额外字符串）
string replaceSpace(string s)
{
	int blank = 0;
	for (auto elem : s)
		if (elem == ' ') blank++;
	int old_size = s.size();
	s.resize(old_size + 2 * blank);//新数组大小
	int left=old_size-1,right=s.size()-1;
	while (left >= 0 && left<right)//left与right相等发生于所有空格已替换的情况下，此时二者同步走，此时程序已经可以结束了所以‘<’即可
	{
		if (s[left] == ' ')
		{
			s[right--] = '0';
			s[right--] = '2';
			s[right--] = '%';
			left--;
		}
		else
		{
			s[right] = s[left];
			right--;
			left--;
		}
	}
	return s;
}

int main()
{
	cout << "hello,STL!" << endl;
	string s = "sas";
	s.substr(
}
