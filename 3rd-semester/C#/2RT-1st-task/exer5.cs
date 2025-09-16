using System.Runtime.InteropServices.JavaScript;

namespace _2RT_1st_task;

public class Exer5
{ 

    private static int milkAmount = 0;
    private static int waterAmount = 0;
    private static (string , int)[] countOperations = [("Americano", 0), ("Latte", 0)];
    private static (string , int)[] prices = [("Americano", 150), ("Latte", 170)];

    static void GetMilkValue()
    {
        Console.Write("\nGive milk value: ");
        milkAmount = int.Parse(Console.ReadLine());
    }

    static void GetWaterValue()
    {
        Console.Write("\nGive water value: ");
        waterAmount =  int.Parse(Console.ReadLine());
    }

    static void Report()
    {
        int total = (
            from c in countOperations
            join p in prices on c.Item1 equals p.Item1
            select c.Item2 * p.Item2
        ).Sum();
        Console.Clear();
        Console.WriteLine($"\n*Report*\nIngredients left:\n  Water: {waterAmount} ml\n  Milk: {milkAmount} ml\n  Americano cups prepared: {countOperations[Array.FindIndex(countOperations, t => t.Item1 == "Americano")].Item2}\n  Latte cups prepared: {countOperations[Array.FindIndex(countOperations, t => t.Item1 == "Latte")].Item2}\nTotal: {total} rubles.");
        return;        
    }

    static bool Isotheraccesible()
    {
        if (milkAmount >= 270 && waterAmount >= 30) { return true; }
        if (waterAmount >= 300) { return true; }
        return false;
    }

    static bool IdleMode(bool flag) 
    {
        Console.Clear();
        Console.Write("\n Hi! What would you like to order? \n Americano - 150 rub. \n Latte - 170 rub. \nOrder: ");
        string order = Console.ReadLine();
        switch (order)
        {
            case "Americano":
            case "americano": 
            case "a":
            {
                if (waterAmount >= 300)
                {
                    waterAmount -= 300;
                    countOperations[Array.FindIndex(countOperations, t => t.Item1 == "Americano")].Item2++;
                    Console.Clear();
                    Console.WriteLine("Americano have been served. Here you go!");
                    return true;
                }
                else if (Isotheraccesible())
                {
                    Console.Clear();
                    Console.WriteLine("Sorry, Americano is not available. Try other products.");
                    return true;
                } else
                {
                    Console.Clear();
                    Console.WriteLine("Sorry, Drinks are not available.");
                    Report(); return false;
                }
                break;
            }
            case "Latte":
            case "latte":    
            case "l":
            {
                if (waterAmount >= 30 && milkAmount >= 270)
                {
                    waterAmount -= 30;
                    milkAmount -= 270;
                    countOperations[Array.FindIndex(countOperations, t => t.Item1 == "Latte")].Item2++;
                    Console.Clear();
                    Console.WriteLine("Latte have been served. Here you go!");
                    return true;
                } else if (Isotheraccesible())
                { 
                    Console.Clear();
                    Console.WriteLine("Sorry, Latte is not available. Try other products.");
                    return true;
                } else
                {
                    Console.Clear();
                    Console.WriteLine("Sorry, not enough water.");
                    Report(); return false;
                }
                break;
            }
            case "Report":
            case "report":
            case "r":
            {
                Report();
                return true;
            }
                
                
            default:
                Console.Clear();
                Console.WriteLine("No such operation. please try again.");
                return true;
        }
        return false;
    }
    

    public static void CoffeeMachine()
    {
        GetMilkValue();
        GetWaterValue();
        bool operationflag = true;

        do
        {
            Console.WriteLine("press any button... "); Console.ReadLine();
            operationflag = IdleMode(operationflag);
            
        } while (operationflag);
        
        

        return;
    }
}