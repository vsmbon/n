#include <stdio.h>
//
#include <stdlib.h>

#define TARGETS_MAX 15

// End Of Targets.
#define EOT -1

struct point{
    int x,y;
};
struct rect{
    struct point pt1,pt2;
};
struct circle{
    struct point o;
    int r;
};


struct point targets_xy[TARGETS_MAX];


int dist2_tbl[TARGETS_MAX][TARGETS_MAX];

int targets_enums[TARGETS_MAX][TARGETS_MAX];

int read_targets_file(const char *file_name)
{
    int i,x,y;
    FILE *fp = fopen(file_name,"r");
    if(fp==NULL) return(-1);
    for(i = 0; (i<TARGETS_MAX) && (fscanf(fp,"%d,%d\n",&x,&y)!=EOF); i++)
    {
        targets_xy[i].x=x;
        targets_xy[i].y=y;
        printf("Hello World! %d,%d\n",targets_xy[i].x,targets_xy[i].y);
    }
    return(i);
}

int write_field_file(int *field,int x_max,int y_max,const char *file_name)
{
    int x,y;
    FILE *fp = fopen(file_name,"w");
    if(fp==NULL) return(-1);

    for(y=y_max-1;y>=0;y--) // usefull for eye
    {
        for(x=0;x<x_max;x++)
            fprintf(fp,"%d",*(field+x*y_max+y));

        fprintf(fp,"\n");
    }

//    for(x=0;x<x_max;x++)  // usefull for find coordinates
//    {
//        for(y=0;y<y_max;y++)
//            fprintf(fp,"%d",*(field+x*y_max+y));

//        fprintf(fp,"\n");
//    }

    fclose(fp);

    return(0);
}

/*
 * The square of the distance between points pt1 and pt2
 */
int dist2(struct point pt1,struct point pt2)
{
    return((pt2.x-pt1.x)*(pt2.x-pt1.x)+(pt2.y-pt1.y)*(pt2.y-pt1.y));
}

/*
//void dist2_tenums_tables_fill(int radius)
//{
//    int n=targets_total_count;
//    int k; // index of targets
//    int k_max=0; // maximum count of targets for shot with the radius
//    int i_opt=0; // index for optimal enum of targets
//    int i,j;
//   // radius=30;/////////////////////////////////////
//    int d2 = 4*radius*radius; // the square of the diametr


//    for(i=0;i<n;i++)
//    {
//       // r2_max=0;
//        for(j=0,k=0;j<n;j++)
//        {
//            if(i<j)
//                dist2_tbl[i][j] = dist2(targets_xy[i],targets_xy[j]);// powf(x[j]-x[i],2)+powf(y[j]-y[i],2);
//            else if(i>j)
//                dist2_tbl[i][j] = dist2_tbl[j][i]; //////// можно сделать не глобальную dist2_tbl[i][j] а с передачей по ссылке и инициализацией в main();
//                //r2[i][j] = r2[j][i];
//            else
//                dist2_tbl[i][j] = 0;

//            if(dist2_tbl[i][j]<d2)

//                //if(r2[i][j]>r2_max)r2_max=r2[i][j];
//                targets_enums[i][k++]=j;

//            printf("%5d",dist2_tbl[i][j]);
//        }
//        targets_enums[i][k]=EOT;
//        if(k>k_max){k_max=k; i_opt=i;}//if k==k_max?
//        printf(" :k=%d;k_max=%d\n",k,k_max);
//    }



//    //dist2_tbl[i][j]=dist2(pt1,pt2)
//}
*/

void init_field(int *field,int x_max,int y_max)
{
    int x,y;
    for(x=0;x<x_max;x++)
        for(y=0;y<y_max;y++)
            *(field+x*y_max+y)=0;
}

// dернет точку с мах значением11111111
struct point add_quadrate(int *field,int x_max,int y_max,struct rect quadrate)
{
    int x,y;
    struct point point_opt;
    if(quadrate.pt1.x<0)quadrate.pt1.x=0;
    if(quadrate.pt1.y<0)quadrate.pt1.y=0;
    if(quadrate.pt2.x>x_max-1)quadrate.pt2.x=x_max-1;
    if(quadrate.pt2.y>y_max-1)quadrate.pt2.y=y_max-1;

    printf("x_max=%d   ",x_max);
    printf("add_q[(%d,%d)-(%d,%d)]\n",quadrate.pt1.x,quadrate.pt1.y,quadrate.pt2.x,quadrate.pt2.y);
    for(x=quadrate.pt1.x;(x<=quadrate.pt2.x)&&(x<x_max);x++)
        for(y=quadrate.pt1.y;(y<=quadrate.pt2.y)&&(y<y_max);y++)
        {
       //     printf("(%d,%d); x*y_max+y=%d\n",x,y,x*y_max+y);
            *(field+x*y_max+y)=*(field+x*y_max+y)+1;
        }
    printf("x_max=%d\n",x_max);
    //return point_opt;
}

struct point add_circle(int *field,int x_max,int y_max,struct circle)
{
    int x,y;
    struct point point_opt;
    if(quadrate.pt1.x<0)quadrate.pt1.x=0;
    if(quadrate.pt1.y<0)quadrate.pt1.y=0;
    if(quadrate.pt2.x>x_max-1)quadrate.pt2.x=x_max-1;
    if(quadrate.pt2.y>y_max-1)quadrate.pt2.y=y_max-1;

    printf("x_max=%d   ",x_max);
    printf("add_q[(%d,%d)-(%d,%d)]\n",quadrate.pt1.x,quadrate.pt1.y,quadrate.pt2.x,quadrate.pt2.y);
    for(x=quadrate.pt1.x;(x<=quadrate.pt2.x)&&(x<x_max);x++)
        for(y=quadrate.pt1.y;(y<=quadrate.pt2.y)&&(y<y_max);y++)
        {
       //     printf("(%d,%d); x*y_max+y=%d\n",x,y,x*y_max+y);
            *(field+x*y_max+y)=*(field+x*y_max+y)+1;
        }
    printf("x_max=%d\n",x_max);
    //return point_opt;
}


int main(int argc, char *argv[])
{
    int x_max=100, y_max=100;
    int field[x_max][y_max];
    const char *targets_file_name;
    int radius;
    int targets_total_count=0;

    if(argc != 3){
        printf("Error: Too Few Parameters. Expected 2.\n"
               "Usage example: nuke.exe targets.dat  20\n");
        return(-1);
    }

    targets_file_name = argv[1];
    radius = atoi(argv[2]);

    targets_total_count = read_targets_file(targets_file_name);

    init_field((int*)field,x_max,y_max);
int i=0;
    struct rect quadrate;

    for(i=0;i<targets_total_count;i++)
    {


        quadrate.pt1.x = targets_xy[i].x-radius;
        quadrate.pt1.y = targets_xy[i].y-radius;
        quadrate.pt2.x = targets_xy[i].x+radius;
        quadrate.pt2.y = targets_xy[i].y+radius;

        add_quadrate((int*)field,x_max,y_max,quadrate);

        write_field_file((int*)field,x_max,y_max,"field.dat");
    }
    //write_field_file(field,x_max,y_max,"field.dat");

//    for(i=0;i<100;i++)
//        for(j=0;j<100;j++)
//        {
//            struct point o = {i,j};
//            if(r2>=dist2(o,//////////))
//        }
    if(targets_total_count<0){
        printf("Error: Can not read file.\n");
        return(-2);
    }


    printf("Hello World!\n");
    return 0;
}


