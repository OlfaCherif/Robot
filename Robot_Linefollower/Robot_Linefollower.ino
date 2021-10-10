// Analog pins
#define D A0 // The right sensor 
#define G A1 // The left sensor
#define CG A2 //The second left sensor
#define CD A4 //The second right sensor
#define M A5 //

const byte AA = 2 ;//bleu
const byte B = 3;//jaune
const byte C = 4; //violet
const byte DD = 13; //vert
const byte E = 0; //vert
const byte F = 1; // vert
const byte GG = 9; //jaune

// The engine variables
int RB=11 ; // the right engine , backward direction
int RF=10 ; // the right engine , forward direction
int LF=6 ;  // the left engine , forward direction
int LB=5 ;  // the left engine , backward direction


int dem=-1 ;
int pred=2;
int etape= 0;

int g,d,m,cd,cg ;
float temps,dist ;
int trig = 7; // trig of the ultrasonic sensor 
int echo = 8; // echo of the ultrasonic sensor
long lecture_echo;
String com="";
int fois=0;
int i=0;
int pcd=0;
int pcg=0;
int j=0;
int etat=0;
int pred2=0; // precedant 
int premierp=0;
int marra=0 ;



void setup() 
{
  
 pinMode(AA , OUTPUT); 
 pinMode(B , OUTPUT); 
 pinMode(C , OUTPUT); 
 pinMode(DD , OUTPUT); 
 pinMode(E , OUTPUT) ;
 pinMode(F , OUTPUT) ;
 pinMode(GG , OUTPUT) ;
 
 digitalWrite(AA,HIGH);
 digitalWrite(B,HIGH);
 digitalWrite(C,HIGH);
 digitalWrite(DD,HIGH);
 digitalWrite(E,HIGH);
 digitalWrite(F,HIGH);
 digitalWrite(GG,HIGH);
 
 pinMode(RF , OUTPUT); 
 pinMode(RB , OUTPUT); 
 pinMode(LF , OUTPUT); 
 pinMode(LB , OUTPUT); 
 pinMode(G , INPUT) ;
 pinMode(D , INPUT) ;
 pinMode(M , INPUT) ;
 pinMode(CD , INPUT) ;
 pinMode(CG , INPUT) ;
 pinMode(trig, OUTPUT);
 digitalWrite(trig, LOW);
 pinMode(echo, INPUT);

}

void correctiond ()
 // Right correction
{ 
  analogWrite(RF ,0 );
  analogWrite(LF , 120);
  analogWrite(RB ,0);
  analogWrite(LB , 0);
}


void correctiong ()
 // left correction
{
  analogWrite(RF , 120 );
  analogWrite(LF , 0);
  analogWrite(RB ,0);
  analogWrite(LB , 0);
}

 
void stoop () 
//STOP the robot
{
  analogWrite(RF , 0 );
  analogWrite(LF ,0);
  analogWrite(RB ,0);
  analogWrite(LB , 0);
}

 void Marche () 
 //This function make the robot walk 
{
  analogWrite(RF , 130); //80
  analogWrite(LF , 135); //85
  analogWrite(RB ,0);
  analogWrite(LB , 0);
}
 
 void Droite ()
//Turn right
{  
  analogWrite(RB ,70 );
  analogWrite(LF ,100);
  analogWrite(RF ,0);
  analogWrite(LB , 0);
  
}

  void Gauche ()
//Turn left
{
  analogWrite(RF ,100) ;
  analogWrite(LB ,70);
  analogWrite(RB ,0);
  analogWrite(LF , 0);
}


 
int distance(int trig,int echo)
{
 // Measure the distance beetween the ultrasonic sensor and the obstacle 
  digitalWrite(trig, HIGH);        
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  temps = pulseIn(echo, HIGH);
  
  if (temps > 25000)  
    return(1000);
  else { temps = temps/2;
    dist = (temps*340)/10000.0;       }
    return(dist);
}



void correction()
{ 
  if  ( g==0 && m==0 && d==1 && cd==0)
  {correctiond ();
  pred=2001;}
  else 
  if   ( g==0 && m==1 && d==1 && cd==0 ) 
  {correctiond ();
  pred=2011;}
  else 
  if  ( g==1 && m==0 && d==0 )
  { correctiong ();
  pred=2100;}
  else 
  if  ( /* a verifier*/ g==1 && m==1 && d==0 ) 
  { correctiong ();
  pred=2110;}
}



void suiveur()
{        
      
             
    if  ( g==0 && m==0 && d==1 && cd==0)
    {
    correctiond ();
    pred=2001;
    }
    else 
    if   ( g==0 && m==1 && d==1 && cd==0 ) 
    {
    correctiond ();
    pred=2011;
    }
    else 
    if  ( g==1 && m==0 && d==0 )
    { 
    correctiong ();
    pred=2100;
    }
    else 
    if  ( /* a verifier*/ g==1 && m==1 && d==0 ) 
    {
    Gauche (); //
    pred=2110;
    }
    else
    if  (( (pred==8) &&( g==0 && m==1 && d==0 )) || ( (pred==8) &&( cg==0 && g==1 && m==1 && d==1 && cd==0 )))
    { 
    Droite () ;
    pred=2011;
    }
    else
    if  ( g==0 && m==1 && d==0 )  
    { 
    Marche () ;
    pred=2010;
    }
    else
    if    ( g==1 && m==1 && d==1 && cg==1 && cd==1 ) 
    {  
    if (premierp==0)
    {
    Marche();
    delay(500);
    premierp=premierp+1;
    }                
    if (pred!=2111)
    { 
    i++;
    }   
    Marche () ;
    pred=2111;
    }
    else                 
    if (( g==0 && m==0 && d==0 ) && (pred==2010)&& (i<4))
    Marche();
    else
    if (( g==0 && m==0 && d==0 ) && (pred==2100) )
    { correctiong ();}
    else
    if (( g==0 && m==0 && d==0 ) && (pred==2001) )
    { correctiond ();}
    else
    if (  ( cg==0 && g==0 && m==1 && d==1 && cd==1  /*&& pred==2010*/ ) ||  ( cg==0 && g==0 && m==0 && d==1 && cd==1 ))
    {
    Droite();
    pred=8;}
    else
    if  ( cd==0 && g==1 && m==0 && d==0 && cd==1 )
    {correctiong ();}
    else
    if  ( cg==1 && g==1 && m==0 && d==0 && cd==1)
    {correctiong ();}
    
}

                 

void combinaison ()
{
  if ( (i==4) && (fois<3) && (pcd!=1) && (pcg!=1) )
{  
  if ((cd==1) && (pcd!=1))
  {
    com=com+"0"; fois=fois+1;
  } 
  
  if ((cg==1) && (pcg!=1))
  {
    com=com+"1"; fois=fois+1;
  }
 
}
}



void pas ()
{
// Make a very slow walk
  analogWrite(RF , 70); //80
  analogWrite(LF , 75); //85
  analogWrite(RB ,0);
  analogWrite(LB , 0);
}

void Demitour()
// Turn around the robot 
{ 
  analogWrite(RB ,80);
  analogWrite(LF ,70);
  analogWrite(RF ,0);
  analogWrite(LB ,0); 
}




void labyrinthe ()
{

 //This code make the robot chose a priority to exit the Maze. 
    if  ( cd==1 && g==1 && m==1 && d==0 && cd==0 )  
    { 
    Gauche () ; //
    pred=2110;
    }    
    else
    if  (cg==0 && g==1 && m==0 && d==0 ) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    {correctiong ();
    pred=2100;}
    else
    if   ( cg==0 && g==1 && m==1 && d==0  )  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    {correctiong ();
    pred=2011;}
    else 
    if ( g==0 && m==1 && d==0 )  
    { 
    Marche () ;
    pred=2010;
    } 
    else
    if  (  g==1 && m==1 && d==1  )  
    { 
    Gauche () ;
    pred=2111;
    }  
    else
    if  (  g==0 && m==0 && d==1 && cd==0 )
    { correctiond ();
    pred=2001;}
    else 
    if  (  g==0 && m==1 && d==1 && cd==0 ) 
    { correctiond ();
    pred=2011;}
    else
    if (( g==0 && m==0 && d==1 &&cd==1 )  || (cg==0&& g==0 && m==1 && d==1 && cd==1 ))
    {Droite();}
    else
    if  ( cg==0 && g==0 && m==0 && d==0 && cd==0 )  
    { 
      if (j==0)
      { 
      pas();              
      delay(1000);
      Demitour () ;
      j=1;
      }
      else
      Demitour();
    }
    if(m==0 && g==0&& d==0)
    {
    Demitour();  
    }
    else 
    j=0;

}


void obstacle()
{
  if ((i>=4) && (marra<1))
  { dist=distance(trig,echo);
  if ((dist<=11) && (marra<1) )
  {stoop(); etat=etat+1; marra=1; 
  delay(5000);
  }
}   
}


void Afficher ()
{ 
 // Show the number on a screen  
  digitalWrite(AA,HIGH);
  digitalWrite(B,HIGH);
  digitalWrite(C,HIGH);
  digitalWrite(DD,HIGH);
  digitalWrite(E,HIGH);
  digitalWrite(F,HIGH);
  digitalWrite(GG,HIGH);  

if (com=="000")
 {
  digitalWrite(AA,LOW);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(DD,LOW);
  digitalWrite(E,LOW);
  digitalWrite(F,LOW);
 }
if (com=="001")
 {
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
 }
if (com=="010")
 {
  digitalWrite(AA,LOW);
  digitalWrite(B,LOW);
  digitalWrite(GG,LOW);
  digitalWrite(E,LOW);
  digitalWrite(DD,LOW);
 }
if (com=="011")
 {
  digitalWrite(AA,LOW);
  digitalWrite(B,LOW);
  digitalWrite(GG,LOW);
  digitalWrite(C,LOW);
  digitalWrite(DD,LOW);
 }
if (com=="100")
 {
  digitalWrite(F,LOW);
  digitalWrite(GG,LOW);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
 }
if (com=="101")
 {
  digitalWrite(AA,LOW);
  digitalWrite(F,LOW);
  digitalWrite(GG,LOW);
  digitalWrite(C,LOW);
  digitalWrite(DD,LOW);
 }
if (com=="110")
 {
  digitalWrite(AA,LOW);
  digitalWrite(F,LOW);
  digitalWrite(GG,LOW);
  digitalWrite(C,LOW);
  digitalWrite(DD,LOW);
  digitalWrite(E,LOW);
 }
if (com=="111")
 {
  digitalWrite(AA,LOW);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
 }

}


void loop() {

pcg=cg;
pcd=cd;

g=digitalRead(G);
d=digitalRead(D);
m=digitalRead(M);
cg=digitalRead(CG);
cd=digitalRead(CD);

if (etat==0)
  {suiveur ();}
else 
  {labyrinthe ();}

combinaison();
obstacle();

if (fois >=3 )
  {
  Afficher();
  } 

}
