#include<stdio.h>
#include<iostream>
#include<queue>
#include<map>
#include<set>
#include<vector>
#include<utility>
#include<stack>
#include<algorithm>
#include<string>
#include<string.h>
#include<assert.h>
#include<unordered_map>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;

string s;

struct node{
    node *fail, *link;
    unordered_map<char, node*> nx;
    int len;

    node() : fail(NULL), link(NULL), len(-1){}
}*head;

// vector<vector<int> >match;m

void addString(string x){

    node *cur = head;
    for(int i = 0; i < x.length(); ++i){
        if(!cur->nx.count(x[i]))cur->nx[x[i]] = new node();
        cur = cur->nx[x[i]];
    }

    cur->len = x.length();
}

queue<node*> qu;
void buildAutomaton(){
    qu.push(head);
    while(!qu.empty()){
        node *now = qu.front(); qu.pop();

        for(auto tmp : now->nx){
            char i = tmp.fi;
            if(!now->nx.count(i))continue;
            node *nt = now->nx[i];
            nt->fail = now->fail;

            while(nt->fail && !nt->fail->nx.count(i))nt->fail = nt->fail->fail;

            if(nt->fail)nt->fail = nt->fail->nx[i];
            else nt->fail = head;

            if(nt->fail->len != -1)nt->link = nt->fail;
            else nt->link = nt->fail->link;

            qu.push(nt);
        }
    }
}

int searchStr(string str){

    node *now = head;
    int res = -1;
    for(int i = 0; i < str.length(); ++i){
        while(now != head && !now->nx.count(str[i])) now = now->fail;

        if(now->nx.count(str[i])){
            now = now->nx[str[i]];
            for(node *curr = now; curr; curr = curr->link){
                if(curr->len == -1)continue;
                if(res == -1)res = i - curr->len + 1;
                else res = min(i - curr->len + 1, res);
            }
        }
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    head = new node();

    int n; cin >> n; cin.get();
    for(int i = 0; i < n; ++i){
        getline(cin, s);
        addString(s);
    }

    buildAutomaton();
    searchStr(s);

    cin >> n; cin.get();
    for(int i = 0; i < n; ++i){
        getline(cin, s);
        int tmp = searchStr(s);
        if(tmp == -1)continue;
        cout << i + 1 << " " << tmp + 1 << endl;
        return 0;
    }

    cout << "Passed" << endl;
}