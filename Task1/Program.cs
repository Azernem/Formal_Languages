class Program {
    public static bool CheckCorrectBrackets(string sentence)
    {
        var openedBrackets = new[] {'(', '[', '{'};
        var closedBrackets = new[] {')', ']', '}'};
        var acc = new List<char>();

        for (var i = 0; i < sentence.Length; i++)
        {
            if (Array.IndexOf(openedBrackets, sentence[i]) != -1)
            {
                acc.Add(sentence[i]);
            }

            else
                if (acc.Count == 0)
                {
                    return false;
                }
                else if (Array.IndexOf(closedBrackets, sentence[i]) == Array.IndexOf(openedBrackets, acc[acc.Count - 1]))
                    acc.RemoveAt(acc.Count - 1);
                else
                    return false;
        }
        
        return acc.Count == 0;
    }

    static void Main(string[] args)
    {

        if (CheckCorrectBrackets(Console.ReadLine()))
        {
            Console.WriteLine("Sentence is correct for building of brackets");
        }
        else
        {
            Console.WriteLine("It isnt correct form of sentence");
        }
    }
}

