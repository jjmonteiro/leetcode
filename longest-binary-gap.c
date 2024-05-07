

#define bitCheck(val, bit) (val>>bit)&1

int getNumberOfBits(int N)
{
    int numBits = 1; // Minimum 1 bit for zero
    unsigned int num = (N < 0) ? -N : N; // Get absolute value for negative numbers

    while (num >>= 1) // Right shift to check each bit
        numBits++;

    return numBits;
}

int solution(int N) {
    int zeros=0, longest=0;
    for (int i = getNumberOfBits(N)-1; i>=0; i--)
    {
        if (bitCheck(N, i))
        {
            if (zeros > longest)
            {
                longest = zeros;
            }
            zeros = 0;
        }
        else 
        {
            zeros++;
        }
    }
    return longest;
}
