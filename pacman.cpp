#include"iGraphics.h"
#include<stdio.h>
#include<string.h>
#include<time.h>
#define screenLength 1500
#define screenWidth 750
#define bricklength 15
#define mazeLength 450
#define mazeWidth 435
#define pacVelocity 15
#define ghostVelocity 15

int ghostTime=300;
int diff=1;
int t;
char timeLeft[10];
void timeCheck();
void deathCheck();
void ghostMove();
void pacMove();
void dotDraw1();
void frightenedCheck();
void showScoreLife();
void setHighScore();
void appendFile();
void dotCheck();
bool initial=true;
bool frightened=false;
int pacCellX,pacCellY;
int startMazeX = 450;
int startMazeY = 150;
int dotNum;
int bigDotNum=4;
int score=0;
char scr[10];
int pacLife=3;
int frightenedTime;
bool sound=true;
bool home=true;
bool play1=false;
bool play2=false;
bool playEnd=false;
bool instructions=false;
bool credits=false;
bool hall=false;
bool difficulty=false;
bool pause=false;
char nameEntry[25];
int nameIndex=0;
char finalName[25];
char finalScore[10];

char moveR[4][15]={"moveRight1.bmp","moveRight1.bmp","moveRight2.bmp","moveRight2.bmp"};
char moveL[4][15]={"moveLeft1.bmp","moveLeft1.bmp","moveLeft2.bmp","moveLeft2.bmp"};
char moveU[4][15]={"moveUp1.bmp","moveUp1.bmp","moveUp2.bmp","moveUp2.bmp"};
char moveD[4][15]={"moveDown1.bmp","moveDown1.bmp","moveDown2.bmp","moveDown2.bmp"};
int maze1CoordinateX[29][30];
int maze1CoordinateY[29][30];
bool dot1[29][30];
bool bigDot1[29][30];

typedef struct
{
    int index,coX,coY;
    bool moveRight,moveLeft,moveUp,moveDown;
}Move;

Move pac;

typedef struct
{
    int cellX,cellY,X,Y,cell,direction;
}ghost;

ghost red,pink,yellow,blue;

typedef struct
{
    int scoreH;
    char nameH[25];
}player;

player bio[6];
player bioM[5];
player bioH[5];

int mazeMap1[29][30]=
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,
    1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
    1,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
    1,0,1,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,1,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

void setCoordinate1()
{
    int i,j;
    int dx=startMazeX,dy=startMazeY;
    for(i=0;i<29;i++)
    {
        for(j=0;j<30;j++)
        {
            maze1CoordinateX[i][j]=dx;
            maze1CoordinateY[i][j]=dy;
            dx+=bricklength;
        }
        dx=startMazeX;
        dy+=bricklength;
    }
}


void mazeDraw1()
{
    for(int i=0;i<29;i++)
            for(int j=0;j<30;j++)
                if(mazeMap1[i][j])
                    iShowBMP(maze1CoordinateX[i][j],maze1CoordinateY[i][j],"mazeBrick.bmp");
}

void setDot1()
{
    dotNum=0;
    for(int i=0;i<29;i++)
    {
        for(int j=0;j<30;j++)
        {
            if(mazeMap1[i][j])
                dot1[i][j]=false;
            else
                {
                    dot1[i][j]=true;
                    dotNum++;
                }
        }
    }
}

void setBigDot1()
{
    for(int i=0;i<29;i++)
        for(int j=0;j<30;j++)
           bigDot1[i][j]=false;
}

void setGhost1()
{
      red.cellX=28;
      red.cellY=14;
      red.X=startMazeX+red.cellX*bricklength;
      red.Y=startMazeY+red.cellY*bricklength;
      red.cell=0;
      blue.cellX=1;
      blue.cellY=27;
      blue.X=startMazeX+blue.cellX*bricklength;
      blue.Y=startMazeY+blue.cellY*bricklength;
      blue.cell=0;
      pink.cellX=18;
      pink.cellY=18;
      pink.X=startMazeX+pink.cellX*bricklength;
      pink.Y=startMazeY+pink.cellY*bricklength;
      pink.cell=0;
      yellow.cellX=13;
      yellow.cellY=14;
      yellow.X=startMazeX+yellow.cellX*bricklength;
      yellow.Y=startMazeY+yellow.cellY*bricklength;
      yellow.cell=0;
}
void ghostMove()
{
    if(!frightened)
    {
        if(red.direction==1)
            iShowBMP2(red.X,red.Y,"redRight.bmp",0);
        else if(red.direction==2)
            iShowBMP2(red.X,red.Y,"redLeft.bmp",0);
        else if(red.direction==3)
            iShowBMP2(red.X,red.Y,"redUp.bmp",0);
        else if(red.direction==4)
            iShowBMP2(red.X,red.Y,"redDown.bmp",0);
        else ;
        if(blue.direction==1)
            iShowBMP2(blue.X,blue.Y,"blueRight.bmp",0);
        else if(blue.direction==2)
            iShowBMP2(blue.X,blue.Y,"blueLeft.bmp",0);
        else if(blue.direction==3)
            iShowBMP2(blue.X,blue.Y,"blueUp.bmp",0);
        else if(blue.direction==4)
            iShowBMP2(blue.X,blue.Y,"blueDown.bmp",0);
        else ;
        if(pink.direction==1)
            iShowBMP2(pink.X,pink.Y,"pinkRight.bmp",0);
        else if(pink.direction==2)
            iShowBMP2(pink.X,pink.Y,"pinkLeft.bmp",0);
        else if(pink.direction==3)
            iShowBMP2(pink.X,pink.Y,"pinkUp.bmp",0);
        else if(pink.direction==4)
            iShowBMP2(pink.X,pink.Y,"pinkDown.bmp",0);
        else ;
        if(yellow.direction==1)
            iShowBMP2(yellow.X,yellow.Y,"yellowRight.bmp",0);
        else if(yellow.direction==2)
            iShowBMP2(yellow.X,yellow.Y,"yellowLeft.bmp",0);
        else if(yellow.direction==3)
            iShowBMP2(yellow.X,yellow.Y,"yellowUp.bmp",0);
        else if(yellow.direction==4)
            iShowBMP2(yellow.X,yellow.Y,"yellowDown.bmp",0);
        else ;
    }
    else if(frightened && frightenedTime)
    {
        iShowBMP2(red.X,red.Y,"frightened.bmp",0);
        iShowBMP2(yellow.X,yellow.Y,"frightened.bmp",0);
        iShowBMP2(pink.X,pink.Y,"frightened.bmp",0);
        iShowBMP2(blue.X,blue.Y,"frightened.bmp",0);
    }
}

void frightenedTimeCheck()
{
    if(frightened)
    {
        if(sound)
            PlaySound("chase.wav",NULL,SND_ASYNC);
        frightenedTime--;
    }
    if(!frightenedTime)
        frightened=false;
}

void moveGhost()
{
    if(play2)
    {
            if((red.cell<12)||(red.cell>=58 && red.cell<62))
        {
                red.Y-=ghostVelocity;
                red.cellY--;
                red.direction=4;
                red.cell++;
        }
        else if((red.cell>=12 && red.cell<15)||(red.cell>=18 && red.cell<40))
        {
                red.X-=ghostVelocity;
                red.cellX--;
                red.direction=2;
                red.cell++;
        }
        else if((red.cell>=15&&red.cell<18)||(red.cell>=47 && red.cell<50)||(red.cell>=70 && red.cell<74)||(red.cell>=76 && red.cell<83))
        {
                red.Y+=ghostVelocity;
                red.cellY++;
                red.direction=3;
                red.cell++;
                  if(red.cell==83)
                {
                      red.cellX=28;
                      red.cellY=14;
                      red.X=startMazeX+red.cellX*bricklength;
                      red.Y=startMazeY+red.cellY*bricklength;
                      red.cell=0;
                }
        }
        else if((red.cell>=40 && red.cell<47)||(red.cell>=50 && red.cell<58)||(red.cell>=62 && red.cell<70)||(red.cell>=74 && red.cell<76))
        {
                red.X+=ghostVelocity;
                red.cellX++;
                red.direction=1;
                red.cell++;
        }
        else ;

        if((blue.cell<26)||(blue.cell>=41 && blue.cell<43)||(blue.cell>=58 && blue.cell<61)||(blue.cell>=85 && blue.cell<87))
        {
                blue.Y-=ghostVelocity;
                blue.cellY--;
                blue.direction=4;
                blue.cell++;
        }
        else if((blue.cell>=26 && blue.cell<29) || (blue.cell>=32 && blue.cell<41)|| (blue.cell>=43 && blue.cell<48)||(blue.cell>=51 && blue.cell<58)||(blue.cell>=61 && blue.cell<64))
        {
            blue.X+=ghostVelocity;
            blue.cellX++;
            blue.direction=1;
            blue.cell++;
        }
        else if((blue.cell>=29 && blue.cell<32)||(blue.cell>=48 && blue.cell<51)||(blue.cell>=64 && blue.cell<75)||(blue.cell>=88&&blue.cell<89)||(blue.cell>=96 && blue.cell<99)||(blue.cell>=108 && blue.cell<120))
        {
            blue.Y+=ghostVelocity;
            blue.cellY++;
            blue.direction=3;
            blue.cell++;
            if(blue.cell==120)
            {
                blue.cellX=1;
                blue.cellY=27;
                blue.X=startMazeX+blue.cellX*bricklength;
                blue.Y=startMazeY+blue.cellY*bricklength;
                blue.cell=0;
            }
        }
        else if((blue.cell>=75 && blue.cell<85)||(blue.cell>=85 && blue.cell<88)||(blue.cell>=89 && blue.cell<96)||(blue.cell>=99 && blue.cell<108))
        {
            blue.X-=ghostVelocity;
            blue.cellX--;
            blue.direction=2;
            blue.cell++;
        }
        else ;

        if((pink.cell<3)||(pink.cell>=13 && pink.cell<17)||(pink.cell>=49 && pink.cell<52)||(pink.cell>=61 && pink.cell<66)||(pink.cell>=68 && pink.cell<74)||(pink.cell>=84 && pink.cell<87))
        {
            pink.Y-=ghostVelocity;
            pink.cellY--;
            pink.direction=4;
            pink.cell++;
        }
        else if((pink.cell>=3 && pink.cell<8)||(pink.cell>=12 && pink.cell<13)||(pink.cell>=17 && pink.cell<21)||(pink.cell>=74 && pink.cell<84)||(pink.cell>=87 && pink.cell<95))
        {
            pink.X+=ghostVelocity;
            pink.cellX++;
            pink.direction=1;
            pink.cell++;
        }
        else if((pink.cell>=8 && pink.cell<12)||(pink.cell>=21 && pink.cell<27)||(pink.cell>=29 && pink.cell<31)||(pink.cell>=40 && pink.cell<44)||(pink.cell>=95 && pink.cell<103))
        {
            pink.Y+=ghostVelocity;
            pink.cellY++;
            pink.direction=3;
            pink.cell++;
        }
        else if((pink.cell>=27 && pink.cell<29)||(pink.cell>=31 && pink.cell<40)||(pink.cell>=44 && pink.cell<49)||(pink.cell>=52 && pink.cell<61)||(pink.cell>=66 && pink.cell<68)||(pink.cell>=103 && pink.cell<104))
        {
            pink.X-=ghostVelocity;
            pink.cellX--;
            pink.direction=2;
            pink.cell++;
            if(pink.cell==104)
            {
                pink.cellX=18;
                pink.cellY=18;
                pink.X=startMazeX+pink.cellX*bricklength;
                pink.Y=startMazeY+pink.cellY*bricklength;
                pink.cell=0;
            }
        }
        else ;

        if((yellow.cell<2)||(yellow.cell>=14 && yellow.cell<21)||(yellow.cell>=24 && yellow.cell<33)||(yellow.cell>=61 && yellow.cell<64)||(yellow.cell>=108 && yellow.cell<110)||(yellow.cell>=114 && yellow.cell<137)||(yellow.cell>=140 && yellow.cell<142))
        {
            yellow.X-=ghostVelocity;
            yellow.cellX--;
            yellow.direction=2;
            yellow.cell++;
        }
        else if((yellow.cell>=2 && yellow.cell<6)||(yellow.cell>=33 && yellow.cell<46)||(yellow.cell>=74 && yellow.cell<77)||(yellow.cell>=85 && yellow.cell<88)||(yellow.cell>=137 && yellow.cell<140)||(yellow.cell>=142 && yellow.cell<147)||(yellow.cell>=157 && yellow.cell<158))
        {
            yellow.Y+=ghostVelocity;
            yellow.cellY++;
            yellow.direction=3;
            yellow.cell++;
        }
        else if((yellow.cell>=6 && yellow.cell<12)||(yellow.cell>=46 && yellow.cell<49)||(yellow.cell>=51 && yellow.cell<58)||(yellow.cell>=64 && yellow.cell<74)||(yellow.cell>=77 && yellow.cell<85)||(yellow.cell>=88 && yellow.cell<90)||(yellow.cell>=147 && yellow.cell<157)||(yellow.cell>=158 && yellow.cell<160))
        {
            yellow.X+=ghostVelocity;
            yellow.cellX++;
            yellow.direction=1;
            yellow.cell++;
            if(yellow.cell==160)
            {
                yellow.cellX=13;
                yellow.cellY=14;
                yellow.X=startMazeX+yellow.cellX*bricklength;
                yellow.Y=startMazeY+yellow.cellY*bricklength;
                yellow.cell=0;
            }
        }
        else if((yellow.cell>=12 && yellow.cell<14)||(yellow.cell>=21 && yellow.cell<24)||(yellow.cell>=49 && yellow.cell<51)||(yellow.cell>=58 && yellow.cell<61)||(yellow.cell>=90 && yellow.cell<108)||(yellow.cell>=110 && yellow.cell<114))
        {
            yellow.Y-=ghostVelocity;
            yellow.cellY--;
            yellow.direction=4;
            yellow.cell++;
        }
    }
}

 void deathCheck()
 {
     if(play2)
     {
         if(!frightened)
         {
             if((pacCellX==red.cellX&&pacCellY==red.cellY)||(pacCellX==blue.cellX&&pacCellY==blue.cellY)||(pacCellX==pink.cellX&&pacCellY==pink.cellY)||(pacCellX==yellow.cellX&&pacCellY==yellow.cellY))
             {
                 if(sound)
                    PlaySound("pacDead.wav",NULL,SND_ASYNC);
                pacCellX=15;
                pacCellY=1;
                pac.coX=startMazeX+pacCellX*bricklength;
                pac.coY=startMazeY+(pacCellY)*bricklength;
                pacLife--;
                score-=50;
                if(!pacLife)
                {
                    home=false;
                    play1=false;
                    play2=false;
                    playEnd=true;
                    difficulty=false;
                    hall=false;
                    credits=false;
                    instructions=false;
                    appendFile();
                    setHighScore();
                }
                initial=true;
                pac.moveDown=false;
                pac.moveRight=false;
                pac.moveRight=false;
                pac.moveUp=false;
             }
         }
         else if(frightened)
         {
             if(pacCellX==red.cellX&&pacCellY==red.cellY)
             {
                if(sound)
                    PlaySound("eatGhost.wav",NULL,SND_ASYNC);
                red.cellX=28;
                red.cellY=14;
                red.X=startMazeX+red.cellX*bricklength;
                red.Y=startMazeY+red.cellY*bricklength;
                red.cell=0;
                score+=200;
             }
             if(pacCellX==blue.cellX&&pacCellY==blue.cellY)
             {
                  if(sound)
                    PlaySound("eatGhost.wav",NULL,SND_ASYNC);
                  blue.cellX=1;
                  blue.cellY=27;
                  blue.X=startMazeX+blue.cellX*bricklength;
                  blue.Y=startMazeY+blue.cellY*bricklength;
                  blue.cell=0;
                  score+=200;
             }
             if(pacCellX==pink.cellX&&pacCellY==pink.cellY)
             {
                 if(sound)
                    PlaySound("eatGhost.wav",NULL,SND_ASYNC);
                 pink.cellX=18;
                 pink.cellY=18;
                 pink.X=startMazeX+pink.cellX*bricklength;
                 pink.Y=startMazeY+pink.cellY*bricklength;
                 pink.cell=0;
                 score+=200;
             }
             if(pacCellX==yellow.cellX&&pacCellY==yellow.cellY)
             {
                 if(sound)
                    PlaySound("eatGhost.wav",NULL,SND_ASYNC);
                 yellow.cellX=13;
                 yellow.cellY=14;
                 yellow.X=startMazeX+yellow.cellX*bricklength;
                 yellow.Y=startMazeY+yellow.cellY*bricklength;
                 yellow.cell=0;
                 score+=200;
             }
         }
     }
 }

 void pacMove()
 {
         if(initial)
            iShowBMP2(pac.coX+1,pac.coY+1,"initial.bmp",0);
        else if(pac.moveRight)
            iShowBMP2(pac.coX+1,pac.coY+1,moveR[pac.index],0);
        else if(pac.moveLeft)
            iShowBMP2(pac.coX+1,pac.coY+1,moveL[pac.index],0);
        else if(pac.moveUp)
            iShowBMP2(pac.coX+1,pac.coY+1,moveU[pac.index],0);
         else if(pac.moveDown)
            iShowBMP2(pac.coX+1,pac.coY+1,moveD[pac.index],0);
        else
        ;
 }

 void dotDraw1()
 {
      for(int i=0;i<29;i++)
    {
        for(int j=0;j<30;j++)
        {
            if(dot1[i][j])
            {
                iShowBMP2(maze1CoordinateX[i][j]+4,maze1CoordinateY[i][j]+4,"pacDot.bmp",0);
            }
        }
    }
 }
 void bigDotDraw1()
 {
     for(int i=0;i<29;i++)
     {
         for(int j=0;j<30;j++)
         {
             if(bigDot1[i][j])
                iShowBMP2(maze1CoordinateX[i][j],maze1CoordinateY[i][j],"bigDot.bmp",0);
         }
     }
 }

 void showScoreLife()
 {
     iSetColor(255,255,255);
    iText(1000,550,"Score: ",GLUT_BITMAP_TIMES_ROMAN_24);
    sprintf(scr,"%i",score);
    iText(1070,550,scr,GLUT_BITMAP_TIMES_ROMAN_24);
    iText(1150,550,"Lives: ",GLUT_BITMAP_TIMES_ROMAN_24);
    for(int i=0;i<pacLife;i++)
        iShowBMP2(1220+i*30,550-5,"life.bmp",0);
    iText(250,550,"Time Left :",GLUT_BITMAP_TIMES_ROMAN_24);
    sprintf(timeLeft,"%i",t);
    iText(370,550,timeLeft,GLUT_BITMAP_TIMES_ROMAN_24);
 }

 void timeCheck()
 {
     if(play2)
     {
         t--;
         if(!t)
         {
                    home=false;
                    play1=false;
                    play2=false;
                    playEnd=true;
                    difficulty=false;
                    hall=false;
                    credits=false;
                    instructions=false;
                    appendFile();
                    setHighScore();
         }
     }
 }

 void frightenedCheck()
 {
     if(bigDot1[pacCellY][pacCellX])
     {
             if((pacCellX==28 && pacCellY==4)||(pacCellX==5 && pacCellY==7)||(pacCellX==22 && pacCellY==27)||(pacCellX==16 && pacCellY==14))
         {
             score+=10;
             bigDot1[pacCellY][pacCellX]=false;
             bigDotNum--;
             frightened=true;
             frightenedTime=10;
             dotCheck();
         }
     }
 }

 void appendFile()
 {
      sprintf(finalScore,"%i",score);
      if(diff==1)
      {
          FILE * fp1=fopen("highName.txt","a");
          FILE * fp2=fopen("highScore.txt","a");
          fprintf(fp1,"%s\n",finalName);
          fprintf(fp2,"%s\n",finalScore);
          fclose(fp1);
          fclose(fp2);
      }
      else if(diff==2)
      {
          FILE * fp1=fopen("mediumName.txt","a");
          FILE * fp2=fopen("mediumScore.txt","a");
          fprintf(fp1,"%s\n",finalName);
          fprintf(fp2,"%s\n",finalScore);
          fclose(fp1);
          fclose(fp2);
      }
      else if(diff==3)
      {
          FILE * fp1=fopen("hardName.txt","a");
          FILE * fp2=fopen("hardScore.txt","a");
          fprintf(fp1,"%s\n",finalName);
          fprintf(fp2,"%s\n",finalScore);
          fclose(fp1);
          fclose(fp2);
      }
      else
           ;
 }

 void gameEnd()
 {
     sprintf(finalScore,"%i",score);
     iSetColor(0,0,0);
     if(!dotNum )
     {
         iShowBMP(0,0,"completeScore.bmp");
         iText(736,432,finalScore,GLUT_BITMAP_TIMES_ROMAN_24);
     }
     else if(!pacLife)
     {
         iShowBMP(0,0,"deadScore.bmp");
         iText(730,432,finalScore,GLUT_BITMAP_TIMES_ROMAN_24);
     }
     else if(!t)
     {
         iShowBMP(0,0,"timeScore.bmp");
         iText(730,432,finalScore,GLUT_BITMAP_TIMES_ROMAN_24);
     }
     else
     {
         iShowBMP(0,0,"userEnd.bmp");
         iText(730,432,finalScore,GLUT_BITMAP_TIMES_ROMAN_24);
     }
 }

 void dotCheck()
 {
     if(!dotNum && !bigDotNum)
     {
                home=false;
                play1=false;
                play2=false;
                playEnd=true;
                difficulty=false;
                hall=false;
                credits=false;
                instructions=false;
                appendFile();
                setHighScore();
     }
 }

 void setHighScore()
 {
     if(diff==1)
      {
          FILE * f1=fopen("highName.txt","r");
          FILE * f2=fopen("highScore.txt","r");
          for(int i=0;i<6;i++)
            {
                if(f1!=NULL && f2!=NULL)
                {
                    fscanf(f1,"%s",bio[i].nameH);
                    fscanf(f2,"%d",&bio[i].scoreH);
                }
            }

            for(int i=0;i<6;i++)
            {
                for(int j=i+1;j<6;j++)
                {
                    if(bio[i].scoreH<=bio[j].scoreH)
                    {
                        int temp1=bio[i].scoreH;
                        bio[i].scoreH=bio[j].scoreH;
                        bio[j].scoreH=temp1;
                        char temp2[20];
                        strcpy(temp2,bio[i].nameH);
                        strcpy(bio[i].nameH,bio[j].nameH);
                        strcpy(bio[j].nameH,temp2);
                    }
                }
            }

            fclose(f1);
            fclose(f2);

            FILE * f3=fopen("highName.txt","w");
            FILE * f4=fopen("highScore.txt","w");
            for(int i=0;i<5;i++)
                {
                    fprintf(f3,"%s\n",bio[i].nameH);
                    fprintf(f4,"%d\n",bio[i].scoreH);
                }
            fclose(f3);
            fclose(f4);
      }
      else if(diff==2)
      {
          FILE * f1=fopen("mediumName.txt","r");
          FILE * f2=fopen("mediumScore.txt","r");
          for(int i=0;i<6;i++)
            {
                if(f1!=NULL && f2!=NULL)
                {
                    fscanf(f1,"%s",bio[i].nameH);
                    fscanf(f2,"%d",&bio[i].scoreH);
                }
            }

            for(int i=0;i<6;i++)
            {
                for(int j=i+1;j<6;j++)
                {
                    if(bio[i].scoreH<=bio[j].scoreH)
                    {
                        int temp1=bio[i].scoreH;
                        bio[i].scoreH=bio[j].scoreH;
                        bio[j].scoreH=temp1;
                        char temp2[20];
                        strcpy(temp2,bio[i].nameH);
                        strcpy(bio[i].nameH,bio[j].nameH);
                        strcpy(bio[j].nameH,temp2);
                    }
                }
            }

            fclose(f1);
            fclose(f2);

            FILE * f3=fopen("mediumName.txt","w");
            FILE * f4=fopen("mediumScore.txt","w");
            for(int i=0;i<5;i++)
                {
                    fprintf(f3,"%s\n",bio[i].nameH);
                    fprintf(f4,"%d\n",bio[i].scoreH);
                }
            fclose(f3);
            fclose(f4);
      }
      else if(diff==3)
      {
          FILE * f1=fopen("hardName.txt","r");
          FILE * f2=fopen("hardScore.txt","r");
          for(int i=0;i<6;i++)
            {
                if(f1!=NULL && f2!=NULL)
                {
                    fscanf(f1,"%s",bio[i].nameH);
                    fscanf(f2,"%d",&bio[i].scoreH);
                }
            }

            for(int i=0;i<6;i++)
            {
                for(int j=i+1;j<6;j++)
                {
                    if(bio[i].scoreH<=bio[j].scoreH)
                    {
                        int temp1=bio[i].scoreH;
                        bio[i].scoreH=bio[j].scoreH;
                        bio[j].scoreH=temp1;
                        char temp2[20];
                        strcpy(temp2,bio[i].nameH);
                        strcpy(bio[i].nameH,bio[j].nameH);
                        strcpy(bio[j].nameH,temp2);
                    }
                }
            }

            fclose(f1);
            fclose(f2);

            FILE * f3=fopen("hardName.txt","w");
            FILE * f4=fopen("hardScore.txt","w");
            for(int i=0;i<5;i++)
                {
                    fprintf(f3,"%s\n",bio[i].nameH);
                    fprintf(f4,"%d\n",bio[i].scoreH);
                }
            fclose(f3);
            fclose(f4);
      }
      else
        ;

 }

 void showHighScore()
 {
     FILE * f1=fopen("highName.txt","r");
     FILE * f2=fopen("highScore.txt","r");
     FILE * f3=fopen("mediumName.txt","r");
     FILE * f4=fopen("mediumScore.txt","r");
     FILE * f5=fopen("hardName.txt","r");
     FILE * f6=fopen("hardScore.txt","r");
     for(int i=0;i<5;i++)
    {
        if(f1!=NULL && f2!=NULL)
        {
            fscanf(f1,"%s",bio[i].nameH);
            fscanf(f2,"%d",&bio[i].scoreH);
            fscanf(f3,"%s",bioM[i].nameH);
            fscanf(f4,"%d",&bioM[i].scoreH);
            fscanf(f5,"%s",bioH[i].nameH);
            fscanf(f6,"%d",&bioH[i].scoreH);
        }
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);
 }


void iDraw()
{
    iClear();
    if(home)
        iShowBMP(0,0,"home.bmp");\
    else if(play1)
    {
        iShowBMP(0,0,"enterName.bmp");
        iSetColor(0,0,0);
        iText(450,350,nameEntry,GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else if(play2)
    {
        iShowBMP(1000,200,"endgame.bmp");
        mazeDraw1();
        pacMove();
        dotDraw1();
        bigDotDraw1();
        ghostMove();
        showScoreLife();
    }
    else if(playEnd)
    {
        gameEnd();
    }
    else if(hall)
    {
        iShowBMP(0,0,"hall.bmp");
        for(int i=0;i<5;i++)
        {
            char s1[10],s2[10],s3[10];
            iSetColor(255,255,0);
            iFilledCircle(100,450-i*50,8,100);
            iFilledCircle(600,450-i*50,8,100);
            iFilledCircle(1100,450-i*50,8,100);
            iSetColor(0,0,0);
            iText(130,500,"Name",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(350,500,"Score",GLUT_BITMAP_TIMES_ROMAN_24);
             iText(630,500,"Name",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(850,500,"Score",GLUT_BITMAP_TIMES_ROMAN_24);
             iText(1130,500,"Name",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(1350,500,"Score",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(130,450-i*50-5,bio[i].nameH,GLUT_BITMAP_TIMES_ROMAN_24);
            sprintf(s1,"%i",bio[i].scoreH);
            iText(350,450-i*50-5,s1,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(630,450-i*50-5,bioM[i].nameH,GLUT_BITMAP_TIMES_ROMAN_24);
            sprintf(s2,"%i",bioM[i].scoreH);
            iText(850,450-i*50-5,s2,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(1130,450-i*50-5,bioH[i].nameH,GLUT_BITMAP_TIMES_ROMAN_24);
            sprintf(s3,"%i",bioH[i].scoreH);
            iText(1350,450-i*50-5,s3,GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }
    else if(difficulty)
    {
        iShowBMP(0,0,"difficulty.bmp");
        iSetColor(0,0,0);
        iCircle(456,515,10,100);
        iCircle(458,418,10,100);
        iCircle(457,306,10,100);
        iCircle(1134,518,10,100);
        iCircle(1138,430,10,100);
        iCircle(456,515,11,100);
        iCircle(458,418,11,100);
        iCircle(457,306,11,100);
        iCircle(1134,518,11,100);
        iCircle(1138,430,11,100);
        iSetColor(255,255,0);
        if(diff==1)
            iFilledCircle(456,515,8,100);
        else if(diff==2)
            iFilledCircle(458,418,8,100);
        else if(diff==3)
            iFilledCircle(457,306,8,100);
        else
            ;
        if(sound)
            iFilledCircle(1134,518,8,100);
        else
            iFilledCircle(1138,430,8,100);
    }
    else if(credits)
    {
        iShowBMP(0,0,"credits.bmp");
    }
    else if(instructions)
    {
        iShowBMP(0,0,"instruct.bmp");
    }
    else if(pause)
    {
        iShowBMP(0,0,"pause.bmp");
    }
}

void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{
    if(home)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
             if(mx>=221 && mx<=539 && my>=287 && my <=363)
            {
                home=false;
                play1=true;
                play2=false;
                playEnd=false;
                difficulty=false;
                hall=false;
                credits=false;
                instructions=false;
                score=0;
                if(diff==1)
                   {
                       pacLife=3;
                       t=240;
                   }
                else if(diff==2)
                    {
                        pacLife=2;
                        t=210;
                    }
                else if(diff==3)
                    {
                        pacLife=1;
                        t=180;
                    }
                else
                    ;
                setCoordinate1();
                pacCellX=15;
                pacCellY=1;
                pac.coX=startMazeX+pacCellX*bricklength;
                pac.coY=startMazeY+(pacCellY)*bricklength;
                initial=true;
                pac.moveRight=false;
                pac.moveLeft=false;
                pac.moveUp=false;
                pac.moveDown=false;
                setDot1();
                dot1[pacCellY][pacCellX]=false;
                dot1[14][16]=false;
                dot1[27][22]=false;
                dot1[7][5]=false;
                dot1[4][28]=false;
                for(int i=0;i<5;i++)
                   dotNum--;
                setBigDot1();
                bigDot1[14][16]=true;
                bigDot1[27][22]=true;
                bigDot1[7][5]=true;
                bigDot1[4][28]=true;
                setGhost1();
            }
            else if(mx>=906 && mx<=1232 && my>=37 && my<=123)
            {
                exit(0);
            }
            else if(mx>=900 && mx<=1232 && my>=282 && my<=357)
            {
                showHighScore();
                 home=false;
                play1=false;
                play2=false;
                playEnd=false;
                difficulty=false;
                hall=true;
                credits=false;
                instructions=false;
            }
            else if(mx>=217 && mx<=541 && my>=166 && my<=244)
            {
                home=false;
                play1=false;
                play2=false;
                playEnd=false;
                difficulty=true;
                hall=false;
                credits=false;
                instructions=false;
            }
            else if(mx>=217 && mx<=547 && my>=40 && my<=121)
            {
                home=false;
                play1=false;
                play2=false;
                playEnd=false;
                difficulty=false;
                hall=false;
                credits=true;
                instructions=false;
            }
            else if(mx>=902 && mx<=1230&& my>=167 && my<=253)
            {
                 home=false;
                play1=false;
                play2=false;
                playEnd=false;
                difficulty=false;
                hall=false;
                credits=false;
                instructions=true;
            }
        }
    }
    else if(difficulty)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=441 && mx<=470 && my>=501 && my<=532)
            {
                diff=1;
            }
            else if(mx>=444 && mx<=473 && my>=402 && my<=434)
            {
                diff=2;
            }
            else if(mx>=440 && mx<=473 && my>=290 && my<=322)
            {
                diff=3;
            }
            else if(mx>=1121 && mx<=1147 && my>=505 && my<=532)
            {
                sound=true;
            }
            else if(mx>=1119 && mx<=1154 && my>=421 && my<=443)
            {
                sound=false;
            }
            else if(mx>=12 && mx<=133 && my>=689 && my<=739)
            {
                home=true;
                play1=false;
                play2=false;
                playEnd=false;
                difficulty=false;
                hall=false;
                credits=false;
                instructions=false;
            }
        }
    }
    else if(play1)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
             if(mx>=1146 && mx<=1408 && my>=107 && my <=186)
            {
                if(nameEntry[0])
                {
                    if(sound)
                        PlaySound("startPlay.wav",NULL,SND_ASYNC);
                    strcpy(finalName,nameEntry);
                    nameEntry[0]='\0';
                    nameIndex=0;
                    home=false;
                    play1=false;
                    play2=true;
                    playEnd=false;
                    difficulty=false;
                    hall=false;
                    credits=false;
                    instructions=false;
                }
            }
            if(mx>=83 && mx<=259 && my>=102 && my <=168)
            {
                nameEntry[0]='\0';
                nameIndex=0;
                home=true;
                play1=false;
                play2=false;
                playEnd=false;
                difficulty=false;
                hall=false;
                credits=false;
                instructions=false;
            }
        }
    }
    else if(playEnd)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=1150 && mx<=1395 && my>=116 && my<=186)
            {
                home=true;
                play1=false;
                play2=false;
                playEnd=false;
                difficulty=false;
                hall=false;
                credits=false;
                instructions=false;
            }
        }
    }
    else if(hall)
    {
         if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=52 && mx<=195 && my>=656 && my<=707)
            {
                home=true;
                play1=false;
                play2=false;
                playEnd=false;
                difficulty=false;
                hall=false;
                credits=false;
                instructions=false;
            }
        }
    }
    else if(play2)
    {
         if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=1005 && mx<=1284 && my>=356 && my<=421)
            {
                home=false;
                play1=false;
                play2=false;
                playEnd=true;
                difficulty=false;
                hall=false;
                credits=false;
                instructions=false;
                appendFile();
                setHighScore();
            }
             if(mx>=1006 && mx<=1288 && my>=214 && my<=290)
             {
                 pause=true;
                 play2=false;
             }
        }
    }
     else if(credits)
    {
         if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=38 && mx<=181 && my>=657 && my<=713)
            {
                home=true;
                play1=false;
                play2=false;
                playEnd=false;
                difficulty=false;
                hall=false;
                credits=false;
                instructions=false;
            }
        }
    }
     else if(instructions)
    {
         if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(mx>=24 && mx<=141 && my>=687 && my<=737)
            {
                home=true;
                play1=false;
                play2=false;
                playEnd=false;
                difficulty=false;
                hall=false;
                credits=false;
                instructions=false;
            }
        }
    }
    else if(pause)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
         {
             if(mx>=1108 && mx<=1390 && my>=129 && my<=223)
             {
                 pause=false;
                 play2=true;
             }
             else if(mx>=103 && mx<=398 && my>=124 && my<=219)
             {
                home=false;
                play1=false;
                play2=false;
                playEnd=true;
                difficulty=false;
                hall=false;
                credits=false;
                instructions=false;
                appendFile();
                setHighScore();
             }
         }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

    }
}

void iKeyboard(unsigned char key)
{
    if(play1)
    {
        if(key!='\b')
        {
            nameEntry[nameIndex]=key;
            nameIndex++;
            nameEntry[nameIndex]='\0';
        }
        else
        {
            if(nameIndex<=0)
                nameIndex=0;
            else
                nameIndex--;
            nameEntry[nameIndex]='\0';
        }
    }
}


void iSpecialKeyboard(unsigned char key)
{

    if(play2)
    {
        if(key == GLUT_KEY_RIGHT)
        {
            initial=false;
            pac.moveRight=true;
            pac.moveLeft=false;
            pac.moveUp=false;
            pac.moveDown=false;

            if(!mazeMap1[pacCellY][pacCellX+1])
            {
                pac.coX+=pacVelocity;
                pac.index++;
                if(pac.index>=4)
                    pac.index=0;
                pacCellX++;
                if(dot1[pacCellY][pacCellX])
                {
                    dotNum--;
                    score+=10;
                }
                dot1[pacCellY][pacCellX]=false;
                frightenedCheck();
            }
            dotCheck();
        }

        if(key == GLUT_KEY_LEFT)
        {
            initial=false;
            pac.moveRight=false;
            pac.moveLeft=true;
            pac.moveUp=false;
            pac.moveDown=false;

            if(!mazeMap1[pacCellY][pacCellX-1])
            {
                pac.coX-=pacVelocity;
                pac.index++;
                if(pac.index>=4)
                    pac.index=0;
                pacCellX--;
                if(dot1[pacCellY][pacCellX])
                {
                    dotNum--;
                    score+=10;
                }
                dot1[pacCellY][pacCellX]=false;
                frightenedCheck();
            }
            dotCheck();
        }

        if(key == GLUT_KEY_UP)
        {
            initial=false;
            pac.moveRight=false;
            pac.moveLeft=false;
            pac.moveUp=true;
            pac.moveDown=false;

            if(!mazeMap1[pacCellY+1][pacCellX])
            {
                pac.coY+=pacVelocity;
                pac.index++;
                if(pac.index>=4)
                    pac.index=0;
                pacCellY++;
                if(dot1[pacCellY][pacCellX])
                {
                    dotNum--;
                    score+=10;
                }
                dot1[pacCellY][pacCellX]=false;
                frightenedCheck();
            }
            dotCheck();
        }

        if(key == GLUT_KEY_DOWN)
        {
            initial=false;
            pac.moveRight=false;
            pac.moveLeft=false;
            pac.moveUp=false;
            pac.moveDown=true;
            if(!mazeMap1[pacCellY-1][pacCellX])
            {
                pac.coY-=pacVelocity;
                pac.index++;
                if(pac.index>=4)
                    pac.index=0;
                pacCellY--;
                if(dot1[pacCellY][pacCellX])
                {
                    dotNum--;
                    score+=10;
                }
                dot1[pacCellY][pacCellX]=false;
                frightenedCheck();
            }
            dotCheck();
        }
    }
}

int main()
{
    iSetTimer(ghostTime,moveGhost);
    iSetTimer(5,deathCheck);
    iSetTimer(1000,timeCheck);
    iSetTimer(1000,frightenedTimeCheck);
    if(sound)
        PlaySound("startPlay.wav",NULL,SND_ASYNC);
    iInitialize(screenLength,screenWidth, "PACMAN");
    return 0;
}
