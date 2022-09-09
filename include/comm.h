#ifndef COMM_H
#define COMM_H

#include <vector>

using namespace std;

// 公共方法命名空间
namespace Tool {

void for_each(vector<int> &arr);
// count 产生随机数的个数
void random(vector<int> &arr, int count = 10);
//获取从[start-end)之间的随机index
int getrandom(int start, int end);

}  // namespace Tool

#endif