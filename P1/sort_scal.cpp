template <typename T>
void scal(T A[], int len, int left, int mid, int right) {

    int i = left;
    int j = mid + 1;
    int k = left;
    T B[len]; //pomocnicza

    while (i <= mid && j<= right) //przejdź przez wszystkie elementy
    {
        if (A[i] < A[j]) //porównywanie
        {
            B[k] = A[i];
            i++;
        }
        else
        {
            B[k] = A[j];
            j++;
        }
        k++;
    }

    while (i <= mid) //dopełnienie elementami z pierwszej połówki
    {
        B[k] = A[i];
        i++;
        k++;
    }

    while (j <= right) //dopełnienie elementami z drugiej połówki
    {
        B[k] = A[j];
        j++;
        k++;
    }

    for(i = left; i <= right; i++) //przepisanie elementów z B do A
    {
        A[i] = B[i]; 
    }
    
}

template <typename T>
void sort_scal(T A[], int len, int left, int right) {
    if (left < right)
    {
        int mid = floor((left+right)/2);    //liczenie środka
        sort_scal<T>(A, len, left, mid);       //sortujemy lewą część
        sort_scal<T>(A, len, mid+1, right);    //sortujemy prawą część
        scal<T>(A, len, left, mid, right);     //scalamy obie części
    }
    
}

