#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int i = 0, n = 0, m = 0;
int j = 0;//行
int f = 0;//作为判断是否遇到敏感词的标志
int num = 0;//例文中敏感词数
int l;//敏感词的数量
class mgcs
{
public:
	string words;//敏感词
	string anss;
	int h;
}s[1000];//作为输出的答案
class wordd
{
public:
	string word;
	int hanying;//敏感词的类型
	int zishu;//字数
	string pinyin[1000];
}w[1000];//题目给出的敏感词
void read()
{
	string words;
	cin >> words;
	ifstream ifile;
	ifile.open(words);// 以读模式打开文件
	if (!ifile) cout << "open fail" << endl;
	else
	for (l = 0; ifile >> w[l].word; l++)// 从文件读取敏感词
	{
		if (w[l].word[0] > 0)
		{
			w[l].hanying = 0;//敏感词为英文
		}
		else
		{
			w[l].hanying = 1;//敏感词为汉字
		}
	}
	ifile.close();// 关闭打开的文件
}
void hanzi(string ans, string org)
{
	for (i = 0, m = 0, f = 0; i < org.length(); i++)
	{
		if (org[i] == w[n].word[m] && org[i + 1] == w[n].word[m + 1] && org[i + 2] == w[n].word[m + 2])//utf-8汉字占3字节
		{
			f = 1;
			ans = ans + org[i] + org[i + 1] + org[i + 2];
			m = m + 3;
			if (m > w[n].word.length() - 1)//超出长度则表示已找到敏感词，并开始继续查找
			{
				m = 0;
				f = 0;
				s[num].words = w[n].word;
				s[num].anss = ans;
				s[num].h = j;
				num++;
				ans = "";
				continue;
			}
			i = i + 2;
			continue;
		}
		if (org[i] >= '0' && org[i] <= '9' || org[i] >= 'A' && org[i] <= 'Z' || org[i] >= 'a' && org[i] <= 'z')
		{
			f = 0;
			ans = "";
			continue;
		}//敏感词中插入字母、数字、换行的若干字符就不属于敏感词
		if (f == 1)
			ans = ans + org[i];
	}
}
void yinwen(string ans, string org)
{
	for (i = 0, m = 0, f = 0; i < org.length(); i++)
	{
		if ((org[i] >= 'A' && org[i] <= 'Z') || (org[i] >= 'a' && org[i] <= 'z'))
		{
			if (org[i] == w[n].word[m] || org[i] - w[n].word[m] == 32 || w[n].word[m] - org[i] == 32)//英文文本不区分大小写，在敏感词中不能插入换行、字母
			{
				f = 1;
				ans = ans + org[i];
				m = m + 1;
				if (m > w[n].word.length() - 1)//超出长度则表示已找到敏感词，并开始继续查找
				{
					m = 0;
					f = 0;
					s[num].words = w[n].word;
					s[num].anss = ans;
					s[num].h = j;
					num++;
					ans = "";
				}
			}
			else
			{
				f = 0;
				m = 0;
				ans = "";
			}
			continue;
		}
		if (f == 1)
			ans = ans + org[i];
	}
}
void search()
{
	string org;//例文
	cin >> org;
	ifstream ifile;
	ifile.open(org);// 以读模式打开文件
	if (!ifile) cout << "open fail" << endl;
	else
	while (getline(ifile, org))// 从文件读取每行例文
	{
		j++;
		for (n = 0; n < l; n++)//用循环查找每个敏感词
		{
			string ans;
			if (w[n].hanying == 1)//如果敏感词为汉字
				hanzi(ans,org);
			if (w[n].hanying == 0)//如果敏感词为英文
				yinwen(ans,org);
		}
	}
	ifile.close();// 关闭打开的文件
}
void print()//将答案写入文件中
{
	string ans;
	cin >> ans;
	ofstream outfile; 
	outfile.open(ans);// 以写模式打开文件
	outfile << "Total:" << num << endl;
	for (i = 0; i < num; i++)
	{
		outfile << "Line" << s[i].h << ": " << "<" << s[i].words << ">" << " " << s[i].anss << endl;
	}// 向文件写入得到的数据
	outfile.close();// 关闭打开的文件
}
int main()
{
	system("chcp 65001");
	read();
	search();
	print();
	return 0;
}
