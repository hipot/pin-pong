//!В данном заголовочном файле приведены
//основные функции движения шарика
void moving(int,int,int); //один шаг движения
void GAME(void);          //условия выполнения этого шага


//движение шара: функция выполняет один шаг движения
void moving(int i,int j,int func)
{
 int xy[2];
 setcolor(3);
 setfillstyle(SOLID_FILL,3);
 fillellipse(i,j,6,6);
 switch(func)
 {
  case 1:
    howfunc=1;
    if(i>110+6 && j<370-6)
      {
       j++;
       i--;
       *(xy)=i;
       *(xy+1)=j;
       }
    else return;
    break;
  case 2:
    howfunc=2;
    if( i>110+6&&j>105+6 )
     {
      j--;
      i--;
      *(xy)=i;
      *(xy+1)=j;
     }
    else return;
    break;
  case 3:
    howfunc=3;
    if( i<450-6 && j>105+6)
     {
     j--;
     i++;
     *(xy)=i;
     *(xy+1)=j;
     }
    else return;
    break;
  case 4:
    howfunc=4;
    if(j<370-6 && i<450-6)
    {
     j++;
     i++;
     *(xy)=i;
     *(xy+1)=j;
    }
    else return;
    break;
  }
 setfillstyle(SOLID_FILL,RED);
 fillellipse(i,j,6,6);
 delay(SPEED);
}




void GAME(void)
{
 int xy[2];
 LV:                           //->метка начала нового уровня
  setfillstyle(SOLID_FILL,3);
  bar(110,105,450,370);
  show_life();
  setka();
 LVN:                          //->метка потери жизни <попытки>
  showscore();
  //задержка до начала игры
  //пока не будет запущен шарик левой кнопкой мыши
  do
  {
    setcolor(3);
    int y=getmx();
    setfillstyle(SOLID_FILL,8);
    if(getmx()>=110 && getmx()+60<=450)
	{
	   bar(getmx(),370-10,getmx()+60,370);
	   *xy=getmx()+30;
	   *(xy+1)=370-16;
	   setfillstyle(SOLID_FILL,RED);
	   fillellipse(xy[0],xy[1],6,6);
	}
    else    //особая перерисовка ракетки если мышь за пределами
      {     //миниэкрана
       if(getmx()<110)
	   {
	     bar(110,370-10,110+60,370);
	     *xy=110+30;
	     *(xy+1)=370-16;
	     setfillstyle(SOLID_FILL,RED);
	     fillellipse(xy[0],xy[1],6,6);
	   }
       if(getmx()+60>450)
	   {
	    bar(450-60,370-10,450,370);
	    *xy=450-30;
	    *(xy+1)=370-16;
	    setfillstyle(SOLID_FILL,RED);
	    fillellipse(xy[0],xy[1],6,6);
	   }
       }
    if(y!=getmx())       //перерисовка ракетки если координата
      {                  //изминилась
      setfillstyle(SOLID_FILL,3);
      bar(110,320-22,450,370);
      }
  if(getmb()==2) {pause(); delay(200);}
  }while(getmb()!=1);
  hidemouse();
  howfunc=3;        //первый полет всегда 3й - слево направо вверх
  for(;;)
  {
  m:
  //движение шарика
  if(howfunc==1)
    if(*xy>110+6 && *(xy+1)<370-6)
	{
	 if(xy[1]<370-6 && getpixel(xy[0],xy[1]+8)!=3
		&& xy[1]+8<370-6)
	  {
	   if(xy[1]>370-20) {howfunc=2; goto m;}
	   clrscrkvadrat(xy[0],xy[1]+8); howfunc=2;
	   score+=10; showscore(); goto m;}
	 if(xy[0]-8>110+6 && getpixel(xy[0]-8,xy[1])!=3)
	   {
	    if(xy[1]>370-20) {howfunc=4; goto m;}
	    clrscrkvadrat(xy[0]-8,xy[1]);
	    howfunc=4; score+=10; showscore(); goto m;}
	 moving(*xy,*(xy+1),howfunc);
	 xy[0]--;
	 xy[1]++;
	}
    else
       {
	if(xy[0]<110+10) howfunc=4;
	if(xy[1]>370-10) { howfunc=2;
			    if(!gamover()) goto LV;
			    else goto LVN;   }
       }
  if(howfunc==4)
   if(xy[0]<450-6 && xy[1]<370-6)
	{
	 if(*(xy+1)<370-6 && getpixel(xy[0],xy[1]+8)!=3 &&
	     xy[1]+8<370-6)
	    {
	      if(xy[1]>370-20){howfunc=3;goto m;}
	      clrscrkvadrat(xy[0],xy[1]+8); howfunc=3;
	      score+=10; showscore(); goto m;}
	 if(*xy<450-6 && getpixel(xy[0]+8,xy[1])!=3 &&
	     xy[0]+8<450-6)
	    {
	      if(xy[1]>370-20) {howfunc=1; goto m;}
	      clrscrkvadrat(xy[0]+8,xy[1]); howfunc=1;
	      score+=10; showscore(); goto m;}
	 moving(*xy,*(xy+1),howfunc);
	 xy[0]++;
	 xy[1]++;
	}
     else
       {

	if(xy[0]>450-10) howfunc=1;
	if(*(xy+1)>370-10) {howfunc=3;
			    if(!gamover()) goto LV;
			    else goto LVN;   }
       }
  if(howfunc==3)
    if(xy[0]<450-6 && xy[1]>105+6)
	{
	 if(getpixel(xy[0]+8,xy[1])!=3 && xy[0]+8<450-6)
	    {
	     clrscrkvadrat(xy[0]+8,xy[1]); howfunc=4;
	     score+=10; showscore(); goto m;}
	 if(getpixel(xy[0],xy[1]-8)!=3 && xy[1]-8>105+6)
	   {
	    clrscrkvadrat(xy[0],xy[1]-8); howfunc=4;
	    score+=10; showscore(); goto m;}
	 moving(*xy,*(xy+1),howfunc);
	 xy[0]++;
	 xy[1]--;
	}
    else
       {
	if(xy[0]>450-10) howfunc=2;
	if(*(xy+1)<105+10) howfunc=4;
       }
  if(howfunc==2)
    if(xy[0]>110+6 && xy[1]>105+6)
	{
	 if(getpixel(xy[0]-8,xy[1])!=3 && xy[0]-8>110+6)
	   {
	    clrscrkvadrat(xy[0]-8,xy[1]); howfunc=3;
	    score+=10; showscore(); goto m;}
	 if(getpixel(xy[0],xy[1]-8)!=3 && xy[1]-8>105+6)
	   {
	    clrscrkvadrat(xy[0],xy[1]-8); howfunc=1;
	    score+=10; showscore(); goto m;}
	 moving(*xy,*(xy+1),howfunc);
	 xy[0]--;
	 xy[1]--;
	}
    else
       {
	if(xy[0]<110+10) howfunc=3;
	if(*(xy+1)<105+10) howfunc=1;
       }
    //ракетка:
    setfillstyle(SOLID_FILL,3);
    bar(110,370-20,450,370);
    setfillstyle(SOLID_FILL,8);
    if(getmx()>=110 && getmx()+60<=450)
       bar(getmx(),370-10,getmx()+60,370);
    else
      {
       if(getmx()<110)
	  bar(110,370-10,110+60,370);
       if(getmx()+60>450)
	  bar(450-60,370-10,450,370);
      }
    //end->ракетка.
  if(getmb()==2) pause();
  if(win!=0 && win==72) {New_level(); goto LV;}
 }

}


