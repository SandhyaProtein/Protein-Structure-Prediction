__kernel void procedure_helper(__global int row,__global int col, __global int trow,__global int tcol)
{
int i=get_global_id(0);
switch (i)
{
case 0:	trow = row;
	tcol = col + 1;
	break;
case 1:	trow = row;
	tcol = col - 1;
	break;
case 2: trow = row - 1;
	tcol = col - 1;
	break;
case 3:	trow = row + 1;
	tcol = col + 1;
	break;
case 4: trow = row - 1;
	tcol = col + 1;
	break;
//case 5:	trow = row + 1;
//	tcol = col - 1;
//	break;
}
}