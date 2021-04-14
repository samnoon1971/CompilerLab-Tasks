
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
set <string> key={"int", "double", "float", "char", "for", "if", "else", "break", "goto", "const", "void"};
set <string> reserved={"printf", "scanf", "cin", "cout", "main"};
set <string> numeric ={"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
vector <pair<string, set <string> > > operators;
bool cmp(char c)
{
    return (c<'a' || c>'z') || (c<'A' && c>'Z');
}
set <string> text;
void init()
{
    set <string> arithmetic = {"+", "-", "<", "*", "/", "%"};
    set <string> relational = {"==", "!=", "<", ">", "<=", ">="};
    set <string> logical = {"!", "&&", "||"};
    set <string> state = {"++", "--", "=", "+=", "-=", "/=", "%="};
    text = {"%d", "%f", "%lf", "%c"};
    operators.push_back(make_pair("Arithmetic", arithmetic));
    operators.push_back(make_pair("Relational", relational));
    operators.push_back(make_pair("Logical", logical));
    operators.push_back(make_pair("State change", state));
    operators.push_back(make_pair("Textual", text));
}
bool isNumeric(string s)
{
    return numeric.find(s)!=numeric.end();
}
bool isKey(string s)
{
    return key.find(s)!=key.end();
}
bool isReserved(string s)
{
    return reserved.find(s)!=reserved.end();
}
set <string> outputKeyword, outputFunction, outputVariable;
set <pair<string, string> > outputOperators[5];
void check(string tempString)
{
    for(set <string> :: iterator it=text.begin(); it!=text.end(); it++)
    {
        if(tempString.find(*it)!=std::string::npos)
        {
            outputOperators[4].insert(make_pair("Textual", *it));
        }
    }
    if(isKey(tempString))
     outputKeyword.insert(tempString);
    else if(isNumeric(tempString))
          return;
    else if(isReserved(tempString))
        outputFunction.insert(tempString);
    else
    {
    int cnt=0;
    set <string> :: iterator it;
    vector <pair<string, set <string> > > :: iterator ip;
    for(ip=operators.begin(); ip!=operators.end(); ip++)
    {
    set <string> ms=ip->second;
    if(ms.find(tempString)!=ms.end())
    {
      cnt++;
    if(ip->first=="Arithmetic")
    {
      outputOperators[0].insert(make_pair(ip->first, tempString));
    }
    else if(ip->first=="Relational")
    {
      outputOperators[1].insert(make_pair(ip->first, tempString));
    }
    else if(ip->first=="Logical")
    {
      outputOperators[2].insert(make_pair(ip->first, tempString));
     }
    else if(ip->first=="State change")
    {
      outputOperators[3].insert(make_pair(ip->first, tempString));
    }
    else
     {
     outputOperators[4].insert(make_pair(ip->first, tempString));
     }
    }
     if(!cnt)
     {
         int sum=count_if(tempString.begin(), tempString.end(), cmp);
         if(sum==0)
            outputVariable.insert(tempString);
     }
    }
    }
}
int main()
{
    init();
    string functionInput;
    do
    {
    getline(cin, functionInput);
    set <string> :: iterator it;
    for(it=key.begin(); it!=key.end(); it++)
    {
        if(functionInput.find(*it)!=std::string::npos)
        {
            outputKeyword.insert(*it);
            break;
        }
    }
    for(it=reserved.begin(); it!=reserved.end(); it++)
    {
        if(functionInput.find(*it)!=std::string::npos)
        {
            outputFunction.insert(*it);
            break;
        }
    }
    if(outputFunction.empty())
    {
        string tempString;
        for(int i=0; i<functionInput.size(); i++)
        {
            if(functionInput[i]==' ')
            {
                if(!tempString.empty())
                {
                    if(isKey(tempString)!=true && isReserved(tempString)!=true && tempString!="()")
                    {
                        outputFunction.insert(tempString);
                        break;
                    }
                    tempString.clear();
                }
            }
            else
                tempString+=functionInput[i];
        }
    }
    }while(outputFunction.find("main")==outputFunction.end());
    string input;
    cin >> input;
    while(1)
    {
        int cx=0;
        getline(cin, input);
        for(int i=0; i<input.size(); i++)
        {
            if(input[i]=='}')
            {
                cx++;
                break;
            }
        }
        if(cx) break;
        string tempString;
        for(int i=0; i<input.size(); i++)
        {
            if(input[i]==' ')
            {
                if(!tempString.empty())
                {

                    check(tempString);
                }
                tempString.clear();
            }
            else
            {
                tempString+=input[i];
            }
            if(i+1==input.size())
                check(tempString.substr(0, tempString.size()-1));
        }
    }
    set <string> :: iterator is2;
    cout << "Functions: ";
    for(is2=outputFunction.begin(); is2!=outputFunction.end(); is2++)
    {
        cout << *is2 << " ";
    }
    cout << endl << endl;
    cout << "Variables: ";
    for(is2=outputVariable.begin(); is2!=outputVariable.end(); is2++)
    {
        cout << *is2 << " ";
    }
    cout << endl << endl;
    for(int i=0; i<5; i++)
    {
        if(outputOperators[i].empty())
            continue;
        cout << outputOperators[i].begin()->first << ": " << endl;

        set <pair<string, string> > :: iterator iqs;

        for(iqs=outputOperators[i].begin(); iqs!=outputOperators[i].end(); iqs++)
        {
            cout << iqs->second << " ";
        }
        cout << endl;

    }
    cout << endl << endl;
    cout << "Keyword: ";
    for(is2=outputKeyword.begin(); is2!=outputKeyword.end(); is2++)
    {
        cout << *is2 << " ";
    }
    cout << endl;
    return 0;
}
