using System;
using System.Collections.Specialized;
using System.Formats.Asn1;
using System.Reflection.Metadata;
using System.Runtime.InteropServices;

class Program {

public static double memory = 0;
public static bool casem = false; public static bool casep = false;



static void mhandler(double work)
{
    if (casem) { if (casep) { memory += work; } else { memory -= work; } return; } else { return; }
}

static double CalcValue(string operation)
{
    switch (operation)
    {
        case "M+":
        {
            casem = true;
            casep = true;
            break;
        }
        case "M-":
        {
            casem = true;
            casep = false;
            break;
        }
        case "MR":
        {
            casem = false;
            casep = false;
            double mm = memory;
            memory = 0;
            return mm;
        }
    }
    return 0;
}
static double CalcValue(string operation, Tuple<double, double> pair)
    {
        double value;
        
        switch (operation)
        {
            case "+":
                {
                    value = pair.Item1 + pair.Item2; mhandler(value); return value;
            }
            case "-":
                {
                    value = pair.Item1 - pair.Item2; mhandler(value); return value;
            }
            case "*":
                {
                    value = pair.Item1 * pair.Item2; mhandler(value); return value;
            }
            case "/":
                {
                    if (pair.Item2 == 0)
                    {
                        Console.Write("Error. Division by zero is forbidden. Returning 0"); return 0;
                    }
                    value = pair.Item1 / pair.Item2; mhandler(value); return value;
            }
            case "%":
                {
                    value = pair.Item1 % pair.Item2; mhandler(value); return value;
            }
            case "1/x":
                {
                    if (pair.Item1 == 0)
                    {
                        Console.Write("Error. Division by zero is forbidden. Returning 0"); return 0;
                    }
                    value = 1 / pair.Item1; mhandler(value); return value;
            }
            case "^2":
                {
                    value = pair.Item1 * pair.Item1; mhandler(value); return value;
            }
            case "sqrt":
            {
                value = Math.Sqrt(pair.Item1);
                mhandler(value);
                return value;
            }
        }

        return 0;
    }
    static void Main()
    {
        Console.ForegroundColor = ConsoleColor.Magenta;
        Console.Write("Enter number, then an operation(+, -, /, *, ^2, 1/x, %, sqrt), then another number (if needed). \nUse M+, M-, MR to add up values(also, use spaces as dividers, thanks). \n");
        Console.ForegroundColor = ConsoleColor.Cyan;

        string? input; double output;
        
        do
        {
            input = Console.ReadLine();
            if (input != null)
            {
                string[] words = input.Split(' ');
                if (words.Length < 2)
                {
                    if (words[0] == "MR" ||  words[0] == "mr")
                    {
                        double m = CalcValue(words[0]); Console.Write($"M = {m}. \nM has been reset.\n");
                    } else if (words[0] == "M+" || words[0] == "m+" )
                    {
                        CalcValue(words[0]); Console.WriteLine("M+ activated");
                    } else if (words[0] == "M-")
                    {
                        CalcValue(words[0]); Console.WriteLine("M- activated");
                    } else if (words[0] == "Exit" || words[0] == "exit")
                    {
                        Console.WriteLine("Exiting...");
                    }
                    else
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.WriteLine("Invalid input");
                        Console.ForegroundColor = ConsoleColor.Cyan;
                    }
                
                }
                else if (words.Length == 2)
                {
                    Tuple<double, double> pair = new Tuple<double, double>(double.Parse(words[0]), double.Parse(words[0]));
                    output = CalcValue(words[1], pair);
                    Console.WriteLine(output);
                
                }
                else if (words.Length >= 3)
                {
                    Tuple<double, double> pair = new Tuple<double, double>(double.Parse(words[0]), double.Parse(words[2]));
                    output = CalcValue(words[1], pair);
                    Console.WriteLine(output);
                
                }
            }
        } while (input != "exit");

        Console.ResetColor();
    }
}