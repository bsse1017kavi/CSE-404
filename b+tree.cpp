#include<iostream>
#include<utility>
using namespace std;

struct bplusNode
{
    string *data;
    bplusNode **child_ptr;
    bool isLeaf;
    int n;
};

bplusNode *x,*root;

bplusNode *init()
{
    bplusNode *np;
    np = new bplusNode;
    np->data = new string[5];
    np->child_ptr = new bplusNode*[6];
    np->isLeaf = true;
    np->n = 0;

    for(int i=0;i<6;i++)
    {
        np->child_ptr[i] = NULL;
    }

    return np;
}

void sort(string *p,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<=n;j++)
        {
            if(p[i]>p[j])
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

        cout << b->data[i] << " ";
    }

    if(!b->isLeaf)
    {
        traverse(b->child_ptr[i]);
    }

    cout << endl;

}

string split(bplusNode *x,int i)
{
    int j;
    string mid;

    bplusNode *np1,*np3,*y;

    np3 = init();

    if(i==-1)
    {
        mid = x->data[2];
        x->data[2]="";
        x->n--;

        np1 = init();
        np1->isLeaf = false;
        x ->isLeaf = true;

        for (j = 3; j < 5; j++)
        {
            np3->data[j - 3] = x->data[j];
            np3->child_ptr[j - 3] = x->child_ptr[j];
            np3->n++;
            x->data[j] = "";
            x->n--;
        }

        for(j = 0; j < 6; j++)
        {
            x->child_ptr[j] = NULL;
        }

        np1->data[0] = mid;
        np1->child_ptr[np1->n] = x;
        np1->child_ptr[np1->n + 1] = np3;
        np1->n++;
        root = np1;

    }

    else
    {
        y = x->child_ptr[i];
        mid = y->data[2];
        y->data[2] = "";
        y->n--;
        for (j = 3; j < 5; j++)
        {
            np3->data[j - 3] = y->data[j];
            np3->n++;
            y->data[j] = "";
            y->n--;
        }

        x->child_ptr[i] = y;
        x->child_ptr[i + 1] = np3;
    }

    return mid;
}

void insert(string s)
{
    int i;
    string temp;

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
                if(s > x->data[i] && s < x->data[i+1])
                {
                    i++;
                    break;
                }

                else if(s < x->data[0])
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
                    if(s > x->data[i] && s< x->data[i+1])
                    {
                        i++;
                        break;
                    }

                    else if(s < x->data[0])
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

    x->data[x->n] = s;
    sort(x->data, x->n);
    x->n++;
}

int main()
{
    int n;
    string s;

    cin >> n;

    for(int i=0;i<n;i++)
    {
        cin >> s;
        insert(s);
    }

    cout << "Traversal:" << endl;
    traverse(root);
}

/* Input:
4
who are you I

9
w e t h i j k l m
*/

