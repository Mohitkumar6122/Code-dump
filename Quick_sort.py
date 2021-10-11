def partition(a , low : int, high : int) -> int :
    piv = a[high]
    ind = low - 1
    for i in range( low, high) :
        if a[i] <= piv :
            ind += 1
            a[i], a[ind] = a[ind], a[i] 
    a[ind + 1], a[high] = a[high], a[ind + 1]
    return ind + 1

def quicksort(a , low : int, high : int) -> None:
    if  low < high :
        ind = partition(a, low, high)
        quicksort(a, low, ind - 1)
        quicksort(a, ind + 1, high)

a = [8, 1, 6, 2, 0, 9, 7]
n = len(a) - 1
quicksort(a, 0, n)
print(f"\n {a} " )
