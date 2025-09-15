namespace _2RT_1st_task;

public class Exer2
{
    public static bool LuckyBilet(string x)
    {
        if (x.Length != 6) { return false; }
        int chislo = Convert.ToInt32(x);
        bool result = ( (chislo%10 + chislo%100/10 + chislo%1000/100) == 
                        (chislo%10000/1000 + chislo%100000/10000 +  chislo%1000000/100000) );
        return (result);
    }
}