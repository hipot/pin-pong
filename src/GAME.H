//!данный файл содержит дополнительные интерфейсные модули
//обеспечения игры. Это следующие функции:

void scrkvadrat(struct kvadrat*); //вывод квадрата из поля игры
void clrscrkvadrat(int,int);      //очистка от него
void setka(void);        //вывод сетки из этих квадратов
void music();            //пиканье в игре
int gamover(void);       //функция потери жизни или завершения игры
void New_level(void); //переход на следующий уровень все квадраты сбиты
void show_life();     //отобразить число жизней на экран
void showscore(void);    //отбразить на экран число


//вывод квадрата
void scrkvadrat(struct kvadrat*p)
{
  setfillstyle(SOLID_FILL,p->COL);
  bar(p->x,p->y,p->x+20,p->y+8);
  setcolor(BLACK);
  rectangle(p->x-1,p->y-1,p->x+21,p->y+9);
}


//очистка экрана от квадрата
void clrscrkvadrat(int x,int y)
{
  music();
  setcolor(WHITE);
  int i,j;
  //предусматриваю лишние обращения к памяти
  // в виде структурных переменных   // ¦
  for(i=0;i<=8; i++)                 // ¦
    for(j=0; j<=10; j++)             // ¦
     if(j==8 || j==9)    //<-------------
       {
	if(i!=2 && i!=3 && i!=4 && i!=5)
	 if(x>=st[i][j].x-1 && x<=st[i][j].x+21 &&
	     y>=st[i][j].y-1 && y<=st[i][j].y+9)
	       goto BREAK;
       }
     else
      if(x>=st[i][j].x-1 && x<=st[i][j].x+21 &&
	     y>=st[i][j].y-1 && y<=st[i][j].y+9)
	       goto BREAK;
  BREAK:
  setfillstyle(SOLID_FILL,3);
  bar(st[i][j].x-1,st[i][j].y-1,st[i][j].x+21,st[i][j].y+9);
  win++;
}


/*
  - - - - - - - - - - - -
    - - - - - - - - - -
    - - - - - - - - - -
  - - - - - - - - - - - -
*/
void setka(void)
{
  int i=0,r=140,j=160;
  for(int t=0; t<8;t++)
   {
     for(int e=0; e<10; e++)
       {
	 if(i==8||i==3||i==BLACK||i==7) i++;
	 if(t>1 && t<6)       //память на элементы  8 9 строк 2 3 4 5
	   {                  //выделена но они не используются
	    st[t][e].x=j+25;  //на баги бы не напороться!
	    if (e>7) break;
	   }
	 else
	   st[t][e].x=j;
	 st[t][e].y=r;
	 st[t][e].COL=i;
	 if(i>=getmaxcolor())
	    i=0;
	 else
	    i++;
	 j+=25;
	}
     r+=12;
     j=160;
   }
 for(i=0; i<8; i++)
    for(j=0; j<=10; j++)
      scrkvadrat(&st[i][j]);
}




void New_level(void)
{
  char*st;
  setfillstyle(SOLID_FILL,8);
  bar(110,105,450,370);
  settextstyle(1,HORIZ_DIR,4);
  setcolor(BLUE);
  sprintf(st,"LEVEL %d",level);
  outtextxy(210,210,st);
  printf("\a");
  delay(2000);
  level++;
  if(SPEED==0) SPEED=11;
  else SPEED--;
  win=0;
}



int gamover()         //1-потрачена жизнь, 0-потрачены все жизни
{
  if(life==0)
     {
       char*str;
       setfillstyle(SOLID_FILL,8);
       bar(110,105,450,370);
       settextstyle(1,HORIZ_DIR,4);
       setcolor(1);
       outtextxy(180,190,"GAME OVER!");
       settextstyle(0,HORIZ_DIR,1);
       setcolor(WHITE);
       outtextxy(180,250,"Ваши_очки");
       outtextxy(180,300,"Нажмите_любую_клавишу");
       settextstyle(2,HORIZ_DIR,6);
       sprintf(str,": %li",score);
       setcolor(GREEN);
       outtextxy(260,241,str);
       printf("\a");
       getch();
       score=0;
       win=0;
       life=3;
       SPEED=12;
       level=2;
       return 0;
    }
 if(life!=0)
    {
     setfillstyle(SOLID_FILL,3);
     unsigned ImageSize=imagesize(110,350,450,370);
     void *Image=malloc(ImageSize);
     if(Image!=NULL)
     getimage(110,350,450,370,Image);
     for(int i=0; i<5; i++)
      {
	music();
	bar(110,350,450,370);
	delay(100);
	putimage(110,350,Image,COPY_PUT);
	delay(100);
      }
     life--;
     free(Image);
     show_life();
     return 1;
    }
}

void show_life()
{
  char*str;
  setfillstyle(SOLID_FILL,7);
  settextstyle(2,HORIZ_DIR,6);
  bar(361,77,449,92);
  setcolor(BLACK);
  sprintf(str,"%d",life);
  outtextxy(440,74,str);
}


void showscore(void)
{
  char *scor;
  setfillstyle(SOLID_FILL,7);
  bar(171,77,269,92);
  settextstyle(2,HORIZ_DIR,6);
  setcolor(BLACK);
  sprintf(scor,"%i",score);
  outtextxy(270-textwidth(scor),74,scor);
}


void music()
{
  sound(3412211);
  delay(10);
  nosound();
}