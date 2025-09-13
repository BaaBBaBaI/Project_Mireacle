namespace _2RT_1st_task;

public class Exer2
{
    public static bool LuckyBilet(string x)
    {
        if (x.Length != 6) { return false; }
        int sum1 = 0, sum2 = 0;
        for (int i = 0; i < 6; i++)
        {
            sum1 += (i < 3) ? Convert.ToInt32(x[i]) : 0;
            sum2 += (i < 3) ? 0 : Convert.ToInt32(x[i]);
        }
        return (sum1 == sum2) ? true : false;
    }
}