/*
┌──────────────────────────────────────────┐
│ !ОКНА И ПОДКЛЮЧЕНИЕ ДВУХ ФАЙЛОВ ИГРЫ ==  │
│ ОСНОВНОЙ   ТЕКСТ   ИГРЫ   "PING-PONG"    │
└──────────────────────────────────────────┘
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <dos.h>
#include <mouse.h>

int SPEED=11;             //скорость движения шара в порядке уменьшения
long score=0;            //очки
int level=2;             //уровни
int life=3;              //жизни <попытки>
int win=0;               //флажок выиграша
int howfunc=0;           //каков полет шара был совершен
void pause(void);        //пауза в игре, используется в gamemain.h

#include "GAME.H"
#include "GAMEMAIN.H"

//!ДЛЯ КНОПОК
struct knopka{
  int x,y;      //левый верхний угол
  char *text;   //текст на кнопке
  int l;        //длина текста
} knp1={110,380,"New_game"},
  knp2={258,380,"помощь"},
  knp3={390,380,"выход"};

inline void vivod(knopka*);                  //вывод кнопки
inline void vivod_utop(knopka*);  //вывод утопленной кнопки
inline void clrofcnopka(knopka*,int);   //очистка от кнопки
void wind0(void);     //начальное окно программы + заставка
void wind1();                     //основное окно программы
void help();                           //помощь в программе
void NEWGAME();    //окно-прерывание - начать ли новую игру
void case_menu();              //меню выбора во время паузы


//вывод кнопки
inline void vivod(knopka*ptr)
{
  settextstyle(0,HORIZ_DIR,1);
  (ptr->l)=textwidth(ptr->text);
  setfillstyle(SOLID_FILL,BLACK);
  bar(ptr->x+10,ptr->y+6,ptr->x+ptr->l+28,ptr->y+25);
  setfillstyle(SOLID_FILL,GREEN);
  bar(ptr->x,ptr->y,ptr->x+20+ptr->l,ptr->y+18);
  setcolor(WHITE);
  outtextxy(ptr->x+10,ptr->y+6,ptr->text);
}


//утопление кнопки
inline void vivod_utop(knopka*ptr)
{
  settextstyle(0,HORIZ_DIR,1);
  setfillstyle(SOLID_FILL,GREEN);
  bar(ptr->x+10,ptr->y,ptr->x+28+ptr->l,ptr->y+18);
  setcolor(WHITE);
  outtextxy(ptr->x+20,ptr->y+6,ptr->text);
}


//очистка от кнопки, где с-цвет фона
inline void clrofcnopka(knopka*ptr,int c)
{
  setfillstyle(SOLID_FILL,c);
  bar(ptr->x-3,ptr->y,ptr->x+ptr->l+28,ptr->y+27);
}

//начальное окно и заставка
void wind0(void)
{
  setfillstyle(SOLID_FILL,7);
  setlinestyle(SOLID_LINE,1,3);
  settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
  line(174,141,174,331);
  line(175,331,454,331);
  bar(175,140,455,330);
  outtextxy(210,160,"Игровая");
  outtextxy(273,160,"программа");
  setcolor(RED);
  settextstyle(8,HORIZ_DIR,2);
  outtextxy(211,165,"PING-PONG");
  settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
  setcolor(WHITE);
  outtextxy(210,230,"разработал");
  outtextxy(297,230,"cтудент");
  outtextxy(357,230,"Чебан");
  outtextxy(402,230,"В");
  outtextxy(414,230,"В");
  settextstyle(2,HORIZ_DIR,4);
  outtextxy(210,240,"(c)2005");
  knopka knp_1={230,300,"Ok"};
  knopka knp_2={320,300,"выход"};
  vivod(&knp_1);
  vivod(&knp_2);
  unsigned int ImageSize=imagesize(170,140,455,334);
  void *Image=malloc(ImageSize);
  if(Image!=NULL)
    getimage(170,140,455,334,Image);
  cleardevice();
  delay(100);
  int x;
  for(int tmp=-300;tmp<=170; tmp+=2)
     if(Image!=NULL && !kbhit())
       putimage(tmp,140,Image,COPY_PUT);
     else
       {
	cleardevice();
	putimage(170,140,Image,COPY_PUT);
	break;
       }
  free(Image);
  SetMouseXY(getmaxx()/2,getmaxy()/2);
  showmouse();
  for(;;)
  {
   if( getmx()>=320 && getmx()<=(320+knp_2.l+20) &&
      getmy()>=300 && getmy()<=300+18 && getmb()==1 )
      {
	clrofcnopka(&knp_2,7);
	vivod_utop(&knp_2);
	delay(100);
	exit(0);
      }
   if(getmx()>=230 && getmx()<=(230+knp_1.l+20) &&
      getmy()>=300 && getmy()<=300+18 && getmb()==1)
      {
	clrofcnopka(&knp_1,7);
	vivod_utop(&knp_1);
	delay(100);
	hidemouse();
	wind1();
      }
  }
}


void wind1(void)
{
  setfillstyle(SOLID_FILL,7);
  setlinestyle(SOLID_LINE,1,3);
  line(99,71,99,411);
  line(99,411,519,411);
  bar(100,70,520,410);
  setfillstyle(SOLID_FILL,8);
  bar(110,105,450,370);    //экран->цвета 8 и 3
  setcolor(BLACK);
  setlinestyle(SOLID_LINE,1,1);
  line(109,105,109,371);
  line(109,371,450,371);
  line(109,104,451,104);
  line(451,371,451,105);
  vivod(&knp1);
  vivod(&knp2);
  vivod(&knp3);
  setcolor(BLACK);
  settextstyle(7,HORIZ_DIR,4);
  char *text[9]={"P","I","N","G"," ","P","O","N","G"};
  int j=0,i=100;
  for(i=100;i<100+29*9;i+=29)
   {
      outtextxy(474,i,text[j]);
      j++;
   }
  //score:
  setcolor(WHITE);
  settextstyle(2,HORIZ_DIR,6);
  outtextxy(110,75,"Score:");
  setlinestyle(SOLID_LINE,1,1);
  rectangle(170,76,270,93);
  //попытки
  outtextxy(313,75,"Life:");
  rectangle(360,76,450,93);
  showmouse();
  for(;;)
  {
   if(getmx()>=knp2.x && getmx()<=(knp2.x+20+knp2.l) &&
      getmy()>=knp2.y && getmy()<=(knp2.y+18) && getmb()==1)
      {
	 hidemouse();
	 clrofcnopka(&knp2,7);
	 vivod_utop(&knp2);
	 delay(100);
	 clrofcnopka(&knp2,7);
	 vivod(&knp2);
	 help();
      }
   if(getmx()>=knp3.x && getmx()<=(knp3.x+20+knp3.l) &&
      getmy()>=knp3.y && getmy()<=(knp3.y+18) && getmb()==1)
     {
	hidemouse();
	clrofcnopka(&knp3,7);
	vivod_utop(&knp3);
	delay(100);
	exit(1);
     }
   if(getmx()>=knp1.x && getmx()<=(knp1.x+20+knp1.l) &&
      getmy()>=knp1.y && getmy()<=(knp1.y+18) && getmb()==1)
     {
	hidemouse();
	clrofcnopka(&knp1,7);
	vivod_utop(&knp1);
	delay(100);
	clrofcnopka(&knp1,7);
	vivod(&knp1);
	delay(100);
	GAME();
     }
 }
}



void help(void)
{
  unsigned ImageSize=imagesize(48,48,355,355);
  void *Image=malloc(ImageSize);
  if(Image!=NULL)
    getimage(48,48,355,355,Image);
  setcolor(WHITE);
  setlinestyle(SOLID_LINE,1,3);
  line(49,51,49,350);
  line(49,351,354,351);
  setfillstyle(SOLID_FILL,7);
  settextstyle(0,HORIZ_DIR,1);
  setlinestyle(SOLID_LINE,1,1);
  bar(50,50,355,350);
  setcolor(RED);
  outtextxy(140,52,"Игра_PING_PONG");
  setcolor(WHITE);
  outtextxy(52,80,"Движение_ракетки_осуществляется_мышкой");
  outtextxy(52,90,"Чтобы_начать_игру_необходимо_нажать");
  outtextxy(52,100,"на_кнопку_New_game");
  outtextxy(52,120,"Чтобы_воспользоваться_меню_во_время");
  outtextxy(52,130,"игры_либо_войти_в_режим_паузы");
  outtextxy(52,140,"необходимо_щелкнуть_правую_кнопку_мыши");
  outtextxy(52,160,"Чтобы_отключить_паузу_необходимо");
  outtextxy(52,170,"щелкнуть_мышкой_в_поле_миниэкрана_игры");
  outtextxy(52,190,"Следует_не_допускать_падение_шарика_на");
  outtextxy(52,200,"нижнюю_стенку");
  outtextxy(52,220,"У_вас_три_попытки_пропустить_шарик");
  outtextxy(52,230,"Усложнее_игры_состоит_в_увеличеннии");
  outtextxy(52,240,"скорости_движения_шарика");
  outtextxy(52,260,"Игру_разработал_студент_Чебан_В_В");
  outtextxy(52,270,"в_виде_курсового_проектирования");
  knopka knp={175,320,"Ok"};
  vivod(&knp);
  showmouse();
  for(;;)
   if(getmx()>=knp.x && getmx()<=(knp.x+20+knp.l) &&
      getmy()>=knp.y && getmy()<=(knp.y+18) && getmb()==1)
      {
	 hidemouse();
	 clrofcnopka(&knp,7);
	 vivod_utop(&knp);
	 putimage(48,48,Image,COPY_PUT);
	 delay(100);
	 free(Image);
	 showmouse();
	 return;
     }
}


//функция запроса начать ли новую игру
void NEWGAME()
{
  unsigned ImageSize=imagesize(158,149,385,262);
  void *Image=malloc(ImageSize);
  if(Image!=NULL)
    getimage(158,149,385,262,Image);
  setlinestyle(SOLID_LINE,1,3);
  line(159,151,159,260);
  line(159,261,384,261);
  setfillstyle(SOLID_FILL,7);
  settextstyle(0,HORIZ_DIR,1);
  setlinestyle(SOLID_LINE,1,1);
  bar(160,150,385,260);
  outtextxy(200,170,"Начать");
  outtextxy(257,170,"новую");
  outtextxy(310,170,"игру");
  settextstyle(2,HORIZ_DIR,5);
  outtextxy(343,165,",");
  settextstyle(2,HORIZ_DIR,3);
  outtextxy(339,182,"?");
  outtextxy(340,185,".");
  settextstyle(0,HORIZ_DIR,1);
  outtextxy(200,185,"закончить");
  outtextxy(280,185,"текущюю");
  knopka knp={280,230,"Нет"};
  knopka _knp={200,230,"Да"};
  vivod(&_knp);
  vivod(&knp);
  showmouse();
  for(;;)
  {
   if(getmx()>=knp.x && getmx()<=(knp.x+20+knp.l) &&
      getmy()>=knp.y && getmy()<=(knp.y+18) && getmb()==1)
      {
	hidemouse();
	clrofcnopka(&knp,7);
	vivod_utop(&knp);
	delay(100);
	putimage(158,149,Image,COPY_PUT);
	delay(100);
	free(Image);
	showmouse();
	return;
     }
   if(getmx()>=_knp.x && getmx()<=(_knp.x+20+_knp.l) &&
      getmy()>=_knp.y && getmy()<=(_knp.y+18) && getmb()==1)
      {
	hidemouse();
	clrofcnopka(&_knp,7);
	vivod_utop(&_knp);
	delay(250);
	free(Image);
	/*все игровые параметры сбрасываем в DEFAULT
	 и начинаем новую игру...*/
	score=0;
	life=3;
	level=2;
	win=0;
	SPEED=11;
	GAME();
     }
 }
}

//пауза игры
void pause(void)
{
  int x=getmx(),y=getmy();   //запоминаем координаты мыши
  setcolor(BLACK);      //для корректного выхода из паузы
  settextstyle(0,HORIZ_DIR,1);
  unsigned ImageSize=imagesize(250,235,300,243);
  void *Image=malloc(ImageSize);
  if(Image!=NULL)
    getimage(250,235,300,243,Image);
  outtextxy(250,235,"Пауза");
  delay(20);
  SetMouseXY(250,335);
  for(int i=0; i<9; i++)
     showmouse();
  case_menu();
  SetMouseXY(x,y);
  hidemouse();
  putimage(110+140,105+130,Image,COPY_PUT);
  free(Image);
}


void case_menu()
{
  for(;;)
  {
   if(getmx()>=knp2.x && getmx()<=(knp2.x+20+knp2.l) &&
      getmy()>=knp2.y && getmy()<=(knp2.y+18) && getmb()==1)
      {
	 hidemouse();
	 clrofcnopka(&knp2,7);
	 vivod_utop(&knp2);
	 delay(100);
	 clrofcnopka(&knp2,7);
	 vivod(&knp2);
	 help();
       }
   if(getmx()>=knp3.x && getmx()<=(knp3.x+20+knp3.l) &&
      getmy()>=knp3.y && getmy()<=(knp3.y+18) && getmb()==1)
      {
	 hidemouse();
	 clrofcnopka(&knp3,7);
	 vivod_utop(&knp3);
	 delay(100);
	 exit(1);
      }
   if(getmx()>=knp1.x && getmx()<=(knp1.x+20+knp1.l) &&
      getmy()>=knp1.y && getmy()<=(knp1.y+18) && getmb()==1)
     {
	 hidemouse();
	 clrofcnopka(&knp1,7);
	 vivod_utop(&knp1);
	 delay(100);
	 clrofcnopka(&knp1,7);
	 vivod(&knp1);
	 delay(100);
	 NEWGAME();
     }
  if(getmx()>110 && getmx()<450 &&
     getmy()>105 && getmy()<370 && getmb()==1) return;
 }

}


void main()
{
  //инициализация мыши и графического режима
  initmouse();
  int gdriver=DETECT,gmode,res;
  initgraph(&gdriver,&gmode,"");
  res=graphresult();
  if(res !=grOk)
  {
   printf("Graphics error:%s",graphresult());
   printf("\nPress any key to halt:");
   getch();
   exit(1);
  }
  wind0();     //начальное окно вызывает последующее
}

/*
┌──────────────────────────────────────┐
│!КОНЕЦ АЛГОРИТМА,  И ВСЕ НЕ ТАК УЖ И  │
│СЛОЖНО.  ВСЕГО  ВАМ   ХОРОШЕГО   8-)  │
└──────────────────────────────────────┘
*/
