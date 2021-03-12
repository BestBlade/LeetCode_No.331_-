/* ------------------------------------------------------------------|
序列化二叉树的一种方法是使用前序遍历。当我们遇到一个非空节点时，我们可以记录下这个节点的值。如果它是一个空节点，我们可以使用一个标记值记录，例如 #。

     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
例如，上面的二叉树可以被序列化为字符串 "9,3,4,#,#,1,#,#,2,#,6,#,#"，其中 # 代表一个空节点。

给定一串以逗号分隔的序列，验证它是否是正确的二叉树的前序序列化。编写一个在不重构树的条件下的可行算法。

每个以逗号分隔的字符或为一个整数或为一个表示 null 指针的 '#' 。

你可以认为输入格式总是有效的，例如它永远不会包含两个连续的逗号，比如 "1,,3" 。

示例 1:

输入: "9,3,4,#,#,1,#,#,2,#,6,#,#"
输出: true
示例 2:

输入: "1,#"
输出: false
示例 3:

输入: "9,#,#,1"
输出: false

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/verify-preorder-serialization-of-a-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*	双指针法
*
*	执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
*	内存消耗：8.1 MB, 在所有 C++ 提交中击败了81.94%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

bool isValidSerialization(string preorder) {
    int n = preorder.size();
    if (n == 1 && preorder[0] == '#') {
        return true;
    }
    if (preorder[0] == '#') {
        return false;
    }
    stack<int> s;
    s.emplace(1);
    int i = 0;
    while (i < n) {
        if (s.empty()) {
            return false;
        }
        if (preorder[i] == ',') {
            i++;
        }
        else if (preorder[i] == '#') {
            s.top() -= 1;
            i++;
            if (!s.top()) {
                s.pop();
            }
        }
        else {
            s.top() -= 1;
            while (i < n && preorder[i] != ',') {
                i++;
            }
            if (!s.top()) {
                s.pop();
            }
            s.emplace(2);
        }
    }
    return s.empty();
}
/*	栈法
*
*	执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
*	内存消耗：6.8 MB, 在所有 C++ 提交中击败了66.08的用户
*/
bool isValidSerialization(string preorder) {
    int n = preorder.size();
    if (n == 1 && preorder[0] == '#') {
        return true;
    }
    if (preorder[0] == '#') {
        return false;
    }
    int numpos = 0;
    int len = (n + 1) / 2;
    //<numpos,cnt>
    stack<pair<int, int>> st;
    st.emplace(pair<int, int>{preorder[0], 0});
    int i = 2;
    while (i < n) {
        if (st.empty()) {
            return false;
        }
        if (preorder[i] == ',') {
            i++;
        }
        else if (preorder[i] == '#') {
            st.top().second++;
            i++;
        }
        else {
            st.top().second++;
            while (i < n && preorder[i] != ',') {
                i++;
            }
            st.emplace(pair<int, int>{++numpos, 0});
        }
        while (!st.empty() && st.top().second >= 2) {
            st.pop();
        }
    }
    return st.empty();
}

int main() {
    string s = "9,#,92,#,#";
    cout << isValidSerialization(s);
}