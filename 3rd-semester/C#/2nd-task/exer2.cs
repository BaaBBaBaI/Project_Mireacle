namespace _2nd_task;


public class Exer2
{
    public static Dictionary<int, int> BankNote(int cash)
    {
        Dictionary<int, int> returnvalue = new Dictionary<int, int>();
        if (cash % 100 != 0)
        {
            return null;
        }
        while (cash >= 5000)
        {
            if (!returnvalue.ContainsKey(5000))
                returnvalue[5000] = 0;
            returnvalue[5000]++;
            cash -= 5000;
        }
        while (cash >= 2000)
        {
            if (!returnvalue.ContainsKey(2000))
                returnvalue[2000] = 0;
            returnvalue[2000]++;
            cash -= 2000;
        }
        while (cash >= 1000)
        {
            if (!returnvalue.ContainsKey(1000))
                returnvalue[1000] = 0;
            returnvalue[1000]++;
            cash -= 1000;
        }
        while (cash >= 500)
        {
            if (!returnvalue.ContainsKey(500))
                returnvalue[500] = 0;
            returnvalue[500]++;
            cash -= 500;
        }
        while (cash >= 200)
        {
            if (!returnvalue.ContainsKey(200))
                returnvalue[200] = 0;
            returnvalue[200]++;
            cash -= 200;
        }
        while (cash >= 100)
        {
            if (!returnvalue.ContainsKey(100))
                returnvalue[100] = 0;
            returnvalue[100]++;
            cash -= 100;
        }
        return returnvalue;
    }

    
}