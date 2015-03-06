#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <istream>


using namespace std; 

int c = 0;

struct item
{
	string type;
	string id;
	float score;
	string data;
};

item *list_;

bool same (string s1, string s2)
{
        int sz = s1.size();
        if (s2.size() != sz)
                return false;
        for (int i = 0; i < sz; i++)
                if (tolower(s1[i]) != tolower(s2[i]))
                        return false;
        return true;
}

bool findS(string s1, string s2)
{
	int sz = s1.size();
	for (int i = 0; i <sz; i++)
		if (tolower(s1[i]) == tolower(s2[0]))
		{
			int a = i;
			for (int j = 0; j < s2.size(); j++)
				if (tolower(s1[a]) != tolower(s2[j]))
					break;
				else if (s2.size() == j+1)
					return true;
				else 
					a++;
		}
	return false;
}


void add (item next)
{
	if (c > 0)
	{
		item* temp_ = new item [c + 1];
		for (int i = 0; i < c; i++)
		{
			temp_[i] = list_[i];
		}
		delete [] list_;
		list_ = temp_;
		list_[c] = next;
	}
	else
	{
		list_ = new item[c+1];
		list_[c] = next;
	}	
	c++;
}

void del (string id2)
{
	if (c > 1)
	{
		item* temp_ = new item [c - 1];
		int j = 0;
		for (int i = 0; i < c; i++ )
		{
			if (!same(list_[i].id, id2))
			{
				temp_[j] = list_[i];
				j++;
			}
		}
		delete[] list_;
		list_ = temp_;
		c--;	
	}
	else
	{
		list_ = NULL;
		c--;
	} 
}


void sort (float *arr, string *arrID, int left, int  right)
{
	int i = left;
	int j = right; 
	float pivot = arr[(i + j)/2];
	float tmp;
	string tmp2; 
	
	while (i <=j)
	{
		while (arr[i] > pivot)
			i++;
		while (arr[j] < pivot)
			j--;
		if (i <= j)
		{
			tmp = arr[i];
			tmp2 = arrID[i]; 
			arr[i] = arr[j];
			arrID[i] = arrID[j];
			arr[j] = tmp;
			arrID[j] = tmp2; 
			i++;
			j--;
		}
	};
	
	if (left < j)
		sort (arr, arrID, left,  j);
	if (i < right)
		sort (arr, arrID, i, right);
}

void query (int results, string search)
{
//	if (results <2)
//	{
//		cout << endl;
//		return;
//	}
	
	int t = 0;
	float* arr = new float [c];
	string* arrID = new string [c]; 
	
	for (int i = 0 ; i < c; i++)
	{
		if (findS(list_[i].data, search))
		{
			arr[t] = list_[i].score;
			arrID[t] = list_[i].id;
			t++;
		}
	}
	sort (arr, arrID, 0, t-1);

	for (int i = 0; i < results; i++)
	{
		if (i > t-1)
			break;
		cout << arrID[i] << " ";
	}
	cout << endl;
}

int main ()
{
	ifstream input ("input.txt");
	int max;
	input >>  max;
	int l = 0;
	string function;
	string type;
	string id;
	float score;
	string data;
	int results;
	item a ;
	while (l < max)
	{
		input >> function;
		cout << function << endl;
		if (function == "ADD")
		{
			input >> type >> id >> score;
			getline(input, data);
			a.type = type;
			a.id = id;
			cout << id << endl;
			a.score = score;
			a.data = data;
			cout << data << endl;;
			add (a);	
			cout << "done" << endl;
		}
		else if (function == "DEL")
		{
			input >> id; 
			del (id);
	 	}	
		else if (function == "QUERY")
		{
			input >> results;
			getline(input, data);
			query(results, data);	
		}
		else if (function == "WQUERY"){
			getline(input, data);
		}
		else 
		{
			cout << "Wrong Input" << endl;
		}
		l++;
	}
/*
	cout << "hello" << endl;			
	cout << c << endl;
	item a1 = {"usier", "hi", 100.0, "c"};
	add (a1);
	item a2 = {"a", "b", 1.0, "c"};
	add (a2);
	add (a2);
	cout << c << endl;
	item a3 = {"d", "e", 2.0, "c"};
	add (a3);
	del ("hi");
	cout << c << endl;
//	query (15, "c");
	string hello = "hello World";
	string hi = "o w";
	if (findS(hello, hi))
		cout << hi << endl;
*/
	return 0;
}
