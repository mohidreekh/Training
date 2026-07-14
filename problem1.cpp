#include<iostream>
#include<algorithm>
#include<unordered_map>


using namespace std;



int main() {

	//vector<int> nums = { 2,7,11,15 };
	//vector<int> nums = { 3,2,4 };
	vector <int> nums = { 3,3 };
	int target = 6;


	sort(nums.begin(), nums.end());

	int left = 0;
	int right = nums.size() - 1;

	for (int i = 0; i < nums.size(); i++) {
		if (nums[left] + nums[right] == target)
		{
			cout << "[ " << left << " , " << right << " ]";
			break;
		}
		else if (nums[left] + nums[right] > target)
		{
			right--;
		}
		else {
			left++;
		}

	}




	//unordered_map<int, int> mNums;

	//for (int i = 0; i < nums.size(); i++)
	//{
	//	mNums[nums[i]] = i;

	//	int tryNum = target - nums[i];

	//}

	//for (auto item : mNums) {

	//	int tryNum = target - item.first;

	//	if (mNums.find(tryNum) != mNums.end() && mNums[tryNum] != item.second)
	//	{
	//		cout << "[ " << item.second << " , " << mNums[tryNum] << " ]";
	//		break;
	//	}
	//}

}