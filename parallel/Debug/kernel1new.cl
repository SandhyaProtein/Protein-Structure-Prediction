__kernel void procedure_helper(__global int row,__global int col, __global int trow,__global int tcol,__global int **coordinates,__global int *flag,__global int *cnt)
{
int i=get_global_id(0);
switch(i)
{	case 0:
	trow=row;
	tcol=col+1;	
	break;
	case 1:
	trow=row;
	tcol=col-1;		 	
	break;
	case 2: trow=row-1;
	tcol=col-1;
	break;
	case 3:	trow=row+1;
	tcol=col+1;
	break;
	case 4: trow=row-1;
	tcol=col+1;
	break;
	case 5:	trow=row-1;
	tcol=col+1;
	break;
	}
	int tx,ty;
	cnt[i]=0;flag[i]=0;
	if(cordinates[trow][tcol]==-1 )
	{
	for(tx=trow-1;tx<trow+2;tx++)		
	for(ty=tcol-1;ty<tcol+2;ty++)
	{	if(!((tx==trow-1&&ty==tcol-1)||(tx==trow+1&&ty==tcol+1)))
		if(cordinates[tx][ty]==c)
		cnt[i]++;
	}
	}
	else
	{
	flag[i]=1;
	}
	}	
