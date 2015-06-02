#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool Compare(pair <int, int> &a, pair<int, int> &b)
{
	return (a.second > b.second);
}

class PersonalChart
{
private:
	map < string, map<int, int> > Info;

public:
	void VoteRecord(const string &username, int trackID)
	{
		Info[username][trackID]++;
	}

	vector<int> GetTop(string username, int topSize)
	{
		vector<pair<int, int>> BaseUser;
		vector<int> Rez;
		map<int, int>::iterator cur;
		if (Info.find(username) == Info.end())
			return Rez;
		for (cur = (*Info.find(username)).second.begin(); cur != (*Info.find(username)).second.end(); cur++)
		{
			BaseUser.push_back(*(cur));
		}
		sort(BaseUser.begin(), BaseUser.end(), Compare);
		
		topSize = min(topSize, (int)Info[username].size());
		for (int i = 0; i < topSize; i++)
			Rez.push_back(BaseUser[i].first);
		return Rez;
	}

	int GetHistorySize(string username)
	{
		int Rez = 0;
		if (Info.find(username) == Info.end())
			return Rez;
		map<int, int>::iterator cur;
		for (cur = (*Info.find(username)).second.begin(); cur != (*Info.find(username)).second.end(); cur++)
		{
			Rez += (*cur).second;
		}
		return Rez;
	}

	int GetDistinctTrackSize(string username)
	{
		if (Info.find(username) == Info.end())
			return 0;
		return (*Info.find(username)).second.size();
	}

	int size()
	{
		return Info.size();
	}
};

void RunTest()
{
	PersonalChart Base;
	ifstream infile("ChartBase.txt");
	int Number_of_tests, i, trackID, top, j;
	string Comand, name;
	infile >> Number_of_tests;
	for (i = 0; i < Number_of_tests; i++)
	{
		infile >> Comand;
		if (Comand == "VOTE")
		{
			infile >> name >> trackID;
			Base.VoteRecord(name, trackID);
		}
		if (Comand == "TOP")
		{
			infile >> name >> top;
			vector<int> Rez;
			Rez = Base.GetTop(name, top);
			for (j = 0; j < Rez.size(); j++)
				cout << Rez[j] << " ";
			cout << endl;
		}
		if (Comand == "HISTORY_SIZE")
		{
			infile >> name;
			cout << Base.GetHistorySize(name);
			cout << endl;
		}
		if (Comand == "DISTINCT")
		{
			infile >> name;
			cout << Base.GetDistinctTrackSize(name);
			cout << endl;
		}
	}
	
}

int main()
{
	RunTest();
	return 0;
}