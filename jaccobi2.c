#include <math.h>
#include <stdio.h>
#include <stdlib.h>
float coefficient[10][10], Dinv[10][10], approximate[10][1], R[10][10], matrixRes[10][1], bb[10][1],temp[10][1];
int row,column,I;
void multiply(float matrixA[][10],float matrixB[][1],int v)
{
    int ctr,ictr;

    for(ctr=0; ctr<v; ctr++)
    {
        matrixRes[ctr][0]=0;
        for(I=0; I<v; I++)
            matrixRes[ctr][0]=matrixRes[ctr][0]+matrixA[ctr][I]*matrixB[I][0];
    }
}
int main()
{



    FILE *inFile, *outFile;
    char name[100];

    inFile = fopen("input.txt","r");
    outFile = fopen("output.txt","w");

    //inFile.open("input.txt");


    double element[25][25];


    double b[25];
    int j=0,k=0;
    int num=0;

    fprintf(outFile,"Given equations:\n");

    while(fgets(name, sizeof(name), inFile))
    {

        fprintf(outFile,"%s\n",name);
        char ptr[100];
        strcpy (ptr, name);

        char x;
        char ch,ch2,ch3,ch4;
        char buff[32];
        double  valArray[32],val;
        int   len = 0;
        int f=0,main_i;
        num = 0;

        memset(buff, 0, 32);
        for (main_i=0; ptr[main_i]!='\0'; main_i++)
        {
            ch=ptr[main_i];

            ch2=ptr[main_i+1];
            ch3 = ptr[main_i-1];
            ch4 = ptr[main_i+2];

            if(!((ch4>='A'&&ch4<='Z')||(ch4>='a'&&ch4<='z' ))&&f>0 && ((ch=='-'  && ch2==' ' && ch3 == ' ')||(ch=='+'  && ch2==' ' && ch3 == ' ')))
            {
                buff[len++] =ch;
                main_i++;

            }



            else if(f>0 && isdigit(ch)  && ((ch3>='A'&&ch3<='Z')||(ch3>='a'&&ch3<='z' )))
            {
                main_i++;

            }


            else if((ch>='A'&&ch<='Z'&& isdigit(ch2))||(ch>='a'&&ch<='z'&& isdigit(ch2))&& f!=0)
            {
                //printf("2nd if ch= %c ch2= %c\n",ch,ch2);
                main_i++;
            }


            else if ((isdigit(ch) && ch != '\0') ||(ch=='-' && isdigit(ch2))||(ch=='+' && isdigit(ch2)))
            {
                buff[len++] =ch;

            }

            else
            {


                if(f==0 && ((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')))
                {
                    valArray[num++] = 1;

                }

                if(ch=='+')
                {

                    if(!isdigit(ch2))
                    {
                        valArray[num++] = 1;
                    }
                }


                if(ch=='-')
                {
                    if(!isdigit(ch2))
                    {
                        valArray[num++] = -1;
                    }
                }

                if (len != 0)
                {
                    val = atoi(buff);
                    valArray[num++] = val;
                    memset(buff, 0, 32);
                    len = 0;
                }
            }

            f++;
        }
        val = atoi(buff);
        valArray[num++] = val;

        for(int i=0; i<num-1; i++)
        {

            if (i==num-2)
                b[j]=valArray[i];
            else
                element[j][i]= valArray[i];

        }

        j++;

        //inFile.close();
    }

    fprintf(outFile,"Generated Matrix:\n");
    for(int i=0; i<num-2; i++)
    {

        for(j=0; j<num-2; j++)
        {
            fprintf(outFile,"%lf   ",element[i][j]);
        }
        puts(" ");
    }
    fprintf(outFile,"\n\nConstant vector:\n");
    for(j=0; j<num-2; j++)
    {
        fprintf(outFile,"%f ",b[j]);
        bb[j][0]=b[j];

    }

    printf("Enter the first approximation\n");
    for(row=0; row<num-2; row++)
    scanf("%f",&approximate[row][0]);


//for(row=0;row<num-2;row++)
//printf("%f\n",approximate[row][0]);

for(row=0;row<num-2;row++)
bb[row][0]=b[row];

for(row=0;row<num-2;row++)//We calculate the diagonal inverse matrix make all other entries as zero except Diagonal entries whose resciprocal we store
    for(column=0;column<num-2;column++)
    {    if(row==column)
        Dinv[row][column]=1/element[row][column];
        else
        Dinv[row][column]=0;
    }
for(row=0;row<num-2;row++)
    for(column=0;column<num-2;column++)//calculating the R matrix L+U
    {    if(row==column)
        R[row][column]=0;
        else
        if(row!=column)
        R[row][column]=element[row][column];
    }
int iter=6;
fprintf(outFile,"\nThe number of iterations is 6:\n");


    fprintf(outFile,"\n\nSolution:\n");
//scanf("%d",&iter);//enter the number of iterations
int ctr=1;
int octr;
while(ctr<=iter)
{
multiply(R,approximate,num-2);//multiply L+U and the approximation
for(row=0;row<num-2;row++)
temp[row][0]=bb[row][0]-matrixRes[row][0];//the matrix(b-Rx)
multiply(Dinv,temp,num-2);//multiply D inverse and (b-Rx)
for(octr=0;octr<num-2;octr++)
approximate[octr][0]=matrixRes[octr][0];//store matrixRes value in the next approximation
fprintf(outFile,"\nThe Value after iteration %d is\n",ctr);
for(row=0;row<num-2;row++)
fprintf(outFile,"X%d = %.3f  ",row+1, approximate[row][0]);//display the value after the pass
ctr++;
}




    /*printf("Enter the number of unknown(below 10)\n");
    scanf("%d",&size);//enter the size
    printf("Enter the coefficent matrix\n");
    for(row=0; row<size; row++)
        for(column=0; column<size; column++)
            scanf("%f",&coefficient[row][column]);
    printf("Enter the first approximation\n");
    for(row=0; row<size; row++)
        scanf("%f",&approximate[row][0]);
    printf("Enter the RHS coefficient\n");
    for(row=0; row<size; row++)
        scanf("%f",&b[row][0]);
    for(row=0; row<size; row++) //To calculate the diagonal inverse matrix make all other entries as zero except Diagonal entries whose resciprocal to store
        for(column=0; column<size; column++)
        {
            if(row==column)
                Dinv[row][column]=1/coefficient[row][column];
            else
                Dinv[row][column]=0;
        }
    for(row=0; row<size; row++)
        for(column=0; column<size; column++) //calculating the R matrix L+U
        {
            if(row==column)
                R[row][column]=0;
            else if(row!=column)
                R[row][column]=coefficient[row][column];
        }
    int iter;
    printf("Enter the number of iterations:\n");
    scanf("%d",&iter);//enter the number of iterations
    int ctr=1;
    int octr;
    while(ctr<=iter)
    {
        multiply(R,approximate);//multiply L+U and the approximation
        for(row=0; row<size; row++)
            temp[row][0]=b[row][0]-matrixRes[row][0];//the matrix(b-Rx)
        multiply(Dinv,temp);//multiply D inverse and (b-Rx)
        for(octr=0; octr<size; octr++)
            approximate[octr][0]=matrixRes[octr][0];//store matrixRes value in the next approximation
        printf("The Value after iteration %d is\n",ctr);
        for(row=0; row<size; row++)
            printf("%.3f\n",approximate[row][0]);//display the value after the pass
        ctr++;
    }*/
}
