// TriangularLattice.cpp : Defines the entry point for the console application.
//#include"stdafx.h"
#include "stdafx.h"
#include<stdlib.h>
#include<gl/glut.h>
#include<math.h>
#include<gl/glu.h>
#include<windows.h>
#include<gl/glu.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<CL/cl.h>
#include<conio.h>

#define pi 3.1415926
#define MAX 500
#define moves 6
#define populationSize 30
#define ISEMPTY printf("\n Not a nice path\n");
#define MAX_SOURCE_SIZE (0X100000)

int CurrentWidth, CurrentHeight, dif;

FILE *fptr, *fptrI;
int row, col, x, y;
char str[MAX], res[100], val[2];
short int k, l = 0, maxRow, maxCol, minRow, Efinal[2], minCol, cordinates[(2 * MAX)][(2 * MAX)];
char direction[(2 * MAX)][(2 * MAX)];

struct Energy_
{
	int i;
	int energy;
}Energy[populationSize], tmp;

struct node 
{
	//structure for storing the result
	short int x;
	short int y;
	short int v;
	short int index;
	char nxtMov;
	struct node *next;

};
struct node *newnode, *ptr, *temp;
struct node *first[populationSize], *last[populationSize], *tmpFirst[2], *tmpLast[2];

struct EnergyVar
{
	//Energy variation coordinates
	short int x1, x2, y1, y2;
	struct EnergyVar *next;
};
struct EnergyVar *newnodeE, *ptrE, *tempE;
struct EnergyVar *firstE[populationSize], *lastE[populationSize], *tmpFirstE[2], *tmpLastE[2];


struct node* create_node(short int x, short int y, short int v)//,char nxtMov)
{//allocate a node to result

	newnode = (struct node *)malloc(sizeof(struct node));
	if (newnode == NULL)
	{
		printf("\nMemory was not allocated");
		return 0;
	}
	else
	{
		newnode->x = x;
		newnode->y = y;
		newnode->v = v;
		return newnode;
	}
}

void insert_node(short int x, short int y, short int v)//,char nxtMov)
{	//add a node
	newnode = create_node(x, y, v);//,nxtMov);
	if (first[k] == last[k] && last[k] == NULL)
	{
		first[k] = last[k] = newnode;
		first[k]->next = NULL;
		last[k]->next = NULL;
	}
	else
	{
		last[k]->next = newnode;
		last[k] = newnode;
		last[k]->next = NULL;
	}

}
void insert_nodefinal(short int x, short int y, short int v)//,char nxtMov)
{	//keep the final best 2 nodes
	newnode = create_node(x, y, v);//,nxtMov);
	if (tmpFirst[l] == tmpLast[l] && tmpLast[l] == NULL)
	{
		tmpFirst[l] = tmpLast[l] = newnode;
		tmpFirst[l]->next = NULL;
		tmpLast[l]->next = NULL;
	}
	else
	{
		tmpLast[l]->next = newnode;
		tmpLast[l] = newnode;
		tmpLast[l]->next = NULL;
	}

}
struct EnergyVar* create_nodeE(short int x1, short int y1, short int x2, short int y2)//,char nxtMov)
{
	newnodeE = (struct EnergyVar *)malloc(sizeof(struct EnergyVar));
	if (newnodeE == NULL)
	{
		printf("\nMemory was not allocated");
		return 0;
	}
	else
	{
		newnodeE->x1 = x1;
		newnodeE->y1 = y1;
		newnodeE->x2 = x2;
		newnodeE->y2 = y2;
		//  newnode[k]->nxtMov =nxtMov;
		return newnodeE;
	}
}

void insert_nodeE(short int x1, short int y1, short int x2, short int y2)//,char nxtMov)
{
	newnodeE = create_nodeE(x1, y1, x2, y2);//,nxtMov);
	if (firstE[k] == lastE[k] && lastE[k] == NULL)
	{
		firstE[k] = lastE[k] = newnodeE;
		firstE[k]->next = NULL;
		lastE[k]->next = NULL;
	}
	else
	{
		lastE[k]->next = newnodeE;
		lastE[k] = newnodeE;
		lastE[k]->next = NULL;
	}

}

void insert_nodeEFinal(short int x1, short int y1, short int x2, short int y2)//,char nxtMov)
{
	newnodeE = create_nodeE(x1, y1, x2, y2);//,nxtMov);
	if (tmpFirstE[l] == tmpLastE[l] && tmpLastE[l] == NULL)
	{
		tmpFirstE[l] = tmpLastE[l] = newnodeE;
		tmpFirstE[l]->next = NULL;
		tmpLastE[l]->next = NULL;
	}
	else
	{
		tmpLastE[l]->next = newnodeE;
		tmpLastE[l] = newnodeE;
		tmpLastE[l]->next = NULL;
	}


}
void display(int best)
{	//display the result
	printf("%dth possibility\n", k + 1);
	if (first[k] == NULL)
	{
		ISEMPTY;
		//printf("\n:No nodes in the list to display\n");
	}
	else
	{
		if (best == 0)
		{
			/*for (ptr = first[k];ptr != NULL;ptr = ptr->next)
			{

			//    printf("(%d,%d) %c\t", ptr->x,ptr->y,ptr->nxtMov);
			}*/
		}
		else
		{
			tmpLast[l] = tmpFirst[l] = NULL;
			tmpLastE[l] = tmpFirstE[l] = NULL;
			for (ptr = first[k]; ptr != NULL; ptr = ptr->next)
			{

				printf("(%d,%d) %c\t", ptr->x, ptr->y, ptr->nxtMov);
				insert_nodefinal(ptr->x, ptr->y, ptr->v);

				tmpLast[l]->nxtMov = ptr->nxtMov;
				tmpLast[l]->index = last[k]->index;

			}
			for (ptrE = firstE[k]; ptrE != NULL; ptrE = ptrE->next)
			{

				insert_nodeEFinal(ptrE->x1, ptrE->y1, ptrE->x2, ptrE->y2);

			}
		}




	}
	printf("\n");

}


void calculateEnergy()
{
	short int i, j;
	firstE[k] = NULL;
	lastE[k] = NULL;
	for (i = minRow; i <= maxRow; i++)
	for (j = minCol; j <= maxCol; j++)
	{
		if (cordinates[i][j] == 1 && cordinates[i][j + 1] == 1 && j != maxCol)
		{
			if ((direction[i][j] != 'E' && direction[i][j + 1] != 'W'))
			{
				Energy[k].energy++;
				//		printf("ptew (%d,%d) to (%d,%d) %d %c %c\t", i-MAX+1,j-MAX+1, i-MAX+1,j+1-MAX+1,Energy[k].energy,direction[i][j],direction[i][j+1]);
				insert_nodeE(i - MAX + 1, j - MAX + 1, i - MAX + 1, j + 1 - MAX + 1);
			}
		}
		if (cordinates[i][j] == 1 && cordinates[i + 1][j] == 1 && i != maxRow)
		{
			if ((direction[i][j] != 'N' && direction[i + 1][j] != 'S'))
			{
				Energy[k].energy++;
				//		printf("ptsn (%d,%d) to (%d,%d) %d %c %c\t",  i-MAX+1,j-MAX+1, i+1-MAX+1,j-MAX+1,Energy[k].energy,direction[i][j],direction[i+1][j]);
				insert_nodeE(i - MAX + 1, j - MAX + 1, i + 1 - MAX + 1, j - MAX + 1);
			}
		}
		if (cordinates[i][j] == 1 && cordinates[i + 1][j + 1] == 1 && j != maxCol && i != maxRow)
		{
			if ((direction[i][j] != 'y' && direction[i + 1][j + 1] != 'x'))
			{
				Energy[k].energy++;
				//		printf("ptew (%d,%d) to (%d,%d) %d %c %c\t", i-MAX+1,j-MAX+1, i-MAX+1,j+1-MAX+1,Energy[k].energy,direction[i][j],direction[i][j+1]);
				insert_nodeE(i - MAX + 1, j - MAX + 1, i + 1 - MAX + 1, j + 1 - MAX + 1);
			}
		}
		if (cordinates[i][j] == 1 && cordinates[i + 1][j - 1] == 1 && i != maxRow &&j != maxCol)
		{
			if ((direction[i][j] != 'a' && direction[i + 1][j - 1] != 'z'))
			{
				Energy[k].energy++;
				//		printf("ptsn (%d,%d) to (%d,%d) %d %c %c\t",  i-MAX+1,j-MAX+1, i+1-MAX+1,j-MAX+1,Energy[k].energy,direction[i][j],direction[i+1][j]);
				insert_nodeE(i - MAX + 1, j - MAX + 1, i + 1 - MAX + 1, j - 1 - MAX + 1);
			}
		}


	}

}

int findMaxVariation(int size, short int E[])
{
	short int i;
	int maxVar = 0;
	//printf("%d",E[maxVar]);
	for (i = 1; i<size; i++)
	{
		if (E[maxVar]<E[i])
			maxVar = i;

	}
	return maxVar;

}
int findMaxVariation1(int size)
{
	short int i;
	int maxVar = 0;
	//printf("%d",E[maxVar]);
	for (i = 1; i<size; i++)
	{
		if (Energy[maxVar].energy<Energy[i].energy)
			maxVar = i;
		Energy[i].i = i;
	}
	
	return maxVar;

}

void sortEnergySt()
{
	int i, j;
	for (i = 0; i<populationSize; i++)
	for (j = i + 1; j<populationSize; j++)
	{
		if (Energy[i].energy<Energy[j].energy)
		{
			tmp.i = Energy[i].i;
			tmp.energy = Energy[i].energy;
			Energy[i].i = Energy[j].i;
			Energy[i].energy = Energy[j].energy;
			Energy[j].energy = tmp.energy;
			Energy[j].i = tmp.i;
		}
	}

	for (i = 0; i<10; i++)
	{
		for (ptr = first[Energy[i].i]; ptr != NULL; ptr = ptr->next)
		{


			fprintf(fptr, "(%d,%d) %c\t~", ptr->x, ptr->y, ptr->nxtMov);

		}
		fprintf(fptr, "%d %s", Energy[i].energy, "||\n");
	}
}


void procedure(int Case)
{
	short int i, j, row, col, trow, tcol, tx, ty, xIn, r, posMov[moves], c;
	char nxtMov;
	short int cnt[moves], flag[moves];
	int strIndex;
	double start,end,time;
	start=clock();
	
	while (k<populationSize)
	{//	fprintf(fptr,"\n%dth pros\n",k);
		first[k] = NULL; last[k] = NULL;
		for (i = 0; i<(2 * MAX); i++)
		for (j = 0; j<(2 * MAX); j++)
		{
			cordinates[i][j] = -1;
			direction[i][j] = 'H';
		}
		


		//Initialization
		//startP oint = latticeCenter
		// PointsList:add(startP oint)
		row = MAX - 1;
		col = MAX - 1;
		trow = -1; //san
	    tcol =-1; //san
		cordinates[row][col] = str[0] - '0';
		//printf("%d",cordinates[row][col]);
		minCol = col;
		insert_node(row - MAX + 1, col - MAX + 1, cordinates[row][col]);//,'H');
		//secondP oint = eastNeighbour(startP oint)
		// PointsList:add(secondP oint)

		nxtMov = 'E';
		last[k]->nxtMov = nxtMov;
		last[k]->index = 0;
		direction[row][col] = nxtMov;
		//='
		col = col + 1;
		cordinates[row][col] = str[1] - '0';

		insert_node(row - MAX + 1, col - MAX + 1, cordinates[row][col]);//,nxtMov);
		last[k]->index = 1;
		minRow = maxRow = row;
		maxCol = col;


		for (strIndex = 2; strIndex<strlen(str); strIndex++)
		{
			i = 0;
			switch (Case)
			{
			case 1:
				if (str[strIndex] == '1')
					c = 1;
				else
					c = 0;
				break;
			case 0:
				if (str[strIndex] == '1')
					c = 1;
				else
					c = -2;
				break;
			}
			/*for (i = 0; i<moves; i++)//san /*
			{
				switch (i)
				{
				case 0:
					trow = row;
					tcol = col + 1;
					break;
				case 1:
					trow = row;
					tcol = col - 1;
					break;
						
					/*case 2:
					trow=row+1;
					tcol=col;
					break;
					case 3:
					trow=row-1;
					tcol=col;
					break;		 //--end comment here
						

					case 2: trow = row - 1;
					tcol = col - 1;
					break;
					case 3:	trow = row + 1;
						tcol = col + 1;
						break;
					case 4: trow = row - 1;
						tcol = col + 1;
						break;
					case 5:	trow = row - 1;
						tcol = col + 1;
						break;
			} 
			//}  //san*/
				
					//we will try and run this for loop in a kernel - kernel1.cl
			FILE *fp;
			char *source_str;
			size_t source_size;
			fp = fopen("kernel1.cl", "r");
			if (!fp)
			{
				fprintf(stderr, "Failed to load kernel");
				getchar();
				exit(1);
			}
			source_str = (char*)malloc(MAX_SOURCE_SIZE);
			source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
			fclose(fp);

			cl_platform_id platform_id = NULL;
			cl_device_id device_id = NULL;
			cl_uint ret_num_devices;
			cl_uint ret_num_platforms;
			cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);

			ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

			cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
			cl_command_queue command_queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &ret);
		
			// sandhya	
			cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(short int), NULL, &ret);
			cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,sizeof(short int), NULL, &ret);
			cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(short int), NULL, &ret);
			cl_mem d_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(short int), NULL, &ret);
			
			// san	
		
			/*/cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int), NULL, &ret);
			cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,sizeof(int), NULL, &ret);
			cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int), NULL, &ret);
			cl_mem d_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int), NULL, &ret);
			
			// san */

			ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, row*sizeof( short int),(void *) row, 0, NULL, NULL);
			ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, col*sizeof(short int), (void *)col, 0, NULL, NULL);
			cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size, &ret);
			ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
			cl_kernel kernel = clCreateKernel(program, "procedure_helper", &ret);
			ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
			ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (short int *)&b_mem_obj);
			ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (int *)&c_mem_obj);
			ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (int *)&d_mem_obj);

			size_t global_item_size = 1;
			size_t local_item_size = 10;

			cl_event event;
			ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, &event);
			cl_ulong time_start; 
			cl_ulong time_stop;
			double total_time;
			ret = clFinish(command_queue);
	end=clock();
		//clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
		//clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_stop), &time_stop, NULL);
			ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, trow*sizeof(short int), (void *)trow, 0, NULL, NULL);	//san	
			ret = clEnqueueReadBuffer(command_queue, d_mem_obj, CL_TRUE, 0, tcol*sizeof(short int), (void *)tcol, 0, NULL, NULL); //san
			//total_time = (double)(time_stop - time_start);
		//total_time /= 1000000;
			time=(end-start)/CLOCKS_PER_SEC;
			
		//	printf("\nThe free energy E* is  %d \t ",Energy[k].energy);
			printf("\nTime taken for kernel execution is =%f msec",time);
			printf("\nDone");
	
			
			getchar();
			ret = clFlush(command_queue);

			ret = clReleaseKernel(kernel);
			ret = clReleaseProgram(program);
			ret = clReleaseMemObject(a_mem_obj);
			ret = clReleaseMemObject(b_mem_obj);
			ret = clReleaseMemObject(c_mem_obj);
			ret = clReleaseMemObject(d_mem_obj);
			ret = clReleaseCommandQueue(command_queue);
			ret = clReleaseContext(context);
			
				cnt[i] = 0; flag[i] = 0;
				// san  find the suitable coordinate  replaced trow with row and tcol with col
				if (cordinates[trow][tcol] == -1)
				{
					for (tx = trow - 1; tx<trow + 2; tx++)
					for (ty = tcol - 1; ty<tcol + 2; ty++)
					{
						if (!((tx == trow - 1 && ty == tcol - 1) || (tx == trow + 1 && ty == tcol + 1)))
						if (cordinates[tx][ty] == c)
							cnt[i]++;
					}
				}
				else
				{
					flag[i] = 1;

				}

			}
			//find max cnt index

			xIn = 0;//yIn=0;
			while (flag[xIn] == 1)
			{
				if (xIn<moves)
					xIn++;
			}
			if (xIn<moves)
			{

				for (i = 0; i<moves; i++)
				if (cnt[i]>cnt[xIn] && flag[i] != 1)
				{
					xIn = i;

				}
				//	printf("MAX CNT IN %d\n",xIn);
				j = 0;
				for (i = xIn; i<moves; i++)
				if (cnt[i] == cnt[xIn] && flag[i] != 1)
				{
					posMov[j++] = i;
					//printf("%d\n",posMov[j-1]);
				}
				else
					posMov[i] = -1;

				r = rand() % j;
				switch (posMov[r])
				{
				case 0:	col = col + 1; nxtMov = 'E';
					break;
				case 1: col = col - 1; nxtMov = 'W';
					break;
					/*	case 2: row=row+1;nxtMov='N';
					break;
					case 3: row=row-1;nxtMov='S';
					break;
					*/
				case 2: row = row - 1; col = col - 1; nxtMov = 'x';
					break;
				case 3: row = row + 1; col = col + 1; nxtMov = 'y';
					break;

				case 4: row = row - 1; col = col + 1; nxtMov = 'z';
					break;
				case 5: row = row + 1; col = col - 1; nxtMov = 'a';
					break;

				}
				cordinates[row][col] = str[strIndex] - '0';
				last[k]->nxtMov = nxtMov;
				direction[last[k]->x + MAX - 1][last[k]->y + MAX - 1] = nxtMov;
				//	fprintf(fptr,"coordinates %d %d %d \n",cordinates[row][col],row-MAX+1,col-MAX+1);
				insert_node(row - MAX + 1, col - MAX + 1, cordinates[row][col]);//,nxtMov);

				last[k]->index = strIndex;
				if (minRow>row)
					minRow = row;
				if (minCol>col)
					minCol = col;
				if (maxRow<row)
					maxRow = row;
				if (maxCol<col)
					maxCol = col;
			}
			else
			{
				//	printf("\n Not a favourable move\nFurther moves not possible\n");
				first[k] = NULL;
				break;
			}

		}

		last[k]->nxtMov = 'H';
		direction[row][col] = 'H';
		//display(0);

		if (strIndex<strlen(str))
			Energy[k].energy = -1;
		else
		{
			Energy[k].energy = 0;
			direction[row][col] = 'H';
			calculateEnergy();
				printf("\nEnergy Variation %d\n",Energy[k].energy);
		}

		k++;
	//}  //sandhya

		k = findMaxVariation1(populationSize);
	//printf("\nThe maximum energy variation Path\n");
		printf("\nThe free energy E* is  %d \t ",Energy[k].energy);
	display(1);
	printf("\nk=%dth Energy Variation %d\n", k, Energy[k].energy);
	Efinal[l] = Energy[k].energy;
	sortEnergySt();
	l++;
}
void lineh(int x, int y, int x2)
{	//Horizontal line

	glBegin(GL_LINES);
	glLineWidth(4.0);
	glVertex2i(x, y);
	glVertex2i(x2, y);
	glEnd();
}
void linev(int x, int y, int y2)
{	//Vertical line
	glBegin(GL_LINES);
	glLineWidth(1.0);
	glVertex2i(x, y);
	glVertex2i(x, y2);
	glEnd();
}
void line(int x1, int y1, int x2, int y2)
{	// line
	glBegin(GL_LINES);
	glLineWidth(1.0);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}
void color(float red, float green, float blue)
{	//for color
	glColor3f(red, green, blue);
}
void points(float x, float y)
{	//to draw a point
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}
void Polygon(int x1, int y1, int x2, int y2)
{	//only for square or rectangle
	glBegin(GL_POLYGON);
	glVertex2i(x1, y1);
	glVertex2i(x1, y2);
	glVertex2i(x2, y2);
	glVertex2i(x2, y1);
	glEnd();
}

void printText(float x, float y, int font_size, char *string)
{//for displaying the text
	int len, j;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	if (font_size == 10)
	for (j = 0; j < len; j++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[j]);
	}
	if (font_size == 12)
	for (j = 0; j < len; j++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[j]);
	}
	if (font_size == 18)
	for (j = 0; j < len; j++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[j]);
	}
}
void DrawCircle(float x_pt, float y_pt, float radius, int num_segments)
{
	int ii;
	float angle, x, y;
	for (ii = 0; ii < num_segments; ii++)
	{	//formula used arc_length=radius*angle
		angle = 2.0 * pi * float(ii) / float(num_segments);//get the current angle 

		x = radius * cosf(angle);//calculate the x component 
		y = radius * sinf(angle);//calculate the y component 

		glVertex2f(x + x_pt, y + y_pt);//output vertex 

	}
	

	glEnd();
}
	
void mouse2(int x, int y)
{//passive mouse function within the Home page
	color(1, 0, 0);
	printText(x, y, 10, val);
	glutPostRedisplay();
	Sleep(500);
	glutSwapBuffers();
	glFlush();
}

void myInit(void)
{//Setting Background Color
	glClearColor(0.7, 0.7, 0.6, 0);
	glLoadIdentity();
}
void Reshape(int width, int height)
{  //othr pages 
	CurrentWidth = width;
	CurrentHeight = height;
	dif = 0;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, CurrentWidth, CurrentHeight);
	y = CurrentHeight / 2;
	x = CurrentWidth / 2;
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void circle(int y, int x)
{
	glBegin(GL_POLYGON);
	DrawCircle(x, y, 5, 10);
}


void Graph_page(void)
{//for displaying front page and then creating a new window aftr few delay
	int q = 0;
	glClear(GL_COLOR_BUFFER_BIT);

	l = findMaxVariation(2, Efinal);

	glClearColor(1, 1, 1, 1);
	glBegin(GL_POLYGON);
	color(0, 1, 0);
	DrawCircle(y, x, 9, 10);
	color(0, 0, 0);

	for (ptr = tmpFirst[l]; ptr != NULL; ptr = ptr->next)
	{
		if (ptr == tmpFirst[l])
		{
			glBegin(GL_POLYGON);
			color(0, 0, 0);
			DrawCircle(y + (ptr->y * 20), x + (ptr->x * 20), 6, 10);
		}
		if (ptr == tmpLast[l])
		{
			glBegin(GL_POLYGON);
			color(0, 1, 1);
			DrawCircle(y + (ptr->y * 20), x + (ptr->x * 20), 7, 10);
		}

		if (ptr->v == 1)
			color(1, 0, 0);
		else
			color(1, 0.5, 0.5); //(0,0,1) for blue
		circle(x + (ptr->x * 20), y + (ptr->y * 20));
		color(0, 0, 0);
		if (ptr->nxtMov == 'E')
			lineh(y + (ptr->y * 20) + 5, x + (ptr->x * 20), y + (ptr->y * 20) + 15);

		else if (ptr->nxtMov == 'W')
			lineh(y + (ptr->y * 20) - 5, x + (ptr->x * 20), y + (ptr->y * 20) - 15);

		/*else if(ptr->nxtMov=='N')
		linev(y+(ptr->y * 20),x+(ptr->x * 20)+5,x+(ptr->x * 20)+15);

		else if(ptr->nxtMov=='S')
		linev(y+(ptr->y * 20),x+(ptr->x * 20)-5,x+(ptr->x * 20)-15);*/
		else if (ptr->nxtMov == 'x')
			line(y + (ptr->y * 20) - 20, x + (ptr->x * 20) - 20, y + (ptr->y * 20), x + (ptr->x * 20));
		else if (ptr->nxtMov == 'y')
			line(y + (ptr->y * 20) + 20, x + (ptr->x * 20) + 20, y + (ptr->y * 20), x + (ptr->x * 20));
		else if (ptr->nxtMov == 'z')
			line(y + (ptr->y * 20) + 20, x + (ptr->x * 20) - 20, y + (ptr->y * 20), x + (ptr->x * 20));
		else if (ptr->nxtMov == 'a')
			line(y + (ptr->y * 20) - 20, x + (ptr->x * 20) + 20, y + (ptr->y * 20), x + (ptr->x * 20));
		color(0, 0.5, 1);

	}


	color(0.8, 1, 0);
	for (ptrE = tmpFirstE[l]; ptrE != NULL; ptrE = ptrE->next)
	{
		line(y + (ptrE->y1 * 20), x + (ptrE->x1 * 20), y + (ptrE->y2 * 20), x + (ptrE->x2 * 20));
	}
	//	printText(50,650,10,res);
	sprintf(res, "The Energy Variation is %ld", Efinal[l]);
	color(0, 0, 0);
	printText(100, 650, 18, res);
	glutPostRedisplay();
	//glutPostRedisplay();
	glutSwapBuffers();
	glFlush();

}
int main(int argc, char **argv)
{

	glutInit(&argc, argv);//initialize openGl glut library
	//	printf("Enter the binary sequence\n");
	//	scanf("%s",str);


	fptr = fopen("result.txt", "a");
	if (fptr == NULL)
		printf("Error in opening file");
	fptrI = fopen("input.txt", "r");
	if (fptrI == NULL)
		printf("Error in opening file");
	fgets(str, 1024, fptrI);
	//printf("Sequence length %d\n", strlen(str));
	strlen(str);
	switch(strlen(str))
	{
	case 25: 
		printf("Seq ID:\t 1\nSequence: HHPPHPPHPPHPPHPPHPPHPPHH");
		printf("\nSequence length %d\n",strlen(str));
		break;
	case 50:
		printf("Seq ID:\t 2\nSequence: HHPHPHPHPHHHHPHPPPHPPPHPPPHPPPHPPPHPHHHHPHPHPHPHH");
		printf("\nSequence length %d\n",strlen(str));
		break;
	case 64:
		printf("Seq ID:\t 3\nSequence: HHHHHHHHHHHHPHPHPPHHPPHHPPHPPHHPPHHHPPHHPPHHPPHPHPHHHHHHHHHHHH");
		printf("\nSequence length %d\n",strlen(str));
		break;
	case 85:
		printf("Seq ID:\t 4\nSequence: HHHHPPPPHHHHHHHHHHHHPPPPPPHHHHHHHHHHHHPPPHHHHHHHHHHHHPPPHHHHHHHHHHHHPPPHPPHHPPHHPHPH");
		printf("\nSequence length %d\n",strlen(str));
		break;
	case 100:
		printf("Seq ID:\t 5\nSequence: PPPPPPHPHHPPPPPHHHPPPPPHPHHPPPPHHPPHHPPPPPHPHHHHHHHHHHPHHPHHHHHHHPPPPPPPPPPHHHHHHHPPHPHHHPPPPPPHPHH");
		printf("\nSequence length %d\n",strlen(str));
		break;
	default:
		printf("Sequence first time in the file");
		break;

	}
	//printf("\nThe free energy E* is  %d \t ",Energy[k].energy);
	procedure(1);
	procedure(0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//2 buffers are used as it is animation and RGB color model is used
	glutInitWindowSize(800, 700);//to set window size( width,height)
	glutInitWindowPosition(300, 100);//to set window position
	glutCreateWindow("Graph");//creates window
	glutDisplayFunc(Graph_page);//Register the call back function "myDisplay" Function
	//glutDisplayFunc(conversation);
	glutReshapeFunc(Reshape);
	myInit();
	glutMainLoop();
	fclose(fptr);
	return 0;
}
