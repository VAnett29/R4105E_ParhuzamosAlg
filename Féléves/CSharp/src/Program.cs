using System;
using System.Threading;
using System.Diagnostics;
using System.IO;
using System.Collections.Generic;

namespace ParhuzamosCSharp 
{
    public class Program
    {
        public static void Main()
        {
            int number;
            // szám bekérése
            do
            {
                Console.WriteLine("Enter a number: ");
            } while (!int.TryParse(Console.ReadLine(), out number));

            // számjegyek összegének kiszámítása
            int sumOfDigits = Run.SumOfDigits(number);

            List<Run> runs = new List<Run>();

            int maxThreadCount = Environment.ProcessorCount;
            for (int i = 1; i <= maxThreadCount; i*=2)
            {
                Run r = new Run(maxNumber: 10000, threadCount: i, sumOfDigits: sumOfDigits);
                r.Start();
                runs.Add(r);
            }

            WriteCSV(maxThreadCount, runs);

            foreach (var run in runs)
            {
                run.PrintResults();
            }

            Console.ReadLine();
        }

        private static void WriteCSV(int maxThreadCount, List<Run> runs)
        {
            //eredmények kiírása
            using (StreamWriter sw = new StreamWriter($"cs_threads.csv"))
            {
                //fejléc elkészítése
                string line = "Thread";
                for (int i = 0; i < runs.Count; i++)
                {
                    line += ",Milliseconds,Numbers found";
                }
                sw.WriteLine(line);

                // mért adatok beírása
                for (int i = 0; i < maxThreadCount; i++)
                {
                    line = $"Thread {i}";
                    foreach (var run in runs)
                    {
                        ThreadParam result = run.GetResult(i);
                        // ha nincs ilyen, mert kevesebb száll volt a futás során,
                        // kihagyás következő futásra lépés
                        if (result == null)
                            continue;

                        line += $",{result.ElapsedMilliseconds},{result.NumbersFound}";
                    }
                    sw.WriteLine(line);
                }

                line = $"Total";
                foreach (var run in runs)
                {
                    line += $",{run.totalMillisecs},{run.result}";
                }
                sw.WriteLine(line);

                sw.Close();
            }
        }
    }
}