
#include <bits/stdc++.h>
using namespace std;
int id, numeric, index;
set <string> keyword =
{"auto","break","case","char",
"const","continue","default",
"do","double","else","enum",
"extern","float","for","goto",
"if","int","long","register",
"return","short","signed",
"sizeof","static","struct",
"switch","typedef","union",
"unsigned","void","volatile","while"};
set <string> operators = {"+","-","*","/","%","="};
set <string> numerics = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

bool isNumeric(string numeric_value)
{
   for(int i=0; i<numeric_value.size(); i++)
   {
       if(numerics.find(numeric_value.substr(i, 1))==numerics.end())
        return false;
   }
   return true;
}
bool isOperators(string operator_value)
{
    if(operators.find(operator_value)!=operators.end())
        return true;
    return false;
}
bool hasSpace(string space)
{
    for(int i=0; i<space.size(); i++)
    {
        if(space[i]==' ')
            return false;
    }
    return true;
}
bool isKeyword(string key_value)
{
    if(keyword.find(key_value)!=keyword.end())
        return true;
    return false;
}
void check(map <int, string> &output, string k)
{
    if(isKeyword(k))
            {
                string s=" < "+k+" > ";
                output.insert(make_pair(index++, s));
            }
    else if(isNumeric(k))
            {
                string s=" < numeric , "+to_string(++numeric) + ">";
                output.insert(make_pair(index++, s));
            }
    else if(isOperators(k))
            {
                string s="<"+k+">";
                output.insert(make_pair(index++, s));
            }
    else if(!k.empty() && hasSpace(k))
            {
                string s="<id, "+to_string(++id)+">";
                output.insert(make_pair(index++, s));
            }
}
int main()
{
    map <int, string> output;
    string input, k;
    getline(cin, input);
    int n=input.size(), cnt=0;
    for(int i=0; i<n; i++)
    {
        if(input[i]==' ')
        {
            check(output, k);
            k.clear();
        }
        else
        {
            k+=input[i];
        }
        if(i==n-1)
            check(output, k);
    }
    cout << "LEXEM: " << endl << input << endl;
    map <int, string> :: iterator it;
    cout << "Token: " << endl;
    for(it=output.begin(); it!=output.end(); it++)
    {
        cout << it->second << " ";
    }
    cout << endl;
    return 0;
}
