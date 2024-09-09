#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <sstream>
using namespace std;

int main()
{
	int mode;
	double number[20];
	bool is;

	cout<<"this a calculator"<<endl;
	cout<<"1-----addition"<<endl;
	cout<<"2-----subtraction"<<endl;
	cout<<"3-----multiplication"<<endl;
	cout<<"4-----division"<<endl;
	cin>>mode;
	while(is)
	{
		for(int i = 0;i <20; i++){
			cin>>number[i];
		}
	}

	double resu;
	switch(mode){
		case 1:
			cout<<"1-----addition"<<endl;
			break;
		case 2:
			cout<<"2-----subtraction"<<endl;
			break;
		case 3:
			cout<<"3-----multiplication"<<endl;
			break;
		case 4:
			cout<<"4-----division"<<endl;
			break;
		default:
			break;
	}

	stringstream ss;
	bool isfirst = true;
	while(true)
	{
		string tmp;
		getline(cin,tmp);
		if(tmp == "w") break;
		ss.clear();
		ss.str(tmp);
		double tmpval;
		ss >> tmpval;
		if(isfirst)
		{
			resu = tmpval;
			isfirst = false;
		}
		else
		{
			switch(mode)
			{
				case 1:
					resu += tmpval;
					break;
				case 2:
					resu -= tmpval;
					break;
				case 3:
					resu *= tmpval;
					break;
				case 4:
					resu /= tmpval;
					break;
				default:
					assert(0);
					break;
			}
		}
	}

	cout << "Result: " << resu << endl;
	cout << "Calculation ended." << endl;

	return 0;
}