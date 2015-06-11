// Question 1 - Quora Application Questions 2015

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <istream>


using namespace std; 

int c = 0;

// Query Entry Type
struct item
{
	string type;
	string id;
	float score;
	string data;
};

item *list_;

// identifies if two strings are identical, regardless of capitilization
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

// identifies if one string is existent as a substring of another
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

// add query entry into database
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

// remove data entry from database

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

// recursively sort data in order of significance
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

// searches database for existense of an entry
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
	// recieves input entries of from input.txt file stores in same folder
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

	return 0;
}
