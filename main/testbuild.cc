#include "minirpc/comm/log.h"
#include <string>
#include <iostream>
using namespace std;
class Solution
{
    string name[20] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    string teen_name[20] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    string decimal_name[20] = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    string carry_name[5] = {"Thousand", "Million", "Billion"};
    string hundred_name = "hundred";

public:
    string numberToWords(int num)
    {
        string ans;

        if (num == 0)
        {
            return "Zero";
        }
        if (num < 1000)
        {
            ans += hundredToWords(num);
        }
        else if (num >= 1000 && num < 1000000)
        {
            ans = hundredToWords(num / 1000) + " " + carry_name[0] + hundredToWords(num % 1000);
        }
        else if (num >= 1000000 && num < 1000000000)
        {
            ans = hundredToWords(num / 1000000) + " " + carry_name[1];
            if ((num / 1000) % 1000 != 0)
            {
                ans = ans + hundredToWords((num / 1000) % 1000) + " " + carry_name[0];
            }
            ans = ans + hundredToWords(num % 1000);
        }
        else if (num >= 1000000000)
        {
            ans = hundredToWords(num / 1000000000) + " " + carry_name[2];

            if ((num / 1000000) % 1000 != 0)
            {
                ans = ans + hundredToWords((num / 1000000) % 1000) + " " + carry_name[1];
            }
            if ((num / 1000) % 1000 != 0)
            {
                ans = ans + hundredToWords((num / 1000) % 1000) + " " + carry_name[0];
            }
            ans = ans + hundredToWords(num % 1000);
        }
        else
            return "Error";
        if (!ans.empty() && ans[0] == ' ')
        {
            return ans.substr(1);
        }
        else
            return ans + "??";
    }
    string hundredToWords(int num)
    {
        string s;
        if (num >= 1000)
        {
            return "Error Call\n";
        }
        if (num / 100 >= 1)
        {
            s = s + " " + name[num / 100] + " Hundred"; // 百位
        }
        if (num % 100 >= 1)
        {
            int midnum = (num % 100) / 10;
            if (midnum == 1)
            {
                s = s + " " + teen_name[num % 10]; // 十位
            }
            else
            {
                if (midnum >= 2)
                {
                    s = s + " " + decimal_name[midnum]; // 十位
                }
                if (num % 10 > 0)
                {
                    s = s + " " + name[num % 10]; // 个位
                }
            }
        }
        return s;
    }
};
int main()
{
    Solution s;
    int num;
    cin >> num;
    cout << s.numberToWords(num) << endl;
    return 0;
}