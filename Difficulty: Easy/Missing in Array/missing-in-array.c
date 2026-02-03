int missingNum(int arr[], int n) {
    long long sum = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    long long expected = (long long)(n + 1) * (n + 2) / 2;

    return (int)(expected - sum);
}