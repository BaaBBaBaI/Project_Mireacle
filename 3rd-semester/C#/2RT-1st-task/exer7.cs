namespace _2RT_1st_task;

public class Exer7
{
    public static double Mars(double a, double b, double w, double h, double n)
    {    
        bool Can(long d)
        {
            double aw = a + 2.0 * d; double bh = b + 2.0 * d; if (aw <= 0 || bh <= 0) return false;

            long c1 = (long)(w / aw) * (long)(h / bh); 
            
            double aw2 = b + 2.0 * d; double bh2 = a + 2.0 * d; long c2 = (long)(w / aw2) * (long)(h / bh2); 

            return Math.Max(c1, c2) >= (long)n;
        }

        if (!Can(0)) return 0.0;
        long lo = 0, hi = 1;
        while (Can(hi))
        {
            if (hi > (long)1e18) break;
            hi <<= 1;
        }
        while (lo < hi)
        {
            long mid = lo + (hi - lo + 1) / 2;
            if (Can(mid)) lo = mid;
            else hi = mid - 1;
        }
        return (double)lo;
    }
}