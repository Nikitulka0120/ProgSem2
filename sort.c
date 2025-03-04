void selectionSort(int n, struct Student A[])
{
    for (int i = 0; i < n - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < n; j++)
        {
            if (A[j].total > A[k].total)
            {
                k = j;
            }
        }
        if (i != k) //asd
        {
            struct Student temp = A[i];
            A[i] = A[k];
            A[k] = temp;
        }
    }
}