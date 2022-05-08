// Calvin Vu
// Lab 1: Bitsets
// CIS29
// C++17
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <memory>
#include <utility>
#include <bitset>
using namespace std;

class File{
    private:
        vector<char> rawdata;
    public:
        void readFile(string f);
        vector<char> getData(){return rawdata;}
};
void File::readFile(string f){ 
    ifstream in;
    in.open(f, ios::in | ios::binary);
    if(in.is_open()){
        streampos start = in.tellg();
        in.seekg(0, ios::end);
        streampos end = in.tellg();
        in.seekg(0, ios::beg);
        rawdata.resize(static_cast<size_t>(end-start));
        in.read(&rawdata[0], rawdata.size());
    }
    in.close();
}
class Database{
    private:
        vector<char> data;
        vector<char> result;
    public:
        void setData(vector<char> d){data = d;}
        vector<char> getData(){return data;}
        void setResult(vector<char> r){result = r;}
        vector<char> getResult(){return result;}
};

class Process{
    private:
        enum bits{zero_one=0b00000001, one_zero=0b00000010, zero_zero=0b000000000, one_one=0b00000011};
        unique_ptr<vector<tuple<char, bitset<12>>>> morseKey; //smart pointer
        vector<char> decrypted;
    public:
        Process(){
            morseKey = make_unique<vector<tuple<char, bitset<12>>>>();
            morseKey->push_back(make_tuple('A', bitset<12>("1001")));
            morseKey->push_back(make_tuple('B', bitset<12>("01101010")));
            morseKey->push_back(make_tuple('C', bitset<12>("01100110")));
            morseKey->push_back(make_tuple('D', bitset<12>("011010")));
            morseKey->push_back(make_tuple('E', bitset<12>("10")));
            morseKey->push_back(make_tuple('F', bitset<12>("10100110")));
            morseKey->push_back(make_tuple('G', bitset<12>("010110")));
            morseKey->push_back(make_tuple('H', bitset<12>("10101010")));
            morseKey->push_back(make_tuple('I', bitset<12>("1010")));
            morseKey->push_back(make_tuple('J', bitset<12>("10010101")));
            morseKey->push_back(make_tuple('K', bitset<12>("011001")));
            morseKey->push_back(make_tuple('L', bitset<12>("10011010")));
            morseKey->push_back(make_tuple('M', bitset<12>("0101")));
            morseKey->push_back(make_tuple('N', bitset<12>("0110")));
            morseKey->push_back(make_tuple('O', bitset<12>("010101")));
            morseKey->push_back(make_tuple('P', bitset<12>("10010110")));
            morseKey->push_back(make_tuple('Q', bitset<12>("01011001")));
            morseKey->push_back(make_tuple('R', bitset<12>("100110")));
            morseKey->push_back(make_tuple('S', bitset<12>("101010")));
            morseKey->push_back(make_tuple('T', bitset<12>("01")));
            morseKey->push_back(make_tuple('U', bitset<12>("101001")));
            morseKey->push_back(make_tuple('V', bitset<12>("10101001")));
            morseKey->push_back(make_tuple('W', bitset<12>("100101")));
            morseKey->push_back(make_tuple('X', bitset<12>("01101001")));
            morseKey->push_back(make_tuple('Y', bitset<12>("01100101")));
            morseKey->push_back(make_tuple('Z', bitset<12>("01011010")));
            morseKey->push_back(make_tuple('0', bitset<12>("0101010101")));
            morseKey->push_back(make_tuple('1', bitset<12>("1001010101")));
            morseKey->push_back(make_tuple('2', bitset<12>("1010010101")));
            morseKey->push_back(make_tuple('3', bitset<12>("1010100101")));
            morseKey->push_back(make_tuple('4', bitset<12>("1010101001")));
            morseKey->push_back(make_tuple('5', bitset<12>("1010101010")));
            morseKey->push_back(make_tuple('6', bitset<12>("0110101010")));
            morseKey->push_back(make_tuple('7', bitset<12>("0101101010")));
            morseKey->push_back(make_tuple('8', bitset<12>("0101011010")));
            morseKey->push_back(make_tuple('9', bitset<12>("0101010110")));
            morseKey->push_back(make_tuple('.', bitset<12>("100110011001")));
            morseKey->push_back(make_tuple(',', bitset<12>("010110100101")));
            morseKey->push_back(make_tuple('"', bitset<12>("100110100110")));
            morseKey->push_back(make_tuple('\'',bitset<12>("100101010110")));
            morseKey->push_back(make_tuple(' ', bitset<12>("11")));
        }
        void decrypt(Database& d);
        void search(bitset<12> binchar);
        vector<char> get(){return decrypted;}
};
void Process::decrypt(Database& d){
    string binchar ="";
    bitset<8> bit_limiter(0b00000011);
    vector<char> encryptedstring = d.getData();
    for(int i=0;i<encryptedstring.size();i++){
        bitset<8> temp (encryptedstring.at(i));
        int index = 6;
        for(int j=0;j<4;j++){
            bitset<8> retrieve(((temp>>index)&(bit_limiter)));
            if(retrieve==zero_one){binchar+="01";}
            else if(retrieve==one_zero){binchar+="10";}
            else if(retrieve==zero_zero){
                search(bitset<12>(binchar));
                binchar.clear();
            }
            else if(retrieve==one_one){
                decrypted.push_back(' ');
                binchar.clear();
            }
            index-=2;
        }
    }
    d.setResult(decrypted);
}
void Process::search(bitset<12> binchar){
    for (auto&& tuple: *morseKey){
        char letter;
        bitset<12> binary;
        tie(letter, binary) = tuple;
        if(binary == binchar){decrypted.push_back(letter);}
    }
}

class Output{
    private:
    public:
        void print(vector<char> s){
            for(int i=0;i<s.size();i++){cout<<s.at(i);}
        }
};

int main(){
    File f;
    Database d;
    Process p;
    Output o;
    f.readFile("Morse.bin");
    d.setData(f.getData());
    p.decrypt(d);
    o.print(d.getResult());
    // bitset<8> x ('R');
    // bitset<8> y("00000011");
    // bitset<8> z(((x>>0)&(y)));
    // cout << (z) << endl;
}