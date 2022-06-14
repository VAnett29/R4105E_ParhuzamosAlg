using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ParhuzamosCSharp
{
    public class Run
    {
        // szálak száma
        public int threadCount;
        // tartomány nagysága
        private int range;
        // végeredmény
        public int result = 0;
        // sync object zároláshoz
        private object syncobject = new object();
        // szállak tömbje
        private Thread[] threads;
        // paraméterek tömbje
        private ThreadParam[] parameters;
        // teljes futás millisecben
        public string totalMillisecs;
        public Run(int maxNumber, int threadCount, int sumOfDigits)
        {
            this.threadCount = threadCount;
            range = Convert.ToInt32(Math.Ceiling(Convert.ToDouble(maxNumber) / Convert.ToDouble(threadCount)));

            // szálak és paraméterek tömbjének lefoglalása
            threads = new Thread[threadCount];
            parameters = new ThreadParam[threadCount];

            //felparaméterezés
            for (int i = 0; i < threadCount; i++)
            {
                threads[i] = new Thread(CountSumOfDigits);
                threads[i].Name = $"Thread {i}";
                parameters[i] = new ThreadParam(i * range, Math.Min((i + 1) * range, maxNumber), sumOfDigits);
            }
        }

        public ThreadParam GetResult(int index)
        {
            if (index >= threadCount)
                return null;
            
            return parameters[index];
        }

        public void Start()
        {
            Console.WriteLine($"\nStarting run with {threadCount} threads");

            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            for (int i = 0; i < threadCount; i++)
            {
                threads[i].Start(parameters[i]);
            }
            for (int i = 0; i < threadCount; i++)
            {
                threads[i].Join();
            }
            stopwatch.Stop();
            totalMillisecs = $"{stopwatch.ElapsedTicks / 10000}.{stopwatch.ElapsedTicks % 10000}";

            Console.WriteLine($"\nFinished run with {threadCount} threads");
        }

        /// <summary>
        /// számjegyek összegének kiszámítása
        /// </summary>
        /// <param name="number">szám aminek ki kell számolni a számjegyeinek összegét</param>
        /// <returns>számjegyek összege</returns>
        public static int SumOfDigits(int number)
        {
            int sumOfDigits = 0;
            while (number != 0) //ha a szám elfogyott kilépés
            {
                sumOfDigits += number % 10; //legkisebb helyiérték hozzáadása
                number /= 10; //legkisebb helyiérték eltüntetése
            }
            return sumOfDigits;
        }

        /// <summary>
        /// Szálfüggvény, tartományban a megegyző számjegyek összegével rendelkez számok összeszámolása
        /// </summary>
        /// <param name="param">ThreadParam</param>
        private void CountSumOfDigits(object param)
        {
            //kasztolás az adatok eléréséhez
            ThreadParam data = param as ThreadParam;
            Console.WriteLine($"{Thread.CurrentThread.Name} starting from " +
                $"{data.From} to {data.To} finding {data.SumOfDigits}");

            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            // tartomány vizsgálata
            for (int i = data.From; i < data.To; i++)
            {
                if (SumOfDigits(i) == data.SumOfDigits)
                {
                    lock (syncobject)
                    {
                        result++;
                    }
                    data.NumbersFound++;
                    Console.WriteLine($"\t[{Thread.CurrentThread.Name}] found {i}.");
                }
            }
            stopwatch.Stop();
            data.ElapsedTimeInTicks = stopwatch.ElapsedTicks;

            Console.WriteLine($"[{Thread.CurrentThread.Name}] finished.");
        }

        public void PrintResults()
        {
            Console.WriteLine($"\nResults with {threadCount} threads:");
            for (int i = 0; i < threadCount; i++)
            {
                Console.WriteLine($"[Thread {i}]: \t " +
                    $"time: {parameters[i].ElapsedMilliseconds,10} millisecs, \t " +
                    $"numbers found: {parameters[i].NumbersFound,4}");
            }

            Console.WriteLine($"\nTotal numbers found with sum of digits {parameters[0].SumOfDigits}: {result}");
        }
    }
}
