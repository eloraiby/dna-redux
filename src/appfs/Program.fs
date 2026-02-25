namespace AppFS

open System
open System.Collections.Generic

module Program =

    let measureMs f x =
        let dtStart = DateTime.UtcNow
        let result = f x
        let elapsed = DateTime.UtcNow - dtStart
        result, int elapsed.TotalMilliseconds

    let sqr (x: double) = x * x

    let sum_to_n n =
        let mutable i = 1
        let mutable sum = 0
        while i <= n do
            sum <- sum + i
            i <- i + 1
        sum

    let fastFib n =
      let sqrt5 = sqrt 5.0
      let a = (1.0 + sqrt5) / 2.0
      let b = (1.0 - sqrt5) / 2.0
      let power = float n
      let result = ((a ** power) - (b ** power)) / sqrt5
      int (round result)

    let rec slowFib n =
        match n with
        | 0 -> 0
        | 1 -> 1
        | _ -> slowFib (n - 1) + slowFib (n - 2)

    let memoFib =
        let dict = new Dictionary<int, int>()
        fun n ->
            if dict.ContainsKey n then dict.[n]
            else
                let result = slowFib n
                dict.Add(n, result)
                result

    let seq_Fib n =
        let rec fib_seq = seq {
            yield! [0; 1]
            yield! fib_seq
                |> Seq.pairwise
                |> Seq.map (fun (prev, next) -> prev + next)
        }
        fib_seq |> Seq.item n

    let testFunctions () =
        let n = 31
        let sumResult, _ = measureMs sum_to_n n
        printfn "sum(1..%d) = %d" n sumResult

        let sqrResult, _ = measureMs (fun x -> int (sqr (double x))) n
        printfn "sqr(%d) = %d" n sqrResult

        let slowResult, _ = measureMs slowFib n
        printfn "slowFib(%d) = %d" n slowResult

        let memoResult, _ = measureMs memoFib n
        printfn "memoFib(%d) = %d" n memoResult

        let seqResult, _ = measureMs seq_Fib n
        printfn "seq_Fib(%d) = %d" n seqResult

    [<EntryPoint>]
    let main _ =
        Console.WriteLine("Hello World from F#!")
        printfn "The %s is: %d" "answer" 42

        testFunctions()
        0
