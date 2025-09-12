namespace _2nd_task;

public class Exer1
{
    public static byte CheckDay(int last, int weekday)
    {
        if (last > 31) { Console.WriteLine("May has only 31 days."); return 2; }
        for (int day = 1; day < last; day++)
        {
            if (weekday < 7) {weekday++;} else {weekday = 1;}
        }
        switch (last)
        {
            case 1 or 2 or 3 or 4 or 5 or 8 or 9 or 10:
            {
                return 1;
                break;
            }
            default:
            {
                if (weekday == 6 || weekday == 7)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
}