template <typename T>
void quicksort(T A[], int left, int right)
{
    int mid = floor((left+right)/2);    //liczenie środka (pivota)
    int i = left;
    int j = right;
    int k; //pomocnicza

    do
    {
        while(A[mid] > A[i]) i++;
        while(A[mid] < A[j]) j--;

        if(i <= j)
        {
            k = A[i];
            A[i] = A[j];
            A[j] = k;
            i++;
            j--;
        }
    }
    while(i <= j);

    if(j > left) quicksort(A,left, j);
    if(i < right) quicksort(A, i, right);
}