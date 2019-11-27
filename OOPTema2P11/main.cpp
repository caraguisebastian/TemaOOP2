#include <iostream>
#include <string.h>
#include <queue>


using namespace std;

class node
{
    int info,kids;
    node *father,*children;
public:
    friend ostream& operator<<(ostream& out, node& f)
    {
        out<<"Nodul curent are campul info = "<<f.info<<endl;
        try
        {
            if(f.father!=NULL) throw 1;
            else throw 'r';
        }
        catch(int a){ cout<<"Tatal acestui nod este "<<f.father->info<<endl;}
        catch(char a){cout<<"Acest nod este radacina! "<<endl;}

        try
        {
            throw f.kids;
        }
        catch(int a)
        {
        if(a>0)
            {
                out<<"Acest nod are "<<f.kids<<" copii iar acestia sunt: "<<endl;
                for(int i=0;i<f.kids;i++)
                {
                    out<<"Copilul "<<i<<" are valoare info = "<<f.children[i].info<<endl;
                }
                cout<<endl;
                return out;
            }
            else {cout<<endl; return out;}
        }
    }

    friend istream& operator>>(istream& input, node& f)
    {
        cout<<"Ce info sa aiba acest nod? ";
        input>>f.info;
        cout<<endl<<"Cati copii are acest nod? ";
        input>>f.kids;
        int ok=0;
        while(ok==0)
        {
            try
            {
               if(f.kids>=0) throw f.kids;
               else throw -1;
            }
            catch(int a)
            {
                if(a>=0) ok=1;
                else {
                        cout<<"Numarul de copii nu poate sa fie negativ! "<<endl;
                        cout<<endl<<"Cati copii are acest nod? ";
                        input>>f.kids;
                    }
            }
        }

        f.children=new node [f.kids];
        for(int i=0;i<f.kids;i++)
            {
                cout<<"Ce valoare are copilul "<<i<<" ? ";
                input>>f.children[i].info;
                f.children[i].father = new node;
                f.children[i].father = &f;
            }
        cout<<endl;
        return input;
    }

    node(int x=6)
    {
        info=x;
        kids=0;
        father=NULL;
        children=NULL;
    }

    ~node()
    {
        info=0;
        kids=0;
        delete [] children;
    }

    node(node &a)
    {
        info=a.info;
        kids=a.kids;
        father = new node;
        father=a.father;
        children = new node[kids];
        for(int i=0;i<kids;i++)
            children[i]=a.children[i];
    }

    node& operator=(const node& a);
    void set_children(int k)
    {
        children=new node[k];
    }

    int get_info(){return info;};
    friend class arbore_oarecare;
    friend class arbore;
    friend class arbore_binar;
    void transform_father(node* (&p)){if(p->father!=NULL) p=p->father; else cout<<"Acest nod este radacina! "<<endl;};
    void transform_children(node* (&p),int i){if(i<p->kids) p=p->children+i;else cout<<"Acest copil nu exista! "<<endl;};

};

node& node::operator=(const node& a)
{
    info=a.info;
    kids=a.kids;
    father=new node;
    father=a.father;
    if(kids!=0)
    {
        children=new node [kids];
        for(int i=0;i<kids;i++)
        {
            children[i]=a.children[i];
        }
    }
    return *this;
}





class arbore
{
    int nr_nodes;
public:
    virtual void show(int a,node* (&p))=0;
    void nodesSum(node* (&p),int &nr)
    {
        nr++;
        for(int i=0;i<p->kids;i++)
        {
            node *aux=p->children+i;
            nodesSum(aux,nr);
        }
    };
    arbore(int a=1){nr_nodes=a;};
    int set_i(int i){nr_nodes=i;};
    int get_i(){return nr_nodes;};
    arbore(arbore &a){nr_nodes=a.nr_nodes;};
    ~arbore(){nr_nodes=0;};
    arbore& operator=(const arbore& a);

};

arbore& arbore::operator=(const arbore& a)
{
    nr_nodes=a.nr_nodes;
    return *this;
}





class arbore_oarecare: public arbore
{
    protected: node *root;

public:

    arbore_oarecare(int x=2,int y=1): arbore(y)
    {
        root=new node(x);
    }

    virtual ~arbore_oarecare()
    {
        delete root;
    }

    arbore_oarecare(arbore_oarecare &a): arbore(a)
    {
        root=new node;
        root=a.root;
    }

     arbore_oarecare& operator=(const arbore_oarecare& a);
     friend istream& operator>>(istream& input, arbore_oarecare& f)
     {
         f.root = new node;
         cout<<"Cate noduri are acest arbore? ";
         int x,ok=1;
         input>>x;
         while(ok==1)
         {
             try
             {
                 throw x;
             }
             catch(int x)
             {
                 if(x>0) {f.set_i(x);ok=0;}
                 else
                 {
                     cout<<"Numarul de noduri trebuie sa fie > 0! "<<endl;
                     cout<<"Cate noduri are acest arbore? ";
                     input>>x;
                 }
             }
         }

         input>>f.root[0];
         node *p;
         p=f.root;
         ok=1;
         while(ok==1)
         {
            cout<<"Va aflati pe nodul cu info "<<p->get_info()<<endl;
            cout<<"Alegeti comanda: "<<endl;
            cout<<"1 - Mergeti catre un fiu sau tatal nodului curent"<<endl<<"2 - Modificati nodul curent(info + children)"<<endl<<"3 - Afiasti copiii nodului curent si tatal"<<endl<<"4 - Iesire"<<endl;
            int command;
            input>>command;
            switch (command)
            {
            case 1:
                {
                    cout<<"1 -> fiu     2 -> tata ";
                    int e;
                    input>>e;
                    if(e==2)
                    {
                    p->transform_father(p);
                    }
                    else if(e==1)
                    {
                        cout<<"Catre al catelea fiu doriti sa mergerti? ";
                        int i;
                        input>>i;
                        p->transform_children(p,i);
                    }
                    else cout<<"Comannda nu exista! "<<endl;
                    break;
                }
            case 2:
                {
                    input>>p[0];
                    break;
                }
            case 3:
                {
                    cout<<p[0];
                    break;
                }
            case 4:
                {
                    ok=0;
                    break;
                }
            default:
                {
                    cout<<"Comanda nu exista! "<<endl;
                    break;
                }
            }
         }

         int nr=0;
         f.nodesSum(f.root,nr);
         f.arbore::set_i(nr); //f.set_i(nr);
         return input;
     }

    void show(int a,node* (&p))
    {
        if(a==1)
            {
                cout<<*p<<endl;
                for(int i=0;i<p->kids;i++)
                {
                    node *aux=p->children+i;
                    show(1,aux);
                }
            }
        else if(a==2)
        {
            queue <node*> coada;
            coada.push(root);
            node *aux;
            while (!coada.empty())
            {
                aux=coada.front();
                cout<<*aux;
                for(int i=0;i<aux->kids;i++)
                    coada.push(&aux->children[i]);
                coada.pop();
            }
        }
    }
    friend ostream& operator<<(ostream& out, arbore_oarecare& f)
    {
        cout<<"HF: "<<endl;
        f.show(1,f.root);
        cout<<"BF: "<<endl;
        f.show(2,f.root);

        return out;
    }
};

arbore_oarecare& arbore_oarecare::operator=(const arbore_oarecare& a)
{
    this->arbore::operator=(a);
    root=new node;
    root=a.root;
    return *this;
}




class arbore_binar: public arbore_oarecare
{
public:

    arbore_binar(int a=1,int b=1): arbore_oarecare(a,b) {};
    ~arbore_binar(){};
    arbore_binar(arbore_binar &a): arbore_oarecare(a) {};
    void make(node * (&p))
    {
        if(p->kids>2)
        {
            for(int i=p->kids-1;i>=2;i--)
            {
                delete (p->children+i);
            }
            p->kids=2;
            for(int i=0;i<p->kids;i++)
            {
                node* aux=p->children+i;
                make(aux);
            }
        }
        else
         for(int i=0;i<p->kids;i++)
            {
                node* aux=p->children+i;
                make(aux);
            }
    }

    friend istream& operator>>(istream& input, arbore_binar& f)
    {
        cout<<"Atentei! Fiecare nod va avea maxim 2 fii! Daca se insereaza mai multi, acestia vor fi stersi dupa iesirea din meniu! "<<endl;
        input>>(arbore_oarecare&)f;
        f.make(f.root);
        cout<<"Numarul de copii al fiecarui nod a fost redus (daca este cazul) la 2 pentru a se crea arborelele binar!"<<endl<<endl ;
        return input;
    }

    void show(int a, node* (&p))
    {
        if(a==1)//RSD
        {
            cout<<p->info<<" ";
            for(int i=0;i<p->kids;i++)
            {
                node *aux=p->children+i;
                show(1,aux);
            }
        }
        if(a==2) //SRD
        {
            if(p->kids>=1)
            {
                node *aux=p->children;
                show(2,aux);
            }
            cout<<p->info<<" ";
            if(p->kids>=2)
                {
                node *aux=p->children+1;
                show(2,aux);
            }
        }
        if(a==3) //SDR
        {
            if(p->kids>=1)
            {
                node *aux=p->children;
                show(3,aux);
            }
            if(p->kids>=2)
                {
                node *aux=p->children+1;
                show(3,aux);
            }
            cout<<p->info<<" ";
        }
    }


    friend ostream& operator<<(ostream& out, arbore_binar& f)
    {
        out<<" RSD: "<<endl;
        f.show(1,f.root);
        out<<endl;
        out<<" SRD: "<<endl;
        f.show(2,f.root);
        out<<endl;
        out<<" SDR: "<<endl;
        f.show(3,f.root);
        out<<endl;

        return out;
    }

    arbore_binar& operator=(const arbore_binar& a);

};

arbore_binar& arbore_binar::operator=(const arbore_binar& a)
{
    this->arbore_oarecare::operator=(a);
    return *this;
}


class n_objects
{
    int dim;
    arbore_oarecare *tree_any;
    arbore_binar *tree_binary;
public:
    n_objects(int x=1)
    {
        dim=x;
        tree_any=new arbore_oarecare [x];
        tree_binary=new arbore_binar [x];
    }
    ~n_objects(){dim=0; delete [] tree_any; delete [] tree_binary;}
    n_objects(n_objects& a)
    {
        dim=a.dim;
        tree_any=new arbore_oarecare[a.dim];
        for(int i=0;i<a.dim;i++)
            tree_any[i]=a.tree_any[i];
        tree_binary=new arbore_binar[a.dim];
        for(int i=0;i<a.dim;i++)
            tree_binary[i]=a.tree_binary[i];
    }
    n_objects& operator=(const n_objects& a);
    friend ostream& operator<<(ostream& out, n_objects& f)
    {
        out<<"Ce tip de arbore afisati? "<<endl;
        char s[20];
        cin>>s;
        out<<endl;
        if(strstr(s,"binar"))
           for(int i=0;i<f.dim;i++)
            out<<f.tree_binary[i];
        else
            for(int i=0;i<f.dim;i++)
             out<<f.tree_any[i];
        out<<endl;
        return out;
    }
    friend istream& operator>>(istream& input, n_objects& f)
    {
        cout<<"Cati arbori doriti sa afisati? "<<endl;
        int x;
        input>>x;
        cout<<endl<<"Ce fel de arbore doriti? "<<endl;
        char s[20];
        input>>s;
        cout<<endl;
        for(int j=0;j<x;j++)
        {
                if(strstr(s,"oarecare"))
            {
                f.tree_any=new arbore_oarecare [x];
                for(int i=0;i<f.dim;i++)
                    input>>f.tree_any[i];
            }
            else
                {
                f.tree_binary=new arbore_binar [x];
                for(int i=0;i<f.dim;i++)
                    input>>f.tree_binary[i];
        }
        }
        return input;
    }

};

n_objects& n_objects::operator=(const n_objects& a)
{
    dim=a.dim;
    tree_any=new arbore_oarecare [a.dim];
    for(int i=0;i<a.dim;i++)
        tree_any[i]=a.tree_any[i];
    tree_binary=new arbore_binar [a.dim];
    for(int i=0;i<a.dim;i++)
        tree_binary[i]=a.tree_binary[i];
    return *this;
}

int main()
{
    n_objects P;
    cin>>P;
    cout<<P;

    return 0;
}
