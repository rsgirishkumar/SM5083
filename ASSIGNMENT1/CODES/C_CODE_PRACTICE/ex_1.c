#include<stdio.h>
#include<math.h>
#include<stdbool.h>
bool collinearity_value;
double area_triangle;
float a[2]={1,1};
float b[2]={3,5};
float c[2]={-2,4};
float d[2]={-1,-5};
double det(float a[2],float b[2], float c[2])
{
    area_triangle = ((b[0]*c[1])-(b[1]*c[0]))-((a[0]*c[1])-(a[1]*c[0]))+((a[0]*b[1])-(a[1]*b[0]));
    printf("\n %.2f",area_triangle);
    return area_triangle;
}
bool collinearity_check(float a[2],float b[2],float c[2])
{
    area_triangle = 0.5 * det(a,b,c);
    if (area_triangle == 0)
    {
        collinearity_value = true;
    }
    else
    {
        collinearity_value = false;
    }
    return collinearity_value;
}
void main(void)
{
    
    double area_1;
    double area_2;
    double area_quad;
    bool collinear_value1=false;
    bool collinear_value2=false;
    //Input the coordinates
    for(int i=0;i<2;i++)
    {
        printf("\n Enter vertex A[%d]:",i);
        scanf("%f",&a[i]);
    }
    for(int i=0;i<2;i++)
    {
        printf("\n Enter vertex B[%d]:",i);
        scanf("%f",&b[i]);
    }
    for(int i=0;i<2;i++)
    {
        printf("\n Enter vertex C[%d]:",i);
        scanf("%f",&c[i]);
    }
    for(int i=0;i<2;i++)
    {
        printf("\n Enter vertex D[%d]:",i);
        scanf("%f",&d[i]);
    }
    //Collinearity Check
    collinear_value1 = collinearity_check(a,b,c);
    collinear_value2 = collinearity_check(a,b,d);
    //determinant calculation
    if(collinear_value1 || collinear_value2 == true)
    {
        printf("\n Given coordinates are Collinear. Hence they do not form a Qualdrilateral.");
    }
    else
    {
        area_1 = 0.5 * det(a,b,c);
        printf("\n %.2f", area_1);
        area_2 = 0.5 * det(a,c,d);
        printf("\n %.2f", area_2);
        area_quad = area_1 + area_2;
        printf("\n Area of Quadrilateral formed by points A(%.2f,%.2f), B(%.2f,%.2f), C(%.2f,%.2f), D(%.2f,%.2f) = %.2f",a[0],a[1],b[0],b[1],c[0],c[1],d[0],d[1],area_quad);
    }
return;
}