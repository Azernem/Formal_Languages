using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Task3
{
    class Vertex
    {
        public string Name { get; set; }
        public List<Vertex> Neightboors { get; set; }

        public Vertex(string name)
        {
            Name = name;
            Neightboors = new List<Vertex>();
        }

        public override string ToString() => Name;
    }

    class Program
    {
        public static void Main()
        {
            // G: d,(a#b);c
            // c: abc
            var lines = File.ReadAllLines("Task3/1.txt");
            var vertices = new Dictionary<string, Vertex>();

            // вершины
            foreach (var line in lines)
            {
                if (!line.Contains(":")) continue;
                var left = line.Split(':')[0].Trim();
                if (!vertices.ContainsKey(left))
                    vertices[left] = new Vertex(left);
            }

            // связи
            foreach (var line in lines)
            {
                if (!line.Contains(":")) continue;

                var parts = line.Split(':');
                var left = parts[0].Trim();
                var right = parts[1].Trim();

                var from = vertices[left];


                string[] tokens = right
                    .Replace("(", "")
                    .Replace(")", "")
                    .Replace(";", "")
                    .Split(new[] { ',', '#', ' ' }, StringSplitOptions.RemoveEmptyEntries);

                foreach (var token in tokens)
                {
                    if (!vertices.ContainsKey(token))
                        vertices[token] = new Vertex(token);

                    from.Neightboors.Add(vertices[token]);
                }
            }

            // Обход графа в ширину 
            Console.WriteLine("Обход графа в ширину (BFS)");

            if (vertices.ContainsKey("G"))
            {
                var reachable = Bypass(vertices["G"]);
                foreach (var v in reachable)
                    Console.WriteLine(v.Name);
            }
            else
            {
                Console.WriteLine("Нет вершины G в грамматике.");
            }
        }

        public static List<Vertex> Bypass(Vertex start)
        {
            var queue = new Queue<Vertex>();
            var reachible = new List<Vertex>();

            queue.Enqueue(start);

            while (queue.Count > 0)
            {
                var current = queue.Dequeue();

                if (reachible.Contains(current))
                    continue;

                reachible.Add(current);

                foreach (var neighboor in current.Neightboors)
                {
                    if (!reachible.Contains(neighboor))
                    {
                        queue.Enqueue(neighboor);
                    }
                }
            }

            return reachible;
        }
    }
}
