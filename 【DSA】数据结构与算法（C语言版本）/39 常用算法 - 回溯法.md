#算法 
# 概要
回溯法（back tracking）（探索与回溯法）是一种选优搜索法，又称为试探法，按选优条件向前搜索，以达到目标。但当探索到某一步时，发现原先选择并不优或达不到目标，就退回到上一步，重新选择，这种走不通就退回再走的技术为回溯法，而满足回溯条件的某个状态的点称为“回溯点”。

# 通用方法
通常的算法模板如下：
```cpp
result = []
// 路径表示你已经做出的选择，选择列表代表你还可以继续做的选择
backtrack (路径，选择列表):
  if 满足结束条件：
    result.push(路径);
    return;

  for 选择 in 选择列表:
    做选择;
    backtrack(路径, 选择列表);
    撤销选择;
```

![](img/09_other_algorithm/全排列%20回溯算法.png)


# 全排列
以对一个数组进行全排列算法为例子：

```cpp
class Solution {
public:
    void backtrack(vector<vector<int>>& res, vector<int>& output, int usedLen, int len) {
    // 所有数都填完了
        if (usedLen == len) {
            // 测试打印代码
            cout << "output emplace back to res : [";
            for (auto i : output)
            {
                cout << i << ",";
            }
            cout << "]" << endl;

            res.emplace_back(output);
            return;
        }
        for (int i = usedLen; i < len; ++i) {
            // 测试打印代码
            cout << "i = " << i << ", usedLen = " << usedLen << endl;
            // 动态维护数组
            swap(output[i], output[usedLen]);

            // 测试打印代码
            cout << "swap : ";
            cout << "output[" << i << "] = " << output[i] <<" ";
            cout << "output[" << usedLen << "] = " << output[usedLen] << endl;

            // 继续递归填下一个数
            backtrack(res, output, usedLen + 1, len);
         
            // 撤销操作
            swap(output[i], output[usedLen]);
      }
   }
   vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        backtrack(res, nums, 0, (int)nums.size());
        return res;
   }
};

int main(void) {
    Solution solu;
    vector<vector<int>> res;
    vector<int> input{3, 5, 6};
    res = solu.permute(input);

    // 测试打印代码
    for (int i = 0; i < res.size(); i++) {
        cout << "[";
        for (int j = 0; j < res[i].size(); j++)
        {
            cout << res[i][j] << ",";
        }
        cout << "]";
    }

   return 0;
}
```

打印输出：
```txt
i = 0, usedLen = 0
swap : output[0] = 3 output[0] = 3
i = 1, usedLen = 1
swap : output[1] = 5 output[1] = 5
i = 2, usedLen = 2
swap : output[2] = 6 output[2] = 6
output emplace back to res : [3,5,6,]
i = 2, usedLen = 1
swap : output[2] = 5 output[1] = 6
i = 2, usedLen = 2
swap : output[2] = 5 output[2] = 5
output emplace back to res : [3,6,5,]
i = 1, usedLen = 0
swap : output[1] = 3 output[0] = 5
i = 1, usedLen = 1
swap : output[1] = 3 output[1] = 3
i = 2, usedLen = 2
swap : output[2] = 6 output[2] = 6
output emplace back to res : [5,3,6,]
i = 2, usedLen = 1
swap : output[2] = 3 output[1] = 6
i = 2, usedLen = 2
swap : output[2] = 3 output[2] = 3
output emplace back to res : [5,6,3,]
i = 2, usedLen = 0
swap : output[2] = 3 output[0] = 6
i = 1, usedLen = 1
swap : output[1] = 5 output[1] = 5
i = 2, usedLen = 2
swap : output[2] = 3 output[2] = 3
output emplace back to res : [6,5,3,]
i = 2, usedLen = 1
swap : output[2] = 5 output[1] = 3
i = 2, usedLen = 2
swap : output[2] = 5 output[2] = 5
output emplace back to res : [6,3,5,]
[3,5,6,][3,6,5,][5,3,6,][5,6,3,][6,5,3,][6,3,5,]
```



```cpp
class Solution {
public:
    vector<vector<int>> res;    // 返回结果
    vector<int> temp;           // 存储暂时的单个排列
    vector<vector<int>> permute(vector<int> &nums) {
        vector<int> path(nums.size(), 0);   // 存储已经过路径
        BackTrack(nums, temp, path);

        return res;
    }

    void BackTrack(vector<int> &nums, vector<int> &temp, vector<int> &path)
    {
        // 满足结束条件
        if (temp.size() == nums.size()) {
            res.emplace_back(temp);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (path[i] == 0) {
                temp.emplace_back(nums[i]);
                path[i] = 1;

                // path 记录了对应的位置的原数组是否已经被复制
                BackTrack(nums, temp, path);

                temp.pop_back();
                path[i] = 0;
            } 
        }
    }
};
```