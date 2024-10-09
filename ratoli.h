/*

			RATOLI.H:

		-Llibreria amb rutines de control del Mouse.
		-Ultima modificaci¢: 7-II-1995

*/
#include <dos.h>

/* NOTA:    Valors de retorn de la funci¢ boto():
	-----------------------------------------------
	|  Valor:  |  Esquerra:  |  (Mig:)  |  Dret:  |
	-----------------------------------------------
	|    0     |     NO      |    NO    |   NO    |
	|    1     |     SI      |    NO    |   NO    |
	|    2     |     NO      |    NO    |   SI    |
	|    3     |     SI      |    NO    |   SI    |
	|    4     |     NO      |    SI    |   NO    |
	|    5     |     SI      |    SI    |   NO    |
	|    6     |     NO      |    SI    |   SI    |
	|    7     |     SI      |    SI    |   SI    |
	-----------------------------------------------
*/

union REGS rin,rout;

/*
-----------------------------------------------------------------------------
  INITMOUSE: Inicialitza el mouse.
-----------------------------------------------------------------------------
*/
int InitMouse(void)
{
  rin.x.ax=0;
  int86(0x33,&rin,&rout);
  return (rout.x.ax);            /* Retorna -1 si el mouse s'ha instalat. */																 /*         0 si no instalado*/
}

/*
-----------------------------------------------------------------------------
  MOUSEOFF: Amaga el cursor del mouse.
-----------------------------------------------------------------------------
*/
void mouseoff(void)
{
  rin.x.ax=2;
  int86(0x33,&rin,&rout);
}

/*
-----------------------------------------------------------------------------
  MOUSEON: Fa aparäixer el cursor del mouse.
-----------------------------------------------------------------------------
*/
void mouseon(void)
{
  rin.x.ax=1;
  int86(0x33,&rin,&rout);
}

/*
-----------------------------------------------------------------------------
  EIXX: Retorna la posici¢ horitzontal del mouse (depän de la ressoluci¢ del
    text o dels grÖfics).
-----------------------------------------------------------------------------
*/
int eixx(void)
{
  rin.x.ax=3;
  int86(0x33,&rin,&rout);
  return(rout.x.cx);
}

/*
-----------------------------------------------------------------------------
  EIXY: Retorna la posici¢ vertical del mouse.
-----------------------------------------------------------------------------
*/
int eixy(void)
{
  rin.x.ax=3;
  int86(0x33,&rin,&rout);
  return(rout.x.dx);
}

/*
-----------------------------------------------------------------------------
  BOTO: Retorna l'estat dels botons. Veure la taula del principi per a saber
    els valors exactes.
-----------------------------------------------------------------------------
*/
int boto(void)
{
  rin.x.ax=3;
  int86(0x33,&rin,&rout);
  return(rout.x.bx);
}

/*
-----------------------------------------------------------------------------
  SETMOUSEPOS: Col.loca el cursor del mouse en la posici¢ (x,y).
-----------------------------------------------------------------------------
*/
void SetMousePos(int x, int y)
{
  rin.x.ax=4;
  rin.x.cx=x;
  rin.x.dx=y;
  int86(0x33,&rin,&rout);
}