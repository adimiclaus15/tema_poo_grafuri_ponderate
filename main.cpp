#include <iostream>
#include <algorithm>
#include <fstream>
#define INF 999999
using namespace std;
ifstream f("date.in");
ofstream g("date.out");
class Nod
{
    int nod,cost;
    Nod *urm;
public:
    Nod()
    {
        this->nod=0;
        this->cost=0;
        this->urm=NULL;
    }
    Nod(int nod,int cost)
    {
        this->nod=nod;
        this->cost=cost;
        this->urm=NULL;
    }
    Nod* Next()
    {
        return urm;
    }
    void SetNext(Nod *p)
    {
        this->urm=p;
    }
    int GetNod()
    {
        return nod;
    }
    int GetCost()
    {
        return cost;
    }
};
class Lista
{
    Nod *prim;
public:
    Lista()
    {
        prim=NULL;
    }
    Nod* GetPrim()
    {
        return prim;
    }
    void add(int nod,int cost)
    {
        Nod *p=new Nod(nod,cost);
        p->SetNext(prim);
        prim=p;
    }
};
class Muchie
{
    int x,y,cost;
public:
    Muchie()
    {
        this->x=0;
        this->y=0;
        this->cost=0;
    }
    Muchie(int x,int y,int cost)
    {
        this->x=x;
        this->y=y;
        this->cost=cost;
    }
    int GetX()
    {
        return x;
    }
    int GetY()
    {
        return y;
    }
    int GetCost()
    {
        return cost;
    }
    bool operator < (const Muchie &muchie) const
    {
        if(cost<muchie.cost)
        {
            return 1;
        }
        return 0;
    }
    bool operator == (const Muchie &muchie) const
    {
        if(x==muchie.x && y==muchie.y)
        {
            return 1;
        }
        if(x==muchie.y && y==muchie.x)
        {
            return 1;
        }
        return 0;
    }
    Muchie& operator = (const Muchie &muchie)
    {
        x=muchie.x;
        y=muchie.y;
        cost=muchie.cost;
        return *this;
    }
    bool operator != (const Muchie &muchie) const
    {
        if(*this==muchie)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    bool operator > (const Muchie &muchie) const
    {
        if(cost>muchie.cost)
        {
            return 1;
        }
        return 0;
    }
};
class Graf
{
    int V,E,nr_comp_conexe,nr_muchii_apm;
    Lista *lista;
    Muchie *muchii;
    Lista *comp_conexe;
    Muchie *muchii_apm;
    int *viz;
public:
    Graf()
    {
        this->V=0;
        this->E=0;
        this->nr_muchii_apm=0;
        this->nr_comp_conexe=0;
        this->lista=NULL;
        this->muchii=NULL;
        this->comp_conexe=NULL;
        this->viz=NULL;
    }
     //Constructor Copiere
    Graf(Graf &graf)
    {
        this->V=graf.V;
        this->E=graf.E;
        this->nr_muchii_apm=graf.nr_muchii_apm;
        this->nr_comp_conexe=graf.nr_comp_conexe;
        this->lista=new Lista[this->V+1];
        this->viz=new int[this->V+1];
        this->comp_conexe=new Lista[this->V+1];
        this->muchii_apm=new Muchie[this->E+1];
        this->muchii=new Muchie[this->E+1];
       // this->muchii=new Muchie(0,0,0);

        for(int i=1;i<=graf.E;i++)
        {
            this->muchii[i]=graf.muchii[i];
            this->Adauga_Muchie(graf.muchii[i].GetX(),graf.muchii[i].GetY(),graf.muchii[i].GetCost());
            this->Adauga_Muchie(graf.muchii[i].GetY(),graf.muchii[i].GetX(),graf.muchii[i].GetCost());
           // cout<<p->GetX()<<" "<<p->GetY()<<" "<<p->GetCost()<<"\n";
        }
        for(int i=1;i<=graf.V;i++)
        {
            this->viz[i]=graf.viz[i];
        }
        for(int i=1;i<=graf.nr_comp_conexe;i++)
        {
            Nod *p=graf.comp_conexe[i].GetPrim();
            while(p!=NULL)
            {
                this->Adauga_componenta(i,p->GetNod(),0);
                p=p->Next();
            }
        }
        for(int i=1;i<=graf.nr_muchii_apm;i++)
        {
            this->muchii_apm[i]=graf.muchii_apm[i];
        }
    }
    //Constructor atribuire
    Graf &operator = ( const Graf &graf)
    {
        if(this!=&graf)
        {
            this->V=graf.V;
            this->E=graf.E;
            this->nr_muchii_apm=graf.nr_muchii_apm;
            this->nr_comp_conexe=graf.nr_comp_conexe;
            this->lista=new Lista[this->V+1];
            this->viz=new int[this->V+1];
            this->comp_conexe=new Lista[this->V+1];
            this->muchii_apm=new Muchie[this->E+1];
            this->muchii=new Muchie[this->E+1];
       // this->muchii=new Muchie(0,0,0);

            for(int i=1;i<=graf.E;i++)
            {
                this->muchii[i]=graf.muchii[i];
                this->Adauga_Muchie(graf.muchii[i].GetX(),graf.muchii[i].GetY(),graf.muchii[i].GetCost());
                this->Adauga_Muchie(graf.muchii[i].GetY(),graf.muchii[i].GetX(),graf.muchii[i].GetCost());
           // cout<<p->GetX()<<" "<<p->GetY()<<" "<<p->GetCost()<<"\n";
            }
            for(int i=1;i<=graf.V;i++)
            {
                this->viz[i]=graf.viz[i];
            }
            for(int i=1;i<=graf.nr_comp_conexe;i++)
            {
                Nod *p=graf.comp_conexe[i].GetPrim();
                while(p!=NULL)
                {
                    this->Adauga_componenta(i,p->GetNod(),0);
                    p=p->Next();
                }
            }
            for(int i=1;i<=graf.nr_muchii_apm;i++)
            {
                this->muchii_apm[i]=graf.muchii_apm[i];
            }
        }
        return *this;

    }
    ~Graf()
    {
        for(int i=1;i<=V;i++)
        {
            Nod *p=lista[i].GetPrim();
            while(p!=NULL)
            {
                Nod *q;
                q=p->Next();
                delete p;
                p=q;
            }
        }
        V=0;
        for(int i=1;i<=nr_comp_conexe;i++)
        {
            Nod *p=comp_conexe[i].GetPrim();
            while(p!=NULL)
            {
                Nod *q;
                q=p->Next();
                delete p;
                p=q;
            }
        }
        nr_comp_conexe=0;
        delete[] viz;
        delete[] muchii;
        E=0;
    }
    void Adauga_Muchie(int x,int y,int cost)
    {
        lista[x].add(y,cost);
    }
    void Adauga_componenta(int x,int y,int cost)
    {
        comp_conexe[x].add(y,cost);
    }
    int GetV()
    {
        return V;
    }
    int GetE()
    {
        return E;
    }
    int GetNr_Comp_Conexe()
    {
        return nr_comp_conexe;
    }
    int GetNr_Muchii_APM()
    {
        return nr_muchii_apm;
    }
    int** MatricePonderi();
    int* DrumMinim(int,int);
    Lista* ComponenteConexe();
    void DFS(int,int);
    void Conex();
    Muchie* APM(int);
    friend Graf operator *(Graf,Graf);
    friend ifstream & operator>>(ifstream &,Graf &);
    friend ofstream & operator<<(ofstream &,Graf &);
};
ifstream & operator>>(ifstream &in,Graf &graf)
{
    int i,V,E,x,y,cost;
    in>>V>>E;
    graf.V=V;
    graf.E=E;
    graf.lista=new Lista[V+1];
    graf.comp_conexe=new Lista[V+1];
    graf.viz=new int[V+1];
    graf.muchii=new Muchie[E+1];
    graf.muchii_apm=new Muchie[E+1];
    for(i=1;i<=graf.E;i++)
    {
        in>>x>>y>>cost;
        graf.muchii[i]=Muchie(x,y,cost);
        graf.Adauga_Muchie(x,y,cost);
        graf.Adauga_Muchie(y,x,cost);
    }
    return in;
}
ofstream & operator<<(ofstream &out,Graf &graf)
{
    out<<graf.V<<" "<<graf.E<<"\n";
    for(int i=1;i<=graf.E;i++)
    {
        g<<graf.muchii[i].GetX()<<" "<<graf.muchii[i].GetY()<<" "<<graf.muchii[i].GetCost()<<"\n";
    }
    return out;
}
Graf operator * (Graf graf1,Graf graf2)
{
    Muchie *v;
    v=new Muchie[graf1.E+1];
    int i,j,nr=0;
    for(i=1;i<=graf1.E;i++)
    {
        for(j=1;j<=graf2.E;j++)
        {
            if(graf1.muchii[i]==graf2.muchii[j])
            {
                nr++;
                if(graf1.muchii[i]<graf2.muchii[j])
                {
                    v[nr]=graf1.muchii[i];
                }
                else
                {
                    v[nr]=graf2.muchii[j];
                }
            }
        }
    }
    graf1.~Graf();
    graf1.V=graf2.V;
    graf1.E=nr;
    graf1.lista=new Lista[graf1.V+1];
    graf1.comp_conexe=new Lista[graf1.V+1];
    graf1.viz=new int[graf1.V+1];
    graf1.muchii=new Muchie[graf1.E+1];
    graf1.muchii_apm=new Muchie[graf1.E+1];
    for(i=1;i<=graf1.E;i++)
    {
        graf1.muchii[i]=v[i];
        graf1.Adauga_Muchie(v[i].GetX(),v[i].GetY(),v[i].GetCost());
        graf1.Adauga_Muchie(v[i].GetY(),v[i].GetX(),v[i].GetCost());
    }
    return graf1;

}
 int** Graf::MatricePonderi()
{
    int **a;
    int i,j,k;
    a=new int*[V+1];
    for(i=1;i<=V;i++)
    {
        a[i]=new int[V+1];
    }
    for(i=1;i<=V;i++)
    {
        for(j=1;j<=V;j++)
        {
            a[i][j]=INF;
        }
    }
    for(i=1;i<=E;i++)
    {
        a[muchii[i].GetX()][muchii[i].GetY()]=a[muchii[i].GetY()][muchii[i].GetX()]=muchii[i].GetCost();
    }
    for(i=1;i<=V;i++)
    {
        a[i][i]=0;
    }
    for(k=1;k<=V;k++)
    {
        for(i=1;i<=V;i++)
        {
            for(j=1;j<=V;j++)
            {
                a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
            }
        }
    }
    g<<"Matricea ponderilor : "<<"\n";
    for(i=1;i<=V;i++)
    {
        for(j=1;j<=V;j++)
        {
            g<<a[i][j]<<" ";
        }
        g<<"\n";
    }
    return a;
}
int* Graf::DrumMinim(int x,int y)
{
    int i,j,*viz,*d,*t,vfmin,minim,*drum,nr,q;
    viz=new int[V+1];
    d=new int[V+1];
    t=new int[V+1];
    drum=new int[V+1];
    for(i=1;i<=V;i++)
    {
        d[i]=INF;
        viz[i]=0;
        t[i]=0;
    }
    viz[x]=1;
    d[x]=0;
    Nod *p=lista[x].GetPrim();
    while(p!=NULL)
    {
        d[p->GetNod()]=p->GetCost();
        t[p->GetNod()]=x;
        p=p->Next();
    }
    for(j=1;j<=V;j++)
    {
        minim=INF;
        vfmin=0;
        for(i=1;i<=V;i++)
        {
            if(viz[i]==0 && d[i]<minim)
            {
                minim=d[i];
                vfmin=i;
            }
        }
        viz[vfmin]=1;
        Nod *p=lista[vfmin].GetPrim();
        while(p!=NULL)
        {
            if(viz[p->GetNod()]==0 && d[p->GetNod()]>minim+p->GetCost())
            {
                d[p->GetNod()]=minim+p->GetCost();
                t[p->GetNod()]=vfmin;
            }
            p=p->Next();
        }
    }
    nr=0;
    q=y;
    while(q!=0)
    {
        nr++;
        drum[nr]=q;
        q=t[q];
    }
    drum[0]=nr;
    if(nr==1)
    {
        g<<"Nu exista drum intre "<<x<<" si "<<y<<"\n";
    }
    else
    {
        g<<"Drumul de cost minim dintre "<<x<<" "<<y<<" : \n";
        for(i=1;i<=nr;i++)
        {
            g<<drum[i]<<" ";
        }
        g<<"\n";
    }
    return drum;
}
void Graf::DFS(int x,int nrc)
{
    viz[x]=nrc;
    Adauga_componenta(nrc,x,0);
    Nod *p=lista[x].GetPrim();
    while(p!=NULL)
    {
        if(viz[p->GetNod()]==0)
        {
            DFS(p->GetNod(),nrc);
        }
        p=p->Next();
    }

}
Lista* Graf::ComponenteConexe()
{
    int i;
    for(i=1;i<=V;i++)
    {
        viz[i]=0;
    }
    nr_comp_conexe=0;
    for(i=1;i<=V;i++)
    {
        if(viz[i]==0)
        {
            nr_comp_conexe++;
            DFS(i,nr_comp_conexe);
        }
    }
    g<<"Componentele conexe "<<"\n";
    for(i=1;i<=nr_comp_conexe;i++)
    {
        g<<i<<" : "<<" ";
        Nod *p=comp_conexe[i].GetPrim();
        while(p!=NULL)
        {
            g<<p->GetNod()<<" ";
            p=p->Next();
        }
        g<<"\n";
    }
    return comp_conexe;
}
void Graf::Conex()
{
    if(nr_comp_conexe!=1)
    {
        g<<"Graful nu este conex";
    }
    else
    {
        g<<"Graful este conex";
    }
    g<<"\n";
}
Muchie* Graf::APM(int x)
{
    int *comp,i,j,minim,maxim;
    Muchie aux;
    muchii_apm=new Muchie[E+1];
    comp=new int[V+1];
    for(i=1;i<=V;i++)
    {
        comp[i]=i;
    }
    //sort(muchii+1,muchii+E+1);
    for(i=1;i<=E;i++)
    {
        for(j=i+1;j<=E;j++)
        {
            if(muchii[i]>muchii[j])
            {
                aux=muchii[i];
                muchii[i]=muchii[j];
                muchii[j]=aux;
            }
        }
    }
    nr_muchii_apm=0;
    for(i=1;i<=E;i++)
    {
        if(viz[muchii[i].GetX()]==viz[x] && viz[muchii[i].GetY()]==viz[x])
        {
            if(comp[muchii[i].GetX()]!=comp[muchii[i].GetY()])
            {
                nr_muchii_apm++;
                muchii_apm[nr_muchii_apm]=Muchie(muchii[i].GetX(),muchii[i].GetY(),muchii[i].GetCost());
                minim=min(comp[muchii[i].GetX()],comp[muchii[i].GetY()]);
                maxim=max(comp[muchii[i].GetX()],comp[muchii[i].GetY()]);
                for(j=1;j<=V;j++)
                {
                    if(comp[j]==maxim)
                    {
                        comp[j]=minim;
                    }
                }
            }
        }
    }
    g<<"Muchii APM :"<<"\n";
    for(i=1;i<=nr_muchii_apm;i++)
    {
        g<<muchii_apm[i].GetX()<<" "<<muchii_apm[i].GetY()<<" "<<muchii_apm[i].GetCost()<<"\n";
    }
    return muchii_apm;

}
int main()
{
    Graf a,b,c;
    f>>a>>b;
    g<<a;
    a.ComponenteConexe();
    a.APM(2);
    a.DrumMinim(8,3);
    a.MatricePonderi();
    a.Conex();
    c=(a*b);
    g<<c;
    g<<b;
    b.ComponenteConexe();
    b.APM(2);
    b.DrumMinim(8,3);
    b.MatricePonderi();
    b.Conex();
    return 0;
}
