#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <memory>
#include <utility>
#include <regex>
#include <map>
using namespace std;

class Node{
    public:
        Node();
        virtual double freq()=0;
        virtual string symbol()=0;
};

class Branch: public Node{
    private:
        Node* left;
        Node* right;
    public:
        Branch(Node* n0, Node* n1);
        Node* getLeft(){return left;}
        Node* getRight(){return right;}
        double freq(){return left->freq()+right->freq();}
};

class Leaf: public Node{
    private:
        double _freq;
        string _symbol;
    public:
        Leaf(string&s, double f){
            _freq=f;
            _symbol=s;
        }
        double freq(){return _freq;}
        string symbol(){return _symbol;}
};

class Priority_Queue
{
	vector<Node*> vdata;
public:
	Priority_Queue() { }
	Node* top()
	{
		if (vdata.size() > 0)
			return vdata[0];
		return *vdata.end();
	}
	int size() { return vdata.size(); }
	bool empty() { return vdata.size() < 1; }
	void push(Node* n)
	{
		vdata.push_back(n);
		sort(vdata.begin(), vdata.end(),
			[](Node* a, Node* b)
			{
				return a->symbol() < b->symbol();
			});
	}
	void pop()
	{
		vdata.erase(vdata.begin());
	}
	void print()
	{
		for_each(vdata.begin(), vdata.end(),
			[](Node* n)
			{
				cout << n->symbol() << '\t' << n->freq() << endl;
			});
	}
};

class QueueTree{
    private:
    public:
};

class File{
    private:
        map<char,double> table;
    public:
        map<char,double> getTable(){return table;}
        void readText(string f);
        void readBin(string f);
};
void File::readText(string f){
    ifstream FileIn(f);
    string ascii,frequency;;
    if (FileIn.is_open()){  
        string line;
        while(getline(FileIn, line)){ 
            regex pattern("'(.*?)',([0-9]+\\.?[0-9]*)");
            std::smatch m;
            while (std::regex_search (line,m,pattern)) {
                for (auto x:m){
                    ascii=m[1];
                    frequency=m[2];
                }
                table.insert(make_pair(ascii[0],stod(frequency)));
                line = m.suffix();
            }
        }
    }
}

class Data{
    private:
        map<char,double> table;
    public:
        void setTable(map<char,double> m){table=m;}
        map<char,double> get(){return table;}
        void print_map(){
            for (auto const &pair: table){cout << pair.first << " " << pair.second << "\n";}
        }
};

int main(){
    File f;
    f.readText("AsciiFrequenciesV3.txt");
    Data d;
    d.setTable(f.getTable());
    // d.print_map();
    Priority_Queue p;
    for (auto const &pair: d.get()){
        string s(1, pair.first);
        double d = pair.second;
        Leaf l = Leaf(s,d);
        Leaf* L = &l;
        p.push(L);
    }
}