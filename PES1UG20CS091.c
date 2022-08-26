#include "header.h"
#include<limits.h>
// ANY STATIC FUNCTIONS ARE UP HERE
/*Function used to check if node is visited in graph
If not, it marks it as visited and proceeds to scan for next unvisited node,
reachable from that node*/
static void dfs(int n,int v, int visited[n],connection_t connections[n][n])
{
    visited[v]=1;
    for(int i=0;i<n;i++)
    {
        if(connections[v][i].distance<100 && visited[i]!=1)
        {
            dfs(n,i,visited,connections);
        }
    }
}
static void swap(airport_t *a, airport_t *b)
{
    airport_t t = *a;
    *a = *b;
    *b = t;
}
/*Partition function used to divide the array at the pivot and determine if elements needs to be swapped
or not*/
static int partition(airport_t array[], int start, int end,int (*predicate_func)(const airport_t *, const airport_t *))
{
    int pivot1 = start;
    airport_t pivot_air = array[end];
    int i;
    for(i = start; i < end; i++)
    {
        if(predicate_func(&array[i] , &pivot_air))
        {
            swap(&array[i], &array[pivot1]);
            pivot1++;
        }
    }
    swap(&array[end], &array[pivot1]);
    return pivot1;
}
/*Quicksort method used to sort array elemets*/
static void quickSort(airport_t array[], int start, int end,int (*predicate_func)(const airport_t *, const airport_t *) )
{
    if(start < end)
    {
        int qIndex = partition(array, start, end,predicate_func);
        quickSort(array, start, qIndex-1,predicate_func);
        quickSort(array, qIndex+1, end,predicate_func);
    }
}
/*Computing shift table for Horspool's algorithm by first initialising all table values 
to length of pattern.*/
static int* shifttable(const char* pat)
{
    int table[500];
    int i,j,m;
    i=0;
    while(pat[i]!='\0')
    {
        i++;
    }
    int len=i;
    for(i=0;i<500;i++)
    {
        table[i]=len;
    }
    for(j=0;j<len;j++)
    {
        table[pat[j]]=len-1-j;//Table values changed according to position of character in pattern
    }
    return table;
}

static int Horspool(char* text, char* pat,int* table)
{
    int text_l,pat_l;//lengths of text and pattern respectively
    int i=0;
    int k;
    while(text[i]!='\0')//Computing length of text
    {
        i++;
    }
    text_l=i;
    i=0;
    while(pat[i]!='\0')//Computing length of pattern
    {
        i++;
    }
    pat_l=i;
    i=pat_l-1;//Initialising iterator to last index position of pattern
    while(i<text_l)
    {
        k=0;
        while((k<pat_l)&&(pat[pat_l-1-k]==text[i-k]))//Comparing text and pattern backwards
        {
            k++;
        }
        if(k==pat_l)
        {
            return(i-pat_l+1);//Returns index
        }
        else
        {
            i+=table[text[i]];//Modifies based on shift table value
        }
    }
    return -1;
}
/*MST is found here*/
static int MST_func(int n, connection_t connections[n][n],pair_t edges[n-1])
{
    int min=INT_MAX;
    int min_sum=0;//variable holds the total time finally taken at the end
    int visit[n];//Creating an array here for all vertices that have been visited.
    for(int i=0;i<n;i++)
    {
        visit[i]=0;//Initially all vertices marked as visited
    }
    int k=0, temp=0;
    for(int i=0;i<n;i++)
    {
        min=INT_MAX;//Initialising min to largest possible number
        if(visit[i]==0)//Only perform the following if the given vertex has not been visited yet
        {
            for(int j=0;j<n;j++)
            {
                if(connections[i][j].time<min && connections[i][j].time!=0)
                {
                    min=connections[i][j].time; //Updating minimum value
                    visit[j]=1;//Marking vertex as visited
                    temp=j;
                }
                
            }
            edges[k].first=i;//Storing indices in edges array
            edges[k].second=temp;
            k++;
            visit[i]=1;
            min_sum=min_sum+min;//computing final time taken
        }
    }
    return min_sum;
}
/*Returns minimum of given array*/
static int min_arr(int n,int a[n])
{
    int min=a[0];
    for(int i=0;i<n;i++)
    {
        if(a[i]<min)
            min=a[i];
    }
    return min;
}
// YOUR SOLUTIONS BELOW
int q1(int n, const connection_t connections[n][n])
{
    int vis_count=0;//Keeping count of number of airports visited cumulatively
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i!=j)
            {
                if(connections[i][j].distance<100)//checking to see if the distance is a valid number
                {
                    vis_count++;//incrementng the count each time a connection exists
                }
            }
        }
    }
    /*For all airports to be accessed, the total number of visits would be
    size of matrix-number of rows
    nxn - n*/
    if(vis_count==n*n-n)
    {
        return 1;
    }
    return 0;
}
//DFS Graph traversal employed here
int q2(const airport_t *src, const airport_t *dest, int n, int k,
       const connection_t connections[n][n])
{
    int visited[100];
    for(int i=0;i<100;i++)
    {
        visited[i]=0;
    }
    int s=src->num_id;
    int d=dest->num_id;
    dfs(n,s,visited,connections);
    if(visited[d]==1)
    {
        return 1;
    }
    return 0;
}
int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
    int i=src->num_id;
    for(int j=0;j<n;j++)
    {
        if((i!=j)&&(connections[i][j].distance<INT_MAX))
        {
            if(connections[j][i].distance<INT_MAX)
                return 1;
        }
    }
    return 0;
}
/*nlogn--quicksort*/
void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),
        airport_t airport_list[n])
{
    quickSort(airport_list,0,n-1,predicate_func);
}

pair_t q5(int n, airport_t airports[n])
{
    pair_t ret;
    int same[n][n];
    //Creating a matrix that holds the number of times a same character appears
    //Initially all values of this matrix are 0
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            same[i][j]=0;
        }
    }
    char *text, *patt;
    for(int i=0;i<n-1;i++)
    {
        text=airports[i].airport_name;
        int a,b;
        for(int j=i+1;j<n;j++)
        {
            a=0;
            b=0;
            patt=airports[j].airport_name;
            while(text[a]!='\0')
            {
                //Iteratively comparing text and pattern for same characters
                if(text[a]==patt[b])
                {
                    same[i][j]++;//updating table on finding same character
                    same[j][i]++;
                    b++;
                }
                else
                {
                    b=0;
                }
                a++;
            }
        }
    }
    int max=same[0][0];
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(same[i][j]>max)
            {
                max=same[i][j];//Finding the highest number of common occurances in the table 'same'
            }
        }
    }
    int x1,y1;
    //Mapping the index positions of the highest value previously computed to index values 
    //exiting once found
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(max==same[i][j]) 
            {
                x1=i;
                y1=j;
                i=n;
                j=n;
            }
        }
    }
    if(max!=0)
    {
        ret.first=x1;
        ret.second=y1;
        return ret;
    }
    pair_t ans = {-1, -1};
    return ans;
}
int q6(int n, int amount, const int entry_fee[n])
{
    int l=0;
    int r=n-1;
    //Finding out the middle position which maybe used either for
    //Moving forward in the entry_fee array
    //Moving backwards in the entry_fee array
    while(l<=r)
    {
        int range=r-l;
        int m=l+range/2;
        if(entry_fee[m]==amount)
            return m+1; //Because indexing begins at 0;
        else if(entry_fee[m]<amount)
        {
            l=m+1;
        }
        else
        {
            r=m-1;
        }
    }
    return 0;
}
void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{
    //Using Horspool's algorithm
    int* st;
    int pos;
    st=shifttable(pat);
    for(int i=0;i<n;i++)
    {
        pos=Horspool(airports[i].airport_name, pat, st);
        if(pos>=0)
        {
            contains[i]=1;
        }
        else
        {
            contains[i]=0;
        }
    }
}

int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    //Firstly, we compute which airport index i has the highest distance to cover
    //so that we may exempt that as we are to calculate for shortest distance
    int max=0;
    int x;
    connection_t ap;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if((connections[i][j].distance>max)&&(connections[i][j].distance<INT_MAX))
            {
                max=connections[i][j].distance;
                ap=connections[i][j];
                x=i; //storing index as x variable
            }
        }
    }
    int cost=0;
    int i=0,j=0;
    int first=-1;
    int t=0; //Number of airports traversed
    while(t<n-1)
    {
         if(t==0)
                first=i;
        if((i==x)&&(i<n-1))
        {
            i++;//Directly incrementing value of i as it is not to be checked if it is = to x
        }
        if(j==x)
        {
            j++;//Similar for j
        }
        if((connections[i][j].distance<INT_MAX)&&(connections[i][j].distance!=0))
        {
            trip_order[t]=i;//Adding index to trip_order list
            t++;//Incrementing list by 1
            cost=cost+connections[i][j].distance;//Computing cost
            i=j;//Changing value of i to j as j is now the new row to be traversed
            j=0;
        }
        else
        {
            j++;
        }
    }
    if(i!=first)//Checking if we were able to return to initial airport
    {
        for(int i=0;i<n;i++)
        {
           trip_order[i]=-1;
        }
    }
    if(i==first)
    {
        return cost;
    }
    
    return -1;
}
/*Computing patternfor finding MST and the time traversed by such a pattern*/
int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    int time=MST_func(n,connections,edges);
    return time;
}

void q10(int n, int k, const airport_t *src,
         const connection_t connections[n][n], const int destinations[k],
         int costs[k])
{
    int u=src->num_id;
    //Creating a matrix only to hold time values of each connection
    //for convinience
    int time_mat[n][n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(connections[i][j].time!=0)
                time_mat[i][j]=connections[i][j].time;
            else
                time_mat[i][j]=INT_MAX;
        }
    }
    //Calculating min of row corresponding to source in time matrix
    int min;
    min=min_arr(n,time_mat[u]);
    for(int i=0;i<k;i++)
    {
        /*Checking if minimum time of that row + time of destination from that mini vertex 
        is lower or higher than the actual time from source to destination*/
        if(min+time_mat[min][destinations[i]]<time_mat[u][destinations[i]])
        {
            costs[i]=min+time_mat[min][destinations[i]];
        }
        else
        {
            costs[i]=time_mat[u][destinations[i]];
        }
    }
}
// END