#include<iostream>
#include<vector>
using namespace std;
#define int long long

int normalsearch(vector<int>a,int b)
{
    if (a.size()==0)
    {
        return 1000000;
    }

    int j=1;
    for(int i=0;i<a.size();i++)
    {
        if(a[i]==b)
        {
            j=(-1)*i-1;
            break;
        }
    }
    return j;
}

int searcher(vector<int> a,int b)
{
    int i=0;
    if (a.size()==0)
    {
        return 1000000;
    }
    
    while((b>a[i])&&(i<a.size()))
    {
        i++;
    }
    if(i!=a.size())
    {
        if(b==a[i])
        {
            return ((-1)*i-1);
        }
        else
        {
            return i;
        }
    }
    else
    {
        return a.size();
    }
}

vector<int> inserter(vector<int> a,int b)
{
    if(a.size()==0)
    {
        a.push_back(b);
        return a;
    }
    int index=searcher(a,b);
    if(index>=0)
    {
        a.push_back(b);
        for(int i=a.size()-1;i>index;i--)
        {
            int temp=a[i];
            a[i]=a[i-1];
            a[i-1]=temp;
        }
    }
    return a;
}

vector<int> deleter(vector<int>a,int b)
{
    if(a.size()==0)
    {
        return a;
    }
    int index=searcher(a,b);
    if((index<0)&&(a.size()!=1))
    {
        for(int i=(-index-1);i<(a.size()-1);i++)
        {
            int temp=a[i];
            a[i]=a[i+1];
            a[i+1]=temp;
        }
        a.pop_back();
    }
    else if((index<0)&&(a.size()==1))
    {
        a.clear();
    }
    return a;
}

int belongs_to(vector<int>a,int b)
{
    if(a.size()==0)
    {
        return 0;
    }
    if(searcher(a,b)<0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

vector<int> labourunion(vector<int>a,vector<int>b)
{
    if(a.size()==0)
    {
        return b;
    }
    else if(b.size()==0)
    {
        return a;
    }
    else{
        for(int i=0;i<b.size();i++)
        {
            a=inserter(a,b[i]);
        }
        return a;
    }
}

vector<int> theroadnottaken(vector<int>a,vector<int>b)
{
    vector<int> c;
    if((a.size()==0)||(b.size()==0))
    {
        return c;
    }
    for(int i=0;i<b.size();i++)
    {
        if(searcher(a,b[i])<0)
        {
            c.push_back(b[i]);
        }
    }
    return c;
}

vector<int> difference(vector<int>a,vector<int>b)
{
    if(a.size()==0)
    {
        return a;
    }
    else if(b.size()==0)
    {
        return a;
    }
    else{
        for(int i=0;i<b.size();i++)
        {
            a=deleter(a,b[i]);
        }
        return a;
    }
}

vector<int> symmetricdiff(vector<int>a,vector<int>b)
{
    vector<int>c,d;
    c=difference(a,b);
    d=difference(b,a);
    return labourunion(c,d);
}

int printer(vector<int>a)
{
    for(int i=0;i<a.size()-1;i++)
    {
        cout<<a[i]<<",";
    }
    cout<<a[a.size()-1]<<"\n";
    return 0;
}

class SET
{
    public:
    vector<int> keys;
    vector<vector<int> > sets;
    void insert(int a,int b)
    {
        int index=normalsearch(keys,a);
        if(index>=0)
        {
            keys.push_back(a);
            vector<int>c;
            c.push_back(b);
            sets.push_back(c);
            cout<<"1\n";
            return;
        }
        else
        {
            int meow=-index-1;
            vector<int>c;
            c=inserter(sets[meow],b);
            sets[meow]=c;
            cout<<sets[meow].size()<<"\n";
            return;
        }
    }

    void deleteMe(int a, int b)
    {
        int index=normalsearch(keys,a);
        if(index>=0)
        {
            cout<<"-1\n";
        }
        else
        {
            int meow=-index-1;
            sets[meow]=deleter(sets[meow],b);
            cout<<sets[meow].size()<<"\n";
        }
    }

    void baghban(int a, int b)
    {
        int index=normalsearch(keys,a);
        if(index>=0)
        {
            cout<<"-1\n";
        }
        else
        {
            index=belongs_to(sets[-index-1],b);
            cout<<index<<"\n";
        }
    }

    void unity(int a, int b)
    {
        int index1=normalsearch(keys,a);
        int index2=normalsearch(keys,b);
        if(index1>=0)
        {
            vector<int>c;
            keys.push_back(a);
            sets.push_back(c);
            index1=keys.size()-1;
        }
        else
        {
            index1=-index1-1;
        }
        if(index2>=0)
        {
            vector<int>d;
            keys.push_back(b);
            sets.push_back(d);
            index2=keys.size()-1;
        }
        else
        {
            index2=-index2-1;
        }
        sets[index1]=labourunion(sets[index1],sets[index2]);
        cout<<sets[index1].size()<<"\n";
    }

    void intersector(int a, int b)
    {
        int index1=normalsearch(keys,a);
        int index2=normalsearch(keys,b);
        if(index1>=0)
        {
            vector<int>c;
            keys.push_back(a);
            sets.push_back(c);
            index1=keys.size()-1;
            cout<<"0\n";
            if(index2>=0)
            {
                vector<int>d;
                keys.push_back(b);
                sets.push_back(d);
            }
            return;
        }
        else if(index2>=0)
        {
            vector<int>e;
            keys.push_back(b);
            sets.push_back(e);
            index2=keys.size()-1;
            index1=-index1-1;
            sets[index1].clear();
            cout<<"0\n";
            return;
        }
        else
        {
            index1=-index1-1;
            index2=-index2-1;
            sets[index1]=theroadnottaken(sets[index1],sets[index2]);
            cout<<sets[index1].size()<<"\n";
        }
        
    }
    
    void racist(int a, int b)
    {
        int index1=normalsearch(keys,a);
        int index2=normalsearch(keys,b);
        if(index1>=0)
        {
            vector<int>c;
            keys.push_back(a);
            sets.push_back(c);
            index1=keys.size();
        }
        else
        {
            index1=-index1-1;
        }
        if(index2>=0)
        {
            vector<int>d;
            keys.push_back(b);
            sets.push_back(d);
            index2=keys.size();
        }
        else
        {
            index2=-index2-1;
        }
        sets[index1]=difference(sets[index1],sets[index2]);
        cout<<sets[index1].size()<<"\n";
    }

    void symmetrico(int a, int b)
    {
        int index1=normalsearch(keys,a);
        int index2=normalsearch(keys,b);
        if(index1>=0)
        {
            vector<int>c;
            keys.push_back(a);
            sets.push_back(c);
            index1=keys.size()-1;
        }
        else
        {
            index1=-index1-1;
        }
        if(index2>=0)
        {
            vector<int>d;
            keys.push_back(b);
            sets.push_back(d);
            index2=keys.size()-1;
        }
        else
        {
            index2=-index2-1;
        }
        sets[index1]=symmetricdiff(sets[index1],sets[index2]);
        cout<<sets[index1].size()<<"\n";

    }

    void johnny(int a)
    {
        int index=normalsearch(keys,a);
        if(index<0)
        {
            cout<<sets[-index-1].size()<<"\n";
        }
        else
        {
            keys.push_back(a);
            vector<int>c;
            sets.push_back(c);
            cout<<"0\n";
        }
    }

    void print(int a)
    {
        int index=normalsearch(keys,a);
        if(index<0)
        {
            if(sets[-index-1].size()>0){
                printer(sets[-index-1]);
            }
            else
            {
                cout<<"\n";
            }
        }
        else
        {
            keys.push_back(a);
            vector<int>c;
            sets.push_back(c);
            cout<<"\n";
        }
    }
};



signed main()
{
    SET me;
    int temp;
    while(cin>>temp)
    {
        switch(temp)
        {
            int a,b;

            case 1:
            cin>>a>>b;
            me.insert(a,b);
            break;

            case 2:
            cin>>a>>b;
            me.deleteMe(a,b);
            break;

            case 3:
            cin>>a>>b;
            me.baghban(a,b);
            break;

            case 4:
            cin>>a>>b;
            me.unity(a,b);
            break;

            case 5:
            cin>>a>>b;
            me.intersector(a,b);
            break;

            case 6:
            cin>>a;
            me.johnny(a);
            break;

            case 7:
            cin>>a>>b;
            me.racist(a,b);
            break;

            case 8:
            cin>>a>>b;
            me.symmetrico(a,b);
            break;

            case 9:
            cin>>a;
            me.print(a);
            break;
        }
    }
}