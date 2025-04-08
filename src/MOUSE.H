/*
	Cool Mouse Unit.
*/

void initmouse()
{
 int	rv;
 asm	mov	ax,0
 asm	int	33h
 asm	mov	rv,ax
 if(!rv)
  {
    cleardevice();
    closegraph();
    printf("There is no mouse on it PC!");
    exit(1);    
  }
}

void showmouse()
{
 asm	mov	ax,1
 asm	int	33h
}
void hidemouse()
{
 asm	mov	ax,2
 asm	int	33h
}
int getmx()
{
 int	rv;
 asm	mov	ax,3
 asm	int	33h
 asm	mov	rv,cx
 return rv;
}
int getmy()
{
 int	rv;
 asm	mov	ax,3
 asm	int	33h
 asm	mov	rv,dx
 return rv;
}
int getmb()
{
 int    rv;
 asm    mov     ax,3
 asm    int     33h
 asm    mov     rv,bx
 return rv;
}
//set mouse in pixel (x,y)
void SetMouseXY(unsigned int x,unsigned int y)
{
 asm mov ax, 0x4
 asm mov cx, x
 asm mov dx, y
 asm int 0x33
}
