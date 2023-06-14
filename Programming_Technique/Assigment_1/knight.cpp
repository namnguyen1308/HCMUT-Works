#include "knight.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}


bool arthur=false;
bool lancelot=false;

void event0(int & rescue)
{
    rescue=1;
}

const int baseDamageMons[5]={10,15,45,75,95};


void event1_5(int & HP, int & level, int evt, char monster)
{   
  
    int x = evt%10;
    int levelOp=evt>6?(x>5?x:5):x;

    if(level>levelOp || arthur || lancelot) level++;
    else if(level<levelOp) 
    {
        x=monster-'1';
        HP-=baseDamageMons[x]*levelOp;
    }
 
}

void event6(int & HP, int & level, int evt, int & tihon)
{   
   
    int x = evt%10;
    int levelOp=evt>6?(x>5?x:5):x;

    
    if(level>levelOp || arthur || lancelot) level+=2;
    else if(level<levelOp) tihon=3;
    
}

void event7(int & HP, int & level, int evt, int & ech)
{
    
    int x = evt%10;
    int levelOp=evt>6?(x>5?x:5):x;

   
    if(level>levelOp || arthur || lancelot) level+=2;
    else if(level<levelOp) ech=3;
  
}

bool isPrime[1000];
void findPrime()
{
    for(int i=0;i<1000;i++) isPrime[i]=true;
    isPrime[0]=false; isPrime[1]=false;

    for(int i=2;i*i<1000;i++)
    {   
        if(isPrime[i])
            for(int j=i*i;j<1000;j+=i) isPrime[j]=false;
    }
}

void event11(int & HP, int & level, int & phoenixdown, int & maxHP)
{
    //tinh n1
    int n=((level+phoenixdown)%5+1)*3;
    int k=99, sum=0;
    //tinh s1
    for(int i=0;i<n;i++)
    {
        sum+=k;
        k-=2;
    }

    HP+=sum%100+1;
    HP++;
    while(HP < maxHP && !isPrime[HP]) HP++;
}

int isFib[17];
void Fib()
{
    isFib[0]=0;
    isFib[1]=1;
    int x=1,y=1,k=2;
    for(int i=2;i<17;i++) isFib[i]=isFib[i-1]+isFib[i-2];
}

void event12(int & HP)
{
    HP=max(1,HP-1);
    for(int i=16;i>-1;i--) 
    {
        if(HP>isFib[i])
        {
            HP=isFib[i];
            break;
        }
    }
}

int gm[8];
void ghostmush(string dgeon)
{
    //read file
    ifstream fmr(dgeon);
    int n;
    fmr>>n;
    string s;
    getline(fmr,s);
    getline(fmr,s);
    int a[n],k=0;
    int sum=0,nho=1;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]==',') 
        {
            a[k]=sum*nho;
            nho=1;
            sum=0;
            k++;
        }
        else 
        {
            if(s[i]=='-') nho=-1;
            else sum=sum*10+(s[i]-'0');
        }
    }
    a[k]=sum; 
 
    int mx=a[0], mn=a[0],mxi=0,mni=0;


    for(int j=1;j<n;j++)
    {
        if(a[j]>=mx)
        {
            mx=a[j];
            mxi=j;
        }
        if(a[j]<=mn)
        {
            mn=a[j];
            mni=j;
        }
    }
    gm[0]=mxi; gm[1]=mni;
    //////

    // kiem tra day nui cho nam so 2
    bool isMoun=true, isHighest=false;
    int mtx=-1,mti=-1;

    for(int i=0;i<n-1;i++)
    {
        //khong tang ngat hoac giam ngat
        if(a[i]==a[i+1]) 
        {
            isMoun=false;
            break;
        } 
        // tim thay dinh nui dau tien
        else if(a[i]>a[i+1] && !isHighest)
        {
            mtx=a[i];
            mti=i;
            isHighest=true;
        }
        // tim thay dinh nui khac
        else if(a[i]<a[i+1] && isHighest) 
        {
            isMoun=false;
            break;
        }
    }

    if(!isMoun)
    {   
        mtx=-2;
        mti=-3;
    }
    else if(!isHighest)
    {
        mtx=a[n-1];
        mti=n-1;
    }

    gm[2]=mtx; gm[3]=mti;
    //nam 3

    int b[n];
    int mxi2=0,mni2=0;
    mn=INT32_MAX; mx=0;

    for(int i=0;i<n;i++)
    {
        b[i]=a[i];
        
        if(b[i]<0) b[i]*=-1;
        b[i]=(17*b[i]+9)%257;

        if(b[i]>mx)
        {
            mx=b[i];
            mxi2=i;
        }

        if(b[i]<mn)
        {
            mn=b[i];
            mni2=i;
        }
    }
    gm[4]=mxi2; gm[5]=mni2;
    //nam 4

    int mx2=mn, mx2i=0;
    mx=b[0];
    for(int i=1;i<min(3,n);i++) mx=max(mx,b[i]);
    for(int i=1;i<min(3,n);i++)
    {
        if(b[i]<mx && b[i]>mx2)
        {
            mx2=b[i];
            mx2i=i;
        }
    }
    if(mx2==mn)
    {
        mx2=-5;
        mx2i=-7;
    }
    gm[6]=mx2; gm[7]=mx2i;
    ////////////
}

void event13(string s, int & HP, int & maxHP, int & phoenixdown)
{
    /////////xu li HP sau khi gap cac loai nam///////
    for(int i=2;i<s.size();i++)
    {
        //gap nam ma so 1
        if(s[i]=='1') //thay doi HP
            HP-=(gm[0]+gm[1]);
        //nam so 2
        else if(s[i]=='2') //thay doi HP
            HP-=(gm[2]+gm[3]);
        //nam so 3
        else if(s[i]=='3') //thay doi HP
            HP -=(gm[4]+gm[5]); 
        //nam so 4
        else if(s[i]=='4') // thay doi HP
            HP-=(gm[6]+gm[7]);

        //cap nhap HP
        HP=min(HP,maxHP);
        
        if(HP<=0)
        {
            if(phoenixdown)
            {
                phoenixdown--;
                HP=maxHP; //Hoi sinh
            }
            else return;
        }
    }
}
void event15(int &remedy)
{
    remedy++;
}
void event16(int &maidenkiss)
{
    maidenkiss++;
}
void event17(int &phoenixdown)
{
    phoenixdown++;
}

void event18(int & HP, int & maxHP, string s)
{
    ifstream fml(s);
    int n;
    fml>>n; 
    string s2;
    getline(fml,s2);
    for(int j=0;j<n;j++)
    {
        getline(fml,s2);
        bool inchar[6];
        for(int i=0;i<6;i++) inchar[i]=true;
        
        for(int i=0;i<s2.size();i++)
        {
            if(s2[i]=='M' || s2[i]=='m') inchar[0] = false;
            else if(s2[i]=='E' || s2[i]=='e') inchar[1] = false;
            else if(s2[i]=='R' || s2[i]=='r') inchar[2] = false;
            else if(s2[i]=='L' || s2[i]=='l') inchar[3] = false;
            else if(s2[i]=='I' || s2[i]=='i') inchar[4] = false;
            else if(s2[i]=='N' || s2[i]=='n') inchar[5] = false;
        }

        bool ismerlin=true;
        for(int i=0;i<6;i++) 
            if(inchar[i]) 
            {
                ismerlin=false;
                break;
            }
        if(ismerlin)
        {
            HP+=2;
            string t="Merlin",t2="merlin";
            int x=0;
            for(int i=0;i<s2.size();i++)
            {
                if(s2[i]==t[x] || s2[i]==t2[x]) x++;
                else x=0;
                if(s2[i]==t[x] || s2[i]==t2[x]) x++;
                if(x==6)
                {
                    HP++;
                    break;
                }
            }
        }
    }
    HP=min(HP,maxHP);
    fml.close();
}

void event19(int & remedy, int & maidenkiss, int & phoenixdown, string heal)
{
    int r1,c1;
    ifstream fa(heal);
    fa>>r1>>c1;
    int a[r1][c1];
    for(int i=0;i<r1;i++)
    {
        int d=3;
        for(int j=0;j<c1;j++) 
        {
            fa>>a[i][j];
            if(a[i][j]==16 && d>0) 
            {
                remedy=min(remedy+1,99);
                d--;
            }
            else if(a[i][j]==17 && d>0) 
            {
                maidenkiss=min(maidenkiss+1,99);
                d--;
            }
            else if(a[i][j]==18 && d>0) 
            {
                phoenixdown=min(phoenixdown+1,99);
                d--;
            }
        }
    }
}


void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) 
{
   

    /////////////////READ////////////////
    ifstream fi(file_input);
    string event;

    //// doc thong so hiep si///////
    fi>>HP>>level>>remedy>>maidenkiss>>phoenixdown;

    //cac gioi han suc manh
    HP=min(HP,999);
    HP=max(HP,1);

    level=max(level,1);
    level=min(level,10);

    remedy=max(remedy,0);
    remedy=min(remedy,99);

    maidenkiss=max(maidenkiss,0);
    maidenkiss=min(maidenkiss,99);

    phoenixdown=max(phoenixdown,0);
    phoenixdown=min(phoenixdown,99);
    //////////////////
    getline(fi,event); // xuong hang

    //// doc cac su kien//////
    getline(fi,event);
    //// doc file ho tro su kien//////
    string filedungeon; getline(fi,filedungeon);
    //tach ten file 
    string dungeon[3]; 
    int numofdungeon = 0;
    bool first=false;
    for(int i=0;i<filedungeon.length();i++)
    {
        if(filedungeon[i]==',') 
        {
            numofdungeon++;
            continue;
        }
        dungeon[numofdungeon]+= filedungeon[i];
    }
    /////////////////////////////////////    

    //////////////SU KIEN/////////////
    int maxHP=HP;
    rescue=-1; 

    //cho su kien 6
    bool bitihon=false;
    int tihon=-1;

    //cho su kien 7
    bool biech=false;
    int beforelevel=1;
    int ech;

    //cho su kien 11
    findPrime();

    //kiem tra than phan
    if(HP==999) arthur=true;
    else if(isPrime[HP]) lancelot=true;
    
    //cho su kien 12
    Fib();

    //cho su kien 13
    if(dungeon[0]!="") ghostmush(dungeon[0]);
    
    //cho su kien 18
    bool merlin=true;

    //cho su kien 19
    bool asclepius=true;

    stringstream s2(event);
    string s;
    first=true;
    int numevt=1;
    while(s2>>s)
    {
        if(!first) display(HP,level,remedy,maidenkiss,phoenixdown,rescue);
        else first=false;
        /////////xu li su kien///////
        if(s.size()<2)
        {
            int z=s[0]-'0';
            //su kien 0
            if(s[0]=='0') 
            {
                event0(rescue);
                break;
            }
            // su kien quai 1-5
            else if(z>=1 && z<=5) event1_5(HP,level,numevt,s[0]);
            //su kien 6
            else if(s[0]=='6' && !bitihon && !biech) event6(HP,level,numevt,tihon);
            //su kien 7
            else if(s[0]=='7' && !bitihon && !biech) event7(HP,level,numevt,ech);
        }
        else 
        {
            if(s[0]=='9') //edited
            {
                if(arthur || (lancelot && level>=8) || level==10) level=10;
                else rescue=0;
            }
            else
            {
                //ma su kien 11
                if(s[1]=='1') event11(HP , level, phoenixdown, maxHP); 
                //ma su kien 12
                else if(s[1]=='2') event12(HP);
                //ma su kien 13
                else if(s[1]=='3') event13(s,HP,maxHP,phoenixdown);
                //ma su kien 15
                else if(s[1]=='5') remedy=min(remedy+1,99);
                //ma su kien 16
                else if(s[1]=='6') maidenkiss = min(maidenkiss+1,99);
                //ma su kien 17
                else if(s[1]=='7') phoenixdown =min(phoenixdown+1,99);
                //ma su kien 19
                else if(s[1]=='9' && asclepius) 
                {
                    asclepius=false;
                    if(dungeon[1]!="") 
                    event19(remedy,maidenkiss,phoenixdown,dungeon[1]);
                }
                //ma su kien 18
                else if(s[1]=='8' && merlin)
                {
                    merlin=false;
                    if(dungeon[2]!="") event18(HP,maxHP,dungeon[2]);
                }
            }
        }

        ////cap nhap lai HP va level sau su kien nho////
        
        //cap nhap level
        level=min(level,10);

        //trang thai ti hon
        // bien thanh ti hon
        if(tihon==3 && !bitihon)
        {
            HP=max(HP,5);
            HP/=5;
            bitihon=true;
        }
        if(bitihon)
        {
            if(!remedy && tihon>-1) tihon--;
            if(tihon==-1 || remedy)// ket thuc ti hon
            {
                if(remedy) remedy--;
                bitihon=false;
                HP=min(HP*5,maxHP);
                tihon=-1;
            }
        }
        
        //bi bien thanh ech///
        if(ech==3 && !biech)
        {
            beforelevel=level;
            level=1;
            biech=true;
        }

        if(biech)
        {
            if(!maidenkiss && ech>-1) ech--;
            if(ech==-1 || maidenkiss) // het trang thai ech
            {
                if(maidenkiss) maidenkiss--;
                biech=false;
                level=beforelevel;
                ech=-1;
            }
        }
        
        if(HP<=0)
        {
            if(phoenixdown)
            {
                phoenixdown--;
                HP=maxHP; //Hoi sinh
                tihon=-1;
                bitihon=false;
                biech=false;
                if(ech) 
                {
                    level=beforelevel;
                    ech=false;
                }
            }
            else 
            {  
                rescue=0;
            }
        }
        if(rescue==0) break;
        s="";
        numevt++;
    }
    if(rescue!=0) rescue=1;
    display(HP,level,remedy,maidenkiss,phoenixdown,rescue);
}