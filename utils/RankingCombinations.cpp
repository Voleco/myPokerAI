#include"RankingCombinations.h"

uint64_t RankingCombination::NChooseK(int N, int k) const
{
    if (k>N)
        return 0;
    if (k==0)
        return 1;
    if (k>N/2)
        return NChooseK(N, N-k);

    uint64_t res = 1;

    for (int i = 1; i <= k; i++)
    {
        res *= N - i + 1;
        res /= i;
    }

    return res;
}

uint64_t RankingCombination::Rank(int *items, int k, int N) const
{
    /*co-lex ranking
    rank(S) = sum_{i=0}^{k-1} (S[i] choose [i+1])
    */
   uint64_t rank =0;
   for (int i=0;i<k;i++)
   {
       //std::cout<<"items[i]: "<<items[i]<<" i+1: "<<i+1<<"\n";
       rank += NChooseK(items[i],i+1);
   }
   return rank;

}




void RankingCombination::Unrank(uint64_t hash, int *items, int k, int N) const
{
    /*co-lex unranking
    (k,m)   m is the index
    S <- [k]
    i <- k-1
    while i>= 0:
        l <- i
        while (l choose i+1) <= m:
            l <- l+1
        S[i] <- l-1
        m <- m - (l-1 choose i+1)
        i <- i-1
    return S
    */

   uint64_t m = hash;
   int i,l;
   i = k-1;
   while (i>=0)
   {
       l = i;
       while (NChooseK(l,i+1) <= m)
            l++;
       items[i] = l-1;
       m = m - NChooseK(l-1,i+1);
       i = i-1; 
   }
}