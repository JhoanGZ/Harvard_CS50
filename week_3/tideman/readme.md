## Tideman Method - Ranked Pairs

The Tideman voting method (also known as “ranked pairs”) is a ranked-choice voting method that’s guaranteed to produce the Condorcet winner of the election if one exists.

Ranked pairs (or RP) or Tideman Method, is a tournament-style system of ranked-choice voting first proposed by Nicolaus Tideman in 1987.

Ranked pairs begins with a round-robin tournament, where the one-on-one margins of victory for each candidate are compared to find a majority winner. If there is a Condorcet cycle (a rock-paper-scissors sequence A > B > C > A), the cycle is broken by dropping nearly-tied elections, i.e. the closest elections in the cycle.

Tne winner should satisfy the Condorcet criterion.
Voting systems where a majority-rule winner always wins the elections are said to satisfy the majority-rule principle.
Condorcet voting methods extend majority rule to elections with more than one candidate.

To handle this, the Tideman algorithm must be careful to avoid creating cycles in the candidate graph. How does it do this? The algorithm locks in the strongest edges first, since those are arguably the most significant.

In particular, the Tideman algorithm specifies that matchup edges should be “locked in” to the graph one at a time, based on the “strength” of the victory (the more people who prefer a candidate over their opponent, the stronger the victory).

So long as the edge can be locked into the graph without creating a cycle, the edge is added; otherwise, the edge is ignored.
