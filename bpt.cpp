#include<iostream>
#include<stdio.h>
#include<utility>
using namespace std;

struct dicNode
{
    string key;
    string meaning;
};

struct bplusNode
{
    dicNode *data;
    bplusNode **child_ptr;
    bool isLeaf;
    int n;
};

bplusNode *x,*root;

bplusNode *init()
{
    bplusNode *np;
    np = new bplusNode;
    np->data = new dicNode[5];
    np->child_ptr = new bplusNode*[6];
    np->isLeaf = true;
    np->n = 0;

    for(int i=0;i<6;i++)
    {
        np->child_ptr[i] = NULL;
    }

    return np;
}

void sort(dicNode *p,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<=n;j++)
        {
            if(p[i].key>p[j].key)
            {
                swap(p[i],p[j]);
            }
        }
    }
}

void traverse(bplusNode * b)
{
    int i;

    for(i=0;i<b->n;i++)
    {
        if(!b->isLeaf)
        {
            traverse(b->child_ptr[i]);
        }

        cout << b->data[i].key << " " << b->data[i].meaning << endl;
    }

    if(!b->isLeaf)
    {
        traverse(b->child_ptr[i]);
    }

    cout << endl;

}

void search(string k)
{
    x = root;

    int i;

    while(!(x->isLeaf))
    {
        for(i =0;i<x->n;i++)
        {
            if(k > x->data[i].key && k < x->data[i+1].key)
            {
                i++;
                break;
            }

            else if(k < x->data[0].key)
            {
                break;
            }

            else
            {
                continue;
            }
        }

        x = x->child_ptr[i];
    }

    for(int j=0;j<x->n;j++)
    {
        if(x->data[j].key==k)
        {
            cout << k << "--" << x->data[j].meaning << endl;
            break;
        }
    }
}

dicNode split(bplusNode *x,int i)
{
    int j;
    //string mid,mmid;
    dicNode mid;

    bplusNode *np1,*np3,*y;

    np3 = init();

    if(i==-1)
    {
        /*mid = x->data[2].key;
        mmid = x->data[2].meaning;*/
        mid = x->data[2];
        x->data[2].key="";
        x->data[2].meaning="";
        //mid = x->data[2];
        //x->data[2]=NULL;
        x->n--;

        np1 = init();
        np1->isLeaf = false;
        x ->isLeaf = true;

        for (j = 3; j < 5; j++)
        {
            np3->data[j - 3] = x->data[j];
            np3->child_ptr[j - 3] = x->child_ptr[j];
            np3->n++;
            x->data[j].key = "";
            x->data[j].meaning = "";
            //x->data[j] = NULL;
            x->n--;
        }

        for(j = 0; j < 6; j++)
        {
            x->child_ptr[j] = NULL;
        }

        /*np1->data[0].key = mid;
        np1->data[0].meaning = mmid;*/
        np1->data[0] = mid;
        np1->child_ptr[np1->n] = x;
        np1->child_ptr[np1->n + 1] = np3;
        np1->n++;
        root = np1;

    }

    else
    {
        y = x->child_ptr[i];
        /*mid = y->data[2].key;
        mmid = x->data[2].meaning;*/
        mid = y->data[2];
        y->data[2].key = "";
        y->data[2].meaning = "";
        //y->data[2] = NULL;
        y->n--;
        for (j = 3; j < 5; j++)
        {
            np3->data[j - 3] = y->data[j];
            np3->n++;
            y->data[j].key = "";
            y->data[j].meaning = "";
            //y->data[j] = NULL;
            y->n--;
        }

        x->child_ptr[i] = y;
        x->child_ptr[i + 1] = np3;
    }

    return mid;
}

void insert(string s,string s1)
{
    int i;
    //string temp;
    dicNode temp;

    x = root;

    if(x==NULL)
    {
        root = init();
        x = root;
    }

    else
    {
        if(x->isLeaf && x->n==5)
        {
            temp = split(x,-1);
            x = root;

            for(i =0;i<x->n;i++)
            {
                if(s > x->data[i].key && s < x->data[i+1].key)
                {
                    i++;
                    break;
                }

                else if(s < x->data[0].key)
                {
                    break;
                }

                else
                {
                    continue;
                }
            }

            x = x->child_ptr[i];

        }

        else
        {
            while(!x->isLeaf)
            {
                for(i=0;i<x->n;i++)
                {
                    if(s > x->data[i].key && s< x->data[i+1].key)
                    {
                        i++;
                        break;
                    }

                    else if(s < x->data[0].key)
                    {
                        break;
                    }

                    else
                    {
                        continue;
                    }

                }

                if((x->child_ptr[i]->n)==5)
                {
                    temp = split(x,i);
                    //x->data[x->n].key = temp;
                    x->data[x->n] = temp;
                    x->n++;
                    continue;
                }

                else
                {
                    x = x->child_ptr[i];
                }
            }
        }
    }

    x->data[x->n].key = s;
    x->data[x->n].meaning = s1;
    sort(x->data, x->n);
    x->n++;
}

int main()
{
    int n;
    string s,s1,temp,k;
    bool chk = false;

    cin >> n;
    getline(cin,s);

    for(int i=0;i<n;i++)
    {
        getline(cin,temp);
        //cin >> temp;
        chk = false;
        s = "";
        s1 = "";

        for(int j=0;j<temp.length();j++)
        {
            if(temp[j]=='|' && s=="")
            {
                continue;
            }

            else if(temp[j]=='|' && s1=="" && s!="")
            {
                chk = true;
                continue;
            }

            if(!chk)
            {
                s+=temp[j];
            }

            else
            {
                s1+=temp[j];
            }

        }

        //cout << "Inserting " << s << "--" << s1 << endl;

        insert(s,s1);
    }

    //cout << "Traversal:" << endl;
    //traverse(root);

    while(true)
    {
        cin >> k;
        if(k=="q")break;
        search(k);
    }
}

/* Input:
4
who are you I

9
w e t h i j k l m
*/


