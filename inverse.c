    #include<stdio.h>

    #include<math.h>

    #include<string.h>


    double determinant(double [][25], double);

    void cofactor(double [][25], int, double [25]);

    void transpose(double [][25], double [][25], double, double [25]);




    void matrix_x_vector(int n, double y[25], double x[25][25]){



          int i, j; // i = row; j = column;
          printf("\nSolution Matrix:\n");
          double A[25][25];
          for(int i=0;i<25;i++)
           memset(A[i], 0, 25);


          // Load up A[n][n]
          for (i=0; i<n; i++)
          {
            for (j=0; j<n; j++)
            {
              A[j][0] += x[j][i] * y[i];
              //printf("%4i", A[j][0]);
            }

          }
          printf("\n");

          for (i=0; i<n; i++)
            printf("%lf\n", A[i][0]);

    }








    void InverseMatrix()
    {
        FILE *inFile;
        char name[100];

        inFile = fopen("input.txt","r");
        //inFile.open("input.txt");
        //freopen("input2.txt","r", stdin);
    freopen("output2.txt","w", stdout);


        double element[25][25],d;


        double b[25];
        int j=0,k=0;
        int num=0;


        printf("Given Equations:\n");

        while(fgets(name, sizeof(name), inFile))
        {
            //char *str = n;
            //char *ptr = str;
            printf("%s",name);
            char ptr[100];
            strcpy (ptr, name);
            //printf("%s",ptr);

            //cout << "GG : "<< ptr << endl;
            //char *ptr = name.c_str();
            char x;
            char ch,ch2,ch3,ch4;
            char buff[32];
            double  valArray[32];
            double  val;
            int len = 0;
            int f=0,main_i;
            num = 0;

            memset(buff, 0, 32);
            for (main_i=0; ptr[main_i]!='\0'; main_i++)
            {
                ch=ptr[main_i];

                ch2=ptr[main_i+1];
                ch3 = ptr[main_i-1];
                ch4 = ptr[main_i+2];
                //printf("i= %d  ch : %c ######### ch2 : %c\n",main_i,ch,ch2);

                if(!((ch4>='A'&&ch4<='Z')||(ch4>='a'&&ch4<='z' ))&&f>0 && ((ch=='-'  && ch2==' ' && ch3 == ' ')||(ch=='+'  && ch2==' ' && ch3 == ' ')))
                {
                    //printf("smart check if ch= %c ch2= %c\n",ch,ch2);
                    buff[len++] =ch;
                    main_i++;

                }



                else if(f>0 && isdigit(ch)  && ((ch3>='A'&&ch3<='Z')||(ch3>='a'&&ch3<='z' )))
                {
                    //printf("1st if ch= %c ch2= %c\n",ch,ch2);
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
                    //printf("3rd if ch= %c ch2= %c\n",ch,ch2);
                }

                else
                {
                    //cout << " "<< ch  << " " << ch2 << endl;


                    if(f==0 && ((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')))
                    {
                        valArray[num++] = 1;
                        //printf("else er modddhe 1st if ch= %c ch2= %c\n",ch,ch2);
                    }

                    if(ch=='+')
                    {

                        if(!isdigit(ch2))
                        {
                            valArray[num++] = 1;
                            //printf("else er modddhe 2nd if ch= %c ch2= %c\n",ch,ch2);

                        }
                    }


                    if(ch=='-')
                    {
                        if(!isdigit(ch2))
                        {
                            valArray[num++] = -1;
                        //printf("else er modddhe 3rd if ch= %c ch2= %c\n",ch,ch2);
                        }
                    }

                    if (len != 0)
                    {
                        //cout << "buff :" << buff <<endl;
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

                //printf("%d %d %d %lf\n",j,i,valArray[i],element[j][i]);
            }

            j++;

            //inFile.close();
        }

        num--;

        printf("\n\nGenerated Matrix:\n");
        for(int i=0; i<num-1; i++)
        {

            for(j=0; j<num-1; j++)
            {
                printf("%f ",element[i][j]);
            }
            puts(" ");
        }


        puts("");
        puts("Resultant Vector:");
        for(j=0; j<num-1; j++)
            {
                printf("%f ",b[j]);
            }


        d = determinant(element, num-1);

          if (d == 0)

           printf("\nInverse of Entered Matrix is not possible\n");

          else

            cofactor(element, num-1, b);



    }









    int main()

    {


      InverseMatrix();



    }



    /*For calculating Determinant of the Matrix */

    double determinant(double a[25][25], double k)

    {

      double s = 1, det = 0, b[25][25];

      int i, j, m, n, c;

      if (k == 1)

        {

         return (a[0][0]);

        }

      else

        {

         det = 0;

         for (c = 0; c < k; c++)

           {

            m = 0;

            n = 0;

            for (i = 0;i < k; i++)

              {

                for (j = 0 ;j < k; j++)

                  {

                    b[i][j] = 0;

                    if (i != 0 && j != c)

                     {

                       b[m][n] = a[i][j];

                       if (n < (k - 2))

                        n++;

                       else

                        {

                         n = 0;

                         m++;

                         }

                       }

                   }

                 }

              det = det + s * (a[0][c] * determinant(b, k - 1));

              s = -1 * s;

              }

        }



        return (det);

    }



    void cofactor(double num[25][25], int f,double vec[25])

    {

     double b[25][25], fac[25][25];

     int p, q, m, n, i, j;

     for (q = 0;q < f; q++)

     {

       for (p = 0;p < f; p++)

        {

         m = 0;

         n = 0;

         for (i = 0;i < f; i++)

         {

           for (j = 0;j < f; j++)

            {

              if (i != q && j != p)

              {

                b[m][n] = num[i][j];

                if (n < (f - 2))

                 n++;

                else

                 {

                   n = 0;

                   m++;

                   }

                }

            }

          }

          fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);

        }

      }

      transpose(num, fac, f, vec);

    }

    /*Finding transpose of matrix*/

    void transpose(double num[25][25], double fac[25][25], double r, double vec[25])

    {

      int i, j;

      double b[25][25], inverse[25][25], d;



      for (i = 0;i < r; i++)

        {

         for (j = 0;j < r; j++)

           {

             b[i][j] = fac[j][i];

            }

        }

      d = determinant(num, r);

      for (i = 0;i < r; i++)

        {

         for (j = 0;j < r; j++)

           {

            inverse[i][j] = b[i][j] / d;

            }

        }

       printf("\n\n\nThe inverse of matrix is : \n");



       for (i = 0;i < r; i++)

        {

         for (j = 0;j < r; j++)

            {

             printf("\t%lf", inverse[i][j]);

            }

        printf("\n");

        }



         matrix_x_vector(r,vec,inverse);

    }




